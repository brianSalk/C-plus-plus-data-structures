#include "hashSet.h"

template <>
size_t briguy::hashSet<std::string>::hash(std::string const& val) const
{
	// std::cout << "string" << std::endl;
	size_t ans = 0;
	for (size_t i = 0; i < 16 && i < val.size(); ++i)
	{
		ans += val[i];
	}
	return ans;
}
template <typename T>
size_t briguy::hashSet<T>::hash(T const& val) const
{
	return _hash(val, std::is_integral<T>::type());
}

template <typename T>
size_t briguy::hashSet<T>::_hash(T const& val, std::true_type) const
{
	// std::cout << "int" << std::endl;
	T temp = val;
	if (temp < 0) { temp *= -1; }
	return val % ARR_SIZE;
}
template <typename T>
size_t briguy::hashSet<T>::_hash(T const& val, std::false_type) const
{ 
	return __hash(val, std::is_floating_point<T>::type());
}
template <typename T>
size_t briguy::hashSet<T>::__hash(T const& val, std::true_type) const
{
	// std::cout << "double" << std::endl;
	long long int pref = val;
	long long int suff = (val - pref) * 100;
	long long int ans = pref + suff;
	if (ans < 0) { ans *= -1; }
	return ans;
}
template <typename T>
size_t briguy::hashSet<T>::__hash(T const& val, std::false_type) const
{
	// std::cout << "ADT" << std::endl;
	return val.hash();
}

template<typename T>
briguy::hashSet<T>::hashSet(hashSet const& that)
{
	copy(that);
}

template <typename T>
void briguy::hashSet<T>::operator=(hashSet const& that)
{
	if (size() != 0) { clear(); }
	copy(that);
}

template <typename T>
void briguy::hashSet<T>::operator=(hashSet&& that)
{
	if (size() != 0) { clear(); }
	mover(that);
}


template <typename T>
inline briguy::hashSet<T>::hashSet(hashSet&& that)
{
	mover(that);
}

template <typename T>
void briguy::hashSet<T>::put(T const& putVal)
{
	size_t index = hash(putVal);
	if (arr[index] == NULL) { arr[index] = new Node(putVal); }
	else
	{
		Node* temp = arr[index];
		Node* curr = arr[index];
		while (curr != NULL)
		{
			if (curr->val == putVal) { return; }
			temp = curr;
			curr = curr->next;
		}
		temp->next = new Node(putVal);
	}
	++n;
}

template <typename T>
bool briguy::hashSet<T>::has(T const& val) const
{
	size_t index = hash(val);
	if (arr[index] == NULL) { return false; }
	else
	{
		Node* curr = arr[index];
		while (curr != NULL)
		{
			if (curr->val == val) { return true; }
			curr = curr->next;
		}
	}
	return false;
}

template <typename T>
inline size_t briguy::hashSet<T>::size() const
{
	return n;
}

template <typename T>
void briguy::hashSet<T>::remove(T const& val)
{
	const size_t index = hash(val);

	if (arr[index] == NULL) { return; }
	if (arr[index]->val == val)
	{
		Node* newHead = arr[index]->next;
		delete arr[index];
		arr[index] = newHead;
		--n;
		return;
	}
	Node* curr = arr[index], * temp = arr[index];
	while (curr != NULL)
	{
		if (curr->val == val)
		{
			temp->next = curr->next;
			delete curr;
			--n;
			return;
		}
		temp = curr;
		curr = curr->next;
	}

}

template<typename T>
void briguy::hashSet<T>::clear()
{
	for (size_t i = 0; i < ARR_SIZE; ++i)
	{
		if (arr[i] != NULL)
		{
			Node* curr = arr[i];
			while (curr != NULL)
			{
				Node* temp = curr;
				curr = curr->next;
				delete temp;
				temp = nullptr;
				--n;
				if (n == 0) { arr[i] = nullptr; return; }
			}
			arr[i] = nullptr;
		}
	}
}

template <typename T>
void briguy::hashSet<T>::copy(hashSet const& that)
{
	for (size_t i = 0; i < ARR_SIZE; ++i)
	{
		if (that.arr[i] != NULL)
		{
			Node* thatCurr = that.arr[i];
			Node* thisCurr = new Node(thatCurr->val);
			Node* thisHead = thisCurr;
			thatCurr = thatCurr->next;
			while (thatCurr != NULL)
			{
				thisCurr->next = new Node(thatCurr->val);
				thatCurr = thatCurr->next;
				thisCurr = thisCurr->next;
			}

			this->arr[i] = thisHead;
		}
	}
	this->n = that.n;
}

template<typename T>
void briguy::hashSet<T>::mover(hashSet& that)
{
	for (size_t i = 0; i < ARR_SIZE; ++i)
	{
		if (that.arr[i] != nullptr)
		{
			this->arr[i] = that.arr[i];
			that.arr[i] = nullptr;
		}
	}
	this->n = that.n;
}

template <typename T>
briguy::hashSet<T>::~hashSet()
{
	clear();
}