/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_stack.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jluknar- <jluknar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 14:32:37 by jan               #+#    #+#             */
/*   Updated: 2021/04/02 10:47:50 by jluknar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.hpp"
#include <iostream>
#include <stack>

int main()
{
    std::cout << "==============/\\STACK TESTS/\\===================" << std::endl;
    std::cout << "/////default constructor/////\n";
    std::stack<int> stacc;
    std::cout << "/////empty(), size() and push()/////\n";
    if(stacc.empty())
        std::cout << "this stack is empty." << std::endl;
    std::cout << "pushing from 0 to 9" << std::endl;
    stacc.push(0);stacc.push(1);stacc.push(2);stacc.push(3);
    stacc.push(4);stacc.push(5);stacc.push(6);stacc.push(7);
    stacc.push(8);stacc.push(9);
    std::cout << "printing out size(): " << stacc.size() << std::endl;
    std::cout << "/////copy constructor/////\n";
    std::stack<int> stacc2(stacc);
    std::cout << "/////relational operators and pop()/////\n";
    if (stacc == stacc2)
        std::cout << "stacc is equal to stacc2" << std::endl;
    std::cout << "stacc2 gets 2 elements popped" << std::endl;
    stacc2.pop();
    stacc2.pop();
    if (stacc2 < stacc)
        std::cout << "stacc2 is smaller than stacc" << std::endl;
    if (stacc2 <= stacc)
        std::cout << "stacc2 is smaller than or equal to stacc" << std::endl;
    if (stacc > stacc2)
        std::cout << "stacc is greater than stacc" << std::endl;
    if (stacc >= stacc2)
        std::cout << "stacc is greater than or equal to stacc" << std::endl;
   std::cout << "/////top()/////\n";
   std::cout << "stacc2 top: " <<stacc2.top() << std::endl;
   std::cout << "stacc top: " << stacc.top() << std::endl;
   stacc2.pop(); stacc2.pop();
    std::cout << "stacc2 top: " <<stacc2.top() << std::endl;


    return 0;
}