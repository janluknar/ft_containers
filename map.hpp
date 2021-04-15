/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jan <jan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 16:18:47 by jluknar-          #+#    #+#             */
/*   Updated: 2021/03/29 13:41:17 by jan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include "./utils/node_map.hpp"
# include <limits>
# include <memory>
# include <type_traits>

namespace ft
{
    template<typename key_type, typename mapped_type>
    class node_map;
    template <typename key_type, typename mapped_type, typename comp = std::less<key_type> >
    class map
    {
	public:
		
        typedef std::less<key_type>                 compare;
        typedef node_map<key_type, mapped_type>     node;
        typedef node*                               node_pointer;
        typedef std::pair<key_type, mapped_type>    value_type;
        typedef compare                             key_compare;

        typedef size_t		                        size_type;
	    typedef ptrdiff_t	                        difference_type;

	    typedef value_type&                         reference;
	    typedef reference                           const_reference;
	    typedef value_type*                         pointer;
	    typedef const pointer                       const_pointer;
            
            /*declare iterators now*/

        protected:
            size_t          _size;
            node_pointer    _root;
            key_compare     _comp;
        public:
        class iterator
        {

            protected:
                bool            _ghost;
                node_pointer    _ptr;
            public:
	            typedef std::pair<key_type, mapped_type>    value_type;
	            typedef compare                             key_compare;

	            typedef value_type&                         reference;
	            typedef reference                           const_reference;
	            typedef value_type*                         pointer;
	            typedef const pointer                       const_pointer;

            public:
                iterator() : _ghost(false) {}
                iterator(node_pointer ptr) : _ghost(false), _ptr(ptr) {}
                iterator(iterator const &rhs): _ghost(rhs.get_is_ghost())
                {
                    if(this->get_is_ghost() == true)
                        _ptr = new node(*(rhs.as_node()));
                    else
                        _ptr = rhs._ptr;
                }
                virtual ~iterator()
                {
                    if(_ghost == true)
                        delete _ptr;
                }
                iterator &operator=(iterator const &rhs)
                {
                    if(_ghost == true)
                        delete _ptr;
                    _ptr = rhs._ptr;
                    return(*this);
                }

                node_pointer            &p(void) {return (this->_ptr);}
	            node_pointer            as_node(void) const {return (this->_ptr);}
                reference               operator*() {return this->_ptr->get_pair();}
                const_reference         operator*() const {return this->_ptr->get_pair();}
                pointer                 operator->() {return (&this->_ptr->get_pair());}
                const_pointer           operator->() const {return (&this->_ptr->get_pair());}

                iterator                &operator++()
                {
                    if(is_last_branch() == true)
                    {
                        node_pointer ghost_node = new node();

                        ghost_node->set_parent(_ptr);
                        set_is_ghost(true);
                        _ptr = ghost_node;
                        return(*this);

                    }
                    if(_ptr->get_right())
                    {
                        _ptr = _ptr->get_right();
                        go_leftmost();
                    }
                    else
                    {
                        while(_ptr->get_parent() && _ptr->get_parent()->get_left() != _ptr)
                            _ptr = _ptr->get_parent();
                        if(_ptr->get_parent()->get_left() == _ptr)
                            _ptr = _ptr->get_parent();
                    }
                    return(*this);
                }
                iterator                operator++(int)
                {
                    iterator tmp(*this);
                    ++(*this);
                    return (tmp);
                }
                iterator                &operator--()
                {
                    if(_ghost == true)
                    {
                        node_pointer    cache_parent = _ptr->get_parent();

                        delete _ptr;
                        set_is_ghost(false);
                        _ptr = cache_parent;
                        return(*this);
                    }
                    if(_ptr->get_left())
                    {
                        _ptr = _ptr->get_left();
                        go_rightmost();
                    }
                    else
                    {
                        while(_ptr->get_parent() && _ptr->get_parent()->get_right() != _ptr)
                            _ptr = _ptr->get_parent();
                        if(_ptr->get_parent()->get_right() == _ptr)
                            _ptr = _ptr->get_parent();
                    }
                    return(*this);
                }
                iterator                operator--(int)
                {
                    iterator tmp(*this);
                    --(*this);
                    return (tmp);
                }
                bool                    operator==(iterator const &rhs) const
                {
                    key_type        &a = _ptr->get_key();
                    key_type        &b = (*rhs).first;

                    if(this->_ghost == true && rhs._ghost == true)
                        return (true);
                    if(this->_ghost == true || rhs._ghost == true)
                        return (false);
                    return(a == b);
                }
                bool                    operator!=(iterator const &rhs) const {return (!(*this == rhs));}

                void                        set_is_ghost(bool val) {_ghost = val;}
                bool                        get_is_ghost() const {return (_ghost);}
				static const bool input_iter = true;

                void  go_leftmost()
                {
                    while(_ptr->get_left())
                        _ptr = _ptr->get_left();
                }

                void    go_rightmost()
                {
                    while(_ptr->get_right())
                        _ptr = _ptr->get_right();
                }
				bool    is_last_branch() 
        		{
           			node_pointer trace2root = _ptr;
                                                   
            		if(trace2root->get_right())
                		return(false);
            		while(trace2root->get_parent() && trace2root->get_parent()->get_right() == trace2root)
                		trace2root = trace2root->get_parent();
            		return(trace2root->get_parent() == 0);
       			}
        };

        class reverse_iterator
        {
 protected:
                bool            _ghost;
                node_pointer    _ptr;
            public:
	            typedef std::pair<key_type, mapped_type>    value_type;
	            typedef compare                             key_compare;

	            typedef value_type&                         reference;
	            typedef reference                           const_reference;
	            typedef value_type*                         pointer;
	            typedef const pointer                       const_pointer;

            public:
                reverse_iterator() : _ghost(false) {}
                reverse_iterator(node_pointer ptr) : _ghost(false), _ptr(ptr) {}
                reverse_iterator(iterator const &rhs): _ghost(rhs.get_is_ghost())
                {
                    if(this->get_is_ghost() == true)
                        _ptr = new node(*(rhs.as_node()));
                    else
                        _ptr = rhs.as_node();
                }
				reverse_iterator(const reverse_iterator &src): _ghost(src.get_is_ghost())
				{
					if (this->get_is_ghost() == true)
						_ptr = new node(*(src.as_node()));
					else
						_ptr = src._ptr;
				}
                virtual ~reverse_iterator()
                {
                    if(_ghost == true)
                        delete _ptr;
                }
                reverse_iterator &operator=(reverse_iterator const &rhs)
                {
                    if(_ghost == true)
                        delete _ptr;
                    _ptr = rhs._ptr;
                    return(*this);
                }

                node_pointer            &p(void) {return (this->_ptr);}
	            node_pointer            as_node(void) const {return (this->_ptr);}
                reference               operator*() {return this->_ptr->get_pair();}
                const_reference         operator*() const {return this->_ptr->get_pair();}
                pointer                 operator->() {return (&this->_ptr->get_pair());}
                const_pointer           operator->() const {return (&this->_ptr->get_pair());}

                reverse_iterator                &operator++()
                {
                    if(is_last_branch() == true)
                    {
                        node_pointer ghost_node = new node();

                        ghost_node->set_parent(_ptr);
                        set_is_ghost(true);
                        _ptr = ghost_node;
                        return(*this);

                    }
                    if(_ptr->get_left())
                    {
                        _ptr = _ptr->get_left();
                        go_rightmost();
                    }
                    else
                    {
                        while(_ptr->get_parent() && _ptr->get_parent()->get_right() != _ptr)
                            _ptr = _ptr->get_parent();
                        if(_ptr->get_parent()->get_right() == _ptr)
                            _ptr = _ptr->get_parent();
                    }
                    return(*this);
                }
                reverse_iterator                operator++(int)
                {
                    iterator tmp(*this);
                    ++(*this);
                    return (tmp);
                }
                reverse_iterator                &operator--()
                {
                    if(_ghost == true)
                    {
                        node_pointer    cache_parent = _ptr->get_parent();

                        delete _ptr;
                        set_is_ghost(false);
                        _ptr = cache_parent;
                        return(*this);
                    }
                    if(_ptr->get_right())
                    {
                        _ptr = _ptr->get_right();
                        go_leftmost();
                    }
                    else
                    {
                        while(_ptr->get_parent() && _ptr->get_parent()->get_left() != _ptr)
                            _ptr = _ptr->get_parent();
                        if(_ptr->get_parent()->get_left() == _ptr)
                            _ptr = _ptr->get_parent();
                    }
                    return(*this);
                }
                reverse_iterator                operator--(int)
                {
                    iterator tmp(*this);
                    --(*this);
                    return (tmp);
                }
                bool                    operator==(reverse_iterator const &rhs) const
                {
                    key_type        &a = _ptr->get_key();
                    key_type        &b = (*rhs).first;

                    if(this->_ghost == true && rhs._ghost == true)
                        return (true);
                    if(this->_ghost == true || rhs._ghost == true)
                        return (false);
                    return(a == b);
                }
                bool                    operator!=(reverse_iterator const &rhs) const {return (!(*this == rhs));}

                void                        set_is_ghost(bool val) {_ghost = val;}
                bool                        get_is_ghost() const {return (_ghost);}
				static const bool input_iter = true;

                void  go_leftmost()
                {
                    while(_ptr->get_left())
                        _ptr = _ptr->get_left();
                }

                void    go_rightmost()
                {
                    while(_ptr->get_right())
                        _ptr = _ptr->get_right();
                }

				bool    is_last_branch()
        		{
            		node_pointer trace2root = _ptr;
					
            		if(trace2root->get_left())
                		return(false);
            		while(trace2root->get_parent() && trace2root->get_parent()->get_left() == trace2root)
                		trace2root = trace2root->get_parent();
            		return(trace2root->get_parent() == 0);
        		}
        };

