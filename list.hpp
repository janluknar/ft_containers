/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jluknar- <jluknar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 11:27:45 by jluknar-          #+#    #+#             */
/*   Updated: 2021/03/30 14:20:28 by jluknar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
# define LIST_HPP

# include <limits>
# include <stdexcept>
# include "./utils/node.hpp"
# include "./utils/predicates.hpp"
# include <iostream>


/*no direct access, have to iterate through all elements to acess a node*/
/*lists are sequenced*/
/*each element keeps information on how to locate the next and previous elements*/

namespace ft
{
    template<typename value_type>
    class node;
    
    template <class T>
    class list
    {
    public:
        typedef T				                value_type;
		typedef size_t			                size_type;
		typedef T&				                reference;
		typedef const T&		                const_reference;
		typedef T*				                pointer;
		typedef const T*		                const_pointer;
		typedef std::ptrdiff_t	                difference_type;
        typedef node<value_type>                node_type;
        typedef node_type*                      node_pointer;
    private:
        void make_bounds(void)
        {
		    this->tail = new node<value_type>();
		    this->reset_bounds();
	    }
	    void reset_bounds(void)
        {
		    this->head = this->tail;
		    this->tail->previous() = 0;
		    this->tail->next() = 0;
	    }
    protected:
        node_pointer            head;
        node_pointer            tail;
        size_type               _size;
    public:
/*========================================================================================================*/  
    class iterator
    {

        protected:
            node_pointer        ptr;
        public:
			typedef T					            value_type;
			typedef value_type*			            pointer;
			typedef value_type const *	            const_pointer;
			typedef value_type&			            reference;
			typedef const value_type&	            const_reference;
			typedef std::ptrdiff_t 		            difference_type;
            typedef node<value_type>                node_type;
            typedef node_type*                      node_pointer;
        public:
            iterator():ptr(0){}
            iterator(node_pointer ptr):ptr(ptr){}
            iterator(iterator const &orig):ptr(orig.ptr){}
            virtual ~iterator(){};

            node_pointer            &p(void) {return (this->ptr);}
	        node_pointer            as_node(void) const {return (this->ptr);}
            reference               operator*() {return this->ptr->value();}
            const_reference         operator*() const {return this->ptr->value();}
            pointer                 operator->() {return (&this->ptr->value);}
            const_pointer           operator->() const {return (&this->ptr->value);}

            iterator                &operator++() {this->ptr = this->ptr->next(); return (*this);}
            iterator                operator++(int)
            {
                iterator tmp(*this);
                this->ptr = this->ptr->next();
                return (tmp);
            }
            iterator                &operator--() {this->ptr = this->ptr->previous(); return (*this);}
            iterator                operator--(int)
            {
                iterator tmp(*this);
                this->ptr = this->ptr->previous();
                return (tmp);
            }
            iterator                &operator+=(int n)
            {
                if(n > 0)
                {
                    for(int i = 0; i < n; i++)
                        this->ptr = this->ptr->next();
                }
                else
                {
                    for(int i = n; i > 0; i--)
                        this->ptr = this->ptr->previous();
                }
                return(*this);
            }
            iterator                operator+(int n) const {iterator tmp(*this); return (tmp += n);}
            iterator                &operator-=(int n){operator+=(-n); return(*this);}
            iterator                operator-(int n) const {iterator tmp(*this); return (tmp -= n);}
            bool                    operator==(iterator const &rhs) const {return (this->ptr == rhs.ptr);}
            bool                    operator!=(iterator const &rhs) const {return (this->ptr != rhs.ptr);}
            bool                    operator<(iterator const &rhs) const {return (this->ptr < rhs.ptr);}
            bool                    operator<=(iterator const &rhs) const {return (this->ptr <= rhs.ptr);}
            bool                    operator>(iterator const &rhs) const {return (this->ptr > rhs.ptr);}
            bool                    operator>=(iterator const &rhs) const {return (this->ptr >= rhs.ptr);}
        };

    class reverse_iterator : public iterator
    {
        public:
            reverse_iterator():iterator(0){}
            reverse_iterator(node_pointer ptr):iterator(ptr){}
            reverse_iterator(reverse_iterator const &orig):iterator(orig.ptr){}
            virtual ~reverse_iterator(){};

