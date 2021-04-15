/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_queue.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jluknar- <jluknar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 12:00:43 by jluknar-          #+#    #+#             */
/*   Updated: 2021/04/02 10:47:26 by jluknar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "queue.hpp"
#include <iostream>
#include <queue>

int main()
{
    std::cout << "==============/\\QUEUE TESTS/\\===================" << std::endl;
    std::cout << "/////default constructor/////\n";
    ft::queue<int> queue;
    std::cout << "/////empty(), size() and push()/////\n";
    if(queue.empty())
        std::cout << "this queue is empty." << std::endl;
    std::cout << "pushing from 0 to 9" << std::endl;
    queue.push(0);queue.push(1);queue.push(2);queue.push(3);
    queue.push(4);queue.push(5);queue.push(6);queue.push(7);
    queue.push(8);queue.push(9);
    std::cout << "printing out size(): " << queue.size() << std::endl;
    std::cout << "/////copy constructor/////\n";
    ft::queue<int> queue2(queue);
    std::cout << "/////relational operators and pop()/////\n";
    if (queue == queue2)
        std::cout << "queue is equal to queue2" << std::endl;
    std::cout << "queue2 gets 2 elements popped" << std::endl;
    queue2.pop();
    queue2.pop();
    if (queue < queue2)
        std::cout << "queue is smaller than queue2" << std::endl;
    if (queue <= queue2)
        std::cout << "queue is smaller than or equal to queue2" << std::endl;
    if (queue2 > queue)
        std::cout << "queue2 is greater than queue" << std::endl;
    if (queue2 >= queue)
        std::cout << "queue2 is greater than or equal to queue" << std::endl;
   std::cout << "/////front() and back()/////\n";
   std::cout << "queue2 front: " <<queue2.front() << std::endl;
   std::cout << "queue front: " << queue.front() << std::endl;
    std::cout << "queue2 back: " <<queue2.back() << std::endl;
   std::cout << "queue back: " << queue.back() << std::endl;
   queue2.pop(); queue2.pop();
   std::cout << "popped two elements:\n";
    std::cout << "queue2 front: " <<queue2.front() << std::endl;

    return 0;
}