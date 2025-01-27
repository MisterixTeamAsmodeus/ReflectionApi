#pragma once

#include "entity.hpp"
#include "helper/typehelper/templates.h"
#include "property.hpp"
#include "reflectionapi_global.h"

namespace ReflectionApi {

template<typename ClassType,
    typename PropertyType,
    typename ReferenceColumnType,
    typename Setter,
    typename Getter,
    typename... ReferenceProperties>
class REFLECTIONAPI_EXPORT ReferenceProperty final : public Property<ClassType, PropertyType, Setter, Getter>
{
public:
    static PropertyType get_empty_reference_variable()
    {
        return ReferenceColumnType();
    }

public:
    explicit ReferenceProperty(
        std::string name,
        const Helper::TypeHelper::Variable_t<ClassType, PropertyType>& variable,
        const Entity<ReferenceColumnType, ReferenceProperties...>& entity)
        : Property<ClassType, PropertyType, Setter, Getter>(name, variable)
        , _entity(entity)
    {
    }

    explicit ReferenceProperty(
        std::string name,
        Setter setter,
        Getter getter,
        const Entity<ReferenceColumnType, ReferenceProperties...>& entity)
        : Property<ClassType, PropertyType, Setter, Getter>(name, setter, getter)
        , _entity(entity)
    {
    }

    ReferenceProperty(const ReferenceProperty& other)
        : Property<ClassType, PropertyType, Setter, Getter>(other)
        , _entity(other._entity)
    {
    }

    ReferenceProperty(ReferenceProperty&& other) noexcept
        : Property<ClassType, PropertyType, Setter, Getter>(std::move(other))
        , _entity(std::move(other._entity))
    {
    }

    ReferenceProperty& operator=(const ReferenceProperty& other)
    {
        if(this == &other)
            return *this;
        Property<ClassType, PropertyType, Setter, Getter>::operator=(other);
        _entity = other._entity;
        return *this;
    }

    ReferenceProperty& operator=(ReferenceProperty&& other) noexcept
    {
        if(this == &other)
            return *this;
        Property<ClassType, PropertyType, Setter, Getter>::operator=(std::move(other));
        _entity = std::move(other._entity);
        return *this;
    }

    Entity<ReferenceColumnType, ReferenceProperties...>& mutable_entity()
    {
        return _entity;
    }

