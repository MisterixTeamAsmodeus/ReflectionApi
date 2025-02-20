#include <ReflectionApi/reflectionapi.h>

#include <iostream>
#include <string>

struct Test
{
    int a = 5;
    std::string b = "inline test";
    bool c = false;
};

struct ParentItem
{
    int a = 10;
    std::string b = "test";
    Test t {};
};

template<typename ClassType, typename Entity, typename PropertyAction>
void visitAllProperty(ClassType&& visitor, Entity&& entity, PropertyAction&& property_action)
{
    using namespace ReflectionApi;

    entity.for_each(Visitor::make_any_property_visitor(
        [&](const auto& property) {
            property_action(visitor, property);
        },
        [&](const auto& reference_property) {
            visitAllProperty(reference_property.value(visitor), reference_property.entity(), property_action);
        }));
}

int main()
{
    using namespace ReflectionApi;

    const auto inline_entity = make_entity<Test>(
        make_property("inline_a", &Test::a),
        make_property("inline_b", &Test::b),
        make_property("inline_c", &Test::c));

    auto entity = make_entity<ParentItem>(
        make_property("a", &ParentItem::a),
        make_property("b", &ParentItem::b),
        make_reference_property("t", &ParentItem::t, inline_entity));

    ParentItem p {};

    std::cout << "visit property without recursive"
              << "\n";
    entity.for_each([](const auto& property) {
        std::cout << "property name - " << property.name() << "\n";
    });

    std::cout << "\n";

    std::cout << "visit property with recursive"
              << "\n";
    visitAllProperty(p, entity, [](const auto& visitor, const auto& property) {
        std::cout << "property name - " << property.name() << " property value - " << property.value(visitor) << "\n";
    });
}
