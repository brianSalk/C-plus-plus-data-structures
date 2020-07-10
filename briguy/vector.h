#pragma once
#include "OutOfBoundsException.h"
#include<initializer_list>
namespace briguy
{
	template<typename T>
	class vector
		: protected OutOfBoundsException
	{
	public:
		/// forward declarations of iterators
		// random access iterator
		class iterator;
		// random access iterator used for reverse traversal of vector elements
		class reverse_iterator;
		// initializer_list constructor
		vector(std::initializer_list<T> il);// : capacity(il.size() * 2), n(il.size());
		
		// zero arg constructor, initializes the capacity to 2 and the size to zero.
		vector() : n(0), capacity(2) { arr = new T[capacity]; }
		/* one arg constructor, this differs from the STL vector provided by C++
			because it does not affect the size of the vector, rather it changes the 
			amount of space allocated by the vectors underlying array.
		*/
		vector(size_t initCapacity) : n(0), capacity(initCapacity) { arr = new T[capacity]; }
		/*
			two arg construcor, this is a fill constructor meant to mimic the behavior of
			 the two arg constructor of the STL vector
		*/
		vector(size_t initCapacity, T fillValue) : n(initCapacity), capacity(initCapacity) 
		{ 
			arr = new T[capacity];
			for (size_t i = 0; i < n; ++i) { arr[i] = fillValue; }
		}
		/*
			Copy constructor, because this data structure contains its own custom constructor(s)
			and destructor, it should also contain its own custom copy constructor
		*/
		vector(vector const& that);
		
		/* move constructor, when invoked, can obviate the need to copy the old container
		   and instead moves the contents of the old container to the new container, leaving
		   the old container in unusable condition.
		*/
		vector(vector&& that);
		// custom assignment operator
		void operator=(vector const& that);
		// custom move assignment operator
		void operator=(vector&& that);
		/* adds a new value to the back of the vector, may also double the capacity if need be
			this operation is guarenteed linear amortized time complexity
		*/
		void push_back(T const& value);
		// move push_back
		void push_back(T&& value);
		/* decreases the size by one, halved the capacity if n == (capacity/4)
			it is important to halve the capacity when the array is one quarter full to 
			avoid thrashing
		*/
		void pop_back();
		/* overloaded [] operator  returns a refence to the ith element of the array
			returning a reference allows the client to use this operator as both a
			mutator and an observer
		*/
		T& operator[](size_t index) const;
		// same as operator[], except performs bounds checking, this is safer but also slower than operator[]
		T& at(size_t index) const;
		// allows client to insert one element to any position in the vector, linear time complexity in worst case
		void insert(size_t index, T const value);
		// allows client to remove any element in the vector, linear time complexity in worst case
		void remove(size_t index);
		// allows client to remove any number of elements that meet a condition,  linear time complexity in worst case
		template <typename Iterator, typename Predicate>
		void remove_if(Iterator first, Iterator last, Predicate pred);
		// returns size of vector
		size_t size() const { return n; }

		/* iterator methods */
		// returns an iterator to the begining of the vector
		const iterator begin() const { return iterator(arr); }
		// returns an iterator one passed the end of the vector
		const iterator end() const { return iterator(arr + n); }
		// returns a reverse iterator to the reverse begining (or end) of the vector
		const reverse_iterator rbegin() const { return reverse_iterator(arr+(n-1)); }
		// returns a reverse iterator to one passed the reverse end (or one before the begining) of the vector
		const reverse_iterator rend() const { return reverse_iterator(arr -1); }

		// custom destructor
		~vector();
		
	private:
		T* arr;
		size_t n;
		size_t capacity;
		// doubles the capacity of the vector
		void grow();
		// halves the capacity of the vector
		void shrink();
		// used within grow() and shrink().  this method reduces repeated code while making code
		// more expressive by hiding implementation detatails
		void copy_arr();
	public:
		
		// define iterator here:
		class iterator
		{
		public:
			// each iterator must contain the five following typedefs 
			// in order to be compatible with stl algorithms
			typedef ptrdiff_t                       difference_type;
			typedef std::random_access_iterator_tag iterator_category;
			typedef T                               value_type;
			typedef T*                              pointer;
			typedef T&                              reference;
			// constructors
			iterator() {}
			iterator(T* ptrVal) : curr(ptrVal) {}
			// arithmetic operators
			iterator operator+=(int increase) { curr += increase; return iterator(curr); }
			iterator operator-=(int decrease) { curr -= decrease; return iterator(curr); }
			iterator operator + (int increase) const { return iterator(curr + increase); }
			iterator operator - (int decrease) const { return iterator(curr - decrease); }
			difference_type operator - (iterator const& that) const { return (long(this->curr) - long(that.curr)) / sizeof(T); }
			
			// pointer-related operators
			reference operator[](size_t i) { return *(curr+i); }
			reference operator*() { return *curr; }
			// value comparison operators
			bool operator <  (iterator const& that) const { return *(this->curr) < *(that.curr); }
			bool operator >  (iterator const& that) const { return *(this->curr) > *(that.curr); }
			bool operator >= (iterator const& that) const { return *(this->curr) >= *(that.curr); }
			bool operator <= (iterator const& that) const { return *(this->curr) <= *(that.curr); }
			// address comparison operators
			bool operator != (iterator that) const { return (this->curr != that.curr); }
			bool operator == (iterator that) const { return (this->curr == that.curr); }

			// prefix decrament operator
			iterator& operator--()
			{
				curr--;
				return *this;
			}
			// post-fix decrament operator
			iterator operator--(int)
			{
				curr--;
				return *this;
			}
			// prefix incrament operator
			iterator& operator++()
			{
				curr++;
				return *this;
			}
			// post-fix operator
			iterator operator++(int)
			{
				curr++;
				return *this;
			}
			// assignment operator
			void operator=(iterator that) { (this->curr) = (that.curr); }
			
		protected: 
			// curr is protected not private because reverse_iterator to allow reverse iterator to access it
			pointer curr; 
		};
		class reverse_iterator : public iterator
		{
		public:
			reverse_iterator() {}
			reverse_iterator(iterator::pointer valuePtr) : iterator(valuePtr) {}
			//prefix incrament operator
			reverse_iterator& operator++()
			{
				iterator::curr--;
				return *this;
			}
			// postfix incrament operator
			reverse_iterator operator++(int) 
			{
				return ++*this;
			}
			// prefix decrament operator
			reverse_iterator& operator--()
			{
				iterator::curr++;
				return *this;
			}
			// postfix decrament operator
			reverse_iterator operator--(int)
			{
				return -- * this;
			}
			// arithmetic operators
			reverse_iterator& operator+=(int increase) { iterator::curr -= increase; return reverse_iterator(iterator::curr); }
			reverse_iterator& operator-=(int decrease) { iterator::curr += decrease; return reverse_iterator(iterator::curr); }
			reverse_iterator operator + (int increase) const { return reverse_iterator(iterator::curr - increase); }
			reverse_iterator operator - (int decrease) const { return reverse_iterator(iterator::curr + decrease); }
			iterator::difference_type operator - (iterator const& that) const { return (long(this->curr) - long(that.curr)) / sizeof(T); }
		};
		
	};
}
#include "vector.hpp"