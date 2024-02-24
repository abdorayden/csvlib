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
	char* fileinfo = malloc(1024);
	if(fileinfo == NULL){
		puts("from malloc");
		csv.CSV_Close(csv.csvfile);
		return 1;
	}
	if (csv.CSV_File_Info(csv.csvfile , fileinfo) == error ){
		puts("from csv");
		csv.CSV_Close(csv.csvfile);
		return 1;
	}
	puts(fileinfo);
	free(fileinfo);
	csv.CSV_Close(csv.csvfile);

	return 0;
}
