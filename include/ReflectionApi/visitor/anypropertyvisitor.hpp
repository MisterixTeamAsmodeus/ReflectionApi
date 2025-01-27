#pragma once

#include "ReflectionApi/referenceproperty.hpp"

namespace ReflectionApi {
namespace Visitor {

template<typename PropertyAction, typename ReferencePropertyAction>
class AnyPropertyVisitor
{
public:
    explicit AnyPropertyVisitor(const PropertyAction& property_action, const ReferencePropertyAction& reference_property_action)
        : _property_action(property_action)
        , _reference_property_action(reference_property_action)
    {
    }

    template<typename ClassType,
        typename PropertyType,
        typename ReferenceColumnType,
        typename Setter,
        typename Getter,
        typename... ReferenceProperties>
    void operator()(ReferenceProperty<ClassType, PropertyType, ReferenceColumnType, Setter, Getter, ReferenceProperties...>& reference_property)
    {
        _reference_property_action(reference_property);
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
    ReferencePropertyAction _reference_property_action;
};

template<typename PropertyAction, typename ReferencePropertyAction>
auto make_any_property_visitor(
    PropertyAction&& property_action,
    ReferencePropertyAction&& reference_property_action)
{
    return AnyPropertyVisitor<PropertyAction, ReferencePropertyAction>(
        std::forward<PropertyAction>(property_action),
        std::forward<ReferencePropertyAction>(reference_property_action));
}

} // namespace Visitor
} // namespace ReflectionApi