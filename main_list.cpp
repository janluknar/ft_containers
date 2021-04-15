/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_list.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jluknar- <jluknar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 14:29:29 by jluknar-          #+#    #+#             */
/*   Updated: 2021/03/30 16:17:50 by jluknar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.hpp"
#include <stdlib.h>
#include <iostream>
#include <list>

struct is_odd {
  bool operator() (const int& value) { return (value%2)==1; }
};

bool more_than (const int& a, const int& b) { return (a > b); }

// compare only integral part:
bool mycomparison (double first, double second)
{ return ( int(first)<int(second) ); }


int main(void)
{
    std::cout << "==============/\\LIST TESTS/\\===================" << std::endl;
    std::cout << "////default constructor////" << std::endl;
    ft::list<int> weewee;
    ft::list<int>::iterator first;
    for(first = weewee.begin(); first != weewee.end(); ++first)
        std::cout << *first << ", ";
    std::cout << "\n=============================================" << std::endl;
    std::cout << "////fill constructor////" << std::endl;
    ft::list<int> list2(5, 400);
     for(first = list2.begin(); first != list2.end(); ++first)
        std::cout << *first << ", "; 
    std::cout << "\n=============================================" << std::endl;
    std::cout << "////range constructor////" << std::endl;
    ft::list<int> list3(list2.begin(), list2.end());
    for(first = list3.begin(); first != list3.end(); ++first)
        std::cout << *first << ", ";
    std::cout << "\n=============================================" << std::endl;
    std::cout << "////copy constructor////" << std::endl;
    ft::list<int> list4(list2);
    for(first = list4.begin(); first != list4.end(); ++first)
        std::cout << *first << ", ";
    std::cout << "\n=============================================" << std::endl;
    std::cout << "////equals operator overload////" << std::endl;
    ft::list<int> list5 = list4;
    for(first = list5.begin(); first != list5.end(); ++first)
        std::cout << *first << ", ";
    std::cout << "\n=============================================" << std::endl;
    std::cout << "////empty, size, max_size////" << std::endl;
    if(weewee.empty())
        std::cout << "weewee is empty\n";
    std::cout << "list2 has " << list2.size() << " elements\n";
    std::cout << "list3 has a max size of " << list3.max_size();
    std::cout << "\n=============================================" << std::endl;
    std::cout << "////front and back (pop, push)////" << std::endl;
    list2.push_back(5);
    std::cout << "i have pushed back a 5 on list2\n";
    list2.push_front(69);
    std::cout << "i have pushed front a 69 on list2\n";
    std::cout << "list 2 front: " << list2.front() << std::endl;
    std::cout << "list 2 back: " << list2.back() << std::endl;
    for(first = list2.begin(); first != list2.end(); ++first)
        std::cout << *first << ", ";
    list2.pop_back(); list2.pop_front();
    std::cout << "\ni have popped both front and back on list2\n";
    for(first = list2.begin(); first != list2.end(); ++first)
        std::cout << *first << ", ";
    std::cout << "\n=============================================" << std::endl;
    std::cout << "////swap (member and non-member)////" << std::endl;
    ft::list<int>epic1(10,6);
    ft::list<int>epic2(3,700);
    std::cout << "epic1: ";
        for(first = epic1.begin(); first != epic1.end(); ++first)
        std::cout << *first << ", ";
    std::cout << "\nepic2: ";
        for(first = epic2.begin(); first != epic2.end(); ++first)
        std::cout << *first << ", ";
    epic1.swap(epic2);
    std::cout << "\nswapped both lists:\n";
    std::cout << "epic1: ";
        for(first = epic1.begin(); first != epic1.end(); ++first)
        std::cout << *first << ", ";
    std::cout << "\nepic2: ";
        for(first = epic2.begin(); first != epic2.end(); ++first)
        std::cout << *first << ", ";
    std::cout << "\nswap (non-member)\n";
    swap(epic1, epic2);
    std::cout << "epic1: ";
    for(first = epic1.begin(); first != epic1.end(); ++first)
        std::cout << *first << ", ";
    std::cout << "\nepic2: ";
        for(first = epic2.begin(); first != epic2.end(); ++first)
        std::cout << *first << ", ";
    std::cout << "\n=============================================" << std::endl;
    std::cout << "////resize////" << std::endl;
    ft::list<int>list6;
    for (int i=0; i<10; ++i) list6.push_back(i);
    std::cout << "before resize: ";
    for(first = list6.begin(); first != list6.end(); ++first)
        std::cout << *first << ", ";
    list6.resize(20,100);
    std::cout << "\nafter resize: ";
    for(first = list6.begin(); first != list6.end(); ++first)
        std::cout << *first << ", ";
    std::cout << "\n=============================================" << std::endl;
    std::cout << "////reverse iterators, rbegin, rend////" << std::endl;
    ft::list<int>::reverse_iterator rit;
    list6.push_front(40);
 
    list6.push_front(28);

    list6.push_front(888);
    
    list6.push_back(888);

    
    std::cout << "\niterating normally through list6\n";
    for(first = list6.begin(); first != list6.end(); ++first)
        std::cout << *first << ", ";
    std::cout << "\nprinting list6 with a reverse iterator rend to rbegin\n";
    for(rit = list6.rend(); rit != list6.rbegin(); --rit)
        std::cout << *rit << ", ";
    std::cout << "\n\niterating normally through list6 backwards\n";
    for(first = list6.end(); first != list6.begin(); --first)
        std::cout << *first << ", ";
    std::cout << "\nprinting list6 with a reverse iterator rbegin to rend\n";
    for(rit = list6.rbegin(); rit != list6.rend(); ++rit)
        std::cout << *rit << ", ";
    std::cout << "\n=============================================" << std::endl;
    std::cout << "////comparative operators////" << std::endl;
    ft::list<int> a;
    a.push_back(10);a.push_back(20);a.push_back(30);
    ft::list<int> b;
    b.push_back(10);b.push_back(20);b.push_back(30);
    ft::list<int> c;
    c.push_back(30);c.push_back(20);c.push_back(10);

    if (a==b) std::cout << "a and b are equal\n";
    if (b!=c) std::cout << "b and c are not equal\n";
    if (b<c) std::cout << "b is less than c\n";
    if (c>b) std::cout << "c is greater than b\n";
    if (a<=b) std::cout << "a is less than or equal to b\n";
    if (a>=b) std::cout << "a is greater than or equal to b";
    std::cout << "\n=============================================" << std::endl;
    std::cout << "////reverse, remove and unique////" << std::endl;
    std::cout << "list6 normal:\n";
    for(first = list6.begin(); first != list6.end(); ++first)
        std::cout << *first << ", ";
    list6.reverse();
    std::cout << "\nlist6 reversed:\n";
    for(first = list6.begin(); first != list6.end(); ++first)
        std::cout << *first << ", ";
    std::cout << std::endl;
    list6.remove(888);
    std::cout << "\n888 removed\n";
    for(first = list6.begin(); first != list6.end(); ++first)
        std::cout << *first << ", ";
    list6.remove(100);
    std::cout << "\n100 removed\n";
    for(first = list6.begin(); first != list6.end(); ++first)
        std::cout << *first << ", ";
    list6.push_front(9);list6.push_front(9);list6.push_front(9);list6.push_front(9);list6.push_back(28);
    list6.unique();
    std::cout << "\nlist6 unique\n";
    for(first = list6.begin(); first != list6.end(); ++first)
        std::cout << *first << ", ";
    std::cout << "\nlist6 remove if element is odd\n";
    list6.remove_if(is_odd());
    for(first = list6.begin(); first != list6.end(); ++first)
        std::cout << *first << ", ";
    std::cout << "\n=============================================" << std::endl;
    std::cout << "////sort////" << std::endl;
    std::cout << "list6 sorted from smallest element to biggest element (default)\n";
    list6.sort();
    for(first = list6.begin(); first != list6.end(); ++first)
        std::cout << *first << ", ";
    std::cout << "\nlist6 sorted from biggest element to smallest element (custom binary predicate)\n";
    list6.sort(more_than);
    for(first = list6.begin(); first != list6.end(); ++first)
        std::cout << *first << ", ";
    std::cout << "\n=============================================" << std::endl;
    std::cout << "////splice////" << std::endl;
    ft::list<int> list7(5,444);
    first = list6.begin();
    first++;
    std::cout << "insertion of list7 which contains 444 5 times into the second position of list6\n";
    list6.splice(first, list7, list7.begin(), list7.end());
    for(first = list6.begin(); first != list6.end(); ++first)
        std::cout << *first << ", ";
        std::cout << "\ninsertion of the last element of list8 at the third position of the list\n";
    first = list6.begin();
    first++;first++;
    ft::list<int> list8(7,1);
    list6.splice(first, list8, --list8.end());
    for(first = list6.begin(); first != list6.end(); ++first)
        std::cout << *first << ", ";
        std::cout << "\n=============================================" << std::endl;
    std::cout << "////merge////" << std::endl;
    ft::list<double> epic;
    ft::list<double> cipriano;
    ft::list<double>::iterator it;

    epic.push_back(3.1);
    epic.push_back(2.2);
    epic.push_back(2.9);

    cipriano.push_back(3.7);
    cipriano.push_back(7.1);
    cipriano.push_back(1.4);

    epic.sort();
    cipriano.sort();
    std::cout << "epic sorted: ";
    for (it = epic.begin(); it!=epic.end(); ++it)
        std::cout << *it << " ";
    std::cout << "\ncipriano sorted: ";
    for (it = cipriano.begin(); it!=cipriano.end(); ++it)
        std::cout << *it << " ";
    epic.merge(cipriano);

  std::cout << "\nepic merged with cipriano.(cipriano is now empty)" << std::endl;

    cipriano.push_back (2.1);

    epic.merge(cipriano,mycomparison);

    std::cout << "epic contains: ";
    
    for (it = epic.begin(); it!=epic.end(); ++it)
        std::cout << *it << " ";
    std::cout << '\n';
    std::cout << "=============================================" << std::endl;
    //system("leaks a.out");
}