#include "stack.h"

template <typename T>
briguy::stack<T>::stack(stack<T> const& that)
{
	copy(that);
}

template <typename T>
void stack<T>::operator=(stack<T> const& that)
{
	if (!isEmpty()) { clear(); }
	copy(that);
}

template <typename T>
void briguy::stack<T>::operator=(stack<T>&& that)
{
	if (!isEmpty()) { clear(); }
	this->head = that.head;
	that.head = nullptr;
}

template <typename T>
void briguy::stack<T>::push(T const& val)
{
	Node* newHead = new Node(val);
	newHead->next = head;
	head = newHead;
}

template <typename T>
T briguy::stack<T>::pop()
{
	if (isEmpty()) { throw briguy::DeleteWhileEmptyException(); }
	T returnVal = head->val;
	Node* newHead = head->next;
	delete head;
	head = newHead;
	return returnVal;
}

template <typename T>
briguy::stack<T>::~stack()
{
	clear();
}


template <typename T>
void briguy::stack<T>::clear()
{
	Node* curr = head;
	Node* delNode;
	while (curr != nullptr)
	{
		delNode = curr;
		curr = curr->next;
		delete delNode;
	}
}

template <typename T>
void briguy::stack<T>::copy(stack<T> const& that) 
{
	this->head = nullptr;
	if (that.head == nullptr) { return; }
	Node* thatCurr = that.head;
	this->head = new Node(thatCurr->val);
	thatCurr = thatCurr->next;
	Node* thisCurr = this->head;
	while (thatCurr != nullptr)
	{
		thisCurr->next = new Node(thatCurr->val);
		thisCurr = thisCurr->next;
		thatCurr = thatCurr->next;
	}
}