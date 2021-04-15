/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jluknar- <jluknar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 11:51:59 by jluknar-          #+#    #+#             */
/*   Updated: 2021/03/30 14:01:33 by jluknar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_HPP
# define QUEUE_HPP

# include "vector.hpp"

namespace ft
{
    template <class T, class Container = vector<T> >
    class queue
    {
        public:
            typedef typename vector<T>::value_type  value_type;
            typedef typename vector<T>::size_type   size_type;
            typedef Container                       container_type;
        template <class value, class underlyingc>
        friend bool    operator==(const queue<value, underlyingc>& lhs, const queue<value, underlyingc>& rhs);
        template <class value, class underlyingc>
        friend bool    operator!=(const queue<value, underlyingc>& lhs, const queue<value, underlyingc>& rhs);
        template <class value, class underlyingc>
        friend bool    operator<(const queue<value, underlyingc>& lhs, const queue<value, underlyingc>& rhs);
        template <class value, class underlyingc>
        friend bool    operator<=(const queue<value, underlyingc>& lhs, const queue<value, underlyingc>& rhs);
        template <class value, class underlyingc>
        friend bool    operator>(const queue<value, underlyingc>& lhs, const queue<value, underlyingc>& rhs);
        template <class value, class underlyingc>
        friend bool    operator>=(const queue<value, underlyingc>& lhs, const queue<value, underlyingc>& rhs);
        protected:
            container_type _container;
        public:
            queue (const container_type& ctnr = container_type()) : _container(ctnr) {}
            queue(queue const &rhs) : _container(rhs._container){}
            queue &operator=(queue const &rhs) { _container = rhs._container; return (*this); }
            virtual ~queue(){}
        public:
            bool empty() const { return(_container.empty()); }
            size_t size() const { return(_container.size()); }
            value_type& front() { return(_container.front()); }
            const value_type& front() const { return(_container.front()); }
            value_type& back() { return(_container.back()); }
            const value_type& back() const { return(_container.back()); }
            void push (const value_type& val) { _container.push_back(val); }
            void pop() { _container.erase(_container.begin()); }
    };
    template <class T, class Container>
    bool operator== (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
    {
        return (lhs._container == rhs._container);
    }
    template <class T, class Container>
    bool operator!= (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
    {
        return (!(lhs._container == rhs._container));
    }
    template <class T, class Container>
    bool operator<  (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
    {
        return (rhs._container < lhs._container);
    }
    template <class T, class Container>
    bool operator<=  (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
    {
        if (lhs._container == rhs._container)
            return(true);
        return (rhs._container < lhs._container);
    }
    template <class T, class Container>
    bool operator>  (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
    {
        return (rhs._container > lhs._container);
    }
        template <class T, class Container>
    bool operator>=  (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
    {
        if (lhs._container == rhs._container)
            return(true);
        return (rhs._container > lhs._container);
    }
}

#endif

/*
**LIST MEMBER FUNCTIONS TO DO:
**  -constructor            ✅  FUNCIONA
**  -destructor             ✅  FUNCIONA
**  -empty                  ✅  FUNCIONA
**  -size                   ✅  FUNCIONA
**  -front                  ✅  FUNCIONA
**  -back                   ✅  FUNCIONA
**  -push                   ✅  FUNCIONA
**  -pop                    ✅  FUNCIONA
**  =================================
**  NON-MEMBER FUNC OVERLOADS
**  =================================
**  -relational operators   ✅  FUNCIONA
**
*/