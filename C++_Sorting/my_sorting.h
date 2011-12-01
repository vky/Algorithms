#ifndef MY_SORTING_H
#define MY_SORTING_H
#include "TestingFramework.h"
// Insertion Sort
// Selection Sort
// Quick Sort
// Heap Sort
// Counting Sort

// Merge Sort
// Radix Sort

template<typename T>
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
template<typename T> // No bounds checking, rather dangerous.
void swap(T* input, int a, int b) {
	T temp;
	temp = input[a];
	input[a] = input[b];
	input[b] = temp;
}
int exp(int d, int n)	{
	int t = 1;
	for (int i = n; i >= 1; i--)	{
		t*=d;
	}
	return t;
}
int digit(int a, int d)	{
	return (a%(exp(10,d)) - a%(exp(10,d-1))) / exp(10,d-1);
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
class S_Quick	{
private:
	int p;
	int r;

public:
	S_Quick(int left, int right)	{
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
template<class T>
class S_Heap{
private:
	int heap_size;
public:
	int parent(int i)	{
		return i/2;
	}
	int left(int i)	{
		return 2*i;
	}
	int right(int i)	{
		return 2*i +1;
	}

	void max_heapify(T* input, int i)	{
		int l = left(i);
		int r = right(i);
		int largest =0;
		if (l <= heap_size && input[l] > input[i])
			largest = l;
		else 
			largest = i;
		if (r <= heap_size && input[r] > input[largest])
			largest = r;
		if (largest != i)	{
			swap(input, i, largest);
			max_heapify(input, largest);
		}
	}

	void build_max_heap(T* input)	{
		heap_size = INPUT_SIZE-1;
		for (int i = (INPUT_SIZE-1)/2; i >= 0; i--)	{
			max_heapify(input, i);
		}
	}

	void operator()(T* input)	{
		if (is_sorted_b(input))
			return;

		build_max_heap(input);
		for (int i = INPUT_SIZE-1; i>=1; i--)	{
			swap(input, 0, i);
			heap_size = heap_size-1;
			max_heapify(input, 0);
		}
	}
};
template<class T>
class S_Counting{
private:
	T sorted[INPUT_SIZE];
	T temp[MAX_INT+1];
	//int sorted[100001];
	//int temp[100001];
public:
	void operator()(T* input)	{
		for (int i = 0; i <= MAX_INT; i++)	{
			temp[i] = 0;
		}
		for (int j = 0; j < INPUT_SIZE; j++)	{
			temp[input[j]]++;
		}
		for (int i = 1; i <= MAX_INT; i++)	{
			temp[i] += temp[i-1];
		}
		for (int j = INPUT_SIZE-1; j >= 0; j--)	{
			sorted[temp[input[j]]-1] = input[j];
			temp[input[j]] = temp[input[j]]-1;
		}
		// Extra for loop to copy the sorted array back to the input array.
		// Testing function will not work if this function were to return
		// a new array.
		for (int i = 0; i < INPUT_SIZE; i++)	{
			input[i] = sorted[i];
		}
	}
};


// Pseudo-code provided by book, not fixed.
template<class T>
class S_Merge{
private:
	int left;
	int right;
	// Oversized arrays.
	int L[INPUT_SIZE];
	int R[INPUT_SIZE];
public:
	S_Merge(int p, int r)	{
		left = p;
		right = r;
	}
	
	
	void merge(T* input, int p, int q, int r)	{
		cout << p << " | " << q << " | " << r << endl;
		int n1 = 0;
		int n2 = 0;

		n1 = q - p + 1;
		n2 = r - q;

		// Set up two sub-arrays for comparison
		for (int i = 0; i < n1; i++)	{
			L[i] = input[p+i-1];
		}
		for (int j = 0; j < n2; j++)	{
			R[j] = input[q+j];
		}
		// Sentinels, not really sure how these should be implmented.
		//L[n2] = MERGE_MAX;
		//R[n2] = MERGE_MAX;

		//print_array(input);
		//cout << n1 << " | " << n2 << endl;
		int i = 0;
		int j = 0;
		for (int k = p; k <= r; k++)	{
			if (L[i] <= R[j])	{
				input[k] = L[i];
				i++;
			}
			else	{
				input[k] = R[j];
				j++;
			}
		}
	}

	void sort(T* input, int p, int r)	{
		if (p < r)	{
			int q = (p + r) / 2;
			sort(input, p, q);
			sort(input, q+1,r);
			merge(input, p, q, r);
		}
	}

	void operator()(T* input)	{
		if (is_sorted_b(input))
			return;

		sort(input, left, right);
	}
};

class Radix{

};
/**/
#endif