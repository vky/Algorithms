#ifndef TEMPLATE_SORTING_H
#define TEMPLATE_SORTING_H

// Template Selection Sort - mostly provided
struct compare_class {
	template<class X>
	bool operator()(X A, X B) const {
		return A < B;
  }
};

template <class t> inline
void exch(t &X, t &Y ){
	t Z = X;
	X = Y;
	Y = Z;
}

template <class t, class cmp_t> inline
bool initial_minimum(t A[], size_t &R, cmp_t& IsSmaller )	{
	while(R--) 
		if( IsSmaller(A[R+1],A[R]) ) 
			return false;
	return true;
}
template <class t, class cmp_t> inline
bool select_exch(t A[], size_t R, cmp_t& IsSmaller)	{
	if( initial_minimum(A, R, IsSmaller) ) 
		return true;
	size_t Min = R + 1;
	while( R-- ) 
		if( IsSmaller(A[R],A[Min]) ) 
			Min = R;
	if( Min > 0 ) 
		exch( *A, A[Min] );
	return false;
}
template <class t, class cmp_t>
void selection_sort(t *A, size_t L, size_t R, cmp_t& IsSmaller){
	if( R <= L ) 
		return;
	A=A+L;
	R=R-L;
	do
		if( select_exch( A++, R--, IsSmaller ) ) 
			return;
	while( R );
}


#endif