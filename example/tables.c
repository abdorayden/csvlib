#define CSV_C_
#define ESCAPR_LEN_OF_FORMAT_DATA
#include "../raycsv.h"

int main(void)
{
	CSV_Class csv = Init_Class_Functions();
	// checking error
	if(csv.CSV_Init("students.csv" , false , "f,f,f" , csv.csvfile) == error){
		fprintf(stderr , "Error : opening file");
		// closing file
		csv.CSV_Close(csv.csvfile);
		return 1;
	}
	if(csv.CSV_Print_Table(csv.csvfile) == error){
		fprintf(stderr , "Error : opening file");
		// closing file
		csv.CSV_Close(csv.csvfile);
		return 1;

	}
	return 0;
}