            iterator                &operator++() {this->ptr = this->ptr->previous(); return (*this);}
            iterator                &operator++(int) {this->ptr = this->ptr->previous();return (*this);}
            iterator                &operator--() {this->ptr = this->ptr->next(); return (*this);}
            iterator                &operator--(int) {this->ptr = this->ptr->next();return (*this);}
            iterator                &operator+=(int n)
            {
                if(n > 0)
                {
                    for(int i = 0; i < n; i++)
                        this->ptr = this->ptr->previous();
                }
                else
                {
                    for(int i = n; i > 0; i--)
                        this->ptr = this->ptr->next();
                }
            }
            iterator                &operator-=(int n){operator+=(-n); return(*this);}
        };
/*========================================================================================================*/
        
        typedef const iterator            const_iterator;
        typedef const reverse_iterator    const_reverse_iterator;

        list(): head(0), tail(0), _size(0)
        {
            make_bounds();
        }
        list(size_type n, const_reference value) : head(0), tail(0), _size(0)
        {
            make_bounds();
            this->assign(n, value);
        }
        list(iterator first, iterator last) : head(0), tail(0), _size(0)
        {
            make_bounds();
            assign(first, last);
        }
        list(const list &x)
        {
            make_bounds();
            assign(x.begin(), x.end());
        }
        virtual ~list()
        {
            this->clear();
            delete this->tail;
        }
        list &operator=(list const &other)
        {
		    this->assign(other.begin(), other.end());
		    return (*this);
        }

        iterator begin() {return iterator(this->head);}
        const_iterator begin() const {return const_iterator(this->head);}
        reverse_iterator rbegin() {return reverse_iterator(this->tail);}
        const_reverse_iterator rbegin() const {return const_reverse_iterator(this->tail);}

        iterator end() {return iterator(this->tail);}
        const_iterator end() const {return const_iterator(this->tail);}
        reverse_iterator rend() {return reverse_iterator(this->head);}
        const_reverse_iterator rend() const {return const_reverse_iterator(this->head);}   
        

        void pop_front()
        {
            if(this->_size == 1)
            {
                delete this->head;
                this->head = this->tail;
                this->tail->previous() = 0;
            }
            else if (this->_size >= 1)
            {
                node_pointer tmp = this->head->next();
                this->head->disconnect();
                delete this->head;
                this->head = tmp;
            }
        }

        void pop_back()
        {
            if(this->_size == 1)
                this->pop_front();
            else if (this->_size >= 1)
            {
                node_pointer tmp = this->tail->previous();
                this->tail->disconnect();
                delete this->tail;
                this->tail = tmp;
            }
        }

        iterator erase (iterator position)
        {
            this->_size--;
            if(position == this->begin())
            {
                pop_front();
                return this->begin();
            }
            else if(position == this->end())
            {
                pop_back();
                return this->end();
            }
            node_pointer next = position.as_node()->next();
            position.as_node()->disconnect();
            delete position.as_node();
            return(iterator(next));
        }

        iterator erase (iterator first, iterator last)
        {
            while(first != last)
                erase(first++);
            return(first);
        }

        void clear()
        {
		    this->erase(this->begin(), this->end());
		    this->reset_bounds();
        }

        void push_back (const_reference val)
        {
            node_pointer tmp = new node_type(val);
            this->tail->insert_before(tmp);
            if(this->_size == 0)
                this->head = tmp;
            ++this->_size;
        }

        void push_front (const_reference val)
        {
            node_pointer tmp = new node_type(val);
            this->tail->insert_after(tmp);
            if(_size == 0)
                this->tail->insert_before(tmp);
            else
                this->head->insert_before(tmp);
            this->head = tmp;
            ++_size;
        }

        void assign(iterator first, iterator last)
        {
            this->clear();
            while(first != last)
                this->push_back(*first++);
        }

        void assign (size_type n, const value_type& val)
        {
            this->clear();
            for(size_type i = 0; i < n; i++)
                this->push_back(val);
        }

        bool        empty() const {return (this->_size == 0);}
        size_type   size() const {return this->_size;}
        size_type   max_size() const
        {
            size_type nmax = std::numeric_limits<difference_type>::max();
			size_type omax = std::numeric_limits<size_type>::max() / (sizeof(node_type) - sizeof(pointer));
			return (nmax < omax ? nmax : omax);
        }

        reference front() {return this->head->value();}
        const_reference front() const {return this->head->value();}
        reference back() {return this->tail->previous()->value();}
        const_reference back() const {return this->tail->previous()->value();}

