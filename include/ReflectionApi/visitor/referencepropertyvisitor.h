#pragma once

#include "ReflectionApi/referenceproperty.h"

namespace ReflectionApi {
namespace Visitor {

template<typename ReferencePropertyAction>
class REFLECTIONAPI_EXPORT ReferencePropertyVisitor
{
public:
    explicit ReferencePropertyVisitor(const ReferencePropertyAction& reference_property_action)
        : _reference_property_action(reference_property_action)
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

private:
    ReferencePropertyAction _reference_property_action;
};

template<typename ReferencePropertyAction>
auto REFLECTIONAPI_EXPORT make_reference_property_visitor(ReferencePropertyAction&& reference_property_action)
{
    return ReferencePropertyVisitor<ReferencePropertyAction>(std::forward<ReferencePropertyAction>(reference_property_action));
}

} // namespace Visitor
} // namespace ReflectionApi