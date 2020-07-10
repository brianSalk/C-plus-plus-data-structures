#pragma once
#include "DeleteWhileEmptyException.h"
#include <functional>
namespace briguy
{
	template <typename T>
	class heap 
		: public DeleteWhileEmptyException
	{
	public:
		// in order for the callable to work correctly, operators including equality should be used
		heap(std::function<bool(T const&, T const&)> p = [](T const& a, T const& b) {return a >= b; })
			: n(0), capacity(10), pred(p) {
			arr = new T[capacity];
		};
		
		T pop();
		void insert(T const& val);
		size_t size() const;
		bool is_empty() const;
	private:
		T* arr;
		size_t n;
		size_t capacity;
		std::function<bool(T const&, T const&)> pred = [](T const& a, T const& b) { return a >= b; };

		void swim(size_t indx);
		void sink(size_t indx);

		void swap(size_t a, size_t b);
		
		void shrink();
		void grow();
	};
}

#include "heap.hpp"