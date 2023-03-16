#ifndef XOR_LIST_HPP
#define XOR_LIST_HPP

#include <iostream>
#include <utility>


template <class T>
class Node {
  public:
    T val;
    Node<T> *pointer;

    Node() : val() {
      pointer = 0;
    }
    Node(T value): val(value) {
      pointer = 0;
    }
};


template <class T>
class XorList {
  public:
    XorList() {
      first = nullptr;
      last = nullptr;
    }
    ~XorList() {
      clean();
    }

    XorList(const XorList &other);
    XorList(XorList &&other) noexcept;

    XorList& operator=(const XorList &other);
    XorList& operator=(XorList &&other) noexcept;
    
    XorList& insert_back(const T& node_value);
    XorList& insert_front(T&& node_value);

    XorList& erase_back();
    XorList& erase_front();

    XorList& merge(const XorList& other);
    XorList& merge(XorList&& other);

    bool empty() const {
      return first==nullptr;
    }

    static Node<T>* xor_pointer(Node<T> *one, Node<T> *two);

    Node<T>* first, *last;
    void clean();

};

template<typename T>
std::ostream& operator<<(std::ostream& out, const XorList<T>& xor_list);

#include "xor_list.cpp"

#endif //XOR_LIST_HPP