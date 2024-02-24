 # CSV Library in C

This library provides a simple and easy-to-use interface for working with CSV (comma-separated values) files in C. It includes functions for creating, reading, updating, and deleting CSV files, as well as searching for specific data within a CSV file and getting data from the file.

## Installation

To install the CSV library, simply copy the `raycsv.h` files into your project directory. You will also need to include the `rayutils.h` header file, which is included in the library , You should to define CSV_C_ before include liberary.


## Usage

To use the CSV library, you will first need to create a `CSV` object. This can be done by calling the `init()` function, which takes the following arguments:

* `filename`: The name of the CSV file to be created or opened.
* `isnew`: A boolean value indicating whether the CSV file is new or already exists.
* `format`: A string specifying the format of the CSV file. The format string consists of a series of characters, each of which represents a different data type. The following characters are supported:
    * `s`: String
    * `n`: Number
    * `b`: Boolean
* `status`: A pointer to a `Status` object, which will be used to return the status of the operation.

For example, the following format string specifies a CSV file with three columns: a string column, a number column, and a boolean column:

```
"s,n,b"
```

```c
#define CSV_C_
#include "raycsv.h"

CSV_Class obj = Init_Class_Functions();
Status status = obj.CSV_Init("test.csv", true, "s,s,s", obj.csv);
if (status != success) {
    // Handle error
}
obj.CSV_Close(obj.csvfile);
```

## Adding Data to a CSV File

To add data to a CSV file, you can use the `obj.CSV_Add_Data()` method. This method takes the following arguments:

* `csv`: A pointer to a `CSV` object.
* `title`: A boolean value indicating whether to add the titles of the data to the CSV file.
* `data`: An array of strings containing the data to be added to the CSV file.
* `data_size`: The size of the `data` array.

The `CSV_Add_Data()` method will append the data to the CSV file, and will automatically add commas between the data values.

## Deleting Data from a CSV File

To delete data from a CSV file, you can use the `del_data()` function. This function takes the following arguments:

* `csv`: A pointer to a `CSV` object.
* `line`: The line number of the data to be deleted.

The `CSV_Del_Data()`
