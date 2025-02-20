#pragma once

#include "helper/tuplealgoritm.h"
#include "reflectionapi_global.h"

#include <string>
#include <tuple>

namespace ReflectionApi {

template<typename ClassType, typename... Properties>
class REFLECTIONAPI_EXPORT Entity
{
public:
    static ClassType empty_entity()
    {
        return ClassType();
    }

public:
    explicit Entity(Properties... properties)
        : _properties(std::make_tuple<Properties...>(std::move(properties)...))
    {
    }

    Entity(const Entity& other)
        : _properties(other._properties)
    {
    }

    Entity(Entity&& other) noexcept
        : _properties(std::move(other._properties))
    {
    }

    Entity& operator=(const Entity& other)
    {
        if(this == &other)
            return *this;
        _properties = other._properties;
        return *this;
    }

    Entity& operator=(Entity&& other) noexcept
    {
        if(this == &other)
            return *this;
        _properties = std::move(other._properties);
        return *this;
    }

    template<typename Action>
    void visit_property(const std::string& property_name, Action&& action)
    {
        Helper::perform_if(
            _properties,
            [&](const auto& column) {
                return column.name() == property_name;
            },
            std::forward<Action>(action));
    }

    template<typename Action>
    void for_each(Action&& action)
    {
        Helper::for_each(
            _properties,
            std::forward<Action>(action));
    }

private:
    std::tuple<Properties...> _properties = {};
};

template<typename ClassType, typename... Properties>
auto REFLECTIONAPI_EXPORT make_entity(Properties&&... properties)
{
    return Entity<ClassType, Properties...>(std::move(properties)...);
}

} // namespace ReflectionApi
