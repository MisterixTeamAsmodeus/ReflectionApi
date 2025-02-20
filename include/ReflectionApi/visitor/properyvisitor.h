#pragma once

#include "ReflectionApi/property.h"

namespace ReflectionApi {
namespace Visitor {

template<typename PropertyAction>
class REFLECTIONAPI_EXPORT PropertyVisitor
{
public:
    explicit PropertyVisitor(const PropertyAction& property_action)
        : _property_action(property_action)
    {
    }

    template<typename ClassType,
        typename PropertyType,
        typename Setter,
        typename Getter>
    void operator()(Property<ClassType, PropertyType, Setter, Getter>& property)
    {
        _property_action(property);
    }

private:
    PropertyAction _property_action;
};

template<typename PropertyAction>
auto REFLECTIONAPI_EXPORT make_property_visitor(PropertyAction&& property_action)
{
    return ProperyVisitor<PropertyAction>(std::forward<PropertyAction>(property_action));
}

} // namespace Visitor
} // namespace ReflectionApi