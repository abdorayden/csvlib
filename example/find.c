#define CSV_C_
#define ESCAPR_LEN_OF_FORMAT_DATA
#include "../raycsv.h"


int main(void){

	CSV_Class csv = Init_Class_Functions();
	// checking error
	if(csv.CSV_Init("students.csv" , false , "n,s,n" , csv.csvfile) == error){
		fprintf(stderr , "Error : opening file");
		// closing file
		csv.CSV_Close(csv.csvfile);
		return 1;
	}
	int pos[2];
	int f;
	// checking error
	if(csv.CSV_Find_Data(csv.csvfile , "fbar" ,pos , &f) == error){
		fprintf(stderr , "data not found");
		// closing file
		csv.CSV_Close(csv.csvfile);
		return 1;
	}
	printf("we found at line : %d\n" , pos[0]);
	puts("getting the line data ... ");
	char dataline[1024];
	if( csv.CSV_Get_Data(csv.csvfile , "fbar" , dataline , array_size(dataline)) == error){
		fprintf(stderr , "Error : error");
		csv.CSV_Close(csv.csvfile);
		return 1;
	}
	puts(dataline);
	char titles[1024];
	if(csv.CSV_Get_Titles(csv.csvfile , titles , array_size(titles)) == error){
		fprintf(stderr , "Error : error");
		csv.CSV_Close(csv.csvfile);
		return 1;
	}
	puts(titles);

	csv.CSV_Close(csv.csvfile);

	return 0;
}
