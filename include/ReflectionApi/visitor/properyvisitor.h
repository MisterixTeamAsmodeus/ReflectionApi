#pragma once

#include "ReflectionApi/property.h"
#include "ReflectionApi/referenceproperty.h"

namespace ReflectionApi {
namespace Visitor {

template<typename PropertyAction>
class PropertyVisitor
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

    template<typename ClassType,
        typename PropertyType,
        typename ReferenceColumnType,
        typename Setter,
        typename Getter,
        typename... ReferenceProperties>
    void operator()(ReferenceProperty<ClassType, PropertyType, ReferenceColumnType, Setter, Getter, ReferenceProperties...>& /*reference_property*/)
    {
    }

private:
    PropertyAction _property_action;
};

template<typename PropertyAction>
auto make_property_visitor(PropertyAction&& property_action)
{
    return PropertyVisitor<PropertyAction>(std::forward<PropertyAction>(property_action));
}

} // namespace Visitor
} // namespace ReflectionApi