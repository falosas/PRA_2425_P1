#ifndef LISTLINKED_H
#define LISTLINKED_H

#include <stdexcept> 
#include <iostream>  
#include "List.h"    
#include "Node.h"    

using std::ostream;
using std::out_of_range;

template <typename T>
class ListLinked : public List<T> {
private:
    Node<T>* first;
    Node<T>* last; 
    int n;          

    Node<T>* getNode(int pos) const {
        if (pos < 0 || pos >= n) {
            throw out_of_range("Posición inválida!");
        }
        Node<T>* current = first;
        for (int i = 0; i < pos; i++) {
            current = current->next;
        }
        return current;
    }

public:
  
    ListLinked() : first(nullptr), last(nullptr), n(0) {}

    ~ListLinked() {
        Node<T>* current = first;
        while (current != nullptr) {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
    }

    void insert(int pos, const T& e) override {
        if (pos < 0 || pos > n) {
            throw out_of_range("Posición inválida!");
        }
        if (pos == 0) {
            prepend(e);
        } else if (pos == n) {
            append(e);
        } else {
            Node<T>* prev = getNode(pos - 1);
            Node<T>* newNode = new Node<T>(e, prev->next);
            prev->next = newNode;
            n++;
        }
    }

    void append(const T& e) override {
        Node<T>* newNode = new Node<T>(e, nullptr);
        if (n == 0) {
            first = newNode;
        } else {
            last->next = newNode;
        }
        last = newNode;
        n++;
    }

    void prepend(const T& e) override {
        Node<T>* newNode = new Node<T>(e, first);
        first = newNode;
        if (n == 0) {
            last = newNode;
        }
        n++;
    }

    T remove(int pos) override {
        if (pos < 0 || pos >= n) {
            throw out_of_range("Posición inválida!");
        }
        T data;
        Node<T>* toRemove;
        if (pos == 0) {
            toRemove = first;
            data = toRemove->data;
            first = first->next;
            if (n == 1) {
                last = nullptr;
            }
        } else {
            Node<T>* prev = getNode(pos - 1);
            toRemove = prev->next;
            data = toRemove->data;
            prev->next = toRemove->next;
            if (pos == n - 1) {
                last = prev;
            }
        }
        delete toRemove;
        n--;
        return data;
    }


    T get(int pos) const override {
        if (pos < 0 || pos >= n) {
            throw out_of_range("Posición inválida!");
        }
        return getNode(pos)->data;
    }

    int search(const T& e) const override {
        Node<T>* current = first;
        for (int i = 0; i < n; i++) {
            if (current->data == e) {
                return i;
            }
            current = current->next;
        }
        return -1;
    }

    bool empty() const override {
        return n == 0;
    }

    int size() const override {
        return n;
    }

    T operator[](int pos) {
        if (pos < 0 || pos >= n) {
            throw out_of_range("Posición inválida!");
        }
        return getNode(pos)->data;
    }

    template <typename U>
    friend ostream& operator<<(ostream &out, const ListLinked<U> &list);
};

template <typename T>
ostream& operator<<(ostream &out, const ListLinked<T> &list) {
    out << "List => [";
    
    Node<T>* current = list.first;
    if (current != nullptr) {
        out << "\n";
        while (current != nullptr) {
            out << "  " << *current << "\n"; 
            current = current->next;
        }
    }
    
    out << "]";
    return out;
}

#endif 
