#pragma once

namespace briguy
{
	template <typename T, size_t N>
	class ringQueue
	{
	public:
		class iterator;
		

		ringQueue() : front_ptr(0), back_ptr(0), n(N + 1) {}
		void enqueue(T const&);
		void dequeue();

		T const& peek() const { return arr[front_ptr]; }
		T get() const { return arr[front_ptr]; }

		bool is_empty() { return front_ptr == back_ptr; }

		iterator const begin(){ return iterator(arr,front_ptr); }
		iterator const end()  { return iterator(arr, back_ptr); }
		iterator const cbegin() { return iterator(arr, 0); }
		iterator const cend() { return iterator(arr, n); }
	private:
		T arr[N+1];
		size_t front_ptr;
		size_t back_ptr;
		size_t n;
	public:
		class iterator
		{
		public:
			typedef T                         value_type;
			typedef std::forward_iterator_tag iterator_category;
			typedef ptrdiff_t                 difference_type;
			typedef T*                        pointer;
			typedef T const&                  reference;

			iterator(pointer a, size_t i) : arr(a), index(i){}

			reference operator *() const { return arr[index]; }
			bool operator !=(iterator const& that) const { return (arr + this->index) != (arr + that.index); }

			// perfix incrament operator
			iterator const& operator++()
			{
				if (&arr[++index] == &arr[N+1]) { index = 0; }
				return *this;
			}
			// suffix incrament operator
			iterator const operator++(int) { return ++ * this; }

		private:
			size_t index;
			pointer arr;

		};
	};
}

#include "ringQueue.hpp"
