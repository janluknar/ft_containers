/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jluknar- <jluknar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 11:16:23 by jluknar-          #+#    #+#             */
/*   Updated: 2021/03/30 14:09:50 by jluknar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "vector.hpp"
#include <stdlib.h>
#include <iostream>
#include <vector>

int main(void)
{
    std::cout << "==============/\\VECTOR TESTS/\\===================" << std::endl;
    std::cout << "////default constructor////" << std::endl;
    ft::vector<int> vec1;
    ft::vector<int>::iterator first; /*default iterator*/
    for(first = vec1.begin(); first != vec1.end(); ++first)
        std::cout << *first << ", ";
    std::cout << "\n=============================================" << std::endl;
    ft::vector<int> vec2(8, 400);
    std::cout << "////constructor fills vector with value and pre-defined size////" << std::endl;
    for(first = vec2.begin(); first != vec2.end(); ++first)
        std::cout << *first << ", ";
    std::cout << "\n=============================================" << std::endl;
    /*constructor that takes iterators*/
    ft::vector<int> vec3(vec2.begin(), vec2.end());
    std::cout << "////constructor that takes an iterator range////" << std::endl;
    for(first = vec3.begin(); first != vec3.end(); ++first)
        std::cout << *first << ", ";

    std::cout << "\n=============================================" << std::endl;
    std::cout << "////push_back, pop_back and dynamic resize test////" << std::endl;
    vec1.push_back(1); vec1.push_back(2); vec1.push_back(3); 
    vec1.push_back(4); vec1.push_back(5); vec1.push_back(6); 
    vec1.push_back(7); vec1.push_back(8); vec1.push_back(9); 
    vec1.push_back(10); vec1.push_back(11); vec1.push_back(12); 
    for(first = vec1.begin(); first != vec1.end(); ++first)
        std::cout << *first << ", ";
    vec1.resize(20, 1);
    std::cout << std::endl;
    for(first = vec1.begin(); first != vec1.end(); ++first)
        std::cout << *first << ", ";
    vec1.pop_back();
    vec1.pop_back();
    std::cout << "\n////popped back the last two elements////" << std::endl;
    for(first = vec1.begin(); first != vec1.end(); ++first)
        std::cout << *first << ", ";
    std::cout << "\n=============================================" << std::endl;
    std::cout << "////string vector test////" << std::endl;
    ft::vector<std::string>::iterator epic;
    ft::vector<std::string>::iterator epic2;
    ft::vector<std::string> vec4(2, "wii");
    std::cout << "fuckd up in the crib playing ";
    for(epic = vec4.begin(); epic != vec4.end(); ++epic)
        std::cout << *epic << ", ";
    std::cout << "\n=============================================" << std::endl;
    std::cout << "////equals operator test////" << std::endl;
    vec3 = vec1;
    for(first = vec3.begin(); first != vec3.end(); ++first)
        std::cout << *first << ", ";
    std::cout << "\n=============================================" << std::endl;
    std::cout << "////operators ++ and -- (ITERATOR)////" << std::endl;
    first = vec3.begin();
    std::cout << "actual: " << *first << std::endl;
    first++;
    std::cout << "advancing++ 1: " << *first << std::endl;
    first--;
    std::cout << "subtracting-- 1: " << *first << std::endl;
    ++first;
    std::cout << "++advancing 1: " << *first << std::endl;
    --first;
    std::cout << "--subtracting 1: " << *first;
    std::cout << "\n=============================================" << std::endl;
    std::cout << "////operators == and != (ITERATOR)////" << std::endl;
    if (*first == 1)
        std::cout << "the current vector position is equals to 1" << std::endl;
    ++first;
    std::cout << "++advancing 1: " << *first << std::endl;
    if (*first != 1)
        std::cout << "the current vector position is not equals to 1";
    std::cout << "\n=============================================" << std::endl;
    std::cout << "////operators += and -= (ITERATOR)////" << std::endl;
    first = vec3.begin();
    std::cout << "actual: " << *first << std::endl;
    first+= 5;
    std::cout << "advancing += 5: " << *first << std::endl;
    first-= 2;
    std::cout << "subtracting -= 2: " << *first;
    std::cout << "\n=============================================" << std::endl;
    std::cout << "////operators ==, !=, >, <, >= and <= (VECTOR NON MEMBER FUNCTIONS)////" << std::endl;
    std::cout << "vec1: ";
    for(first = vec1.begin(); first != vec1.end(); ++first)
        std::cout << *first << ", ";
    std::cout << "\nvec2: ";    
    for(first = vec2.begin(); first != vec2.end(); ++first)
        std::cout << *first << ", ";
    std::cout << "\nvec3: ";   
    for(first = vec3.begin(); first != vec3.end(); ++first)
        std::cout << *first << ", ";
    std::cout << "\nvec5: ";
    ft::vector<int> vec5;
    for(first = vec5.begin(); first != vec5.end(); ++first)
        std::cout << *first << ", ";
    std::cout << std::endl;
    if(vec3[1] == vec3[19])
        std::cout << vec3[1] << " is equals to " << vec3[19] << std::endl;
    if(vec3[1] != vec3[5])
        std::cout << vec3[1] << " is not equals to " << vec3[5] << std::endl;
    if(vec2 < vec3)
        std::cout << "vec2 is less than vec3" << std::endl;
    if(vec3 > vec5)
        std::cout << "vec3 is greater than vec5" << std::endl;
    if(vec2 <= vec3)
        std::cout << "vec2 is less or equal to vec3" << std::endl;
    if(vec3 >= vec5)
        std::cout << "vec3 is greater or equal to vec5";
    std::cout << "\n=============================================" << std::endl;
    std::cout << "////empty, size, capcity and max_size tests////" << std::endl;
    if(vec5.empty())
        std::cout << "vec5 is empty" << std::endl;
    if(!(vec3.empty()))
        std::cout << "vec3 is not empty" << std::endl;
    std::cout << "vec5's size is: " << vec5.size() << std::endl;
    std::cout << "vec3's size is: " << vec3.size() << std::endl;
    std::cout << "vec3's capacity is: " << vec3.capacity() << std::endl;
    std::cout << "vec3's max size is: " << vec3.max_size();
    std::cout << "\n=============================================" << std::endl;
    std::cout << "////at, clear, insert and erase tests////" << std::endl;
    vec5.insert(vec5.begin(), 879);
    vec5.insert(vec5.end(), 6, 65);
    std::cout << "vec5's value at position 0 is: " << vec5.at(0) << std::endl;
    std::cout << "i have inserted 879 at the first position and 6 times 65 at the last position\n";
    for(first = vec5.begin(); first != vec5.end(); ++first)
        std::cout << *first << ", ";
    vec5.erase((first = vec5.begin()));
    vec5.erase(first + 1, vec5.end());
    std::cout << "\ni have erased the first element of the vector and 5 times 65. vec5's size now is: "<< vec5.size() << "\n";
    for(first = vec5.begin(); first != vec5.end(); ++first)
        std::cout << *first << ", ";
    vec5.clear();
    std::cout << "\ni have  cleared all the contents within vec5" << std::endl;
    if(vec5.empty())
        std::cout << "vec5 is empty";
    std::cout << "\n=============================================" << std::endl;
    std::cout <<  "////swap(member) and swap(non member) tests////" << std::endl;
    std::cout << "swap(member):\n";
    ft::vector<int> foo (3,100);   // three ints with a value of 100
    ft::vector<int> bar (5,200);

    foo.swap(bar);
    std::cout << "foo contains:";
    for (unsigned i=0; i<foo.size(); i++)
        std::cout << ' ' << foo[i];
    std::cout << '\n';

    std::cout << "bar contains:";
    for (unsigned i=0; i<bar.size(); i++)
        std::cout << ' ' << bar[i];
    std::cout << "\nswap(non-member):\n";
    swap(foo,bar);
    std::cout << "foo contains:";
    for (unsigned i=0; i<foo.size(); i++)
        std::cout << ' ' << foo[i];
    std::cout << '\n';

    std::cout << "bar contains:";
    for (unsigned i=0; i<bar.size(); i++)
        std::cout << ' ' << bar[i];
    std::cout << "\n=============================================" << std::endl;
    std::cout << "////reverse iterators, rbegin, rend////" << std::endl;
    ft::vector<int> vec6;
    vec6.push_back(420);vec6.push_back(1);vec6.push_back(2);vec6.push_back(3);
    ft::vector<int>::reverse_iterator rit;
    rit = vec6.rbegin();
    std::cout << *vec6.rend() << std::endl;
    std::cout << *vec6.rbegin() << std::endl;
    std::cout << "printing vec6 with a reverse iterator rend to rbegin\n";
    for(rit = vec6.rend(); rit != vec6.rbegin(); --rit)
        std::cout << *rit << ", ";
    std::cout << "printing vec6 with a reverse iterator rbegin to rend\n";
    for(rit = vec6.rbegin(); rit != vec6.rend(); ++rit)
        std::cout << *rit << ", ";
    std::cout << std::endl;
    /*checking for leaks*/
    //system("leaks main_stack");
}