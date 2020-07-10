#pragma once
#include <type_traits>
#include <string>
#include <iostream>

namespace briguy
{
	
	template <typename T>
	class hashSet
	{
		struct Node
		{
			T val;
			Node* next;
			Node(T const& v) : val(v), next(NULL) {}
		};
	public:
		class iterator;

		hashSet() : n(0) {}
		hashSet(hashSet const&);
		hashSet(hashSet&&);
		void operator=(hashSet const&);
		void operator=(hashSet&&);

		void put(T const& val);
		bool has(T const& val) const;
		void remove(T const& val);
		size_t size() const;
		void clear();

		iterator begin()
		{
			size_t index = ARR_SIZE;
			for (size_t i = 0; i < ARR_SIZE; ++i)
			{
				if (arr[i] != NULL)
				{
					index = i;
					break;
				}
			}
			return iterator(&arr[0],index); 
		}
		iterator end() { ; return iterator(&arr[0], ARR_SIZE); }
		~hashSet();

		
		

	private:
		static const size_t ARR_SIZE = 2000;
		Node* arr[ARR_SIZE]{};
		size_t n;

		void copy(hashSet const&);
		void mover(hashSet&);
		
		/*
			the following methods fare an example of template meta-programming.
			at compile time, the computer can call a different function overload depending on the type
			being passed in, this is very useful because different data types need to be
			hashed differently.  this also causes compiler errors when a type is not hashable,
			compile-time errors are prefered to run-time errors in most cases.

		*/
		size_t hash(T const& val) const;
		// this overload is called when the compiler has determined that the type is integral
		size_t _hash(T const& val, std::true_type) const;
		// this overload is called when the compiler has determined that the type is not integral
		size_t _hash(T const& val, std::false_type) const;
		// this overload is called when the compiler hash determined that the type is floating_point
		size_t __hash(T const& val, std::true_type) const;
		// this overload is called when the type is unknown, if the object being passed has no 'hash' method,
		// a compiler error will occure.
		size_t __hash(T const& val, std::false_type) const;
	public:
		class iterator
		{
		public:
			typedef ptrdiff_t                 difference_type;
			typedef std::forward_iterator_tag iterator_category;
			typedef T*                        pointer;
			typedef T                         value_type;
			typedef T&                        reference;

			iterator() {};
			iterator(Node** c, size_t i) : curr(c), incrament(i) { }

			reference operator*() { return curr[incrament]->val; }
			bool operator!=(iterator that) 
			{ 
				return (this->curr[this->incrament] != that.curr[that.incrament]); 
			}
			iterator const& operator++()
			{
				while (curr[++incrament] == NULL) {}
				return *this;
			}
			iterator const operator++(int) 
			{
				while (curr[++incrament] == NULL) {}
				return *this;
			}

		private:
			size_t incrament;
			Node** curr;
			Node* local_curr;
		};
	};

	
}
#include "hashSet.hpp"
