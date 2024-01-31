#define CSV_C_
#define ESCAPR_LEN_OF_FORMAT_DATA
#include "../raycsv.h"


int main(void){
	Status status; // handel error's using Status object
	// to create csv file you need to use init function first
	char* file = "students.csv";
	CSV* csvfile = Init_CSV(
		file, // filename
		true, // this is new file
		"n,s,n", // format file is <name : str , age : number>
		&status // address of status object
	);
	// checking error
	if(status  == error){
		fprintf(stderr , "Error : opening %s file" , file);
		// closing file
		Close_CSV(csvfile);
		return 1;
	}
	// add titles 
	char *titles[3] = {
		"id",
		"name",
		"age"
	};
	status = add_data(
		csvfile, // csvfile object 
		true, // true if this title
		titles, // array string of data or titles
		array_size(titles) // size 
	);
	// checking for warning
	// you can define ESCAPR_LEN_OF_FORMAT_DATA to escape format length and keep wrtiting data
	if(status  == warning){
		fprintf(stderr , "Warning : data or titles length are big then format");
		// closing file
		Close_CSV(csvfile);
		return 1;
	}
	// checking error
	if(status  == error){
		fprintf(stderr , "Error : can't add data");
		// closing file
		Close_CSV(csvfile);
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
	status = add_data(csvfile, false , data , array_size(data));
	// checking for warning
	// you can define ESCAPR_LEN_OF_FORMAT_DATA to escape format length and keep wrtiting data
	if(status  == warning){
		fprintf(stderr , "Warning : data or titles length are big then format");
		// closing file
		Close_CSV(csvfile);
		return 1;
	}
	// checking error
	if(status  == error){
		fprintf(stderr , "Error : can't add data");
		// closing file
		Close_CSV(csvfile);
		return 1;
	}
	char gettingdata[1024];
	status = Get_data(csvfile , "11" ,gettingdata , array_size(gettingdata));
	if(status == error){
		// closing file
		Close_CSV(csvfile);
		return 1;
	}
	// for testing 
	//puts(gettingdata);
	
	// closing file
	Close_CSV(csvfile);
	return 0;
}