/*========================================================================================================*/

        typedef const iterator            const_iterator;
        typedef const reverse_iterator    const_reverse_iterator;

        map(const key_compare& compare = key_compare()) : _size(0), _root(NULL), _comp(compare){}

		template <class iter_>
        map (iter_ first, iter_ last, const key_compare& compare = key_compare(),
		typename std::enable_if<iter_::input_iter, iter_>::type = NULL) : _size(0), _root(NULL), _comp(compare)
		{
			this->insert(first, last);
		}
        map (const map& x): _size(0), _root(NULL), _comp(compare()) {*this = x;}
        map &operator=(map const &src)
        {
            this->clear();
		    if (src.size() > 0)
			    this->insert(src.begin(), src.end());
		    return (*this);
	    };

        virtual ~map() { this->clear(); };

        mapped_type& operator[](const key_type& k)
	    {
		    node_pointer	target_position = find_node(k);

		    if (_root == NULL)
		    {
			    value_type	new_root(value_type(k, mapped_type()));
			    _size++;
			    _root = new_node(new_root);
			    return (_root->get_val());
		    }
		    else if (target_position->get_key() != k)
		    {
			    value_type	new_pair(value_type(k, mapped_type()));
			    _size++;
			    return (assign_pair_nodes(target_position, new_pair));
		    }
		    return (target_position->get_val());
	    };

        bool empty() const { return (_size == 0); };

	    size_type size() const { return (_size); };

	    size_type max_size() const
	    {
			size_type nmax = std::numeric_limits<difference_type>::max();
			size_type omax = std::numeric_limits<size_type>::max() / (sizeof(value_type) + sizeof(node_pointer));
			return (nmax < omax ? nmax : omax);

	    };

        std::pair<iterator,bool> insert(const value_type& val) /*this works*/
	    {
		    if (this->size() > 0 &&
			    find_node(val.first)->get_pair() == val)
			    return (std::pair<iterator, bool>(this->end(), false)); /*element already exists in the map*/

		    (*this)[val.first] = val.second;
		
		    iterator new_node(_root);
		    while (*new_node != val && new_node != this->end())
			    new_node++;

		    return (std::pair<iterator, bool>(new_node, true));
	    };

        iterator insert(iterator position, const value_type& val)
	    {
		    if (this->size() > 0 &&
			    find_node(val.first)->get_pair() == val)
		    {
			    iterator	it = this->begin();

			    while (*it != val && it != this->end())
				    it++;
			    return (it);
		    }

		    node_pointer	pos_node;

		    while (position != this->end() &&
			    _comp((*position).first, val.first) == true)
			    position++;

		    if (position != this->end() &&
			    _comp((*position).first, val.first) == true)
		    {
			    node_pointer new_node = new node(val);

			    pos_node = position.as_node();

			    if (pos_node->get_right())
			    {
				    pos_node = pos_node->get_right();
				    while (pos_node->get_left())
					    pos_node = pos_node->get_left();
				    pos_node->set_left(new_node);
			    }
			    else
				    pos_node->set_right(new_node);
			    new_node->set_parent(pos_node);
			    _size++;
		    }
		    else
			    return ((this->insert(val)).first);

		    return (iterator(pos_node));
	    }

		template <class iter_>
        void insert(iter_ first, iter_ last
		, typename std::enable_if<iter_::input_iter, iter_>::type = NULL)
	    {
		    while (first != last)
		    {
			    this->insert(*first);
			    first++;
		    }
			
	    }
		
        size_type erase(const key_type& k)
	    {
		    node_pointer	node_k = find_node(k);

		    node_pointer	new_root;

		    if (node_k != NULL && node_k->get_key() != k)
			    return (0);

		    _size--;
		    if (node_k->get_left() == NULL && node_k->get_right() == NULL)
			    new_root = delete_branch(node_k);
		    else if (node_k->get_left() == NULL || node_k->get_right() == NULL)
			    new_root = delete_branch_one_child(node_k);
		    else
			    new_root = delete_branch_two_children(node_k);

		    if (new_root != NULL && new_root->get_parent() == NULL)
			    _root = new_root;
		    return (1);
	    }

        node_pointer delete_branch(node_pointer &leaf)
	    {
		    if (leaf->get_parent())
		    {
			    if (leaf->get_parent()->get_left() == leaf)
				    leaf->get_parent()->set_left(NULL);
			    else if (leaf->get_parent()->get_right() == leaf)
				    leaf->get_parent()->set_right(NULL);
		    }
		    delete leaf;

		    return (NULL);
	    }

        node_pointer delete_branch_one_child(node_pointer &leaf)
	    {
		    node_pointer child;

		    if (leaf->get_left())
			    child = leaf->get_left();
		    else
			    child = leaf->get_right();

		    if (leaf->get_parent() != NULL)
		    {
			    if (leaf->get_parent()->get_left() == leaf)
				    leaf->get_parent()->set_left(child);
			    else if (leaf->get_parent()->get_right() == leaf)
				    leaf->get_parent()->set_right(child);
		    }
		    child->set_parent(leaf->get_parent());
		    delete leaf;

		    return (child);
	    }

        node_pointer delete_branch_two_children(node_pointer &leaf)
	    {
		    node_pointer	to_exchange = leaf->get_right();

		    while (to_exchange->get_left())
			    to_exchange = to_exchange->get_left();

		    if (to_exchange == leaf->get_right())
		    {
			    to_exchange->set_parent(leaf->get_parent());
			    if (leaf->get_parent())
			    {
				    if (leaf->get_parent()->get_left() == leaf)
					    leaf->get_parent()->set_left(to_exchange);
				    else if (leaf->get_parent()->get_right() == leaf)
					    leaf->get_parent()->set_right(to_exchange);
			    }
			    to_exchange->set_parent(leaf->get_parent());
			    to_exchange->set_left(leaf->get_left());
			    leaf->get_left()->set_parent(to_exchange);
			    delete leaf;
		    }
		    else
		    {
			    to_exchange->get_parent()->set_left(to_exchange->get_right());
			    to_exchange->set_right(leaf->get_right());
			    to_exchange->get_right()->set_parent(to_exchange);
			    to_exchange->set_parent(leaf->get_parent());
			    to_exchange->set_left(leaf->get_left());
			    to_exchange->get_left()->set_parent(to_exchange);
			    if (to_exchange->get_parent())
			    {
				    if (to_exchange->get_parent()->get_left() == leaf)
					    to_exchange->get_parent()->set_left(to_exchange);
				    else if (to_exchange->get_parent()->get_right() == leaf)
					    to_exchange->get_parent()->set_right(to_exchange);
			    }
			    delete leaf;
		    }
		    return (to_exchange);
	    }

		template <class iter_>
        void erase(iter_ position,
		typename std::enable_if<iter_::input_iter, iter_>::type = NULL)
	    {
		    iter_	next = position;

		    next++;
		    erase(position, next);
	    }

		template <class iter_>
        void erase(iter_ first, iter_ last
		, typename std::enable_if<iter_::input_iter, iter_>::type = NULL)
	    {
		    iter_ prev = first;

		    while (first != last)
		    {
			    first++;
			    this->erase((*prev).first);
			    prev = first;
		    }
	    }


        void clear()
	    {
		    if (this->size() > 0)
			    this->erase(this->begin(), this->end());
		    _root = NULL;
	    }
		
		void swap (map &x)
		{
			size_t 			tmp_size = x._size;
			node_pointer	tmp_root = x._root;

			x._root = _root;
			x._size = _size;
			_root = tmp_root;
			_size = tmp_size;
		}

        iterator begin()
	    {
		    iterator temp(_root);

		    temp.go_leftmost();
		    return (temp);
	    };

        const_iterator begin() const
	    {
		    iterator temp(_root);

		    temp.go_leftmost();
		    return (const_iterator(temp));
	    }

		reverse_iterator rbegin() {return (reverse_iterator(--this->end()));}
		const_reverse_iterator rbegin() const {return (this->rbegin());}

        iterator end() { return (get_fake_it()); }

	    const_iterator end() const
	    {
		    iterator i(get_fake_it());
		    const_iterator ci(i);

		    return (ci);
		}

		reverse_iterator rend() {return (reverse_iterator(get_fake_reverse_it()));}
		const_reverse_iterator rend() const {return (rend());}

		key_compare key_comp() {return (key_compare());}

		class value_compare		//literally got it off cplusplus.com
		{
			public:
				typedef	bool		comparison_result_type;
				compare				comparation;

				value_compare(compare to_compare) : comparation(to_compare){}
				virtual ~value_compare(){}

				bool operator()(const value_type &first, const value_type &last) const
				{
					return (comparation(first.first, last.first));
				}

		};

		iterator find(const key_type& k)
		{
			if (find_node(k) != NULL && find_node(k)->get_key() != k)
				return (this->end());
			else
				return (iterator(find_node(k)));
		}

		const_iterator find(const key_type& k) const
		{
			if (find_node(k) != NULL && find_node(k)->get_key() != k)
				return (this->end());
			else
				return (const_iterator(find_node(k)));
		}

		value_compare value_comp() const {return (value_compare(compare()));}

		size_type count (const key_type& k) const
		{
			if(find(k) == this->end())
				return(0);
			else
				return(1);
		}

		iterator	lower_bound(const key_type& k)
		{
			iterator it = begin();

			while(_comp((*it).first, k) == true && it != end())
				++it;
			return(it);
		}

		const_iterator lower_bound(const key_type& k) const
		{
			return(lower_bound(k));
		}

		iterator	upper_bound(const key_type& k)
		{
			iterator it = begin();

			while(_comp((*it).first, k) == true && it != end())
				++it;
			
			if(it == end())
				return(end());
			if(it != begin())
				it++;
			return(it);
		}

		const_iterator upper_bound(const key_type& k) const
		{
			return (upper_bound(k));
		}

		std::pair<iterator, iterator> equal_range(const key_type& k)
		{
			std::pair<iterator, iterator> ret;
			ret.first = lower_bound(k);
			ret.second = upper_bound(k);

			return(ret);
		}

		std::pair<const_iterator, const_iterator> equal_range(const key_type& k) const
		{
			return(equal_range(k));
		}

        iterator get_fake_it() const
	    {
		    node_pointer	ghost_node = new_node();
		    iterator		rightmostnode(_root);

		    rightmostnode.go_rightmost();
		    ghost_node->set_parent(rightmostnode.as_node());

		    iterator	fake_ite(ghost_node);

		    fake_ite.set_is_ghost(true);
		    return (fake_ite);
	    }

		iterator	get_fake_reverse_it() const
		{
			node_pointer	ghost_node = new_node();
			iterator		leftmostnode(_root);

			leftmostnode.go_leftmost();
			ghost_node->set_parent(leftmostnode.as_node());

			iterator	fake_ite(ghost_node);

			fake_ite.set_is_ghost(true);
			return (fake_ite);
		}
        
        node_pointer new_node() const
	    {
		    node_pointer	new_node = new node();

		    return (new_node);
	    }

        node_pointer new_node(value_type &val) const
	    {
		    node_pointer	new_node = new node(val);

		    return (new_node);
	    }

        node_pointer find_node(const key_type &val) const
	    {
		    node_pointer temp = _root;

		    while (temp != NULL && temp->get_key() != val)
		    {
			    if (_comp(val, temp->get_key()) == true)
			    {
				    if (temp->get_left() != NULL)
					    temp = temp->get_left();
				    else
					    break;
			    }
			    else
			    {
				    if (temp->get_right() != NULL)
						temp = temp->get_right();
				    else
					    break;
			    }
		    }
		    return (temp);
	    }

        mapped_type& assign_pair_nodes(node_pointer node, value_type &val)
	    {
		    node_pointer	temp = new_node(val);

		    temp->set_parent(node);
		    if (_comp(val.first, node->get_key()) == true)
		    {
			    node->set_left(temp);
			    return (node->get_left()->get_val());
		    }
		    else
			    node->set_right(temp);
		    return (node->get_right()->get_val());
	    }

    };
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
**  ITERATORS
**  =================================
**  operator[]       ✅  FUNCIONA
**  operator++       ✅  FUNCIONA
**  operator--       ✅  FUNCIONA
**  ++operator       ✅  FUNCIONA
**  --operator       ✅  FUNCIONA
**  -begin           ✅  FUNCIONA
**  -end             ✅  FUNCIONA
**  -rbegin          ✅  FUNCIONA
**  -rend            ✅  FUNCIONA
**  =================================
**  MODIFIERS 
**  =================================
**  -insert          ✅  FUNCIONA
**  -erase           ✅  FUNCIONA
**  -swap            ✅	FUNCIONA
**  -clear           ✅  FUNCIONA
**  =================================
**  OBSERVERS
**  =================================
**  -value_comp      ✅  FUNCIONA
**  -key_comp        ✅  FUNCIONA
**  =================================
**  OPERATIONS
**  =================================
**  -find            ✅  FUNCIONA
**  -count           ✅  FUNCIONA
**  -lower_bound     ✅  FUNCIONA
**  -upper_bound     ✅  FUNCIONA
**  -equal_range     ✅  FUNCIONA  
** 
**
*/

#endif