#include "linkedList.h"
namespace briguy
{
	template<typename T>
	linkedList<T>::linkedList(linkedList<T> const& that)
	{
		this->n = that.n;
		this->head = new Node(that.head->val);
		Node* thisCurr = this->head;
		Node* thatCurr = that.head->next;
		while (thatCurr != nullptr)
		{
			thisCurr->next = new Node(thatCurr->val);
			thatCurr = thatCurr->next;
			thisCurr = thisCurr->next;
		}
	}
	template <typename T>
	void linkedList<T>::push_back(T const& val)
	{
		++n;
		Node* newTail = new Node(val);
		if (head == nullptr)
		{
			head = newTail;
			return;
		}
		Node* curr = head;
		while (curr->next != nullptr) { curr = curr->next; }
		curr->next = newTail;
	}

	template<typename T>
	void linkedList<T>::push_front(T const& val)
	{
		++n;
		Node* newHead = new Node(val);
		if (head == nullptr)
		{
			head = newHead;
			return;
		}
		newHead->next = head;
		head = newHead;
	}

	template<typename T>
	void linkedList<T>::insert(T const& val, iterator const& it)
	{
		++n;
		Node* newNode = Node(val);
		Node* nextPtr = it->next;
		it->next = newNode;
		newNode->next = nullptr;
	}
	template<typename T>
	void linkedList<T>::remove_back()
	{
		if (head == nullptr) { return; }
		--n;
		Node* temp = head;
		Node* curr = head->next;
		while (curr->next != nullptr)
		{
			temp = curr;
			curr = curr->next;
		}
		temp->next = nullptr;
		delete curr;
	}
	template<typename T>
	void linkedList<T>::remove_front()
	{
		if (head == nullptr) { return; }
		--n;
		Node* newHead = head->next;
		delete head;
		head = newHead;
	}
	template<typename T>
	void linkedList<T>::remove(iterator& it)
	{
		if (it == begin()) { remove_front(); return; }
		--n;
		it.temp->next = it.curr->next;
		Node* delNode = it.curr;
		it.curr = it.temp;
		delete delNode;
	}
	template<typename T>
	void linkedList<T>::reverse()
	{
		Node* temp = head;
		Node* curr = head->next;
		Node* peek = curr->next;
		
		while (peek->next != nullptr)
		{
			curr->next = temp;
			temp = curr;
			curr = peek;
			peek = peek->next;
		}
		head->next = nullptr;
		peek->next = curr;
		curr->next = temp;
		head = peek;
	}
	template<typename T>
	bool linkedList<T>::has(T const& val) const
	{
		if (head == nullptr) { return false; }
		Node* curr = head;
		while (curr != nullptr)
		{
			if (curr->val == val) { return true; }
			curr = curr->next;
		}
		return false;
	}
	template<typename T>
	void linkedList<T>::clear()
	{
		Node* curr = head;
		Node* delNode;
		while (curr)
		{
			delNode = curr;
			curr = curr->next;
			delete delNode;
		}
		head = nullptr;
		n = 0;
	}
	
	template<typename T>
	linkedList<T>::~linkedList()
	{
		// std::cout << "destructor: " << this << std::endl;
		Node* curr = head;
		Node* delNode;
		while (curr != nullptr)
		{
			// std::cout << curr << std::endl;
			delNode = curr;
			curr = curr->next;
			delete delNode;
			delNode = nullptr;
			// std::cout << "del" << std::endl;
		}
		
		head = nullptr;
	}
	template <typename T>
	template <typename Predicate>
	void linkedList<T>::insert_if
	(iterator const& first, iterator const& last, T const& val, Predicate const& pred)
	{
		for (auto it = first; it != last; ++it)
		{
			if (pred(*it))
			{
				insert(val, it);
			}
		}
	}
	template<typename T>
	template<typename Predicate>
	inline void linkedList<T>::remove_if(iterator first, iterator const& last, Predicate const& pred)
	{
		//iterator newFirst = first;
		while (first.curr == head && pred(*first) && first != last)
		{
			--n;
			head = head->next;
			delete first.curr;
			first.curr = head;
		}
		
		for (auto it = first; it != last; ++it)
		{
			if (pred(*it)) { remove(it); }
		}
	}
}