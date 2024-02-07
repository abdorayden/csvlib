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
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define null	0

#ifndef UTILS
#define UTILS

typedef enum{
	error = -1,
	warning,
	success,
}Status;

// developing string methods in c
typedef struct{
	char* string;
	size_t length;
}String;

typedef struct {
	String str;
	////////////////
	void (*split)(String str , char split_what , char* the_str[] , size_t* arr_size);	
	void (*lower)(String str);
	void (*upper)(String str);
	void (*remove_prefix)(String str , int *size ,const char* rm);
	void (*remove_safix)(String str , int *size , const char* rm);
	bool (*startswith)(String str , char* cmp);
	bool (*endswith)(String str, char* cmp);
}StringObj;

#define array_size(arr)	(size_t)(sizeof(arr) / sizeof(arr[0]))
/********************************************************************************/

StringObj str(char* _string);
void splitstr(String str , char split_what , char* the_str[] , size_t* arr_size);
void strlower(String str);
void strupper(String str);
void remove_prefix(String str , int* size , const char* rm);
void remove_safix(String str , int* size , const char* rm);
bool strstartswith(String str, char* cmp);
bool strendswith(String str, char* cmp);

// counting lines in file name .
int countlines(char *filename);

int pgcd(int a , int b);
int ppcm(int a , int b); 
void insert(bool is_by_idx , int arr[] , int value , int* size , int* idx , int idx_to_insert);
int swap(int* a , int* b);
Status sort(int arr[] , int size); 
Status reverse(int arr[] , int size);
Status splitnumbers(int number , int arr[] , int* size);
Status popidx(int arr[] , int* size , int idx); 
Status popvalue(int arr[] , int* size , int value);
int lengh_num(int nums , Status* status);
Status tostr(int num , char arr[] , int arr_size);
Status to_Int(char* num , int outnum[]);
void inser_char(char arr[] , size_t *size , char ch , int idx);
#define random(a , min , max)	(long)&(a) % ((max) + 1 - (min)) + (min)
#endif //UTILS

#ifdef RUN_AS_C_FILE_

StringObj str(char* _string)
{
	StringObj le_str;
	le_str.str.string = _string;
	le_str.str.length = strlen(_string);
	/////////////////////////////
	le_str.split = splitstr;
	le_str.lower = strlower;
	le_str.upper = strupper;
	le_str.remove_prefix = remove_prefix;
	le_str.remove_safix = remove_safix;
	le_str.startswith = strstartswith;
	le_str.endswith = strendswith;

	return le_str;
}
// done
void splitstr(String str , char split_what , char* the_str[] , size_t* arr_size)
{
	if(split_what == '\0' || str.string == NULL)
		return;
	int i = 0; 
	int j = 0; 
	int idxsp = 0;
	char* sp = malloc(512);
	while(str.string[i] != '\0'){
		if(str.string[i] == split_what){
			strcpy(the_str[j++] , sp);
			memset(sp , 0, 512);
			idxsp = 0;
			i++;
		}else{
			sp[idxsp++] = str.string[i];
			i++;
		}
	}
	strcpy(the_str[j++] , sp);
	*arr_size = (size_t)j;
	free(sp);
}
void strlower(String str)
{
	for(int i = 0 ; i < strlen(str.string) ; i++){
		if((str.string[i] <= 'Z') && (str.string[i] >= 'A')){
			str.string[i] += 32;
		}
	}
}
void strupper(String str)
{
	for(int i = 0 ; i < strlen(str.string) ; i++){
		if((str.string[i] <= 'z') && (str.string[i] >= 'a')){
			str.string[i] -= 32;
		}
	}
}
void remove_prefix(String str , int *size ,const char* rm)
{
	if(sizeof(str.string) == null)
		return;
	int i;
	int last =(strlen(str.string)-strlen(rm));
	int idx = 0;
	while(i < *size){
		if(i == strlen(rm)){
			for(int j = i ; j < *size ; j++){
				str.string[idx++] = str.string[j];
			}
			i+= strlen(rm);
			break;
		}
		i++;
	}
	while(i<*size){
		*(str.string+i) = (int)null;
		i++;
	}
	*size -= strlen(rm);
}
void remove_safix(String str , int *size , const char* rm)
{
	int i;
	if(strlen(str.string) == null)
		return;
	int count = strlen(str.string) - strlen(rm); 
	for(i = 0 ; i < *size ; i++){
		if(i >= count){
			*(str.string+i) = (int)null;
		}
	}
	*size -= strlen(rm);
}
bool strstartswith(String str , char* cmp)
{
	if(str.string == NULL || cmp == NULL)
		return false;
	int i = 0;
	while(cmp[i] != '\0'){
		if(str.string[i] != cmp[i])
			return false;
		i++;
	}
	return true;
}
bool strendswith(String str , char* cmp)
{
	if((str.string == NULL) || (cmp == NULL))
		return false;
	int idx ;
	int i;
	for(i = strlen(cmp), idx = 0; (i < strlen(str.string)),(idx < strlen(cmp)) ; i++ , idx++){
		if(cmp[idx] != str.string[i])
			return false;
	}
	return true;
}

