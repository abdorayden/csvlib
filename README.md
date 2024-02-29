 # CSV Library in C

This library provides a simple and easy-to-use interface for working with CSV (comma-separated values) files in C. It includes functions for creating, reading, updating, and deleting CSV files, as well as searching for specific data within a CSV file and getting data from the file.

## Installation

To install the CSV library, simply copy the `raycsv.h` files into your project directory. You will also need to include the `rayutils.h` header file, which is included in the library , You should to define CSV_C_ before include liberary.


# Class Methods

. Here is a brief description of each method provided by the CSV_Class class:

1. CSV_Init: Initializes a new CSV object with the given filename and format. The format is a string that specifies the type of each column in the CSV file (e.g., "snb" for string, number, boolean).
2. CSV_Add_Data: Adds new data to the CSV file. The data is specified as an array of strings, where each string corresponds to a column in the CSV file.
3. CSV_Del_Data: Deletes a line of data from the CSV file.
4. CSV_Find_Data: Searches for a specific value in the CSV file and returns the positions where it was found.
5. CSV_Get_Data: Retrieves a line of data from the CSV file based on its ID.
6. CSV_Get_Titles: Retrieves the titles (first line) of the CSV file.
7. CSV_Edit_Data_Line: Edits a line of data in the CSV file.
8. CSV_File_Info: Retrieves information about the CSV file, such as its name, number of lines, and number of columns.
9. CSV_Print_Table: Prints the contents of the CSV file as a table in the console.
10. CSV_Close: Frees the memory used by the CSV object.

## Usage

1. First, include the CSV header file in your C program:

```c
#include "raycsv.h"
```
2. a new `CSV_Class` object using the `Init_Class_Functions()` function:
```c
CSV_Class csv = Init_Class_Functions();
```
4. Initialize a new CSV file using the CSV_Init() function. In this example, we'll create a new file called "example.csv" with two columns: a string column and a number column:
```c
Status status;
CSV_Class csvfile;
csvfile = Init_Class_Functions();
status = csvfile.CSV_Init("example.csv", true, "sn", csvfile.csvfile);
if (status != success) {
    printf("Error initializing CSV file: %d\n", status);
    return 1;
}
```
5. Add some data to the CSV file using the CSV_Add_Data() function. In this example, we'll add three rows of data:
```c
char* data1[] = {"John", "30"};
char* data2[] = {"Jane", "25"};
char* data3[] = {"Bob", "35"};

status = csv.CSV_Add_Data(csvfile.csvfile, true, (char*[]) {data1, data2, data3}, 3);
if (status != success) {
    printf("Error adding data to CSV file: %d\n", status);
    return 1;
}
```
6. Print the contents of the CSV file using the CSV_Print_Table() function:
```c
status = csv.CSV_Print_Table(csvfile.csvfile);
if (status != success) {
    printf("Error printing CSV file: %d\n", status);
    return 1;
}
```
7. Close the CSV file using the CSV_Close() function:
```c
csv.CSV_Close(csvfile.csvfile);
```
## The complete example code would look like this:

```c
#define CSV_C_
#include "raycsv.h"

int main() {
    CSV_Class csv = Init_Class_Functions();

    Status status = csv.CSV_Init("example.csv", true, "sn", csvfile.csvfile);
    if (status != success) {
        printf("Error initializing CSV file: %d\n", status);
        return 1;
    }

    char* data1[] = {"John", "30"};
    char* data2[] = {"Jane", "25"};
    char* data3[] = {"Bob", "35"};

    status = csv.CSV_Add_Data(csvfile.csvfile, true, (char*[]) {data1, data2, data3}, 3);
    if (status != success) {
        printf("Error adding data to CSV file: %d\n", status);
        return 1;
    }

    status = csv.CSV_Print_Table(csvfile.csvfile);
    if (status != success) {
        printf("Error printing CSV file: %d\n", status);
        return 1;
    }

    csv.CSV_Close(csvfile.csvfile);

    return 0;
}
```
# This example would create a new CSV file called "example.csv" with the following contents:
```csv
string,number
John,30
Jane,25
Bob,35
```
You can modify this example to add more data, search for specific data, edit data, and so on, using the other functions provided by the CSV library.
