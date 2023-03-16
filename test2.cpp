#include "xor_list.hpp"


int main(int argc, char **argv) {
    XorList<int> xor_list;
    xor_list.insert_back(3);
    xor_list.insert_back(5);
    xor_list.insert_back(7);
    std::cout << xor_list << std::endl;
    xor_list.erase_front();
    std::cout << xor_list << std::endl;
    xor_list.insert_front(4);
    std::cout << xor_list << std::endl;
    xor_list.erase_back();
    std::cout << xor_list << std::endl;
    xor_list.insert_back(9);
    std::cout << xor_list << std::endl;
    xor_list.clean();
    std::cout << xor_list << std::endl;
    std::cout << std::endl;

    XorList<int> xor_list1;
    xor_list1.insert_back(1);
    xor_list1.insert_back(2);
    xor_list1.insert_back(3);
    XorList<int> xor_list2;
    xor_list2.insert_front(4);
    xor_list2.insert_back(5);
    std::cout << xor_list1 << " " << xor_list2 << std::endl;
    xor_list1.merge(xor_list2);
    std::cout << xor_list1 << " " << xor_list2 << std::endl;
    xor_list1.merge(std::move(xor_list2));
    std::cout << xor_list1 << " " << xor_list2 << std::endl;
    std::cout << std::endl;

    XorList<int> xor_list3;
    xor_list3.insert_back(1);
    xor_list3.insert_back(2);
    xor_list3.insert_back(3);
    std::cout << xor_list3 << std::endl;
    XorList<int> xor_list4(xor_list3);
    std::cout << xor_list3 << " " << xor_list4 << std::endl;
    XorList<int> xor_list5(std::move(xor_list3));
    std::cout << xor_list3 << " " << xor_list5 << std::endl;
    std::cout << std::endl;

    XorList<int> xor_list6;
    xor_list6.insert_back(1);
    xor_list6.insert_back(2);
    xor_list6.insert_back(3);
    std::cout << xor_list6 << std::endl;
    XorList<int> xor_list7 = xor_list6;
    std::cout << xor_list6 << " " << xor_list7 << std::endl;
    XorList<int> xor_list8 = std::move(xor_list6);
    std::cout << xor_list6 << " " << xor_list8 << std::endl;
    std::cout << std::endl;

    XorList<int> xor_list9 = std::move_if_noexcept(xor_list8);
    std::cout << xor_list8 << " " << xor_list9 << std::endl;
    std::cout << std::endl;
    return 0;
}