/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jluknar- <jluknar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 13:53:49 by jan               #+#    #+#             */
/*   Updated: 2021/03/30 11:54:41 by jluknar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft
{
    template <class T, class Container = vector<T> >
    class stack
    {
        public:
            typedef typename vector<T>::value_type  value_type;
            typedef typename vector<T>::size_type   size_type;
            typedef Container                       container_type;
        template <class value, class underlyingc>
        friend bool    operator==(const stack<value, underlyingc>& lhs, const stack<value, underlyingc>& rhs);
        template <class value, class underlyingc>
        friend bool    operator!=(const stack<value, underlyingc>& lhs, const stack<value, underlyingc>& rhs);
        template <class value, class underlyingc>
        friend bool    operator<(const stack<value, underlyingc>& lhs, const stack<value, underlyingc>& rhs);
        template <class value, class underlyingc>
        friend bool    operator<=(const stack<value, underlyingc>& lhs, const stack<value, underlyingc>& rhs);
        template <class value, class underlyingc>
        friend bool    operator>(const stack<value, underlyingc>& lhs, const stack<value, underlyingc>& rhs);
        template <class value, class underlyingc>
        friend bool    operator>=(const stack<value, underlyingc>& lhs, const stack<value, underlyingc>& rhs);
        protected:
            container_type _container;
        public:
            stack (const container_type& ctnr = container_type()) : _container(ctnr) {}
            stack(stack const &rhs) : _container(rhs._container){}
            stack &operator=(stack const &rhs) { _container = rhs._container; return (*this); }
            virtual ~stack(){}
        public:
            bool empty() const { return(_container.empty()); }
            size_t size() const { return(_container.size()); }
            value_type& top() { return(_container.back()); }
            const value_type& top() const { return(_container.back()); }
            void push (const value_type& val) { _container.push_back(val); }
            void pop() { _container.pop_back(); }
    };
    template <class T, class Container>
    bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    {
        return (lhs._container == rhs._container);
    }
    template <class T, class Container>
    bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    {
        return (!(lhs._container == rhs._container));
    }
    template <class T, class Container>
    bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    {
        return (lhs._container < rhs._container);
    }
    template <class T, class Container>
    bool operator<=  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    {
        if (lhs._container == rhs._container)
            return(true);
        return (lhs._container < rhs._container);
    }
    template <class T, class Container>
    bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    {
        return (lhs._container > rhs._container);
    }
        template <class T, class Container>
    bool operator>=  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    {
        if (lhs._container == rhs._container)
            return(true);
        return (lhs._container > rhs._container);
    }
}

#endif

/*
**LIST MEMBER FUNCTIONS TO DO:
**  -constructor            ✅  FUNCIONA
**  -destructor             ✅  FUNCIONA
**  -empty                  ✅  FUNCIONA
**  -top                    ✅  FUNCIONA
**  -size                   ✅  FUNCIONA
**  -push                   ✅  FUNCIONA
**  -pop                    ✅  FUNCIONA
**  =================================
**  NON-MEMBER FUNC OVERLOADS
**  =================================
**  -relational operators   ✅  FUNCIONA
**
*/