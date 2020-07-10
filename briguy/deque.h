#pragma once
namespace briguy
{
	template<typename T>
	class deque
	{
	public:
		// forward iterator const
		class iterator;
		// reverse_iterator const
		class reverse_iterator;

		deque() : n(0), capacity(2),
			front_ptr(1), back_ptr(0) {
			arr = new T[capacity];
		}
		deque(size_t cpt) : n(0), capacity(cpt),
			front_ptr((cpt / 2) + 1), back_ptr(cpt / 2) {
			arr = new T[capacity];
		}
		deque(deque const&);
		deque(deque&& that);

		void operator=(deque const& that);
		void operator=(deque&& that);

		void push_back(T const&);
		void push_front(T const&);

		T const& peek_back() const;
		T const& peek_front() const;

		void remove_back();
		void remove_front();

		size_t size() const;
		bool is_empty() const;

		T get_front() const;
		T get_back() const;

		iterator const begin() const { return iterator(arr + front_ptr); }
		iterator const end() const { return iterator(arr + back_ptr + 1); }

		reverse_iterator const rbegin() const { return reverse_iterator(arr + back_ptr); }
		reverse_iterator const rend() const { return reverse_iterator(arr + front_ptr - 1); }

		~deque() { if (capacity != 0) { delete[] arr; } }
	private:
		size_t n;
		size_t capacity;
		size_t front_ptr;
		size_t back_ptr;
		T* arr;


		// if front_ptr equals 0 or back_ptr equals (capacity-1) double capacity of deque
		void grow();

		// if n equals (capacity/4) halve the capacity of deque
		void shrink();
		// -------------------------- iterator definition ---------------------------------------------------
	public:
		class iterator
		{
		public:
			typedef ptrdiff_t                 difference_type;
			typedef std::forward_iterator_tag iterator_category;
			typedef T const* pointer;
			typedef T                         value_type;
			typedef T const& reference;

			iterator(pointer ptr) : curr(ptr) {}

			reference operator*() { return *curr; }
			bool operator != (iterator const& that) { return this->curr != that.curr; }
			// prefix incrament operator
			iterator const& operator++()
			{
				++curr;
				return *this;
			}
			// postfix incrament operator
			iterator const operator++(int)
			{
				return ++ * this;
			}
		protected:
			pointer curr;
		};
		// -------------------------------------- reverse_iterator -----------------------------------------------
		class reverse_iterator : public iterator
		{
		public:
			

			reverse_iterator(iterator::pointer c) : iterator(c) {}
			bool operator!=(reverse_iterator const& that) const { return this->iterator::curr != that.iterator::curr; }
			// prefix incrament operator
			reverse_iterator const& operator++()
			{
				--iterator::curr;
				return *this;
			}
			// postfix incrament operator
			reverse_iterator const operator++(int)
			{
				return ++ * this;
			}
		};
	};
}
#include "deque.hpp"