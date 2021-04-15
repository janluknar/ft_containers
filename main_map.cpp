/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_map.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jan <jan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 12:31:03 by jluknar-          #+#    #+#             */
/*   Updated: 2021/03/29 15:03:07 by jan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "map.hpp"
#include <map>

int main()
{
    std::cout << "==============/\\MAP TESTS/\\===================" << std::endl;
    std::cout << "////default constructor////" << std::endl;
    ft::map<int, std::string> map1;
    map1[800] = "valor 800";
	map1[74] = "valor 74";
	map1[68] = "valor 68";
	map1[22] = "valor 22";
	map1[81] = "valor 81";
	map1[3] = "valor 3";
	map1[55] = "valor 67";
	map1[156] = "valor 67";
    std::pair<int, std::string> a(7000, "hola");
    std::pair<int, std::string> t(7, "adios");
    map1.insert(a);
    map1.insert(map1.begin(), t);
    for(ft::map<int, std::string>::iterator first = map1.begin(); first != map1.end(); ++first)
        std::cout << "key: " << first->first << " || value: " << first->second << std::endl;
    std::cout << "////range constructor////" << std::endl;

    ft::map<int, std::string> map2(map1.begin(), map1.end());

    for(ft::map<int, std::string>::iterator first = map2.begin(); first != map2.end(); ++first)
        std::cout << "key: " << first->first << " || value: " << first->second << std::endl;
    std::cout << "////copy constructor////" << std::endl;
    ft::map<int, std::string> map4(map2);
    for(ft::map<int, std::string>::iterator first = map4.begin(); first != map4.end(); ++first)
        std::cout << "key: " << first->first << " || value: " << first->second << std::endl;
    std::cout << "////equals operator////" << std::endl;
    ft::map<int, std::string> map3 = map1;
    for(ft::map<int, std::string>::iterator first = map3.begin(); first != map3.end(); ++first)
        std::cout << "key: " << first->first << " || value: " << first->second << std::endl;
    std::cout << "////empty(), size(), max_size()////" << std::endl;
    ft::map<int, std::string> map5;
    if(map5.empty())
        std::cout << "map5 is empty" << std::endl;
    if(!(map4.empty()))
        std::cout << "map4 is not empty. it's got a size of: " << map4.size() << " and a max_size of: " << map4.max_size() << std::endl;
    std::cout << "////reverse iterators, rbegin and rend////" << std::endl;
    ft::map<int, std::string>::reverse_iterator rlast = map2.rend();
    for(ft::map<int, std::string>::reverse_iterator rfirst = map2.rbegin(); rfirst != rlast; ++rfirst)
        std::cout << "key: " << rfirst->first << " || value: " << rfirst->second << std::endl;
    std::cout << "////swap()////" << std::endl;
        ft::map<char,int> foo,bar;

        foo['x']=100;
        foo['y']=200;

        bar['a']=11;
        bar['b']=22;
        bar['c']=33;

        foo.swap(bar);

        std::cout << "foo contains:\n";
        for (ft::map<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';

        std::cout << "bar contains:\n";
        for (ft::map<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
        std::cout << it->first << " => " << it->second << '\n';
    std::cout << "////value_comp() and key_comp()////" << std::endl;
    ft::map<char,int> mymap;

        mymap['x']=1001;
        mymap['y']=2002;
        mymap['z']=3003;

        std::cout << "mymap contains:\n";

        std::pair<char,int> highest = *mymap.rbegin();

        ft::map<char,int>::iterator it = mymap.begin();
        do {
        std::cout << it->first << " => " << it->second << '\n'; //compares the highest key to current
     }     while ( mymap.value_comp()(*it++, highest) );        //prints the less or equal of the two
                                                                //(by default)
       ft::map<char,int> mymap2;

       ft::map<char,int>::key_compare mycomp = mymap2.key_comp(); //same stuff
                                                                  //but w/ keys instead of values
        mymap2['a']=100;
        mymap2['b']=200;
        mymap2['c']=300;

        std::cout << "mymap2 contains:\n";

        char highest2 = mymap2.rbegin()->first;

        ft::map<char,int>::iterator ite = mymap2.begin();
        do {
            std::cout << ite->first << " => " << ite->second << '\n';
        } while ( mycomp((*ite++).first, highest2) );

    std::cout << "////find////" << std::endl;

    ft::map<char,int> mymap3;
    ft::map<char,int>::iterator it3;

    mymap3['a']=50;
    mymap3['b']=100;
    mymap3['c']=150;
    mymap3['d']=200;

    it3 = mymap3.find('b');
    if (it3 != mymap3.end())
        mymap3.erase (it3);  //b was not found at the end of the map so it's erased

    // print content:
    std::cout << "elements in mymap:" << '\n';
    std::cout << "a => " << mymap3.find('a')->second << '\n';
    std::cout << "c => " << mymap3.find('c')->second << '\n';
    std::cout << "d => " << mymap3.find('d')->second << '\n';

    std::cout << "////count////" << std::endl;

     ft::map<char,int> mymap4;
        char c;

        mymap4 ['a']=101;
        mymap4 ['c']=202;
        mymap4 ['f']=303;

        for (c='a'; c<'h'; c++)
        {
            std::cout << c;
        if (mymap4.count(c)>0)
            std::cout << " is an element of mymap4.\n";
        else 
            std::cout << " is not an element of mymap4.\n";
        }
    //beacuse each key is unique, count can only return 1 if found, 0 if not found

    std::cout << "////lower_bound / upper_bound////" << std::endl;
    ft::map<char,int> mymap5;
    ft::map<char,int>::iterator itlow,itup;

    mymap5['a']=20;
    mymap5['b']=40;
    mymap5['c']=60;
    mymap5['d']=80;
    mymap5['e']=100;

    itlow=mymap5.lower_bound ('b');  // itlow points to b
    itup=mymap5.upper_bound ('d');   // itup points to e (not d!)

    mymap5.erase(itlow,itup);        // erases [itlow,itup)

    //lower_bound returns it to the key pointed at by k whereas
    //upper_bound returns it next to the key pointed at by k

    // print content:
    for (ft::map<char,int>::iterator it=mymap5.begin(); it!=mymap5.end(); ++it)
        std::cout << it->first << " => " << it->second << '\n';
    
    std::cout << "////equal_range////" << std::endl;

    ft::map<char,int> mymap6;

    mymap6['a']=10;
    mymap6['b']=20;
    mymap6['c']=30;

    std::pair<ft::map<char,int>::iterator,ft::map<char,int>::iterator> ret;
    ret = mymap6.equal_range('b');

    std::cout << "lower bound points to: ";
    std::cout << ret.first->first << " => " << ret.first->second << '\n';

    std::cout << "upper bound points to: ";
    std::cout << ret.second->first << " => " << ret.second->second << '\n';

    return 0;
}