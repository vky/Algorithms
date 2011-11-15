// Author: Vijay Korapaty
// Date: 11-4-11
// Title: Sorting.cpp
// Description: Testing insertion, selection, and quick sort performance.

#include "TestingFramework.h"

int main()	{
	srand ( time(NULL) );

	// Create tuples of the various test cases.
	tuple<int*, string> case_increasing(increasing, "Increasing");
	tuple<int*, string> case_decreasing(decreasing, "Decreasing");
	tuple<int*, string> case_random(random, "Random");
	/*
	// These could also be written as follows:
	auto case_increasing = make_tuple(increasing, "Increasing");
	auto case_decreasing = make_tuple(decreasing, "Decreasing");
	auto case_random = make_tuple(random, "Random");
	/* This version in comments looks cleaner, but the one being used feels
	 more informative; it is not necessary to search for the declaration
	 of the arrays to determine what their types are, it is in the tuple 
	 definition.
	*/

	// Create vector that holds all of the test case tuples
	vector<tuple<int*, string>> testCases;
	testCases.push_back(case_increasing);
	testCases.push_back(case_decreasing);
	testCases.push_back(case_random);

	// Create tuples of sorting functions to be tested.
	selection s_selection;
	insertion s_insertion;
	Quick s_quick(0, INPUT_SIZE-1);

	tuple<function<void(int*)>, string> selection_tuple(s_selection, 
		"Selection");
	tuple<function<void(int*)>, string> insertion_tuple(s_insertion, 
		"Insertion");
	tuple<function<void(int*)>, string> quick_tuple(s_quick, "Quick Sort");

	// Vector that holds all functions to be tested.
	vector<tuple<function<void(int*)>, string>> sorting_functions;
	//sorting_functions.push_back(selection_tuple);
	//sorting_functions.push_back(insertion_tuple);
	sorting_functions.push_back(quick_tuple);
	test_all testall;

	testall(sorting_functions, testCases);


	return 0;
}