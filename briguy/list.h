#pragma once
#include "OutOfBoundsException.h"
#include <iostream>
#include <initializer_list>
#include <utility>
namespace briguy
{
	template <typename T>
	class list
		: public OutOfBoundsException
	{
		struct Node
		{
			Node* next;
			Node* prev;
			T val;
			template <typename ...Args>
			Node(Args&& ...args) : next(nullptr), prev(nullptr), val(std::forward<Args>(args)...) {}
			// Node(T const& v) : next(nullptr), prev(nullptr), val(v) {}
		};
	public:
		// bidirectional iterator
		class iterator;
		class reverse_iterator;
		class const_iterator;
		// constructor
		list() : n(0), head(NULL), tail(NULL) {}
		// initializer_list constructor
		list(std::initializer_list<T> il);
		// move constructor
		list(list<T>&& that);
		// copy constructor
		list(list const& that);

		void push_back(T const& val);
		void push_front(T const& val);
		template <typename ...Args>
		void emplace_back(Args&& ...args);
		template <typename ...Args>
		void emplace_front(Args&& ...args);

		void remove_back();
		void remove_front();

		void erase(briguy::list<T>::iterator const& it);
		void erase_range(briguy::list<T>::iterator const& first,
			briguy::list<T>::iterator const& last);

		void remove_first(iterator const& first, iterator const& last, T const& val);
		void remove_last (iterator const& first, iterator const& last, T const& val);
		void remove_all  (iterator const& first, iterator const& last, T const& val);
		template<typename Predicate>
		void remove_if(iterator const& first, iterator const& last, Predicate pred);

		void insert(iterator const& it, T const& val);
		template <typename ...Args>
		void emplace(iterator const& it, Args&& ...args);
		size_t size() const { return n; }

		iterator begin() const { return iterator(head); }
		iterator end() const { return iterator(NULL); }

		reverse_iterator rbegin() const { return reverse_iterator(tail); }
		reverse_iterator rend() const { return reverse_iterator(NULL); }

		~list();
	private:
		Node* head;
		Node* tail;
		size_t n;

		void _insert_node_after(iterator const& it, Node* newNode);

	public:
		class iterator
		{
			friend class list;
		public:
			typedef T                               value_type;         // V
			typedef std::bidirectional_iterator_tag iterator_category;  // I
			typedef ptrdiff_t                       difference_type;    // D
			typedef T*                              pointer;            // P
			typedef T&                              reference;          // R

			iterator(Node* c) : curr(c) {}

			reference operator*() const { return curr->val; }

			bool operator !=(iterator const& that) const { return this->curr != that.curr; }
			bool operator ==(iterator const& that) const { return this->curr == that.curr; }

			iterator& operator++()
			{
				curr = curr->next;
				return *this;
			}
			iterator operator++(int)
			{
				curr = curr->next;
				return *this;
			}
			iterator& operator--()
			{
				curr = curr->prev;
				return *this;
			}
			iterator operator--(int)
			{
				curr = curr->prev;
				return *this;
			}
			Node* operator->() const
			{
				return curr;
			}

		protected:
			Node* curr;
		};
		class reverse_iterator : public iterator
		{
			// friends are not inherited
			friend class list;
		public:
			reverse_iterator(Node* c) : iterator(c) {}
			reverse_iterator& operator++()
			{
				iterator::curr = iterator::curr->prev;
				return *this;
			}
			reverse_iterator operator++(int)
			{
				iterator::curr = iterator::curr->prev;
				return *this;
			}
			reverse_iterator& operator--()
			{
				iterator::curr = iterator::curr->next;
				return *this;
			}
			reverse_iterator operator--(int)
			{
				iterator::curr = iterator::curr->next;
				return *this;
			}
		};
	};
}
	

#include "list.hpp"