    Entity<ReferenceColumnType, ReferenceProperties...> entity() const
    {
        return _entity;
    }

private:
    Entity<ReferenceColumnType, ReferenceProperties...> _entity;
};

template<typename ClassType,
    typename PropertyType,
    typename ReferenceColumnType,
    typename... ReferenceProperties>
auto REFLECTIONAPI_EXPORT make_property(
    std::string name,
    Helper::TypeHelper::Variable_t<ClassType, PropertyType>&& variable,
    Entity<ReferenceColumnType, ReferenceProperties...> reference_entity)
{
    return ReferenceProperty<ClassType, PropertyType, ReferenceColumnType, Helper::TypeHelper::Setter_t<ClassType, PropertyType>, Helper::TypeHelper::ConstGetter_t<ClassType, PropertyType>, ReferenceProperties...>(
        std::move(name),
        std::forward<decltype(variable)>(variable),
        std::move(reference_entity));
}

template<typename ClassType,
    typename PropertyType,
    typename ReferenceColumnType,
    typename... ReferenceProperties>
auto REFLECTIONAPI_EXPORT make_property(
    std::string name,
    Helper::TypeHelper::Setter_t<ClassType, PropertyType>&& setter,
    Helper::TypeHelper::ConstGetter_t<ClassType, PropertyType>&& getter,
    Entity<ReferenceColumnType, ReferenceProperties...> reference_entity)
{
    return ReferenceProperty<ClassType, PropertyType, ReferenceColumnType, decltype(setter), decltype(getter), ReferenceProperties...>(
        std::move(name),
        std::forward<decltype(setter)>(setter),
        std::forward<decltype(getter)>(getter),
        std::move(reference_entity));
}

template<typename ClassType,
    typename PropertyType,
    typename ReferenceColumnType,
    typename... ReferenceProperties>
auto REFLECTIONAPI_EXPORT make_property(
    std::string name,
    Helper::TypeHelper::Setter_t<ClassType, PropertyType>&& setter,
    Helper::TypeHelper::MutableGetter_t<ClassType, PropertyType>&& getter,
    Entity<ReferenceColumnType, ReferenceProperties...> reference_entity)
{
    return ReferenceProperty<ClassType, PropertyType, ReferenceColumnType, decltype(setter), decltype(getter), ReferenceProperties...>(
        std::move(name),
        std::forward<decltype(setter)>(setter),
        std::forward<decltype(getter)>(getter),
        std::move(reference_entity));
}

template<typename ClassType,
    typename PropertyType,
    typename ReferenceColumnType,
    typename... ReferenceProperties>
auto REFLECTIONAPI_EXPORT make_property(
    std::string name,
    Helper::TypeHelper::Setter_t<ClassType, PropertyType> setter,
    Helper::TypeHelper::Getter_t<ClassType, PropertyType> getter,
    Entity<ReferenceColumnType, ReferenceProperties...> reference_entity)
{
    return ReferenceProperty<ClassType, PropertyType, ReferenceColumnType, decltype(setter), decltype(getter), ReferenceProperties...>(
        std::move(name),
        std::forward<decltype(setter)>(setter),
        std::forward<decltype(getter)>(getter),
        std::move(reference_entity));
}

//-----------------------------Перегрузки для примитивов, где параметры в setter не по const &-----------------------------------

template<typename ClassType,
    typename PropertyType,
    typename ReferenceColumnType,
    typename... ReferenceProperties>
auto REFLECTIONAPI_EXPORT make_property(
    std::string name,
    Helper::TypeHelper::BaseSetter_t<ClassType, PropertyType>&& setter,
    Helper::TypeHelper::ConstGetter_t<ClassType, PropertyType>&& getter,
    Entity<ReferenceColumnType, ReferenceProperties...> reference_entity)
{
    return ReferenceProperty<ClassType, PropertyType, ReferenceColumnType, decltype(setter), decltype(getter), ReferenceProperties...>(
        std::move(name),
        std::forward<decltype(setter)>(setter),
        std::forward<decltype(getter)>(getter),
        std::move(reference_entity));
}

template<typename ClassType,
    typename PropertyType,
    typename ReferenceColumnType,
    typename... ReferenceProperties>
auto REFLECTIONAPI_EXPORT make_property(
    std::string name,
    Helper::TypeHelper::BaseSetter_t<ClassType, PropertyType>&& setter,
    Helper::TypeHelper::MutableGetter_t<ClassType, PropertyType>&& getter,
    Entity<ReferenceColumnType, ReferenceProperties...> reference_entity)
{
    return ReferenceProperty<ClassType, PropertyType, ReferenceColumnType, decltype(setter), decltype(getter), ReferenceProperties...>(
        std::move(name),
        std::forward<decltype(setter)>(setter),
        std::forward<decltype(getter)>(getter),
        std::move(reference_entity));
}

template<typename ClassType,
    typename PropertyType,
    typename ReferenceColumnType,
    typename... ReferenceProperties>
auto REFLECTIONAPI_EXPORT make_property(
    std::string name,
    Helper::TypeHelper::BaseSetter_t<ClassType, PropertyType> setter,
    Helper::TypeHelper::Getter_t<ClassType, PropertyType> getter,
    Entity<ReferenceColumnType, ReferenceProperties...> reference_entity)
{
    return ReferenceProperty<ClassType, PropertyType, ReferenceColumnType, decltype(setter), decltype(getter), ReferenceProperties...>(
        std::move(name),
        std::forward<decltype(setter)>(setter),
        std::forward<decltype(getter)>(getter),
        std::move(reference_entity));
}

} // namespace ReflectionApi
