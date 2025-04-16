#pragma once

#include "helper/sfinae.h"

#include <sstream>
#include <string>

namespace ReflectionApi {

namespace Impl {

template<typename T, std::enable_if_t<SFINAE::has_right_shift_operator_v<T>, bool> = true>
void fillFromString(T& value, const std::string& str, int)
{
    std::stringstream stream;
    stream << str;
    stream >> value;
}

template<typename T, std::enable_if_t<SFINAE::has_left_shift_operator_v<T>, bool> = true>
std::string convertToString(const T& value, int)
{
    std::stringstream stream;
    stream << value;

    return stream.str();
}

template<typename T>
void fillFromString(T&, const std::string&, ...)
{
    throw std::runtime_error("fillFromString not implemented");
}

template<typename T>
std::string convertToString(const T&, ...)
{
    throw std::runtime_error("convertToString not implemented");
}

} // namespace Impl

template<typename T>
class Converter
{
public:
    virtual ~Converter() = default;

    virtual void fillFromString(T& value, const std::string& str) const
    {
        Impl::fillFromString<T>(value, str, 0);
    }

    virtual std::string convertToString(const T& value) const
    {
        return Impl::convertToString<T>(value, 0);
    }
};

template<>
class Converter<bool> final
{
public:
    ~Converter() = default;

    void fillFromString(bool& value, const std::string& str) const
    {
        std::stringstream stream;
        stream << str;
        stream >> std::boolalpha >> value;
    }

    std::string convertToString(const bool& value) const
    {
        return value ? "true" : "false";
    }
};

template<>
class Converter<std::string> final
{
public:
    ~Converter() = default;

    void fillFromString(std::string& value, const std::string& str) const
    {
        value = str;
    }

    std::string convertToString(const std::string& value) const
    {
        return value;
    }
};

template<typename T>
class Converter<std::shared_ptr<T>> final
{
public:
    ~Converter() = default;

    void fillFromString(std::shared_ptr<T>& value, const std::string& str) const
    {
        if(str.empty())
            return;

        if(value == nullptr)
            value = std::make_shared<T>();

        std::stringstream stream;
        stream << str;
        stream >> *value;
    }

    std::string convertToString(const std::shared_ptr<T>& value) const
    {
        if(value == nullptr)
            return "";

        std::stringstream stream;
        stream << *value;

        return stream.str();
    }
};

template<typename T>
class Converter<std::unique_ptr<T>> final
{
public:
    ~Converter() = default;

    void fillFromString(std::unique_ptr<T>& value, const std::string& str) const
    {
        if(str.empty())
            return;

        if(value == nullptr)
            value = std::make_unique<T>();

        std::stringstream stream;
        stream << str;
        stream >> *value;
    }

    std::string convertToString(const std::unique_ptr<T>& value) const
    {
        if(value == nullptr)
            return "";

        std::stringstream stream;
        stream << *value;

        return stream.str();
    }
};

} // namespace ReflectionApi