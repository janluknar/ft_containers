/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jluknar- <jluknar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 12:30:04 by jluknar-          #+#    #+#             */
/*   Updated: 2021/03/15 14:19:34 by jluknar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_HPP
# define NODE_HPP

# include <cstring>

namespace ft
{
    template<typename value_type>
    class node{
    protected:
	    node<value_type> *_previous;
	    value_type _value;
	    node<value_type> *_next;
    public:
        node() : _previous(0), _value(), _next(0) {}
        node(value_type const &rhs): _previous(0), _value(rhs), _next(0) {}
	    node(node *_previous, value_type const &rhs, node *_next = 0) : _previous(_previous), _value(rhs), _next(_next) {}
        node(node const &rhs): _previous(rhs._previous), _value(rhs._value), _next(rhs._next) {}
	    virtual ~node() {}

        node &operator=(node const &rhs)
        {
		    this->_previous = rhs._previous;
		    this->_value = rhs._value;
		    this->_next = rhs._next;
		    return (*this);
	    }

        void insert_before(node *rhs)
        {
            if (this->_previous)
            {
                rhs->_previous = this->_previous;
                this->_previous->_next = rhs;
            }
            rhs->_next = this;
            this->_previous = rhs;
        }

        void insert_after(node *rhs)
        {
            if (this->_next)
            {
                rhs->_next = this->_next;
                this->_next->_previous = rhs;
            }
            rhs->_previous = this;
            this->_next = rhs;
        }

        void disconnect(void)
        {
            if(this->_previous)
                this->_previous->_next = this->_next;
            if(this->_next)
                this->_next->_previous = this->_previous;
        }

        void swap(node *rhs)
        {
		    if (this->_next == rhs) 
            {
			    if (this->_previous)
				    this->_previous->_next = rhs;
			    rhs->_previous = this->_previous;
			    this->_previous = rhs;
			    if (rhs->_next)
				    rhs->_next->_previous = this;
			    this->_next = rhs->_next;
			    rhs->_next = this;
            }
            else if (this->_previous == rhs)
            {
			    if (rhs->_previous)
				    rhs->_previous->_next = this;
			    this->_previous = rhs->_previous;
			    rhs->_previous = this;
			    if (this->_next)
				    this->_next->_previous = rhs;
			    rhs->_next = this->_next;
			    this->_next = rhs;
		    } 
            else
            {
			    node<value_type> *m_previous = this->_previous;
			    node<value_type> *m_next = this->_next;

			    if (this->_previous)
				    this->_previous->_next = rhs;
			    if (this->_next)
				    this->_next->_previous = rhs;
			    this->_previous = rhs->_previous;
			    this->_next = rhs->_next;
			    if (rhs->_previous)
				    rhs->_previous->_next = this;
			    if (rhs->_next)
				    rhs->_next->_previous = this;
			    rhs->_previous = m_previous;
			    rhs->_next = m_next;
		    }
        }
        void reverse(void)
        {
		node<value_type> *tmp = this->_previous;
		this->_previous = this->_next;
		this->_next = tmp;
	    }
        void swap_values(node *rhs)
        {
		    value_type tmp;
		    std::memmove(static_cast<void*>(&tmp), static_cast<void*>(&rhs->value), 1);
		    std::memmove(static_cast<void*>(&rhs->value), static_cast<void*>(&this->value), 1);
		    std::memmove(static_cast<void*>(&this->value), static_cast<void*>(&tmp), 1);
        }

        /*member attributes are private and so here are some methods to access node attributes*/

        value_type &value(){return (this->_value);}
        value_type const &value() const {return (this->_value);}
        node  *&previous(){return this->_previous;}
        node* const previous() const {return this->_previous;}
        node  *&next(){return this->_next;}
        node* const next() const {return this->_next;}
    };
}

#endif