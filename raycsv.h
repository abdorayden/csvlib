/**********************************************************************************************************************************************
*			Copyright (c) 2023 Ray Den
*
*	Permission is hereby granted, free of charge, to any person obtaining a copy
*	of this software and associated documentation files (the "Software"), to deal
*	in the Software without restriction, including without limitation the rights
*	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*	copies of the Software, and to permit persons to whom the Software is
*	furnished to do so, subject to the following conditions:
*	
*	The above copyright notice and this permission notice shall be included in
*	all copies or substantial portions of the Software.
*	
*	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
*	THE SOFTWARE.
*
*******************************************************************************************************************************************/

#ifndef CSV_H_
#define CSV_H_

#define RUN_AS_C_FILE_ // run as c file
#include "utils/rayutils.h"

// you can change this cinfiguration.
#define maxTypes	25

// structures 
typedef struct{
	const char* name;
	size_t formatlength;
	char types[maxTypes];
}CSV;

typedef struct {
	CSV* csvfile;
	Status (*CSV_Init)(
		const char* filename , // name of file
		bool isnew , // true if this file is new else false
		char* format, // format of csv file 
		CSV* csv // status out if function works successfully or not 
	);
	Status (*CSV_Add_Data)(
		CSV* csv , // statctures from init function 
		bool title, // if you want to add titles if not we put new line 
		char* data[] , // array of strings data to added to file  
		size_t data_size // array size
	);
	Status (*CSV_Del_Data)(
		CSV* csv , // statctures from init function 
		int line // line to delete
	);
	Status (*CSV_Find_Data)(
			CSV* csv , // struct data of csv file 
			char* element ,// word that u search for like name : mike
			int *position ,// positions of word that u search for.
			int* _founds // how many times found 
		);
	Status (*CSV_Get_Data)(	
		CSV* csv , // struct data of csv file
		char* data , // id of data 
		char* line_data , // array of chars to get the data line
		size_t length // array size
		);

	Status (*CSV_Get_Titles)(
		CSV* csv , // struct data of csv file
		char title[], // array title line
		size_t title_size // size of array title
		);
	Status (*CSV_Close)(CSV* csvfile);
}CSV_Class;


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

static Status init(
	const char* filename , // name of file
	bool isnew , // true if this file is new else false
	char* format, // format of csv file 
	CSV* csv // status out if function works successfully or not 
	);

static Status add_data(
	CSV* csv , // statctures from init function 
	bool title, // if you want to add titles if not we put new line 
	char* data[] , // array of strings data to added to file  
	size_t data_size // array size
	);
static Status del_data(
	CSV* csv , // statctures from init function 
	int line // line to delete
	);
static Status find_data(
			CSV* csv , // struct data of csv file 
			char* element ,// word that u search for like name : mike
			int *position ,// positions of word that u search for.
			int* _founds // how many times found 
			);
static Status Get_data(	
		CSV* csv , // struct data of csv file
		char* data , // id of data 
		char* line_data , // array of chars to get the data line
		size_t length // array size
		);

static Status Get_titles(
		CSV* csv , // struct data of csv file
		char title[], // array title line
		size_t title_size // size of array title
		);

static Status close(CSV* csvfile);

CSV_Class Init_Class_Functions(void);

#endif //CSV_H_

#ifdef CSV_C_
// format:
// 	s: string
// 	n: number
// 	b: boolean

// out param value:
//	warning = -1,
//	success = 0,
//	error   = 1,
// 	
// initial function 

static Status init(const char* filename , bool isnew , char* format , CSV* csv){
	if(!csv)
		return error;
	// we will handle format here
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
		return error;
	
	// now structure is full of information file with all types
	csv->name = filename;	
	fclose(file);
	// Don't forgot to free memory
	//free(csv);
	return success;
}
// why this function didn't work?
static Status add_data(CSV* csv , bool title, char* data[],size_t data_size)
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
static Status del_data(CSV* csv , int line)
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

static Status find_data(CSV* csv ,char* element ,int *position , int* _founds)
{
	Status status = error;
	if(!csv){
		puts("from csv");
		return status;
	}
	size_t size = 0;
	int line = 0;
	FILE *fp = fopen(csv->name , "r");
	if(!fp){
		puts("from fp");
		return error;
	}
	char linechar[256];
	while(fgets(linechar , sizeof(linechar) , fp) != NULL){
		line++;
		char* tok = strtok(linechar , ",");
		while(tok != NULL){
			if(strcmp(tok , element) == 0){
				status = success;
				position[size++] = line;
			}
			tok = strtok(NULL , ",");
		}
	}
	*_founds = (int)size;
	fclose(fp);
	//if(size == 0) return warning;
	return status;
}

static Status Get_data(CSV* csv , char* data , char* line_data , size_t length)
{
	if(!csv)
		return error;
	FILE* fp = fopen(csv->name , "r");
	if(!fp)	return error;
	int position[2];
	int how_many;
	Status status_find = find_data(csv ,data, position , &how_many);
	if(status_find == error){
		return error;
		//free(position);
	}
	int line = 0;
	while(fgets(line_data , length , fp) != NULL){
		line++;
		if(line == position[0])
			// we found data
			break;
	}
	//free(position);
	return success;
}

static Status Get_titles(
		CSV* csv , // struct data of csv file
		char title[], // array title line
		size_t title_size // size of array title
		)
{
	if(!csv) return error;
	FILE *fp = fopen(csv->name , "r");
	if(!fp) return error;
	if(fgets(title , title_size , fp) == NULL){
		fclose(fp);
		return error;
	}
	fclose(fp);
	return success;

}
static Status close(CSV* csvfile)
{
	free(csvfile);
}

CSV_Class Init_Class_Functions(void)
{
	CSV_Class obj;
	obj.csvfile = (CSV*)malloc(sizeof(CSV));
	obj.CSV_Init = init;
	obj.CSV_Add_Data = add_data;
	obj.CSV_Del_Data = del_data;
	obj.CSV_Find_Data = find_data;
	obj.CSV_Get_Data = Get_data;
	/***************************************/
	obj.CSV_Get_Titles = Get_titles;
	obj.CSV_Close = close;

	return obj;
}

#endif
