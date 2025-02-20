#include <ReflectionApi/reflectionapi.h>

#include <iostream>

struct Test
{
    int a;
};

int main()
{
    using namespace ReflectionApi;

    auto entity = make_entity<Test>(make_property("a", &Test::a));

    Test t {};

    std::cout << t.a << " - ";
    entity.visit_property("a", [&t](const auto& property) {
        std::cout << property.value(t);
    });
}
