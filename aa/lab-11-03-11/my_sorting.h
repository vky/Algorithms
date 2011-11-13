#ifndef MY_SORTING_H
#define MY_SORTING_H
#include "helper.h"

template<class T> // No bounds checking, rather dangerous.
void swap(T* input, int a, int b)	{
	T temp;
	temp = input[a];
	input[a] = input[b];
	input[b] = temp;
}

template<class T>
bool is_sorted_b(T input[])	{
	bool sorted = true;

	for ( int z = 0; z < INPUT_SIZE-1; z++ )	{
		if (input[z] > input[z+1])	{
			sorted = false;
			return sorted;
		}
	}
	
	return sorted;
}

// Sorting methods
void insertion(int* input)	{
	for ( int j=1; j < INPUT_SIZE; j++ )	{
		int key = input[j];
		int i = j-1;

		while ( i>=0 && input[i] > key )	{
			input[i+1] = input[i];
			i = i-1;
		}

		input[i+1] = key;
	}
}
void selection(int* input){
	if ( is_sorted_b(input) )
		return;

	int smallest	= input[0];
	int temp		= 0;
	for(int pos = 0; pos < INPUT_SIZE; pos++)	{
		smallest = pos;
		// Finding the smallest number
		for (int i = pos+1; i < INPUT_SIZE; i++)	{
			if (input[i] < input[smallest])	{
				smallest = i;
			}
		}

		// Swapping
		if (smallest != pos)	{
			temp = input[pos];
			input[pos] = input[smallest];
			input[smallest] = temp;
		}
	}
}

int partition(int* input, int p, int r)	{
	int x = input[r];
	int i = p - 1;
	for (int j = p; j <= r-1; j++)	{
		if (input[j] <= x)	{
			i = i+1;
			// swapping A[i] with A[j]
			swap(input, i, j);
		}
	}
	// swapping A[i+1] with A[r]
	swap(input, i+1, r);
	return i+1;
}

// Recursive, does not work for large inputs.
void quick(int* input, int p, int r)	{
	int q;
	if (p < r)	{
		q = partition(input, p ,r);
		quick(input, p, q-1);
		quick(input, q+1, r);
	}
}


void tail_quick(int* input, int p, int r)	{
	print_array(input);
	while (p < r)	{
		int q = partition(input, p, r);
		tail_quick(input, p, q-1);
		p = q+1;
	}
}
#endif