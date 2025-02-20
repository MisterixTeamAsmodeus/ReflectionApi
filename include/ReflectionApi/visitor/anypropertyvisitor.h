#pragma once

#include "properyvisitor.h"
#include "referencepropertyvisitor.h"
#include "ReflectionApi/referenceproperty.h"

namespace ReflectionApi {
namespace Visitor {

template<typename PropertyAction, typename ReferencePropertyAction>
class REFLECTIONAPI_EXPORT AnyPropertyVisitor final : public PropertyVisitor<PropertyAction>, public ReferencePropertyVisitor<ReferencePropertyAction>
{
public:
    explicit AnyPropertyVisitor(const PropertyAction& property_action, const ReferencePropertyAction& reference_property_action)
        : PropertyVisitor<PropertyAction>(property_action)
        , ReferencePropertyVisitor<ReferencePropertyAction>(reference_property_action)
    {
    }
};

template<typename PropertyAction, typename ReferencePropertyAction>
auto REFLECTIONAPI_EXPORT make_any_property_visitor(
    PropertyAction&& property_action,
    ReferencePropertyAction&& reference_property_action)
{
    return AnyPropertyVisitor<PropertyAction, ReferencePropertyAction>(
        std::forward<PropertyAction>(property_action),
        std::forward<ReferencePropertyAction>(reference_property_action));
}

} // namespace Visitor
} // namespace ReflectionApi