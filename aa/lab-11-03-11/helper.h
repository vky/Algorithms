#ifndef	HELPER_H
#define	HELPER_H
#include <Windows.h>
#include <iostream>
#include <string>

// Global variables, will be used by multiple functions.
//const int INPUT_SIZE = 20;
//const int INPUT_SIZE = 10000;
const int INPUT_SIZE = 100000;
int increasing[INPUT_SIZE];
int decreasing[INPUT_SIZE];
int random[INPUT_SIZE];


SYSTEMTIME start, end;


template<class T>	// Useful for testing with INPUT_SIZE = 20
void print_array(T input[])	{
	for(int i = 0; i<INPUT_SIZE; i++)	{
		std::cout << input[i] << " ";
	}
	std::cout << std::endl;
}
template<class T>
void is_sorted(T input[], std::string sortTitle)	{
	bool sorted = true;
	for ( int z = 0; z < INPUT_SIZE-1; z++ )	{
		if (input[z] > input[z+1])	{
			std::cout << sortTitle << " IS NOT sorted." << std::endl;
			//std::cout << "Breaks down: " << z << " | " <<input[z] <<".\n" << std::endl;
			sorted = false;
			break;
		}
	}
	if (sorted == true)	{
		std::cout << sortTitle << " IS sorted." << std::endl;
		//print_array(input);
	}
	//else
		//print_array(input);
}
// Set arrays at the start of each test.
void reset_arrays()	{
	for (int i = 0; i < INPUT_SIZE; i++)	{
		increasing[i] = i+1;
	}

	int decTemp = INPUT_SIZE;
	for (int i = 0; i < INPUT_SIZE; i++)	{
		decreasing[i] = decTemp;
		decTemp--;
	}
		
	for (int i = 0; i < INPUT_SIZE; i++)	{
		random[i] = rand() % 10000;
	}
}
// Print the time taken based off of time before and after a function call.
void print_performance(std::string testTitle)	{
	printf("\nThe start time was: %02d:%04d:%04d\n", start.wMinute, 
		start.wSecond, start.wMilliseconds);
	printf("The end time was: %02d:%04d:%04d\n", end.wMinute, end.wSecond, 
		end.wMilliseconds);
	printf("The %s test took: %02d:%04d:%04d\n", 
		testTitle.c_str(), end.wMinute - start.wMinute, end.wSecond - 
		start.wSecond, end.wMilliseconds - start.wMilliseconds);
}

#endif