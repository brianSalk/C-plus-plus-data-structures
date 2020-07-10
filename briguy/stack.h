#pragma once
#include "DeleteWhileEmptyException.h"
namespace briguy
{
	template <typename T>
	class stack
		: public DeleteWhileEmptyException
	{
		struct Node
		{
			T val;
			Node* next;
			Node(T const& v) : val(v), next(nullptr) {}
		};
	public:

		stack() { head = nullptr; }
		stack(stack<T> const& that);
		stack(stack<T>&& that) noexcept { this->head = that.head; that.head = nullptr; }
		void operator=(stack<T> const& that);
		void operator=(stack<T>&& that);
		void push(T const& val);
		T pop();
		bool isEmpty() const { return head == nullptr; }

		~stack();
	private:
		Node* head;
		// helpers
		void clear();
		void copy(stack<T> const& that);
	};
}
#include "stack.hpp"
