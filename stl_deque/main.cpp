// #include "stl_deque.h"
#include <deque>
#include <vector>
#include <iostream>
#include <algorithm>
#include <list>
#include <memory>

int main(int argc, char * argv[])
{
    std::deque<int> deq = {0,4,5,7,3,1};

    auto print = [&](){for(auto element : deq){ std::cout<< element << " ";} std::cout<<std::endl;};
    print();

    deq.push_back(25);
    deq.push_front(12);
    print();

    std::sort(deq.begin(), deq.end());
    print();

    std::cout<<deq[4]<<std::endl;

    std::cout<<deq.max_size()<<std::endl;

    std::cout<<deq.size()<<std::endl;


    std::string str = "dasdasdasdasdadgdg222a2das";
    std::sort(str.begin(), str.end());
    std::cout<<str<<std::endl;

    std::list<int> list = {1,4,7,5,3,4};
    auto printList = [&](){for(auto element : list){ std::cout<< element << " ";} std::cout<<std::endl;};
    printList();

    // std::sort(list.begin(), list.end()); // that is rand_access_iterator, list's iterator is BidirectIterator
    list.sort();
    printList();

    int* iPn = new int(7);
    std::shared_ptr<int> shptr(iPn);
    std::weak_ptr<int> wptrINT = shptr;

    std::cout<<*(wptrINT.lock())<<std::endl;
    return 0;
}

