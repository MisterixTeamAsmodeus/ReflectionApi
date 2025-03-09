#pragma once

#include "helper/templates.h"

#include <string>

namespace ReflectionApi {

template<typename ClassType,
    typename PropertyType,
    typename Setter = Helper::Setter_t<ClassType, PropertyType>,
    typename Getter = Helper::ConstGetter_t<ClassType, PropertyType>>
class Property
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
    explicit Property(std::string name, const Helper::Variable_t<ClassType, PropertyType> variable)
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

    virtual ~Property() = default;

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
    PropertyType value(const ClassType& classValue) const
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
    Helper::Variable_t<ClassType, PropertyType> _variable = nullptr;

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
auto make_property(
    std::string name,
    Helper::Variable_t<ClassType, PropertyType> variable)
{
    return Property<ClassType, PropertyType>(
        std::move(name),
        std::forward<Helper::Variable_t<ClassType, PropertyType>>(variable));
}

template<typename ClassType, typename PropertyType>
auto make_property(
    std::string name,
    Helper::Setter_t<ClassType, PropertyType> setter,
    Helper::ConstGetter_t<ClassType, PropertyType> getter)
{
    return Property<ClassType, PropertyType>(
        std::move(name),
        setter,
        getter);
}

template<typename ClassType, typename PropertyType>
auto make_property(
    std::string name,
    Helper::Setter_t<ClassType, PropertyType> setter,
    Helper::MutableGetter_t<ClassType, PropertyType> getter)
{
    return Property<ClassType, PropertyType, Helper::Setter_t<ClassType, PropertyType>, Helper::MutableGetter_t<ClassType, PropertyType>>(
        std::move(name),
        setter,
        getter);
}

template<typename ClassType, typename PropertyType>
auto make_property(
    std::string name,
    Helper::Setter_t<ClassType, PropertyType> setter,
    Helper::Getter_t<ClassType, PropertyType> getter)
{
    return Property<ClassType, PropertyType, Helper::Setter_t<ClassType, PropertyType>, Helper::Getter_t<ClassType, PropertyType>>(
        std::move(name),
        setter,
        getter);
}

//-----------------------------Перегрузки для примитивов, где параметры в setter не по const &-----------------------------------

template<typename ClassType, typename PropertyType>
auto make_property(
    std::string name,
    Helper::BaseSetter_t<ClassType, PropertyType>&& setter,
    Helper::ConstGetter_t<ClassType, PropertyType>&& getter)
{
    return Property<ClassType, PropertyType, Helper::BaseSetter_t<ClassType, PropertyType>>(
        std::move(name),
        setter,
        getter);
}

template<typename ClassType, typename PropertyType>
auto make_property(
    std::string name,
    Helper::BaseSetter_t<ClassType, PropertyType> setter,
    Helper::MutableGetter_t<ClassType, PropertyType> getter)
{
    return Property<ClassType, PropertyType, Helper::BaseSetter_t<ClassType, PropertyType>, Helper::MutableGetter_t<ClassType, PropertyType>>(
        std::move(name),
        setter,
        getter);
}

template<typename ClassType, typename PropertyType>
auto make_property(
    std::string name,
    Helper::BaseSetter_t<ClassType, PropertyType> setter,
    Helper::Getter_t<ClassType, PropertyType> getter)
{
    return Property<ClassType, PropertyType, Helper::BaseSetter_t<ClassType, PropertyType>, Helper::Getter_t<ClassType, PropertyType>>(
        std::move(name),
        setter,
        getter);
}

} // namespace ReflectionApi