int countlines(char *filename)
{
	FILE *fp = fopen(filename,"r");
	int ch=0;
	int lines=0;
	
	if (fp == NULL)
		return 0;
	
	lines++;
	while ((ch = fgetc(fp)) != EOF){
	        if (ch == '\n')
		lines++;
	}
	fclose(fp);
	return lines;
}

int pgcd(int a , int b){
	if(b == 0) return a;
	int temp ;
	int rest ;
	if(b > a){
		temp = a;
		a = b;
		b = temp;
	}
	while(1){
		rest = a%b;
		if(rest == 0)
			break;
		a = b;
		b = rest;
	}
	return b;
}
int ppcm(int a , int b){
	if(b == 0) return -1;
	int temp ;
	int r ;
	int all = a*b;
	if(b > a){
		temp = a;
		a = b;
		b = temp;
	}
	while(1){
		r = a%b ;
		if(r == 0)
			break;
		a = b ;
		b = r ;
	}	
	return all/b;
}
void insert(bool is_by_idx , int arr[] , int value , int* size , int* idx , int idx_to_insert){
	for(int i = 0 ; i < (*size) ; i++){
		if( !is_by_idx ){
			if(arr[i] > value){
				*idx = i;
				(*size)++;
				for(int j = (*size) ; j >= i + 1 ; j--)
					arr[j - 1] = arr[j - 2];
				arr[i] = value ;
				break ;
			}
		}else{
			if( i == idx_to_insert ){
				(*size)++;
				for(int j = (*size) ; j >= i + 1 ; j--)
					arr[j - 1] = arr[j - 2];
				arr[i] = value ;
				break ;
			}
		}
	}
}
/******************** sort method *************************/
int swap(int* a , int* b){
          int temp;
          temp = *a;
          *a = *b;
          *b = temp ;
}
Status sort(int arr[] , int size){
	if(size == 0) return error;
          int idx = 0;
          for(int i = 0 ; i < size ; i++){
                  for(int idx = i+1 ; idx < size ; idx++){
                          if( arr[i]>arr[idx] ){
                                  swap(&arr[idx] , &arr[i]);
                          }
                  }
          }
	  return success;
}
/**********************************************************/
Status reverse(int arr[] , int size){
	if(size == 0) return error;
	int temp;
	int i = 0;
	while(i < (size-1)){
		temp = arr[i];
		arr[i] = arr[size-1];
		arr[size-1] = temp;
		i++;
		size--;
	}
	return success;
}

/**********************************************************/
Status splitnumbers(int number , int arr[] , int* size){
	if(number <= 0) return warning;
	int i = 0;
	*size = 0;
	while(number != 0){
		arr[i] = number % 10;
		number /= 10;
		i++ ;
		(*size)++;
	}
	return success;
}

Status popidx(int arr[] , int* size , int idx){
	if(*size == 0) return error;
	int i;
	int j;
	for(i = 0 ;i < *size ; i++){
		if(i == idx){
			for(j = i ; j < *size ; j++){
				arr[j] = arr[j+1];
			}
			(*size)--;
		}
	}
	return success;
}
Status popvalue(int arr[] , int* size , int value){
	if(*size == 0) return error;
	int i;
	int j;
	for(i = 0 ;i < *size ; i++){
		if(arr[i] == value){
			for(j = i ; j < *size ; j++){
				arr[j] = arr[j+1];
			}
			(*size)--;
		}
	}
	return success;
}

int lengh_num(int nums , Status* status){
	if(nums <= 0){
		*status = warning;
		return nums;
	}
	int all = 0;
	int arr[15];
	int size;
	*status = success;
	splitnumbers(nums , arr , &size);
	for(int i = 0 ; i < size ; i++){
		all++;
	}
	return all;

}
void inser_char(char arr[] , size_t *size , char ch , int idx){
	for(int i = 0 ; i < *size ; i++){
		if(i == idx){
			++(*size);
			for(int j = (*size) ; j >= i + 1 ; j--)
				arr[j - 1] = arr[j - 2];
			arr[i] = ch;
			break;
		}
	}
}
Status tostr(int num , char arr[] , int arr_size)
{
	int ascii[10];
	int idx = 0;
	for(int j = 48 ; j < 58 ; j++)
		ascii[idx++] = j;
	int splnum[10];
	idx = 0;
	int size;
	splitnumbers(num , splnum , &size);
	if(size > arr_size) return error;
	for(int i = 0 ; i < 10 ; i++){
		for(int k = 0 ; k<size ; k++)
			if(splnum[k] == i){
				arr[idx++] = ascii[i];
				break;
			}
	}
	if(strlen(arr) != size) 
		return warning;
	return success;
}

Status to_Int(char* num , int outnum[]){
	for(size_t i = 0 ; i < strlen(num) ; i++){
		if(((int)num[i] > 57) || ((int)num[i] < 48))
			return error;
		outnum[i] = num[i] - 48;
	}
	return success;
}

#endif // RUN_AS_C_FILE_
