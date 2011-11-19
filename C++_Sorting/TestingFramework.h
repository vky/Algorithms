#ifndef TESTINGFRAMEWORK_H
#define TESTINGFRAMEWORK_H

#include <Windows.h>
#include <iostream>
#include <string>

#include <time.h>
#include <vector>
#include <tuple>
#include <algorithm>
#include <functional>

//#include "my_sorting.h"
using namespace std;


const int MERGE_MAX = 99999;
const int MAX_INT = 54000;

// Global variables, will be used by multiple functions.
//const int INPUT_SIZE = 20;
//const int INPUT_SIZE = 3200; // Semi-limit changes. Stack is weird.
//const int INPUT_SIZE = 50000;
const int INPUT_SIZE = 100000;

int increasing[INPUT_SIZE];
int decreasing[INPUT_SIZE];
int random[INPUT_SIZE];


SYSTEMTIME start_t, end_t;


// Helper Functions
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
		random[i] = rand() % MAX_INT;
	}
}


// end, start, size
// eg. - end_second, start_second, 60 -> msd
//		 end_millisecond, start_millisecond, 1000 -> msd
// see timer.txt for more readable original mockup that is based 
// off of seconds:milliseconds.
tuple<int,int> real_time(tuple<int, int, int> sec, tuple<int, int, int> mil)	{
	tuple<int,int> total(0,0); // sec:mil
	
	if (get<0>(sec) > get<1>(sec))	{
		if (get<0>(mil) < get<1>(mil))	{
			get<0>(total) = get<0>(sec) - get<1>(sec) - 1;
			get<1>(total) = get<0>(mil) + (get<2>(mil) - get<1>(mil));
		}
		else	{
			get<0>(total) = get<0>(sec) - get<1>(sec);
			get<1>(total) = get<0>(mil) - get<1>(mil);
		}
	}

	if (get<0>(sec) < get<1>(sec))	{
		if (get<0>(mil) < get<1>(mil))	{
			get<0>(total) = get<0>(sec) + (get<2>(sec) - get<1>(sec)) - 1;
			get<1>(total) = get<0>(mil) + (get<2>(mil) - get<1>(mil));
		}
		else	{
			get<0>(total) = get<0>(sec) + (get<2>(sec) - get<1>(sec));
			get<1>(total) = get<0>(mil) - get<1>(mil);
		}
	}
	
	if (get<0>(sec) == get<1>(sec))	{
		if (get<0>(mil) < get<1>(mil))	{
			throw "TIME IS BROKEN; END BEFORE STARTING";
		}
		else	{
			get<0>(total) = get<0>(sec) - get<1>(sec);
			get<1>(total) = get<0>(mil) - get<1>(mil);
		}
	}

	return total;
}
// Print the time taken based off of time before and after a function call.
void print_performance(std::string testTitle)	{
	SYSTEMTIME fin_t;
	fin_t = end_t;

	printf("\nThe start time was: %02d:%04d:%04d\n", start_t.wMinute, 
		start_t.wSecond, start_t.wMilliseconds);
	printf("The end time was: %02d:%04d:%04d\n", end_t.wMinute, end_t.wSecond, 
		end_t.wMilliseconds);
	printf("The %s test took: %02d:%04d:%04d\n", 
		testTitle.c_str(), end_t.wMinute - start_t.wMinute, end_t.wSecond - 
		start_t.wSecond, end_t.wMilliseconds - start_t.wMilliseconds);
	
	// DONE
	if (end_t.wSecond > start_t.wSecond)	{
		if (end_t.wMilliseconds < start_t.wMilliseconds)	{
			fin_t.wSecond = end_t.wSecond - start_t.wSecond - 1;
			fin_t.wMilliseconds = end_t.wMilliseconds + (1000 - start_t.wMilliseconds);
		}
		else	{	//if (end_t.wMilliseconds >= start_t.wMilliseconds)	{
			fin_t.wSecond = end_t.wSecond - start_t.wSecond;
			fin_t.wMilliseconds = end_t.wMilliseconds - start_t.wMilliseconds;
		}
	}

	// DONE
	if (end_t.wSecond < start_t.wSecond)	{
		if (end_t.wMilliseconds < start_t.wMilliseconds)	{
			fin_t.wSecond = end_t.wSecond + (60 - start_t.wSecond) - 1;
			fin_t.wMilliseconds = end_t.wMilliseconds + (1000 - start_t.wMilliseconds);
		}
		else	{	//if (end_t.wMilliseconds >= start_t.wMilliseconds)	{
			fin_t.wSecond = end_t.wSecond + (60 - start_t.wSecond);
			fin_t.wMilliseconds = end_t.wMilliseconds - start_t.wMilliseconds;
		}
	}

	// DONE
	if (end_t.wSecond == start_t.wSecond)	{
		if (end_t.wMilliseconds < start_t.wMilliseconds)	{
			throw "TIME IS BROKEN; END BEFORE STARTING";
		}
		else	{	//if (end_t.wMilliseconds >= start_t.wMilliseconds)	{
			fin_t.wSecond = end_t.wSecond - start_t.wSecond;
			fin_t.wMilliseconds = end_t.wMilliseconds - start_t.wMilliseconds;
		}
	}

	tuple<int,int> secmil;
	tuple<int,int> minsec;
	secmil = real_time(make_tuple(end_t.wSecond, start_t.wSecond, 60),
						make_tuple(end_t.wMilliseconds, start_t.wMilliseconds,
						1000));
	minsec = real_time(make_tuple(end_t.wMinute, start_t.wMinute, 60),
						make_tuple(end_t.wSecond, start_t.wSecond, 60));

	cout << fin_t.wMinute << ":" << fin_t.wSecond << ":" << fin_t.wMilliseconds  << endl;
	cout << get<0>(minsec) << ":" << get<0>(secmil) << ":" << get<1>(secmil)  << endl;
	
}


// Testing functions, requires Sorting functions to be function objects that
// take an array as input.
struct test_single_sort	{
	template<class S, class T>
	void operator()(S func, string funcTitle, tuple<T*, string> testCase)	{
		GetLocalTime(&start_t);
		func(get<0>(testCase));
		GetLocalTime(&end_t);
		string something = funcTitle +"-"+ get<1>(testCase);
		print_performance(something);
		is_sorted(get<0>(testCase), something);
	}
};
struct test_all	{
	template<class T>
	void operator()(vector<tuple<function<void(int*)>, string>> sorts, 
					vector<tuple<T*, string>> tests)	{
		test_single_sort test_func;		
		// Loop through each sorting function in 'sorts' vector
		for (auto inputFunc = sorts.begin(); inputFunc != sorts.end(); ++inputFunc)	{
			// Reset the arrays for each function
			reset_arrays();
			// Loop through all the test cases in the 'tests' vector
			for (auto inputCase = tests.begin(); inputCase != tests.end(); ++inputCase)	
			{
				test_func(get<0>(*inputFunc), get<1>(*inputFunc), *inputCase);
			}
		}
	}
};



#endif