// Author: Vijay Korapaty
// Date: 11-4-11
// Title: Sorting.cpp
// Description: Testing insertion, selection, and quick sort performance.

#include <time.h>
#include "sort_testing.h"

int main()	{
	srand ( time(NULL) );

	std::cout << "Time tracking is done in minutes:seconds:milliseconds."
		<< std::endl;
	 
	std::cout << "\nInsertion Sort:";
	test_insertion();
	
	std::cout << "\n\nSelection Sort:";
	test_selection();
	
	std::cout << "\n\nTemplate Selection Sort:";
	test_template_selection();
	/*
	std::cout << "\n\nQuick Sort:";
	test_quick();
	*/

	return 0;
}

/* // Can this be done?
void test_sort(func function, (array1, arrayTitle1), (array2, arrayTitle2)
		(array3, arrayTitle3))	{

	map	{		// for each tuple, do the following with the given function.
		reset_arrays();

		GetLocalTime(&start);
		function(array);
		print_performance(arrayTitle);
		is_sorted(array, arrayTitle);
		GetLocalTime(&end);
	}

}
*/