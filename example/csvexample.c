#define CSV_C_
#define ESCAPR_LEN_OF_FORMAT_DATA
#include "../raycsv.h"


int main(void){
	Status status; // handel error's using Status object
	// to create csv file you need to use init function first
	char* file = "students.csv";

	CSV_Class obj = Init_Class_Functions();
	status = obj.CSV_Init(
		file, // filename
		true, // this is new file
		"f,f,f", // format file is <name : str , age : number>
		obj.csvfile
	);
	// checking error
	if(status  == error){
		fprintf(stderr , "Error : opening %s file" , file);
		// closing file
		obj.CSV_Close(obj.csvfile);
		return 1;
	}
	// add titles 
	char *titles[3] = {
		"id",
		"name",
		"age"
	};
	status = obj.CSV_Add_Data(
		obj.csvfile, // obj.csvfile object 
		true, // true if this title
		titles, // array string of data or titles
		array_size(titles) // size 
	); 
	// checking for warning
	// you can define ESCAPR_LEN_OF_FORMAT_DATA to escape format length and keep wrtiting data
	if(status  == warning){
		fprintf(stderr , "Warning : data or titles length are big then format");
		// closing file
		obj.CSV_Close(obj.csvfile);
		return 1;
	}
	// checking error
	if(status  == error){
		fprintf(stderr , "Error : can't add data");
		// closing file
		obj.CSV_Close(obj.csvfile);
		return 1;
	}
	// now let's add some data
	char* data[36] = {
		"1",
		"rayden",
		"20", // use number as string
		"2",
		"emma",
		"19", // use number as string
		"3",
		"foobar",
		"49", // use number as string
		"4",
		"fbar",
		"9", // use number as string
		"5",
		"fooar",
		"49", // use number as string
		"6",
		"oobar",
		"49", // use number as string
		"7",
		"fobar",
		"49", // use number as string
		"8",
		"foobr",
		"49", // use number as string
		"9",
		"fooba",
		"49", // use number as string
		"10",
		"far",
		"49", // use number as string
		"11",
		"f",
		"49", // use number as string
		"12",
		"r",
		"49", // use number as string
	};
	status = obj.CSV_Add_Data(
		obj.csvfile, // obj.csvfile object 
		false, // true if this title
		data, // array string of data or titles
		array_size(data) // size 
	); 
	// checking for warning
	// you can define ESCAPR_LEN_OF_FORMAT_DATA to escape format length and keep wrtiting data
	if(status  == warning){
		fprintf(stderr , "Warning : data or titles length are big then format");
		// closing file
		obj.CSV_Close(obj.csvfile);
		return 1;
	}
	// checking error
	if(status  == error){
		fprintf(stderr , "Error : can't add data");
		// closing file
		obj.CSV_Close(obj.csvfile);
		return 1;
	}
	char gettingdata[1024];
	status = obj.CSV_Get_Data(obj.csvfile , "11" ,gettingdata , array_size(gettingdata)); 
	if(status == error){
		// closing file
		obj.CSV_Close(obj.csvfile);
		return 1;
	}
	// for testing 
	//puts(gettingdata);
	
	// closing file
	obj.CSV_Close(obj.csvfile);
	return 0;
}
