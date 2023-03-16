#include "xor_list.hpp"

template <typename T>
Node<T>* XorList<T>::xor_pointer(Node<T> *one, Node<T> *two) {
    return reinterpret_cast<Node<T> *>(
        reinterpret_cast<uintptr_t>(one) ^ 
        reinterpret_cast<uintptr_t>(two));
}

template <typename T>
void XorList<T>::clean() {
    Node<T> *prev = nullptr;
    Node<T> *cur = first;
    while (cur != last) {
        Node<T> *next = XorList<T>::xor_pointer(prev, cur->pointer);
        delete cur;
        prev = cur;
        cur = next;
    }
    delete cur;
    first = last = nullptr;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const XorList<T>& xor_list) {
    Node<T> *prev = nullptr;
    Node<T> *cur = xor_list.first;
    if (xor_list.empty()) {
        out << "()";
        return out;
    }
    out << "(";
    while (cur != xor_list.last) {
        out <<cur->val << " ";
        Node<T> *next = XorList<T>::xor_pointer(prev, cur->pointer);
        prev = cur;
        cur = next;
    }
    out << cur->val;
    out << ")";
    return out;
}

template <typename T>
XorList<T>& XorList<T>::insert_back(const T& node_value) {
    if (first == nullptr) {
        first = last = new Node<T>(node_value);
    }
    else {
        Node<T> *tmp = new Node<T>(node_value);
        tmp->pointer = last;
        last->pointer = xor_pointer(last->pointer, tmp);
        last = tmp;
    }
    return *this;
}

template <typename T>
XorList<T>& XorList<T>::insert_front(T&& node_value) {
    if (first == nullptr) {
        first = last = new Node<T>(node_value);
    }
    else {
        Node<T> *tmp = new Node<T>(node_value);
        tmp->pointer = first;
        first->pointer = xor_pointer(first->pointer, tmp);
        first = tmp;
    }
    return *this;
}

template <typename T>
XorList<T>& XorList<T>::erase_back() {
    if (last == nullptr) {
        return *this;
    }
    Node<T> *tmp = last;
    last = last->pointer;
    last->pointer = xor_pointer(last->pointer, tmp);
    delete tmp;
    return *this;
}

template <typename T>
XorList<T>& XorList<T>::erase_front() {
    if (first == nullptr) {
        return *this;
    }
    Node<T> *tmp = first;
    first = first->pointer;
    first->pointer = xor_pointer(first->pointer, tmp);
    delete tmp;
    return *this;
}

template <typename T>
XorList<T>& XorList<T>::merge(const XorList<T>& other) {
    if (other.first == nullptr) {
        return *this;
    }
    Node<T> *prev = nullptr;
    Node<T> *cur = other.first;
    while (cur != other.last) {
        Node<T> *next = XorList<T>::xor_pointer(prev, cur->pointer);
        insert_back(cur->val);
        prev = cur;
        cur = next;
    }
    insert_back(cur->val);
    return *this;
}

template <typename T>
XorList<T>& XorList<T>::merge(XorList<T>&& other) {
    if (other.first == nullptr) {
        return *this;
    }
    last->pointer = xor_pointer(last->pointer, other.first);
    other.first->pointer = xor_pointer(other.first->pointer, last);
    last = other.last;
    other.first = other.last = nullptr;
    return *this;
}

template <typename T>
XorList<T>::XorList(const XorList<T>& other) {
    first = last = nullptr;
    merge(other);
}

template <typename T>
XorList<T>::XorList(XorList<T>&& other) noexcept{
    first = std::exchange(other.first, nullptr);
    last = std::exchange(other.last, nullptr);
}

template <typename T>
XorList<T>& XorList<T>::operator=(const XorList<T> &other) {
    if (&other == this) {
        return *this;
    }
    clean();
    merge(other);
    return *this;
}

template <typename T>
XorList<T>& XorList<T>::operator=(XorList<T> &&other) noexcept{
    if (&other == this) {
        return *this;
    }
    first = std::exchange(other.first, nullptr);
    last = std::exchange(other.last, nullptr);
    return *this;
}
