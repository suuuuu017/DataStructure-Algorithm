//
// Created by cyx on 20-6-12.
//

#include <iostream>
#include "mylist.h"

int main() {

    try{
        List<int> la, lb;
        la.insertBack(0);
        la.insertBack(0);
        la.insertBack(0);
        la.insertBack(5); // a = 3145
        la.print();

//        lb.insertBack(2);
//        lb.insertBack(0);
//        lb.insertBack(0);
//        lb.insertBack(0);
        lb.insertBack(4);
        lb.insertBack(4);
        lb.insertBack(4);
        lb.insertBack(4);
        lb.insertBack(4);
//        lb.removeFront(); // b = 314
        lb.print();
        lb = la;
        std::cout << "after assginment" << std::endl;
        lb.print();

        List<int> le(lb);

        std::cout <<"larger " << isLarger(la, lb) << '\n';

        List<int> ab_sum(la);
        ab_sum.print();
        std::cout << "sum is ";
        ab_sum = add(la, lb);
        ab_sum.print();

        List<bool> lc;
        lc.insertBack(true);
        lc.insertBack(false);
        lc.insertBack(true);

        List<bool> ld(lc);
        ld.removeFront();
        ld.print();
    }
    catch(EmptyList){
        std::cout << "Remove from empty list!\n";
    }

    return 0;
}

