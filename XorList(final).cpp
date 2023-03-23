#include<iostream>
#include<new>
#include<utility>

template <class T>
class Node {
public:
    T val;
    Node<T> *pointer;

    Node() = default;
    explicit Node(const T &value){
        val = value;
    }
};

template <class T>
class XorList {
public:
    XorList(){
        first = nullptr;
        last = nullptr;
    }
    ~XorList()noexcept{
        if(!empty()) {
            Node<T> *tmp = first;
            Node<T> *prev = first;
            Node<T> *cur = tmp;
            tmp = tmp->pointer;
            (cur->val).~T();
            operator delete(cur, std::nothrow);

            while (tmp != nullptr && tmp != last) {
                cur = tmp;
                tmp = reinterpret_cast<Node<T> *>
                ((reinterpret_cast<unsigned long long>(prev) ^ reinterpret_cast<unsigned long long>((tmp->pointer))));
                prev = cur;
                (cur->val).~T();
                operator delete(cur, std::nothrow);
            }
            if (tmp != nullptr) {
                (cur->val).~T();
                operator delete(tmp, std::nothrow);
            }
        }
    }

    XorList(const XorList &other){
        first = nullptr;
        last = nullptr;
        if(!other.empty()) {
            Node<T> *tmp = other.getFirst();
            Node<T> *prev = other.getFirst();
            insert_back(tmp->val);
            tmp = tmp->pointer;
            while (tmp != nullptr && tmp != other.getLast()) {
                insert_back(tmp->val);
                Node<T> *cur = tmp;
                tmp = reinterpret_cast<Node<T> *>
                ((reinterpret_cast<unsigned long long>(prev) ^ reinterpret_cast<unsigned long long>((tmp->pointer))));
                prev = cur;
            }
            if(tmp!= nullptr)
                insert_back(tmp->val);
        }

    }
    XorList(XorList &&other){
        first = other.first;
        last = other.last;
        other.last = other.first = nullptr;
    }

    XorList& operator=(const XorList &other){
        if(other.first != first && other.last != last) {
            XorList<T> new_list = XorList<T>(other);
            operator=(std::move(new_list));
        }
        return *this;
    }
    XorList& operator=(XorList &&other)noexcept{
        if(other.first != first && other.last != last) {
            (*this).~XorList();
            first = other.first;
            last = other.last;
            other.first = other.last = nullptr;
        }
        return *this;
    }

    XorList& insert_back(const T& node_value){
        if (empty()){
            T val = node_value;
            insert_front(std::move(val));
        }
        else{
            auto *new_last = new Node<T>();
            new_last->val = node_value;
            new_last->pointer = last;
            last->pointer = reinterpret_cast<Node<T>*>
            ((reinterpret_cast<unsigned long long>(new_last) ^ reinterpret_cast<unsigned long long>(last->pointer)));
            last = new_last;
        }

        return *this;
    }

    XorList& insert_front(T&& node_value){
        if(empty()){
            auto *head = new Node<T>();
            head->val = node_value;
            head->pointer = nullptr;
            first = head;
            last = head;
        }
        else{
            auto *new_first = new Node<T>();
            new_first->val = node_value;
            new_first->pointer = first;
            first->pointer = reinterpret_cast<Node<T> *>
            ((reinterpret_cast<unsigned long long>(new_first) ^ reinterpret_cast<unsigned long long>(first->pointer)));
            first = new_first;
        }
        return *this;
    }

    XorList& erase_back() {
        if(empty()){}
        else if(last->pointer == nullptr){
            (last->val).~T();
            operator delete (last, std::nothrow);
            first = last = nullptr;
        }
        else if(last->pointer == first){
            (last->val).~T();
            operator delete (last, std::nothrow);
            last = first;
            first->pointer = last->pointer = nullptr;

        }
        else{
            Node<T> *cur = reinterpret_cast<Node<T>*>
            (reinterpret_cast<unsigned long long>(last) ^ reinterpret_cast<unsigned long long>((last->pointer)->pointer));
            Node<T>* tmp = last;
            last = last->pointer;
            last->pointer = cur;
            (tmp->val).~T();
            operator delete (tmp, std::nothrow);
        }
        return *this;

    }
    XorList& erase_front(){
        if(empty()){}
        else if(first->pointer == nullptr){
            (first->val).~T();
            operator delete (first, std::nothrow);
            first = last = nullptr;
        }
        else if(first->pointer == last){
            (first->val).~T();
            operator delete (first, std::nothrow);
            first = last;
            first->pointer = last->pointer = nullptr;

        }
        else{
            Node<T> *cur = reinterpret_cast<Node<T>*>
            (reinterpret_cast<unsigned long long>(first) ^ reinterpret_cast<unsigned long long>((first->pointer)->pointer));
            Node<T>* tmp = first;
            first = first->pointer;
            first->pointer = cur;
            (tmp->val).~T();
            operator delete (tmp, std::nothrow);
        }
        return *this;
    }

    XorList& merge(const XorList& other){
        if(other.empty()) return *this;
        XorList<T> list = XorList<T>(other);
        merge(std::move(list));
        return *this;
    }

    XorList& merge(XorList&& other){
        if(other.empty()) return *this;
        (other.first)->pointer = reinterpret_cast<Node<T>*>
        (reinterpret_cast<unsigned long long> (last) ^ reinterpret_cast<unsigned long long>(other.first->pointer));
        last->pointer = reinterpret_cast<Node<T>*>
        (reinterpret_cast<unsigned long long> (last->pointer) ^ reinterpret_cast<unsigned long long>(other.first));
        last = other.last;
        other.last = other.first = nullptr;
        return *this;
    }

    bool empty()const{
        if (first == nullptr) return true;
        else return false;
    }

    Node<T>* getFirst()const{
        return first;
    }

    Node<T>* getLast()const{
        return last;
    }

private:
    Node<T>* first;
    Node<T>* last;
};

template<typename T>
std::ostream& operator<<(std::ostream& out, const XorList<T>& xor_list){
    if(!xor_list.empty()) {
        Node<T> *tmp = xor_list.getFirst();
        Node<T> *prev = xor_list.getFirst();
        out << tmp->val << ' ' << std::endl;
        tmp = tmp->pointer;
        while (tmp != nullptr && tmp != xor_list.getLast()) {
            out << tmp->val << ' ' << std::endl;
            Node<T> *cur = tmp;
            tmp = reinterpret_cast<Node<T> *>
            ((reinterpret_cast<unsigned long long>(prev) ^ reinterpret_cast<unsigned long long>((tmp->pointer))));
            prev = cur;
        }
        if(tmp!= nullptr)
            out << tmp->val << ' ' << std::endl;
    }
    return out;
}

int main(){
    XorList<int> list = XorList<int>();
    XorList<int> list1 = XorList<int>();
    list.insert_front(12);
    list.insert_front(13);
    list.insert_front(14);
    list.insert_front(15);
    list = list;
    std::cout<< list << std::endl;
    return 0;
}