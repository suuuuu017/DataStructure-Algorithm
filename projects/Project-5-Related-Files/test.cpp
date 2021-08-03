#include <iostream>
#include "Dlist.h"
using namespace std;

int main(int argc, char *argv[])
{
    int result = 0;

    Dlist<int> ilist;
    int *ip = new int(1);
    ilist.insertFront(ip);
    int *ip1 = new int(2);
    ilist.insertFront(ip1);
    int *ip2 = new int(3);
    ilist.insertBack(ip2);
    std::cout << ilist << std::endl;

    auto ippp = ilist.removeFront();
    std::cout << *ippp << " the list is " << ilist << std::endl;
    auto ipp = ilist.removeBack();
    std::cout << *ipp << " the list is " << ilist << std::endl;

    Dlist<int> copylist(ilist);
//    copylist = ilist;
    std::cout << "the copy list is " << copylist << std::endl;

    if(*ip != 1)
        result = -1;
    delete ip;

    if(!ilist.isEmpty())
        result = -1;

    return result;
}
