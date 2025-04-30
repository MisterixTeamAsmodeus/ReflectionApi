#pragma once

#include "helper/sfinae.h"

#include <memory>
#include <sstream>
#include <string>

namespace reflection_api {
namespace impl {

/// Реализация заполнения данных если реализован оператор >>
template<typename T, std::enable_if_t<sfinae::has_right_shift_operator_v<T>, bool> = true>
void fill_from_string(T& value, const std::string& str, int)
{
    std::stringstream stream;
    stream << str;
    stream >> value;
}

/// Реализация конвертации данных если реализован оператор <<
template<typename T, std::enable_if_t<sfinae::has_left_shift_operator_v<T>, bool> = true>
std::string convert_to_string(const T& value, int)
{
    std::stringstream stream;
    stream << value;

    return stream.str();
}

/// Реализация по умолчанию
template<typename T>
void fill_from_string(T&, const std::string&, ...)
{
    throw std::runtime_error("fill_from_string not implemented");
}

/// Реализация по умолчанию
template<typename T>
std::string convert_to_string(const T&, ...)
{
    throw std::runtime_error("convert_to_string not implemented");
}

} // namespace impl

/**
 * Класс отвечающий за конвертацию строк в строку и обратно
 * @tparam T Тип данных для конвертации
 */
template<typename T>
class converter
{
public:
    virtual ~converter() = default;

    virtual void fill_from_string(T& value, const std::string& str) const
    {
        impl::fill_from_string<T>(value, str, 0);
    }

    virtual std::string convert_to_string(const T& value) const
    {
        return impl::convert_to_string<T>(value, 0);
    }
};

template<>
class converter<bool>
{
public:
    virtual ~converter() = default;

    virtual void fill_from_string(bool& value, const std::string& str) const
    {
        std::stringstream stream;
        stream << str;
        stream >> std::boolalpha >> value;
    }

    virtual std::string convert_to_string(const bool& value) const
    {
        return value ? "true" : "false";
    }
};

template<>
class converter<std::string>
{
public:
    virtual ~converter() = default;

    virtual void fill_from_string(std::string& value, const std::string& str) const
    {
        value = str;
    }

    virtual std::string convert_to_string(const std::string& value) const
    {
        return value;
    }
};

template<typename T>
class converter<std::shared_ptr<T>>
{
public:
    virtual ~converter() = default;

    virtual void fill_from_string(std::shared_ptr<T>& value, const std::string& str) const
    {
        if(str.empty())
            return;

        if(value == nullptr)
            value = std::make_shared<T>();

        std::stringstream stream;
        stream << str;
        stream >> *value;
    }

    virtual std::string convert_to_string(const std::shared_ptr<T>& value) const
    {
        if(value == nullptr)
            return "";

        std::stringstream stream;
        stream << *value;

        return stream.str();
    }
};

template<typename T>
class converter<std::unique_ptr<T>>
{
public:
    virtual ~converter() = default;

    virtual void fill_from_string(std::unique_ptr<T>& value, const std::string& str) const
    {
        if(str.empty())
            return;

        if(value == nullptr)
            value = std::make_unique<T>();

        std::stringstream stream;
        stream << str;
        stream >> *value;
    }

    virtual std::string convert_to_string(const std::unique_ptr<T>& value) const
    {
        if(value == nullptr)
            return "";

        std::stringstream stream;
        stream << *value;

        return stream.str();
    }
};

} // namespace reflection_api