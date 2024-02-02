#define CSV_C_
#define ESCAPR_LEN_OF_FORMAT_DATA
#include "../raycsv.h"


int main(void){

	CSV* csvfiles;
	CSV_ALLOCATE(csvfiles);
	CSV_Class csv = Init_Class_Functions();
	// checking error
	if(csv.CSV_Init("students.csv" , false , "n,s,n" , csvfiles) == error){
		fprintf(stderr , "Error : opening file");
		// closing file
		CSV_FREE(csvfiles);
		return 1;
	}
	int pos[2];
	int f[2];
	// checking error
	if(csv.CSV_Find_Data(csvfiles , "1" ,pos , f) == error){
		fprintf(stderr , "data not found");
		// closing file
		CSV_FREE(csvfiles);
		return 1;
	}
	printf("we found at line : %d\n" , pos[0]);
	puts("getting the line data ... ");
	char dataline[1024];
	if( csv.CSV_Get_Data(csvfiles , "1" , dataline , array_size(dataline)) == error){
		fprintf(stderr , "Error : error");
		CSV_FREE(csvfiles);
	}
	puts(dataline);

	CSV_FREE(csvfiles);

	return 0;
}
