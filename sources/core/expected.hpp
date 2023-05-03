#pragma once

#include "core/types.hpp"

#include <variant>
#include <cassert>

template<typename ValueType, typename ErrorType>
class Expected {
    std::variant<ValueType, ErrorType> m_Data;
public:
    Expected(ValueType value) :
        m_Data(value) {}

    Expected(ErrorType error) :
        m_Data(error) {}

    bool IsError()const {
        return m_Data.index() == 1;
    }

    bool IsValue()const {
        return m_Data.index() == 0;
    }

    const ValueType& Value()const {
        assert(IsValue());

        return *std::get_if<ValueType>(&m_Data);
    }
    
    ValueType& Value() GEN_NON_CONST_GETTER(Value())

    const ErrorType& Error()const {
        assert(IsError());

        return *std::get_if<ErrorType>(&m_Data);
    }

    ErrorType& Error() GEN_NON_CONST_GETTER(Error())
};
