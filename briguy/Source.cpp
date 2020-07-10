#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
#include <vector>
#include "vector.h"
#include "hashSet.h"
#include <list>
#include <unordered_set>
#include <algorithm>
#include "deque.h"
#include "ringQueue.h"
#include "list.h"
#include "heap.h"
#include "linkedList.h"
#include <forward_list>
#include "stack.h"

using namespace std;

struct A
{
	A() { cout << "A()\n"; num++; val = std::numeric_limits<size_t>::max(); }
	A(int& a) { cout << "A(int&)\n"; num++; val = a; }
	A(int&& a) { cout << "A(int&&)\n"; val = a; }
	A(int a, int b) { cout << "A(int,int)\n"; num++; val = a; }
	A(A const& a) { cout << "A(A const&)\n"; *this = a; }
	A(A&& a) { cout << "A(A&&)\n"; }
	void operator=(A const& a) const { cout << "operator=(A const&) const\n"; }
	~A() { cout << "~A()\n"; }
	size_t getVal() const { return val; }
private:
	static size_t num;
	size_t val;
};
size_t A::num = 0;

template <typename Arg>
A create(Arg const& arg)
{
	return A(arg);
}

int main()
{
	briguy::ringQueue<int, 5>q;
	q.enqueue(2);
	q.enqueue(3);
	for (int each : q)
	{
		std::cout << each << std::endl;
	}
	return 0;
}

void example(A const& a)
{
	cout << "value is " << a.getVal() << endl;
}

template <typename  ...Args>
void example2(Args&& ...args)
{
	A* a = new A(std::forward<Args>(args)...);
	cout << a->getVal() << endl;
	delete a;
}