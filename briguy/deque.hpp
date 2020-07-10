#include "deque.h"
using namespace briguy;
template <typename T>
deque<T>::deque(deque const& that)
{
	if (this->capacity != 0) { delete[] arr; }
	this->arr = new T[that.capacity];
	for (size_t i = front_ptr + 1; i <= back_ptr; ++i)
	{
		this->arr[i] = that.arr[i];
	}
	this->back_ptr = that.back_ptr;
	this->front_ptr = that.front_ptr;
	this->n = that.n;
	this->capacity = that.capacity;
}

template <typename T>
deque<T>::deque(deque<T>&& that)
{
	this->arr = that.arr;
	this->n = that.n;
	this->capacity = that.capacity;
	this->front_ptr = that.front_ptr;
	this->back_ptr = that.back_ptr;
	that.arr = nullptr;
}

template<typename T>
void deque<T>::operator=(deque<T> const& that)
{
	if (this->capacity != 0) { delete this->arr; }
	this->n = that.n;
	this->capacity = that.capacity;
	this->front_ptr = that.front_ptr;
	this->back_ptr = that.back_ptr;
	T* newArr = new T[capacity];
	for (size_t i = front_ptr; i <= back_ptr; ++i)
	{
		newArr[i] = that.arr[i];
	}
	this->arr = newArr;
	
}

template <typename T>
void deque<T>::operator=(deque&& that)
{
	this->n = that.n;
	this->front_ptr = that.front_ptr;
	this->back_ptr = that.back_ptr;
	this->capacity = that.capacity;
	this->arr = that.arr;
	that.arr = nullptr;
}

template<typename T>
void deque<T>::push_back(T const& val)
{
	if (back_ptr == capacity-1) { grow(); }
	arr[++back_ptr] = val;
	++n;
}

template<typename T>
void deque<T>::push_front(T const& val)
{
	if (front_ptr == 0) { grow(); }
	arr[--front_ptr] = val;
	++n;
}

template<typename T>
inline T const& deque<T>::peek_back() const
{
	return arr[back_ptr];
}

template<typename T>
inline T const& deque<T>::peek_front() const
{
	return arr[front_ptr];
}

template<typename T>
void deque<T>::remove_back()
{
	if (n == (capacity/4)) { shrink(); }
	--back_ptr;
	--n;
}

template<typename T>
void deque<T>::remove_front()
{
	// if front ptr is three-fourths of front size or more, divide front size by two
	if (n == (capacity/4)) { shrink(); }
	++front_ptr;
	--n;
}

template<typename T>
inline size_t deque<T>::size() const
{
	return n;
}

template<typename T>
inline bool deque<T>::is_empty() const
{
	return size() == 0;
}

template<typename T>
inline T deque<T>::get_front() const
{
	return arr[front_ptr];
}

template<typename T>
inline T deque<T>::get_back() const
{
	return arr[back_ptr];
}

// --------------------------- Private Method Definitions



template<typename T>
inline void deque<T>::grow()
{
	capacity *= 2;
	T* newArr = new T[capacity];
	// copy arr to middle newArr, readjust both front and back ptrs.
	for (size_t i = 0; i <= back_ptr - front_ptr; ++i)
	{
		newArr[(capacity/4)+i] = arr[front_ptr + i];
	}
	size_t ptr_dif = (back_ptr - front_ptr);
	front_ptr = capacity / 4;
	back_ptr = front_ptr + ptr_dif;
	delete[] arr;
	arr = newArr;
}



template<typename T>
void deque<T>::shrink()
{
	capacity /= 2;
	T* newArr = new T[capacity];
	size_t ptr_dif = back_ptr - front_ptr;
	for (size_t i = 0; i <= ptr_dif; ++i)
	{
		newArr[(capacity/4)+i] = arr[front_ptr+i];
	}
	front_ptr = (capacity / 4);
	back_ptr = front_ptr + ptr_dif;
	delete[] arr;
	arr = newArr;
}
