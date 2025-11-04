#ifndef NODE_H
#define NODE_H

#include <ostream> 

using std::ostream;

template <typename T>
class ListLinked; 

template <typename T>
class Node {
public:
    T data;
    Node<T>* next;

    Node(T data, Node<T>* next = nullptr) {
        this->data = data;
        this->next = next;
    }
    template <typename U> 
    friend ostream& operator<<(ostream &out, const Node<U> &node);
    
    friend class ListLinked<T>;
};

template <typename T>
ostream& operator<<(ostream &out, const Node<T> &node) {
    out << node.data;
    return out;
}

#endif // NODE_H
