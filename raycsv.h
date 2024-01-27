#ifndef CSV_H_
#define CSV_H_

#define RUN_AS_C_FILE_ // run as c file
#include "src/rayutils.h"

// you can change this cinfiguration.
#define maxTypes	6

// structures 
typedef struct{
	const char* name;
	size_t formatlength;
	char types[maxTypes];
}CSV;

//typedef struct{
//	char* username;
//	char* password;
//	int id;
//	const char* key;
//}DB; 
#ifndef array_size
#define array_size(a)	(size_t)(sizeof((a)) / sizeof((a)[0])) 
#endif
#ifndef endl
#define endl(file)	(fputs("\n" , (file)))
#endif
CSV* Init_CSV(
	const char* filename , // name of file
	bool isnew , // true if this file is new else false
	char* format, // format of csv file 
	Status* status // status out if function works successfully or not 
	);

Status add_data(
	CSV* csv , // statctures from init function 
	bool title, // if you want to add titles if not we put new line 
	char* data[] , // array of strings data to added to file  
	size_t data_size // array size
	);
Status del_data(
	CSV* csv , // statctures from init function 
	int line // line to delete
	);
Status find_data(
			CSV* csv , // struct data of csv file 
			char* element ,// word that u search for like name : mike
			bool *found , // ptr to var true if found else false
			int *position ,// positions of word that u search for.
			int* _founds // how many times found 
			);
void Close_CSV(CSV* csv);

#endif //CSV_H_

#ifdef CSV_C_
// format:
// 	s: string
// 	n: number
// 	b: boolean
// Example:
// 	init("test.csv" , "s,s,s", &status);
// out param value:
//	warning = -1,
//	success = 0,
//	error   = 1,
// 	
// initial function 
CSV* Init_CSV(const char* filename , bool isnew , char* format , Status* status ){
	// we will handle format here
	CSV* csv = (CSV*)malloc(sizeof(CSV));
	size_t count = 0;
	int idx = 0;
	while(count < strlen(format)){
		switch(format[count]){
			case 's':{
				csv->types[idx++] = 's';
				break;
			}
			case 'n':{
				csv->types[idx++] = 'n';
				break;
			}
			case 'b':{
				csv->types[idx++] = 'b';
				break;
			}
		}
		count++;
	}
	csv->formatlength = strlen(csv->types);
	char* fmt = (isnew ? "w" : "a");
	// creation csv file
	FILE *file = fopen(filename , fmt);
	if(!file)
		*status = error;
	
	// now structure is full of information file with all types
	csv->name = filename;	
	(*status) = success;
	fclose(file);
	// Don't forgot to free memory
	//free(csv);
	return csv;
}
// why this function didn't work?
Status add_data(CSV* csv , bool title, char* data[],size_t data_size)
{
	if(csv == NULL) // init function not called
		return error;
	// append titles of data to csv file
	FILE *file = fopen(csv->name , "a");
	if(!file)
		return error;
	if(!title)
		endl(file);
	// if you put data into a file and data lengh is bigger than lengh of titles it will jamp to new line
	// Example:
	// 	data : test 20 job idx
	//
	// 	csv file:
	// 		name,age,job
	//
	// 		test,20,job
	// 		idk
#ifdef ESCAPR_LEN_OF_FORMAT_DATA
	size_t c = 0;
	for(int i = 0 ; i<data_size; i++ ){
		if(c == csv->formatlength){
			endl(file);
			c = 0;
		}
		if((c <= csv->formatlength) && (c > 0))
			fprintf(file , ",");
		c++;
		fwrite(data[i],strlen(data[i]),sizeof(char),file);	
	}
#else
	if(data_size != csv->formatlength){
		return warning;
	}
	for(size_t i = 0 ; i<data_size; i++ ){
		if((i <= csv->formatlength) && (i > 0))
			fprintf(file , ",");
		fwrite(data[i],strlen(data[i]),sizeof(char),file);	
	}
#endif
	fclose(file);
	return success;
}
Status del_data(CSV* csv , int line)
{
	if(csv == NULL) // init function not called
		return error;
	int count = 0;
	char contentline[1024];
	// append titles of data to csv file
	FILE *tempfile = fopen("temp.csv" , "w");
	FILE *file = fopen(csv->name , "r");
	if((!file) || (!tempfile))
		return error;
	
	while((fgets(contentline , sizeof(contentline) , file)) != NULL){
		count++;
		if(count == line)
			continue;
		fprintf(tempfile , "%s" , contentline);
	}
	fclose(tempfile);
	fclose(file);
	if(rename("temp.csv" , csv->name) != 0)
		return error;
	return success;
}

Status find_data(CSV* csv ,char* element ,bool *found ,int *position , int* _founds)
{
	size_t size = 0;
	int line = 0;
	FILE *fp = fopen(csv->name , "r");
	if(!fp) return error;
	char linechar[256];
	while(fgets(linechar , sizeof(linechar) , fp) != NULL){
		line++;
		char* tok = strtok(linechar , ",");
		while(tok != NULL){
			if(strcmp(tok , element) == 0){
				*found = true;
				position[size++] = line;
			}
			tok = strtok(NULL , ",");
		}
	}
	*_founds = (int)size;
	fclose(fp);
	if(size == 0) return warning;
	return success;
}

void Close_CSV(CSV* csv){
	free(csv);
}
#endif
