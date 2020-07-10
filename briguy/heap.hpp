#include "heap.h"

template <typename T>
T briguy::heap<T>::pop()
{
	if (is_empty()) { throw DeleteWhileEmptyException(); }
	if (n == (capacity / 4)) { shrink(); }
	T value = arr[1];
	swap(1, n--);
	sink(1);
	return value;
}

template <typename T>
void briguy::heap<T>::insert(T const& val)
{
	if (n == capacity) { grow(); }
	arr[++n] = val;
	swim(n);
}
template <typename T>
size_t briguy::heap<T>::size() const
{
	return n;
}

template <typename T>
bool briguy::heap<T>::is_empty() const
{
	return size() == 0;
}

// -------------------------------- private method definitions ---------------------------

template <typename T>
void briguy::heap<T>::sink(size_t indx)
{
	size_t chosenSon;
	while (true)
	{
		
		if (indx * 2 + 1 <= n)
			chosenSon = (pred(arr[indx * 2], arr[indx * 2 + 1])) ? indx * 2 : indx * 2 + 1;
		else if (indx * 2 == n)
			chosenSon = indx * 2;
		else
			break;
		heap::swap(chosenSon, indx);
		indx = chosenSon;

	}
}

template <typename T>
void briguy::heap<T>::swim(size_t indx)
{
	while (indx / 2 > 0 && !pred(arr[indx / 2], arr[indx]))
	{
		heap::swap(indx,indx/2);
		indx /= 2;
	}
}

template <typename T>
void briguy::heap<T>::swap(size_t a, size_t b)
{
	T temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;
}

template <typename T>
void briguy::heap<T>::grow()
{
	capacity *= 2;
	T* newArr = new T[capacity];
	for (size_t i = 1; i <= n; ++i)
	{
		newArr[i] = newArr[i];
	}
	delete arr;
	arr = newArr;
}

template <typename T>
void briguy::heap<T>::shrink()
{
	capacity /= 2;
	T* newArr = new T[capacity];
	for (size_t i = 1; i <= n; ++i)
	{
		newArr[i] = arr[i];
	}
	delete arr;
	arr = newArr;
}