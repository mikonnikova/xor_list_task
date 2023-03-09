#include <iostream>


template <class T>
class Node {
  public:
    T val;
    uintptr_t pointer;

    Node(); // TODO
    Node(T value); // TODO
};


template <class T>
class XorList {
  public:
    XorList(); // TODO
    ~XorList(); // TODO

    XorList(const XorList &other); // TODO
    XorList(XorList &&other); // TODO

    XorList& operator=(const XorList &other); // TODO
    XorList& operator=(XorList &&other); // TODO
    
    XorList& insert_back(const T& node_value); // TODO
    XorList& insert_front(T&& node_value); // TODO

    XorList& erase_back(); // TODO
    XorList& erase_front(); // TODO

    XorList& merge(const XorList& other); // TODO
    XorList& merge(XorList&& other); // TODO

    bool empty(); // TODO

  private:
    Node<T>* first, last;
};

template<typename T>
std::ostream& operator<<(std::ostream& out, const XorList<T>& xor_list);
