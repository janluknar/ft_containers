/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jluknar- <jluknar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 11:16:13 by jluknar-          #+#    #+#             */
/*   Updated: 2021/04/02 10:42:13 by jluknar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <limits>
# include <stdexcept>

namespace ft
{

    template <class T>
    class vector{
    public:
        typedef T				value_type;
		typedef size_t			size_type;
		typedef T&				reference;
		typedef const T&		const_reference;
		typedef T*				pointer;
		typedef const T*		const_pointer;
		typedef std::ptrdiff_t	difference_type;
        
    protected:
        size_type               _size;
        size_type               _capacity;
        value_type              *vec;
    public:
        class iterator{
    protected:
            pointer                     ptr;
    public:
			typedef T					value_type;
			typedef value_type*			pointer;
			typedef value_type const *	const_pointer;
			typedef value_type&			reference;
			typedef const value_type&	const_reference;
			typedef std::ptrdiff_t 		difference_type;
    public:
            iterator():ptr(NULL){}
            iterator(pointer ptr):ptr(ptr){}
            iterator(iterator const &orig):ptr(orig.ptr){}
            virtual ~iterator(){};
            iterator &operator=(iterator const &orig){this->ptr = orig.ptr; return(*this);}

            reference               operator*(){return *this->ptr;}  //dereferenced
            const_reference         operator*() const {return *this->ptr;}   //const dereferenced
            pointer                 operator->(){return this->ptr;}  //pointer
            const_reference         operator->() const {return this->ptr;}   //const pointer
            reference               operator[](int n) {return (*(this->ptr + n));}  //dereferenced
            const_reference         operator[](int n) const {return (*(this->ptr + n));}    //const dereferenced
            reference               operator++(){++ptr; return *ptr;}    //it++
            iterator                operator++(int) {iterator tmp(*this); this->operator++(); return tmp;} //++it
            reference               operator--(){--ptr; return *ptr;}    //it--
            iterator                operator--(int) {iterator tmp(*this); this->operator--(); return tmp;} //--it
            reference               operator+=(int n) {ptr += n; return *ptr;}
            iterator                operator+(int n){ return iterator(ptr + n);}
            reference               operator-=(int n) {ptr -= n; return *ptr;}
            iterator                operator-(int n){ return iterator(ptr - n);}
            bool                    operator==(const iterator &it){return (ptr == it.ptr);}
            bool                    operator!=(const iterator &it){return (ptr != it.ptr);}
        };
        
        class reverse_iterator : public iterator{
        public:
            reverse_iterator(pointer ptr):iterator(ptr){}
            reverse_iterator():iterator(NULL){}
            reverse_iterator(iterator const &orig):iterator(orig.ptr){}

            reference               operator++(){--this->ptr; return *this->ptr;}    //++it
            iterator                operator++(int) {iterator tmp(*this); this->operator++(); return tmp;} //it++
            reference               operator--(){++this->ptr; return *this->ptr;}    //--it
            iterator                operator--(int) {iterator tmp(*this); this->operator--(); return tmp;} //it++
            reference               operator+=(int n) {this->ptr -= n; return *this->ptr;}
            reference               operator-=(int n) {this->ptr += n; return *this->ptr;}
        };

        typedef const iterator            const_iterator;
        typedef const reverse_iterator    const_reverse_iterator;

        /***************************************************CONSTRUCTORS*****************************************************/

        vector():_size(0),_capacity(1),vec(new T[_capacity]){}

        vector(vector const &orig):_size(orig._size),_capacity(orig._capacity),vec(new T[_capacity])
        {
          	for (size_type i = 0; i < _size; ++i)
				vec[i] = orig.vec[i];  
        }

        vector &operator=(vector const &orig)
        {
            this->_size = orig._size;
            this->_capacity = orig._capacity;
            this->vec = new value_type[_capacity];
            for(size_type i = 0; i < _size; ++i)
                this->vec[i] = orig.vec[i];
            return (*this);
        }

        vector(size_type n, const value_type &val)
        {
            vec = new value_type[2 * n];
            for (size_type i = 0; i < n; ++i)
				vec[i] = val;
			_size = n;
			_capacity = 2 * n;
        }

        vector (iterator first, iterator last)
        {
           this->_capacity = distance(first, last) * 2; /*esto alommejor puede dar problemas*/
           this->_size = distance(first, last);
           this->vec = new value_type[this->_capacity];
           this->assign(first, last);
        }

        virtual ~vector(){delete [] vec;}

        /*****************************************************ITERATORS*******************************************************/

        iterator                            begin() {return iterator(&vec[0]);}
        const_iterator                      begin() const {return iterator(&vec[0]);}
        iterator                            end() {return iterator(&vec[_size]);};
        const_iterator                      end() const {return iterator(&vec[_size]);}
        reverse_iterator                    rbegin() {return reverse_iterator(&vec[_size - 1]);}
        const_reverse_iterator              rbegin() const {return reverse_iterator(&vec[_size - 1]);}
        reverse_iterator                    rend() {return reverse_iterator(&vec[-1]);}
        const_reverse_iterator              rend() const {return reverse_iterator(&vec[-1]);}

        /*************************************************MEMBER FUNCTIONS****************************************************/

        /**************************************************ELEMENT ACCESS*****************************************************/

        reference               operator[](size_type n) {return vec[n];}  //dereferenced
        const_reference         operator[](size_type n) const {return vec[n];}    //const dereferenced


        reference           at(size_type pos)
        {
            if(pos < 0 || pos >= _size)
                throw (std::out_of_range("Vector index out of range"));
            else
                return (vec[pos]);
        }

        const_reference     at(size_type pos) const
        {
			if (pos < 0 || pos >= _size)
				throw (std::out_of_range("Vector index out of range"));
			return vec[pos];
		}

        reference           front()
        {
            return (vec[0]);
        }

        const_reference     front() const
        {
            return (vec[0]);
        }

        reference           back()
        {
            return (vec[_size - 1]);
        }

        const_reference     back() const
        {
            return (vec[_size - 1]);
        }

        /**********************************************************CAPACITY***************************************************/

        bool        empty() const {return (_size == 0);}

        size_type   size() const {return _size;}

        size_type   max_size() const
        {
            size_type nmax = std::numeric_limits<difference_type>::max();
			size_type omax = std::numeric_limits<size_type>::max() / sizeof(value_type);
			return (nmax < omax ? nmax : omax);
        }

        void        resize(size_type n, value_type val = value_type())
        {
			if (n > _capacity)
				reserve(n);
			if (n > _size)
			{
				for (size_type i = _size; i < n; ++i)
					vec[i] = val;
				_size = n;
			}
			else if (n < _size)
			{
				for (size_type i = n; i < _size; ++i)
					vec[i].~value_type();
				_size = n;
			}
		}

        void        reserve(size_type new_cap)
        {
			if (new_cap < _capacity)
				return;
			_capacity *= 2;
			value_type *tmp = new value_type[_capacity];
			for (size_type i = 0; i < _size; ++i)
				tmp[i] = vec[i];
			delete [] vec;
			vec = tmp;
        }

        size_type   capacity() const {return _capacity;}


        /**********************************************************MODIFIERS***************************************************/

        void        clear()
        {
			while (_size)
				pop_back();
        }

		iterator insert (iterator position, const value_type& val)
        {
			insert(position, 1, val);
			return position;
		}

        void    insert( iterator pos, size_type count, const value_type& value )
        {
    		vector tmp(pos, end());
			this->_size -= distance(pos, end());
			while (count--)
				push_back(value);
			iterator it = tmp.begin();
			while (it != tmp.end()) {
				push_back(*it);
				++it;
			}     
        }
        
        template<typename Iterator>std::ptrdiff_t distance(Iterator first, Iterator last)
        {
		    std::ptrdiff_t dist = 0;
		    while (first != last) 
            {
			    ++dist;
			    first++;
		    }
		return dist;
	    }

        iterator erase(iterator position)
        {
           	iterator out(position);
			while (position != end() - 1) {
				*position = *(position + 1);
				++position;
			}
			--this->_size;
			return out;
        }

        iterator erase(iterator first, iterator last)
        {
    		iterator out(last);
			while (last != end()) 
            {
				*first = *last;
				++first;
				++last;
			}
			_size -= distance(first, last);
			return out;
        }

        void pop_back()
        {
            this->erase(this->end() - 1);
        }

        void assign(size_type count, const T& value)
        {
            erase(this->begin(), this->end());
            if(count > _size)
                reserve(count);
            for(size_type i = 0; i < count; ++i)
                vec[i] = value;
        }

        void assign(iterator first, iterator last)
        {
            erase(this->begin(), this->end());
            while(first != last)
                push_back(*first++);
        }

        void push_back( const T& value )
        {
            reserve(_size);
            vec[_size] = value;
            _size++;
        }



        void insert (iterator position, iterator first, iterator last)
		{
            vector tmp(position, end());
            this->_size -= distance(this->begin(), this->end());
            while(first != last)
                this->push_back(*first++);
            iterator it = tmp.begin();
            while(it != tmp.end())
                this->push_back(*it++);
        }

        void swap (vector& x)
        {
			vector tmp(*this);
			*this = x;
			x = tmp;
        }


    };
    /*******************************************NON-MEMBER FUNCITONS AND OPERATORS*******************************************/
        
        template <class T>
        bool operator==(const vector<T>& lhs, const vector<T>& rhs)
        {
            typename vector<T>::iterator lit = lhs.begin();
            typename vector<T>::iterator rit = rhs.begin();
            if(lhs.size() != rhs.size())
                return false;
            while(lit != lhs.end() && rit != rhs.end())
            {
                if(*lit != *rit)
                    return false;
                lit++;
                rit++;
            }
            return true;
        }
        template <class T>
        bool operator!=(const vector<T>& lhs, const vector<T>& rhs)
        {
            if(!(lhs == rhs))
                return true;
        }
        template <class T>
        bool operator<(const vector<T>& lhs, const vector<T>& rhs)
        {
            typename vector<T>::iterator lit = lhs.begin();
            typename vector<T>::iterator rit = rhs.begin();
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
        template <class T>
        bool operator<=(const vector<T>& lhs, const vector<T>& rhs)
        {
            if(lhs == rhs)
                return true;
            return(lhs > rhs);
        }
        template <class T>
        bool operator>(const vector<T>& lhs, const vector<T>& rhs)
        {
            return(!(lhs < rhs));
        }
        template <class T>
        bool operator>=(const vector<T>& lhs, const vector<T>& rhs)
        {
            if(lhs == rhs)
                return true;
            return(lhs > rhs);
        }

        template <class T>
        void swap (vector<T>& x, vector<T>& y)
        {
            x.swap(y);
        }
}

