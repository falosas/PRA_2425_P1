#ifndef LISTARRAY_H
#define LISTARRAY_H

#include <stdexcept>
#include <iostream>
#include "List.h"

using std:: out_of_range;
using std::ostream;

template <typename T>
class ListArray : public List<T> {
	private:
		T* data;
		int n;
		int max;
		static const int minsize = 10;

		void resize (int new_size)
		{
			T* new_data = new T[new_size];
			for (int i = 0; i < n; i++) {new_data[i] = data[i];}

			delete[] data;
			data = new_data;
			max = new_size;
		}

	public:
		ListArray()
		{
			n = 0;
			max = minsize;
			data = new T[max];
		}

		~ListArray() {delete[] data;}

		void insert(int pos, T e)
		{
			if (pos < 0 || pos > n)
			{
				throw out_of_range("Posicion invalida");
			}

			for (int i = n; i > pos; i--)
			{
				data[i] = data[i - 1];
			}

			data[pos] = e;
			n++;
		}

		void append (T e) {insert(n, e);}

		void prepend (T e) {insert(0, e);}

		T remove(int pos)
		{
			if (pos < 0 || pos >= n)
			{
				throw out_of_range("Posicion invalida");
			}

			T element = data[pos];

			for (int i = pos; i < n-1; i++)
			{
				data[i] = data [i+1];
			}

			n--;
			if (max > minsize && n <= max/4)
			{
				int new_max = max/2;
				if (new_max < minsize) {new_max = minsize;}
				resize(new_max);
			}

			return element;
		}

		T get(int pos) 
		{
			if (pos < 0 || pos >= n)
			{
				throw out_of_range("Posicion invalida");
			}
			return data[pos];
		}

		int search (T e) 
		{
			for (int i = 0; i < n; i++)
			{
				if (data[i] == e) {return i;}
			}
			return -1;
		}

		bool empty() {return n == 0;}

		int size () {return n;}

		T& operator[] (int pos)
		{
			if (pos < 0 || pos => n)
			{
				throw out_of_range("Posicion invalida");
			}
			return data[pos];
		}

		const T& operator[] (int pos) 
		{
			if (pos < 0 || pos >= n)
			{
				throw out_of_range("Posicion invalida");
			}

			return data[pos];
		}

		template <typename U>
		friend ostream& operator<<(ostream &out, const ListArray<U> &list);
};

template <typename T>
ostream& operator <<(ostream &out, const ListArray<T> &list)
{
	out << "ListArray [ (n=" << list.n << ", max=" << list.max << ") ";
	for (int i = 0; i < list.n; i++) 
	{
		out << list.data[i];
		if (i < list.n - 1) {out << ", ";}
	}
	out << " ]";
	return out;
}

#endif


