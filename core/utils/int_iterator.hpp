#pragma once

#include <iterator>

template<typename T>
class IntIterator: public std::iterator<std::forward_iterator_tag, T>{
    T m_Value;
public:
	IntIterator() = default;

    IntIterator(T v): 
        m_Value(v) 
    {}

    const IntIterator& operator++() { 
        ++m_Value; 
        return *this;
    }

    bool operator!=(const IntIterator & o) { 
        return o.m_Value != m_Value;
    }

    T operator*() const { 
        return m_Value;
    }
};