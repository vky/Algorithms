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
	{/**/}

	// Create vector that holds all of the test case tuples
	vector<tuple<int*, string>> testCases;
	testCases.push_back(case_increasing);
	testCases.push_back(case_decreasing);
	testCases.push_back(case_random);

	// Instantiate sorting functions
	selection s_selection;
	insertion s_insertion;
	S_Quick s_quick(0, INPUT_SIZE-1);
	S_Merge s_merge(0, INPUT_SIZE-1);
	S_Counting<int> s_count;
	S_Heap<int> s_heap;

	// Create 2-type tuples of sorting functions, function & function's title.
	sort_t selection_tuple(s_selection, "Selection");
	sort_t insertion_tuple(s_insertion, "Insertion");
	sort_t counting_tuple(s_count, "Counting Sort");
	sort_t heap_tuple(s_heap, "Heapsort");
	sort_t quick_tuple(s_quick, "Quick Sort");
	sort_t merge_tuple(s_merge, "Merge Sort");

	// Vector that holds all functions to be tested.
	vector<sort_t> sorting_functions;
	sorting_functions.push_back(selection_tuple);
	sorting_functions.push_back(insertion_tuple);
	sorting_functions.push_back(counting_tuple);
	sorting_functions.push_back(heap_tuple);
	//sorting_functions.push_back(merge_tuple);
	//sorting_functions.push_back(quick_tuple);

	// Instantiate testing functor.
	test_all testall;
	// Test.
	testall(sorting_functions, testCases);


	return 0;
}