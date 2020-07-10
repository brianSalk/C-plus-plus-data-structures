#pragma once
namespace briguy
{
	template<typename T>
	class linkedList
	{
	protected:
		struct Node
		{
			Node* next;
			T val;
			Node(T const& v) : val(v), next(nullptr) {}
		};
	public:
		class iterator;
		linkedList() : n(0), head(nullptr) {}
		linkedList(linkedList<T> const& that);

		void push_back(T const& val);
		void push_front(T const& val);
		void insert(T const& val, iterator const& it);
		template<typename Predicate>
		void insert_if(iterator const& first, iterator const& last, T const& val, Predicate const& pred);

		void remove_back();
		void remove_front();
		void remove(iterator& it);
		template<typename Predicate>
		void remove_if(iterator first, iterator const& last, Predicate const& pred);

		void reverse();
		size_t size() const { return n; }
		bool has(T const& val) const;
		void clear();

		iterator begin() { return iterator(nullptr,head); }
		iterator end() const { return iterator(nullptr,nullptr); }

		~linkedList();
		
	private:
		Node* head;
		size_t n;
	public:
		class iterator
		{
		public:
			friend class linkedList;
			// VIDPR
			typedef T                         value_type;
			typedef std::forward_iterator_tag iterator_category;
			typedef ptrdiff_t                 difference_type;
			typedef T*                        pointer_type;
			typedef T&                        reference;

			iterator(Node* t,Node* c) :temp(t), curr(c) {}
			reference operator*() const { return curr->val; }
			void operator=(iterator const& that) { this->curr = that.curr; this->temp = that.curr; }
			bool operator!=(iterator const& that) const { return this->curr != that.curr; }
			bool operator==(iterator const& that) const { return this->curr == that.curr; }
			// prefix incrament operator
			iterator& operator++()
			{
				temp = curr;
				curr = curr->next;
				return *this;
			}
			iterator operator++(int)
			{
				temp = curr;
				curr = curr->next;
				return *this;
			}
		private:
			Node* temp;
			Node* curr;
		};
	};
}
#include "linkedList.hpp"