#include "list.h"

template <typename T>
briguy::list<T>::list(std::initializer_list<T> il)
{
	for (T const& each : il)
	{
		push_back(each);
	}
}

template <typename T>
briguy::list<T>::list(list<T>&& that) : n(that.n)
{
	this->head = that.head;
	this->tail = that.tail;
}

template <typename T>
briguy::list<T>::list(list<T> const& that)
{
	for (T const& each: that)
	{
		this->push_back(each);
	}
}

template <typename T>
void briguy::list<T>::push_back(T const& val)
{
	++n;
	Node* newTail = new Node(val);
	if (tail == NULL)
	{
		tail = head = newTail;
		return;
	}
	tail->next = newTail;
	newTail->prev = tail;
	tail = newTail;
}

template <typename T>
void briguy::list<T>::push_front(T const& val)
{
	++n;
	Node* newHead = new Node(val);
	if (head == NULL)
	{
		head = tail = newHead;
		return;
	}
	head->prev = newHead;
	newHead->next = head;
	head = newHead;
}

template <typename T>
void briguy::list<T>::remove_front()
{
	if (size() == 0) { return; }
	--n;
	Node* oldHead = head;
	Node* newHead = head->next;
	delete oldHead;
	head = newHead;
	head->prev = NULL;
}


template <typename T>
void briguy::list<T>::remove_back()
{
	if (size() == 0) { return; }
	--n;
	Node* oldTail = tail;
	Node* newTail = tail->prev;
	delete oldTail;
	tail = newTail;
	tail->next = NULL;
}

template <typename T>
void briguy::list<T>::erase(iterator const& it)
{
	if (it.curr == head)
	{
		remove_front();
		return;
	}
	else if (it.curr == tail)
	{
		remove_back();
		return;
	}
	Node* before = it.curr->prev;
	Node* after = it.curr->next;
	before->next = after;
	after->prev = before;
	delete it.curr;
	--n;
}

template <typename T>
void briguy::list<T>::erase_range(iterator const& first, iterator const& last)
{
	Node* before = first->prev;
	Node* after = last.curr;
	Node* delNode;
	iterator first_cpy = first;
	while (first_cpy != last)
	{
		delNode = first_cpy.curr;
		++first_cpy;
		delete delNode;
		--n;
	}
	if (before != NULL)
	{
		before->next = after;
	}
	else
	{
		head = after;
		head->prev = NULL;
	}
	if (after != NULL)
	{
		after->prev = before;
	}
	else
	{
		tail = before;
		tail->next = NULL;
	}
	


}

template<typename T>
void briguy::list<T>::remove_first(iterator const& first, iterator const& last, T const& val)
{
	for (auto it = first; it != last; ++it)
	{
		if (*it == val) { erase(it); break; }
	}
}

template<typename T>
void briguy::list<T>::remove_last(iterator const& first, iterator const& last, T const& val)
{
	for (auto it = first; it != last; ++it)
	{
		if (*it == val) { erase(it); break; }
	}
}

template<typename T>
void briguy::list<T>::remove_all(iterator const& first, iterator const& last, T const& val)
{
	for (auto it = first; it != last; ++it)
	{
		if (*it == val) 
		{ 
			iterator temp = it;
			--it;
			erase(temp); 
		}
	}
}

template <typename T>
void briguy::list<T>::insert(iterator const& it, T const& val)
{
	if (it->next == NULL) { push_back(val); return; }
	Node* newNode = new Node(val);
	std::cout << newNode->val.getVal() << std::endl;
	_insert_node_after(it, newNode);
	
}

template <typename T>
template <typename ...Args>
void briguy::list<T>::emplace(iterator const& it, Args&& ...args)
{
	if (it->next == NULL) { emplace_back(std::forward<Args>(args)...); return; }
	Node* newNode = new Node(std::forward<Args>(args)...);
	_insert_node_after(it, newNode);
}


template <typename T>
void briguy::list<T>::_insert_node_after(iterator const& it, Node* newNode)
{
	Node* after = it->next;
	Node* before = it.curr;
	// std::cout << "here" << std::endl;
	before->next = newNode;
	newNode->prev = before;

	after->prev = newNode;
	newNode->next = after;

	++n;
}

template<typename T>
briguy::list<T>::~list()
{
	Node* curr = head, * delPtr;
	while (curr != nullptr)
	{
		delPtr = curr;
		curr = curr->next;
		delete delPtr;
	}
}

template<typename T>
template<typename ...Args>
void briguy::list<T>::emplace_back(Args&& ...args)
{
	Node* newTail = new Node(std::forward<Args>(args)...);
	if (tail == nullptr) 
	{ 
		head = tail = newTail;
	}
	else
	{
		newTail->prev = tail;
		tail->next = newTail;
		tail = newTail;
	}
	++n;
}

template<typename T>
template<typename ...Args>
void briguy::list<T>::emplace_front(Args&& ...args)
{
	Node* newHead = new Node(std::forward<Args>(args)...);
	if (head == nullptr)
	{
		head = tail = newHead;
	}
	else
	{
		newHead->next = head;
		head->prev = newHead;
		head = newHead;
	}
	++n;
}

template <typename T>
template<typename Predicate>
void briguy::list<T>::remove_if(iterator const& first, iterator const& last, Predicate pred)
{
	iterator curr = first;
	if (curr == begin()) 
	{
		while (curr.curr == head && pred(*curr)) { curr++; remove_front(); }
		curr = begin();
	}
	for (; curr != last; ++curr)
	{
		if (pred(*curr)) 
		{  
			iterator temp = curr;
			curr--;
			erase(temp);
		}
	}
}