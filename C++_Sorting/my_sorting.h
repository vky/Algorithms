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
template<class T> // No bounds checking, rather dangerous.
void swap(T* input, int a, int b) {
	T temp;
	temp = input[a];
	input[a] = input[b];
	input[b] = temp;
}
// Helper Function
template<class T>	// Useful for testing with INPUT_SIZE = 20
void temp_print(T input[])	{
	for(int i = 0; i<INPUT_SIZE; i++)	{
		std::cout << input[i] << " ";
	}
	std::cout << std::endl;
}


// Sorting methods

// Will want to rewrite insertion and selection structs as classes that take
// min/max initializer values like Quick Sort, rather than depending on 
// compiler magic for max with INPUT_SIZE global constant.
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
class Quick	{
private:
	int p;
	int r;

public:
	Quick(int left, int right)	{
		p = left;
		r = right;
	}

	int partition(int* input, int p, int r) {
		int x = input[r];
		int i = p - 1;
		for (int j = p; j <= r-1; j++) {
			if (input[j] <= x) {
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
	void quick(int* input, int p, int r) {
		int q;
		if (p < r) {
			q = partition(input, p ,r);
			quick(input, p, q-1);
			quick(input, q+1, r);
		}
	}

	void operator()(int* input)	{
		if (is_sorted_b(input))
			return;

		quick(input, p, r);
	}
};

#endif