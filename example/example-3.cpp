#include <ReflectionApi/reflectionapi.h>

#include <iostream>

struct Test
{
    int a = 0;
};

struct ParentItem
{
    Test t;
};

int main()

{
    using namespace ReflectionApi;

    auto entity = make_entity<ParentItem>(make_reference_property("t", &ParentItem::t,
        make_entity<Test>(make_property("a", &Test::a))));

    ParentItem p {};

    // get value
    std::cout << p.t.a << " - ";
    entity.visit_property("t", Visitor::make_reference_property_visitor([&p](const auto& property) {
        const auto value = property.value(p);
        auto inlineEntity = property.entity();

        inlineEntity.visit_property("a", [&p, value](const auto& inline_property) {
            std::cout << inline_property.value(value);
            std::cout << " get value in inline entity with reflection"
                      << "\n";
        });
    }));

    std::cout << "\n";

    // set value
    entity.visit_property("t", Visitor::make_reference_property_visitor([&p](auto& property) {
        auto value = property.value(p);
        auto inlineEntity = property.entity();

        inlineEntity.visit_property("a", [&p, &value](auto& inline_property) {
            std::cout << "set value in inline entity with reflection. value = " << 6 << "\n";
            inline_property.set_value(value, 6);
        });

        property.set_value(p, value);
    }));

    std::cout << "value - " << p.t.a;
}
