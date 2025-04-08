#pragma once

#include <iostream>
#include <sstream>
#include <string>

namespace ReflectionApi {

template<typename T>
class Converter
{
public:
    virtual ~Converter() = default;

    virtual void fillFromString(T& value, const std::string& str) const
    {
        std::stringstream stream;
        stream << str;
        stream >> value;
    }

    virtual std::string convertToString(const T& value) const
    {
        std::stringstream stream;
        stream << value;

        return stream.str();
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