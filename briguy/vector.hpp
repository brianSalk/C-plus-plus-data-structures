#include "vector.h"
template<typename T>
inline briguy::vector<T>::~vector()
{
	if (capacity > 0)
	{
		delete[] arr;
	}
}
template <typename T>
void briguy::vector<T>::grow()
{
	capacity *= 2;
	copy_arr();
}
template <typename T>
void briguy::vector<T>::shrink()
{
	capacity /= 2;
	copy_arr();
}

template <typename T>
void briguy::vector<T>::copy_arr()
{
	T* newArr = new T[capacity];
	for (size_t i = 0; i < n; ++i)
	{
		newArr[i] = arr[i];
	}
	delete[] arr;
	arr = newArr;
}
// -------------- PUBLIC MEMBERS --------------------------- //

template<typename T>
briguy::vector<T>::vector(std::initializer_list<T> il)
	: n(il.size()), capacity(il.size() * 2)
{
	arr = new T[capacity];
	size_t i = 0;
	for (T const& each : il) { arr[i++] = each; }
}

template <typename T>
briguy::vector<T>::vector(vector const& that)
{
	// if the array contains any data, erase it
	if (this->n != 0) { delete[] this->arr; }
	// allocate new array
	T* newArr = new T[that.capacity];
	// copy 'that' array values into the newArray
	for (size_t i = 0; i < that.n; ++i)
	{
		newArr[i] = that.arr[i];
	}
	// don't forget to point this->arr to newArr and copy all other data members!
	this->arr = newArr;
	this->n = that.n;
	this->capacity = that.capacity;
}
template <typename T>
briguy::vector<T>::vector(vector&& that)
{
	this->n = that.n;
	this->capacity = that.capacity;
	this->arr = that.arr;
	that.arr = nullptr;
}
template <typename T>
void briguy::vector<T>::operator=(vector const& that)
{
	if (this->capacity != 0) { delete this->arr; }
	this->n = that.n;
	this->capacity = that.capacity;
	this->arr = new T[capacity];
	for (size_t i = 0; i < n; ++i)
	{
		this->arr[i] = that.arr[i];
	}
}
template <typename T>
void briguy::vector<T>::operator=(vector&& that)
{
	if (this->capacity != 0) { delete this->arr; }
	this->n = that.n;
	this->capacity = that.capacity;
	this->arr = that.arr;
	that.arr = nullptr;
}

template <typename T>
void briguy::vector<T>::push_back(T const& value)
{
	if (n == capacity) { grow(); }
	arr[n++] = value;
}

template <typename T>
void briguy::vector<T>::push_back(T&& value)
{
	if (n == capacity) { grow(); }
	arr[n++] = std::move(value);
}

template <typename T>
void briguy::vector<T>::pop_back()
{
	if (n == capacity / 4) { shrink(); }
	--n;
}

template <typename T>
inline T& briguy::vector<T>::operator[](size_t index) const
{
	return arr[index];
}
template <typename T>
inline T& briguy::vector<T>::at(size_t index) const
{
	if (index >= n) { throw briguy::OutOfBoundsException(); }
	return arr[index];
}
template <typename T>
void briguy::vector<T>::insert(size_t index, T const value)
{
	if (n == capacity) { grow(); }
	for (size_t i = n; i > index; --i)
	{
		arr[i] = arr[i - 1];
	}
	arr[index] = value;
	++n;
}
template <typename T>
void briguy::vector<T>::remove(size_t index)
{
	if (n == capacity / 4) { shrink(); }
	for (size_t i = index; i < n-1; ++i)
	{
		arr[i] = arr[i + 1];
	}
	--n;
}

template <typename T>
template <typename Iterator, typename Predicate>
void briguy::vector<T>::remove_if(Iterator first, Iterator last, Predicate pred)
{
	// initialize iterator 'it' to first
	typename briguy::vector<T>::iterator it = first;
	size_t range = last - first;
	if (range <= 0) { return; }
	size_t num_removed = 0;
	size_t times_looped = 0;
	
	for (; it != last; ++it)
	{
		
		while (pred(*(it + num_removed)) && (times_looped + num_removed) < range )
		{
			num_removed++;
		}
		*it = *(it + num_removed);
		times_looped++;
	}
	// the 'removed' elements have been pushed to iterator (last - num_removed).
	// if last is not the elements end, move contents of last to the end of the container
	if (last != this->end())
	{
		// DELETE ME: data dump
		// for (auto it = begin(); it != end(); ++it) { std::cout << *it << std::endl; }
		it = this->begin() + (range - num_removed );
		// std::cout << "range: " << (range) << std::endl;
		for (; it != (this->end() - num_removed); ++it)
		{
			// std::cout << "in loop" << std::endl;
			*it = *(it + num_removed);
		}
	}
	n -= num_removed;
	// now shrink to lowest size possible
	while (n <= (capacity / 4))
	{
		capacity /= 2;
	}
	shrink();
}