/*
**VECTOR MEMBER FUNCTIONS TO DO:
**  -constructor    ✅  FUNCIONA
**  -destructor     ✅  FUNCIONA
**  -operator=      ✅  FUNCIONA
**  -assign         ✅  FUNCIONA
**  -at             ✅  FUNCIONA
**  -operator[]     ✅  FUNCIONA
**  -front          ✅  FUNCIONA
**  -back           ✅  FUNCIONA
**  -begin          ✅  FUNCIONA
**  -end            ✅  FUNCIONA
**  -rbegin         ✅  FUNCIONA
**  -rend           ✅  FUNCIONA
**  -empty          ✅  FUNCIONA
**  -size           ✅  FUNCIONA
**  -max_size       ✅  FUNCIONA
**  -reserve        ✅  FUNCIONA
**  -capacity       ✅  FUNCIONA
**  -clear          ✅  FUNCIONA
**  -insert         ✅  FUNCIONA
**  -erase          ✅  FUNCIONA
**  -push_back      ✅  FUNCIONA
**  -pop_back       ✅  FUNCIONA
**  -resize         ✅  FUNCIONA
**  -swap           ✅  FUNCIONA
**  =================================
**  ITERATOR OPERATORS
**  =================================
**  operator++      ✅  FUNCIONA
**  operator--      ✅  FUNCIONA
**  ++operator      ✅  FUNCIONA
**  --operator      ✅  FUNCIONA
**  operator+=      ✅  FUNCIONA
**  operator-=      ✅  FUNCIONA
**  =================================
**  NON MEMBER RELATIONAL OPERATORS
**  =================================
**  operator==      ✅  FUNCIONA
**  operator!=      ✅  FUNCIONA
**  operator<       ✅  FUNCIONA
**  operator<=      ✅  FUNCIONA
**  operator>       ✅  FUNCIONA
**  operator>=      ✅  FUNCIONA
**  -swap           ✅  FUNCIONA
**
**  METER TESTS DE REVERSE ITERATORS EN EL MAIN
**
*/

#endif