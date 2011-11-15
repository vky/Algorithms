#ifndef MY_SORTING_H
#define MY_SORTING_H

// Insertion Sort
// Selection Sort
// Quick Sort
// Merge Sort
// Heap Sort
// Counting Sort
// Radix Sort

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
struct insertion	{
	template<class T>
	void operator()(T* input){
		for ( T j=1; j < INPUT_SIZE; j++ )	{
			T key = input[j];
			T i = j-1;

			while ( i>=0 && input[i] > key )	{
				input[i+1] = input[i];
				i = i-1;
			}

			input[i+1] = key;
		}
	}
};
struct selection	{
	template<class T>
	void operator()(T* input){
		if ( is_sorted_b(input) )
			return;

		T smallest	= input[0];
		int temp		= 0;
		for(T pos = 0; pos < INPUT_SIZE; pos++)	{
			smallest = pos;
			// Finding the smallest number
			for (T i = pos+1; i < INPUT_SIZE; i++)	{
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
};

#endif