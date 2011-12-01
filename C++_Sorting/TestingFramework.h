#ifndef TESTINGFRAMEWORK_H
#define TESTINGFRAMEWORK_H

#include <Windows.h>
#include <iostream>
#include <string>
#include <iomanip>

#include <time.h>
#include <vector>
#include <tuple>
#include <algorithm>
#include <functional>

using namespace std;


//const int MERGE_MAX = 51000;
const int MAX_INT = 100000;

// Global variables, will be used by multiple functions.
//const int INPUT_SIZE = 20;		// For verification.
const int INPUT_SIZE = 100000;

int increasing[INPUT_SIZE];
int decreasing[INPUT_SIZE];
int random[INPUT_SIZE];


SYSTEMTIME start_t, end_t;


// Helper Functions
template<typename T>	// Useful for testing with INPUT_SIZE = 20
void print_array(T input[])	{
	for(int i = 0; i<INPUT_SIZE; i++)	{
		cout << input[i] << " ";
	}
	cout << endl;
}
template<typename T>
void is_sorted(T input[])	{
	bool sorted = true;
	for ( int z = 0; z < INPUT_SIZE-1; z++ )	{
		if (input[z] > input[z+1])	{
			cout << setw(3) << /*sortTitle <<*/ " N ";
			//std::cout << "Breaks down: " << z << " | " <<input[z] <<".\n" << std::endl;
			sorted = false;
			break;
		}
	}
	if (sorted == true)	{
		cout << setw(3) << /*sortTitle <<*/ " Y ";
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
// see timer.txt for the original mockup that was based off of above scenarios.
tuple<int,int> real_time( tuple<int, int, int> sec, tuple<int, int, int> mil )	{
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
			throw "TIME IS BROKEN; END BEFORE START!";
		}
		else	{
			get<0>(total) = get<0>(sec) - get<1>(sec);
			get<1>(total) = get<0>(mil) - get<1>(mil);
		}
	}

	return total;
}
// Print the time taken based off of time before and after a function call.
void print_performance()	{
	tuple<int,int> secmil;
	tuple<int,int> minsec;
	secmil = real_time(make_tuple(end_t.wSecond, start_t.wSecond, 60),
						make_tuple(end_t.wMilliseconds, start_t.wMilliseconds,
						1000));
	minsec = real_time(make_tuple(end_t.wMinute, start_t.wMinute, 60),
						make_tuple(end_t.wSecond, start_t.wSecond, 60));

	cout << setw(7) << get<0>(minsec) << ":" << setw(2) << get<0>(secmil) << ":" << setw(3) << get<1>(secmil);
}


// Testing functions, requires Sorting functions to be function objects that
// take an array as input.
struct test_single_sort	{
	template<class S, class T>
	void operator()(S func, tuple<T*, string> testCase)	{
		GetLocalTime(&start_t);
		func(get<0>(testCase));
		GetLocalTime(&end_t);
		print_performance();
		is_sorted(get<0>(testCase));
	}
};
struct test_all	{
	template<class T>
	void operator()(vector<tuple<function<void(int*)>, string>> sorts, 
					vector<tuple<T*, string>> tests)	{
		test_single_sort test_func;
		cout << setw(16) <<" ";
		for (auto inputCase = tests.begin(); inputCase != tests.end(); ++inputCase)	
		{
			cout << setw(16) << get<1>(*inputCase);
		}
		cout << endl;
		// Loop through each sorting function in 'sorts' vector
		for (auto inputFunc = sorts.begin(); inputFunc != sorts.end(); ++inputFunc)	{
			// Reset the arrays for each function
			reset_arrays();
			cout << setw(16) << get<1>(*inputFunc);
			// Loop through all the test cases in the 'tests' vector
			for (auto inputCase = tests.begin(); inputCase != tests.end(); ++inputCase)	
			{
				test_func(get<0>(*inputFunc), *inputCase);
			}
			cout << endl;
		}
	}
};



#endif