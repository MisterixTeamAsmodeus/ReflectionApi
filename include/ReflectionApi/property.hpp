#pragma once

#include "helper/typehelper/templates.h"
#include "reflectionapi_global.h"

#include <string>

namespace ReflectionApi {

template<typename ClassType,
    typename PropertyType,
    typename Setter = Helper::TypeHelper::Setter_t<ClassType, PropertyType>,
    typename Getter = Helper::TypeHelper::ConstGetter_t<ClassType, PropertyType>>
class REFLECTIONAPI_EXPORT Property
{
public:
    static PropertyType empty_property()
    {
        return PropertyType();
    }

public:
    /**
     * @brief Конструктор, создает экземпляр переменной, связанной с указателем на член-переменную.
     *
     * @param variable Указатель на член-переменную.
     * @param name Имя переменной.
     */
    explicit Property(std::string name, const Helper::TypeHelper::Variable_t<ClassType, PropertyType> variable)
        : _name(std::move(name))
        , _variable(variable)
    {
    }

    /**
     * @brief Конструктор, создает экземпляр переменной, связанной с указателями на члены-функции.
     *
     * @param name Имя переменной.
     * @param setter Указатель на член-функцию, устанавливающую значение переменной.
     * @param getter Указатель на член-функцию, получающую значение переменной.
     */
    explicit Property(std::string name, Setter setter, Getter getter)
        : _name(std::move(name))
        , _getter(std::move(getter))
        , _setter(std::move(setter))
    {
    }

    Property(const Property& other)
        : _name(other._name)
        , _variable(other._variable)
        , _getter(other._getter)
        , _setter(other._setter)
    {
    }

    Property(Property&& other) noexcept
        : _name(std::move(other._name))
        , _variable(other._variable)
        , _getter(std::move(other._getter))
        , _setter(std::move(other._setter))
    {
    }

    Property& operator=(const Property& other)
    {
        if(this == &other)
            return *this;
        _name = other._name;
        _variable = other._variable;
        _getter = other._getter;
        _setter = other._setter;
        return *this;
    }

    Property& operator=(Property&& other) noexcept
    {
        if(this == &other)
            return *this;
        _name = std::move(other._name);
        _variable = other._variable;
        _getter = std::move(other._getter);
        _setter = std::move(other._setter);
        return *this;
    }

private:
    /**
     * @brief Устанавливает значение переменной.
     *
     * @param classValue Объект, в котором находится переменная.
     * @param data Новое значение переменной.
     */
    void set_value(ClassType& classValue, const PropertyType& data)
    {
        if(_variable == nullptr)
            (classValue.*_setter)(data);
        else
            classValue.*_variable = data;
    }

    /**
     * @brief Получает значение переменной.
     *
     * @param classValue Объект, в котором находится переменная.
     * @return Значение переменной.
     */
    decltype(auto) value(const ClassType& classValue) const
    {
        return _variable == nullptr ? (classValue.*_getter)() : classValue.*_variable;
    }

    /**
     * @brief Получает имя переменной.
     *
     * @return Имя переменной.
     */
    std::string name() const
    {
        return _name;
    }

private:
    /**
     * @brief Строка, хранящая имя переменной.
     */
    std::string _name {};

    /**
     * @brief Указатель на член-переменную, связанный с этой переменной.
     * Если указатель равен nullptr, то переменная связана с указателями на члены-функции.
     */
    Helper::TypeHelper::Variable_t<ClassType, PropertyType> _variable = nullptr;

    /**
     * @brief Указатель на член-функцию, получающий значение переменной.
     * Если указатель равен nullptr, то значение переменной получается через член-переменную.
     */
    Getter _getter = nullptr;

    /**
     * @brief Указатель на член-функцию, устанавливающий значение переменной.
     * Если указатель равен nullptr, то значение переменной устанавливается через член-переменную.
     */
    Setter _setter = nullptr;
};

template<typename ClassType, typename PropertyType>
auto REFLECTIONAPI_EXPORT make_property(
    std::string name,
    Helper::TypeHelper::Variable_t<ClassType, PropertyType>&& variable)
{
    return Property<ClassType, PropertyType>(
        std::move(name),
        std::forward<decltype(variable)>(variable));
}

template<typename ClassType, typename PropertyType>
auto REFLECTIONAPI_EXPORT make_property(
    std::string name,
    Helper::TypeHelper::Setter_t<ClassType, PropertyType>&& setter,
    Helper::TypeHelper::ConstGetter_t<ClassType, PropertyType>&& getter)
{
    return Property<ClassType, PropertyType, decltype(setter), decltype(getter)>(
        std::move(name),
        std::forward<decltype(setter)>(setter),
        std::forward<decltype(getter)>(getter));
}

template<typename ClassType, typename PropertyType>
auto REFLECTIONAPI_EXPORT make_property(
    std::string name,
    Helper::TypeHelper::Setter_t<ClassType, PropertyType>&& setter,
    Helper::TypeHelper::MutableGetter_t<ClassType, PropertyType>&& getter)
{
    return Property<ClassType, PropertyType, decltype(setter), decltype(getter)>(
        std::move(name),
        std::forward<decltype(setter)>(setter),
        std::forward<decltype(getter)>(getter));
}

template<typename ClassType, typename PropertyType>
auto REFLECTIONAPI_EXPORT make_property(
    std::string name,
    Helper::TypeHelper::Setter_t<ClassType, PropertyType>&& setter,
    Helper::TypeHelper::Getter_t<ClassType, PropertyType>&& getter)
{
    return Property<ClassType, PropertyType, decltype(setter), decltype(getter)>(
        std::move(name),
        std::forward<decltype(setter)>(setter),
        std::forward<decltype(getter)>(getter));
}

//-----------------------------Перегрузки для примитивов, где параметры в setter не по const &-----------------------------------

template<typename ClassType, typename PropertyType>
auto REFLECTIONAPI_EXPORT make_property(
    std::string name,
    Helper::TypeHelper::BaseSetter_t<ClassType, PropertyType>&& setter,
    Helper::TypeHelper::ConstGetter_t<ClassType, PropertyType>&& getter)
{
    return Property<ClassType, PropertyType, decltype(setter), decltype(getter)>(
        std::move(name),
        std::forward<decltype(setter)>(setter),
        std::forward<decltype(getter)>(getter));
}

template<typename ClassType, typename PropertyType>
auto REFLECTIONAPI_EXPORT make_property(
    std::string name,
    Helper::TypeHelper::BaseSetter_t<ClassType, PropertyType>&& setter,
    Helper::TypeHelper::MutableGetter_t<ClassType, PropertyType>&& getter)
{
    return Property<ClassType, PropertyType, decltype(setter), decltype(getter)>(
        std::move(name),
        std::forward<decltype(setter)>(setter),
        std::forward<decltype(getter)>(getter));
}

template<typename ClassType, typename PropertyType>
auto REFLECTIONAPI_EXPORT make_property(
    std::string name,
    Helper::TypeHelper::BaseSetter_t<ClassType, PropertyType>&& setter,
    Helper::TypeHelper::Getter_t<ClassType, PropertyType>&& getter)
{
    return Property<ClassType, PropertyType, decltype(setter), decltype(getter)>(
        std::move(name),
        std::forward<decltype(setter)>(setter),
        std::forward<decltype(getter)>(getter));
}

} // namespace ReflectionApi