// Author: Vijay Korapaty
// Date: 11-4-11
// Title: Sorting.cpp
// Description: Testing insertion, selection, and quick sort performance.

#include <Windows.h>
#include <iostream>
#include <string>

#include <time.h>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

// Global variables, will be used by multiple functions.
const int INPUT_SIZE = 20;
//const int INPUT_SIZE = 10000;
//const int INPUT_SIZE = 100000;
int increasing[INPUT_SIZE];
int decreasing[INPUT_SIZE];
int random[INPUT_SIZE];


SYSTEMTIME start_t, end_t;


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
	printf("\nThe start time was: %02d:%04d:%04d\n", start_t.wMinute, 
		start_t.wSecond, start_t.wMilliseconds);
	printf("The end time was: %02d:%04d:%04d\n", end_t.wMinute, end_t.wSecond, 
		end_t.wMilliseconds);
	printf("The %s test took: %02d:%04d:%04d\n", 
		testTitle.c_str(), end_t.wMinute - start_t.wMinute, end_t.wSecond - 
		start_t.wSecond, end_t.wMilliseconds - start_t.wMilliseconds);
}

template<class T>	// Useful for testing with INPUT_SIZE = 20
void mod_array(T input[])	{
	for(int i = 0; i<INPUT_SIZE; i++)	{
		input[i] += 10;
	}
}


void print_title(tuple<int*,string> someCase)	{
	print_array(get<0>(someCase));
	cout << get<1>(someCase) << endl;
	mod_array(get<0>(someCase));
	print_array(get<0>(someCase));
}

int main()	{
	srand ( time(NULL) );

	reset_arrays();
	
	// Create tuples of the various test cases
	tuple<int*, string> case_increasing(increasing, "Increasing");
	tuple<int*, string> case_decreasing(decreasing, "Decreasing");
	tuple<int*, string> case_random(random, "Random");
	// These could also be written as follows:
	//		auto case_increasing = make_tuple(increasing, "Increasing");

	// Create vector that holds all of the test case tuples
	vector<tuple<int*, string>> testCases;
	testCases.push_back(case_increasing);
	testCases.push_back(case_decreasing);
	testCases.push_back(case_random);

	for_each(testCases.begin(),testCases.end(), print_title);

	/*
	std::cout << "Time tracking is done in minutes:seconds:milliseconds."
		<< std::endl;
	 
	std::cout << "\nInsertion Sort:";
	test_insertion();
	
	std::cout << "\n\nSelection Sort:";
	test_selection();
	
	std::cout << "\n\nTemplate Selection Sort:";
	test_template_selection();
	

	std::cout << "\n\nQuick Sort:";
	test_quick();
	
	*/

	return 0;
}