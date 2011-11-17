// Author: Vijay Korapaty
// Date: 11-4-11
// Title: Sorting.cpp
// Description: Testing insertion, selection, and quick sort performance.

#include "TestingFramework.h"
#include "my_sorting.h"

typedef tuple<function<void(int*)>, string> sort_t;

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
	S_Quick s_quick(0, INPUT_SIZE-1);
	S_Merge s_merge(0, INPUT_SIZE-1);
	S_Counting<int> s_count;

	sort_t selection_tuple(s_selection, "Selection");
	sort_t insertion_tuple(s_insertion, "Insertion");
	sort_t quick_tuple(s_quick, "Quick Sort");
	sort_t merge_tuple(s_merge, "Merge Sort");
	sort_t counting_tuple(s_count, "Counting Sort");

	// Vector that holds all functions to be tested.
	vector<sort_t> sorting_functions;
	sorting_functions.push_back(selection_tuple);
	sorting_functions.push_back(insertion_tuple);
	sorting_functions.push_back(quick_tuple);
	//sorting_functions.push_back(merge_tuple);
	sorting_functions.push_back(counting_tuple);
	
	test_all testall;

	testall(sorting_functions, testCases);


	return 0;
}