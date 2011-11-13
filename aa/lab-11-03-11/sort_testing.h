#ifndef SORT_TESTING_H
#define SORT_TESTING_H
#include "helper.h"
#include "my_sorting.h"
#include "template_sorting.h"

// Testing functions for simple sorting methods
void test_insertion()	{
	reset_arrays();

	GetLocalTime(&start);
	insertion(increasing);
	GetLocalTime(&end);
	print_performance("Insertion-Increasing");
	is_sorted(increasing, "Insertion-Increasing");

	GetLocalTime(&start);
	insertion(decreasing);
	GetLocalTime(&end);
	print_performance("Insertion-Decreasing");
	is_sorted(decreasing, "Insertion-Decreasing");

	GetLocalTime(&start);
	insertion(random);
	GetLocalTime(&end);
	print_performance("Insertion-Random");
	is_sorted(random, "Insertion-Random");
}
void test_selection()	{
	reset_arrays();

	GetLocalTime(&start);
	selection(increasing);
	GetLocalTime(&end);
	print_performance("Selection-Increasing");
	is_sorted(increasing, "Selection-Increasing");

	GetLocalTime(&start);
	selection(decreasing);
	GetLocalTime(&end);
	print_performance("Selection-Decreasing");
	is_sorted(decreasing, "Selection-Decreasing");

	GetLocalTime(&start);
	selection(random);
	GetLocalTime(&end);
	print_performance("Selection-Random");
	is_sorted(random, "Selection-Random");
}
void test_quick()	{
	reset_arrays();

	GetLocalTime(&start);
	quick(increasing, 1, INPUT_SIZE-1);
	GetLocalTime(&end);
	print_performance("Quick Sort-Increasing");
	is_sorted(increasing, "Quick Sort-Increasing");

	GetLocalTime(&start);
	quick(decreasing, 0, INPUT_SIZE);
	GetLocalTime(&end);
	print_performance("Quick Sort-Decreasing");
	is_sorted(decreasing, "Quick Sort-Decreasing");

	GetLocalTime(&start);
	quick(random, 0, INPUT_SIZE-1);
	GetLocalTime(&end);
	print_performance("Quick Sort-Random");
	is_sorted(random, "Quick Sort-Random");
}

void test_tail_quick()	{
	reset_arrays();

	GetLocalTime(&start);
	tail_quick(increasing, 0, INPUT_SIZE-1);
	GetLocalTime(&end);
	print_performance("Quick Sort-Increasing");
	is_sorted(increasing, "Quick Sort-Increasing");

	GetLocalTime(&start);
	tail_quick(decreasing, 0, INPUT_SIZE-1);
	GetLocalTime(&end);
	print_performance("Quick Sort-Decreasing");
	is_sorted(decreasing, "Quick Sort-Decreasing");

	GetLocalTime(&start);
	tail_quick(random, 0, INPUT_SIZE-1);
	GetLocalTime(&end);
	print_performance("Quick Sort-Random");
	is_sorted(random, "Quick Sort-Random");
	
}

// Testing functions for template sorting methods
void test_template_selection()	{
	reset_arrays();

	GetLocalTime(&start);
	selection_sort(increasing, 0 , INPUT_SIZE, compare_class());
	GetLocalTime(&end);
	print_performance("Template Selection-Increasing");
	is_sorted(increasing, "Template Selection-Increasing");

	GetLocalTime(&start);
	selection_sort(decreasing, 0 , INPUT_SIZE, compare_class());
	GetLocalTime(&end);
	print_performance("Template Selection-Decreasing");
	is_sorted(decreasing, "Template Selection-Decreasing");

	GetLocalTime(&start);
	selection_sort(random, 0 , INPUT_SIZE, compare_class());
	GetLocalTime(&end);
	print_performance("Template Selection-Random");
	is_sorted(random, "Template Selection-Random");
}


#endif