#define CSV_C_
#include "../raycsv.h"

char* my_func(void){
	static size_t i = 0;
	char* test = malloc(6);
	while(i < 14){
		memset(test , 0 , 3);
		i++;
		if(tostr(i , test) == error){
			printf("Error to change integer to string");
			free(test);
			return NULL;
		}
		strcat(test , "te");
		return test;
	}
	return NULL;
}

int main(void){
	CSV_Class csv = Init_Class_Functions();
	if(csv.CSV_Init("students.csv" , false , "f,f,f" , csv.csvfile) == error){
		fprintf(stderr , "Error : opening file");
		csv.CSV_Close(csv.csvfile);
		return 1;
	}
	if(csv.CSV_Add_Data_By_Fn(csv.csvfile , my_func) == error){
		fprintf(stderr , "Error : function add data");
		csv.CSV_Close(csv.csvfile);
		return 1;
	}
	printf("done");
	csv.CSV_Close(csv.csvfile);

	return 0;
}
