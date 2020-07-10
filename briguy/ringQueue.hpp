#include "ringQueue.h"

template <typename T, size_t N>
void briguy::ringQueue<T, N>::enqueue(T const& val)
{
	arr[back_ptr++] = val;
	if (back_ptr == n) { back_ptr = 0; }
	if (back_ptr == front_ptr) { front_ptr++; }
	if (front_ptr == n) { front_ptr = 0; }
}

template <typename T, size_t N>
void briguy::ringQueue<T, N>::dequeue()
{
	if (front_ptr == back_ptr) { return; }
	if (front_ptr == N) { front_ptr = 0; return; }
	front_ptr++;
}