        void swap(list &x)
        {
            node_pointer    head_tmp = this->head;
            node_pointer    tail_tmp = this->tail;
            size_type       size_tmp = this->_size;
            this->head = x.head;
            this->tail = x.tail;
            this->_size = x._size;
            x.head = head_tmp;
            x.tail = tail_tmp;
            x._size = size_tmp;
        }

        void resize(size_type n, value_type val)
        {
            if(n == 0)
                clear();
            if(n < _size)
            {
                iterator first = this->begin();
                for(size_type i = 0; i < n; i++)
                    first++;
                this->erase(first, this->end());
            }
            if(n > _size)
            {
                for(size_type i = (n - _size); i < n; i++)
                    push_back(val);
            }
        }

        void sort(void)
        {
		    if (this->_size <= 1)
			    return ;
		    this->sort(&less_than<value_type>);
        }

        template<typename Compare>
	    void sort(Compare comp)
        {
		    if (this->_size <= 1)
			    return ;
		    iterator first = this->begin();
		    iterator last = this->end();
		    iterator next;
		    iterator tmp;

		    while (first != last) {
			    next = first;
			    while (++next != last) {
				    if ((*comp)(*next, *first)) {
					    if (first.as_node() == this->head)
						    this->head = next.as_node();
					    first.as_node()->swap(next.as_node());
					    tmp = next;
					    next = first;
					    first = tmp; /*mueve first desde el primer elemento que no esta ordenado*/
				    }
			    }
			    ++first;
		    }
	    }

        void reverse()
        {
            list tmp;
            iterator it;
            it = --this->end();
            while(it != this->begin())
            {
                tmp.push_back(*it);
                --it;
            }
            tmp.push_back(*it);
            clear();
            iterator first;
            for(first = tmp.begin(); first != tmp.end(); ++first)
                push_back(*first);
            tmp.clear();
        }

        void remove(const value_type& val)
        {
            iterator it = this->begin();
            while (it != this->end())
            {
                if(*it == val)
                    erase(it);
                it++;
            }
        }

        template <class Predicate>
        void remove_if (Predicate pred)
        {
            iterator it = this->begin();
            while (it != this->end())
            {
                if((pred)(*it))
                    erase(it);
                it++;
            }   
        } 

	    void unique(void)
        {
		    this->unique(&equal<value_type>);
	    }
	    template<typename BinaryPredicate>
	    void unique(BinaryPredicate binary_pred)
        {
		    iterator previous = this->begin();
		    iterator next = previous;
		    iterator last = this->end();

		    while (next != last)
            {
			    ++next;
			    if ((*binary_pred)(*previous, *next))
                {
				    this->erase(next);
				    next = previous;
			    }
                else
				    previous = next;
		    }
	    }

        void merge(list &x)
        {
            if (&x == this)
                return ;
            this->merge(x, &less_than<value_type>);
        }

        template <class Compare>
        void merge(list& x, Compare comp)
        {
            if(&x == this)
                return ;
            if(this->_size == 0)
            {
			    this->assign(x.begin(), x.end());
			    x.clear();
			    return ;
            }
            iterator f1 = this->begin();
		    iterator e1 = this->end();
		    iterator f2 = x.begin();
		    iterator e2 = x.end();

		    while (f1 != e1 && f2 != e2)
            {
			    if ((*comp)(*f2, *f1))
                {
				    x.head = f2.as_node()->next();
				    --x._size;
				    f2.as_node()->disconnect();
				    f1.as_node()->insert_before(f2.as_node());
				    if (f1 == this->begin())
					    this->head = this->head->previous();
				    ++this->_size;
				    f2 = x.begin();
			    }
                else
				    ++f1;
		    }
		    this->splice(e1, x);
        }

        void splice (iterator position, list& x)
        {
            this->splice(position, x, x.begin(), x.end());
        }

        void splice (iterator position, list& x, iterator i)
        {
            this->splice(position, x, i, ++i);
        }

        void splice (iterator position, list &x, iterator first, iterator last)
        {
		    while (first != last) {
			    node_pointer tmp = first++.as_node();
			    if (tmp == x.head)
				    x.head = tmp->next();
			    tmp->disconnect();
			    position.as_node()->insert_before(tmp);
			    if (position.as_node() == this->head)
				    this->head = tmp;
			    ++this->_size;
			    --x._size;
		}
		    if (x._size == 0)
			    x.reset_bounds();
        }
    };

