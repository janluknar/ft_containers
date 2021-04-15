/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_map.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jan <jan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 12:11:31 by jluknar-          #+#    #+#             */
/*   Updated: 2021/03/29 13:36:52 by jan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_MAP_HPP
# define NODE_MAP_HPP

#include <utility>

namespace ft
{
    template<typename key_type, typename mapped_type>
    class node_map{
    public:

        typedef node_map<key_type, mapped_type>	    node;
	    typedef node *					            node_ptr;
	    typedef const node *			            const_node_ptr;
	    typedef std::pair<key_type, mapped_type>    value_type;
	    typedef value_type				            pair;

    protected:
        node_ptr                _parent;
        node_ptr                _left;
        node_ptr                _right;
        pair                    _data;

    public:
        node_map() : _parent(0), _left(0), _right(0) {}
        node_map(value_type const &rhs) : _parent(0), _left(0), _right(0), _data(rhs) {}
        node_map(node_map const &rhs) : _parent(rhs._parent), _left(rhs._left), _right(rhs._right), _data(rhs._data) {/* *this = rhs; */}
        node_map &operator=(node_map const &rhs)
        {
            this->_parent = rhs._parent;
            this->_left = rhs._left;
            this->_right = rhs._right;
            this->_data = rhs._data;
            return(*this);
        }
        virtual ~node_map() {}

        void set_parent(const node_ptr node) {_parent = node;}
        void set_left(const node_ptr node) {_left = node;}
        void set_right(const node_ptr node) {_right = node;}
        
        void set_key(const key_type &key) {_data.first = key;}
        void set_value(const mapped_type &value) {_data.second = value;}
        void set_pair(const pair &data) {*_data = data;}
        
        const_node_ptr  get_current() const {return (this);}
        node_ptr        get_parent() const {return(_parent);}
        node_ptr        get_left() const {return(_left);}
        node_ptr        get_right() const {return(_right);}

        key_type	    &get_key(void) { return (_data.first); };
	    key_type const	&get_key(void) const { return (_data.first); };
	    mapped_type     &get_val(void) { return (_data.second); };
	    pair	        &get_pair(void) { return (_data); };
	    pair const	    &get_pair(void) const { return (_data); };

    };
}


#endif