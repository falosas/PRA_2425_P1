#ifdef LISTA_H
#define LISTA_H

#include <stdexcept>

template <typename T>
class Lista
{
	private:
		Nodo* primero;
		int size;

	public:
		List();

		~List();

		void insert (int pos, const T& e);

		void append (const T& e);

		void prepend (const T& e);

		T remove (int pos);

		T get (int pos);

		int search (const T& e);

		bool empty();

		int size();
};

#endif