    template<typename T>
    void swap(list<T> &x, list<T> &y)
    {
        x.swap(y);
    }

    template<typename value_type>
    bool operator==(list<value_type> const &lhs, list<value_type> const &rhs)
    {
        if(lhs.size() != rhs.size())
            return (false);
        typename list<value_type>::iterator it1 = lhs.begin();
        typename list<value_type>::iterator it2 = rhs.begin();
        while (it1 != lhs.end())
        {
            if(*it1 != *it2)
                return false;
            it1++;
            it2++;
        }
        return true;
    }
    template<typename value_type>
    bool operator!=(list<value_type> const &lhs, list<value_type> const &rhs)
    {
            if(!(lhs == rhs))
                return true;
            return false;
    }
    template <typename value_type>
    bool operator<(const list<value_type>& lhs, const list<value_type>& rhs)
    {
        typename list<value_type>::iterator lit = lhs.begin();
        typename list<value_type>::iterator rit = rhs.begin();
        if(lhs.size() < rhs.size())
            return true;
        if(lhs.size() > rhs.size())
            return false;
        while(lit != lhs.end() && rit != rhs.end())
        {
            if(*lit != *rit)
                return *lit < *rit;
            lit++;
            rit++;
        }
        return false;
    }
    template <typename value_type>
    bool operator<=(const list<value_type>& lhs, const list<value_type>& rhs)
    {
        return (!(rhs < lhs));
    }
    template <typename value_type>
    bool operator>(const list<value_type>& lhs, const list<value_type>& rhs)
    {
        return(!(lhs < rhs));
    }
    template <typename value_type>
    bool operator>=(const list<value_type>& lhs, const list<value_type>& rhs)
    {
        return(!(lhs < rhs));
    }
}

/*
**LIST MEMBER FUNCTIONS TO DO:
**  -constructor     ✅  FUNCIONA
**  -destructor      ✅  FUNCIONA
**  -operator=       ✅  FUNCIONA
**  =================================
**  CAPACITY   
**  =================================   
**  -empty           ✅  FUNCIONA
**  -size            ✅  FUNCIONA
**  -max_size        ✅  FUNCIONA
**  =================================
**  ELEMENT ACCESS  
**  =================================  
**  -front           ✅  FUNCIONA
**  -back            ✅  FUNCIONA
**  =================================
**  ITERATORS
**  =================================
**  operator++       ✅  FUNCIONA
**  operator--       ✅  FUNCIONA
**  ++operator       ✅  FUNCIONA
**  --operator       ✅  FUNCIONA
**  operator+=       ✅  FUNCIONA
**  operator-=       ✅  FUNCIONA
**  -begin           ✅  FUNCIONA
**  -end             ✅  FUNCIONA
**  -rbegin          ✅  FUNCIONA
**  -rend            ✅  FUNCIONA
**  =================================
**  MODIFIERS 
**  =================================
**  -assign          ✅  FUNCIONA
**  -push_front      ✅  FUNCIONA
**  -pop_front       ✅  FUNCIONA
**  -pop_back        ✅  FUNCIONA
**  -push_back       ✅  FUNCIONA
**  -insert          ✅  FUNCIONA
**  -erase           ✅  FUNCIONA
**  -swap            ✅  FUNCIONA
**  -resize          ✅  FUNCIONA
**  -clear           ✅  FUNCIONA
**  =================================
**  OPERATIONS
**  =================================
**  -splice          ✅  FUNCIONA
**  -remove          ✅  FUNCIONA
**  -remove_if       ✅  FUNCIONA
**  -unique          ✅  FUNCIONA 
**  -merge           ✅  FUNCIONA  
**  -sort            ✅  FUNCIONA 
**  -reverse         ✅  FUNCIONA
**  =================================
**  NON MEMBER RELATIONAL OPERATORS
**  =================================
**  -operator==      ✅  FUNCIONA
**  -operator!=      ✅  FUNCIONA
**  -operator<       ✅  FUNCIONA
**  -operator<=      ✅  FUNCIONA
**  -operator>       ✅  FUNCIONA
**  -operator>=      ✅  FUNCIONA
**  -swap            ✅  FUNCIONA
**
** 
**
*/


#endif