# ReflectionApi

ReflectionApi — это библиотека на С++ 14 для реализации компилируемой рефлексии на C++, которая предоставляет обобщённый интерфейс для работы с любыми структурами данных. Она позволяет обращаться к переменным и полям классов

Для взаимодействия с классом необходимо описать объект entity, куда передать property (ссылки на поля класса)

```c++
struct Test
{
    int a = 0;
    std::string b;
};

auto entity = make_entity<Test>(
    make_property("a", &Test::a),
    make_property("b", &Test::b)
    );
```

Так же библиотека умеет работать через get и set функции

```c++
class Test
{
public:
    int get_a() const
    {
        return a;
    }

    void set_a(const int a)
    {
        this->a = a;
    }

private:
    int a = 0;
};

auto entity = make_entity<Test>(make_property("a", &Test::set_a, &Test::get_a));
```

Для реализации вложенных структур реализован класс reference_property

```c++
struct Test
{
    int a = 0;
};

struct ParentItem
{
    Test t;
};

auto entity = make_entity<ParentItem>(
    make_reference_property("t", &ParentItem::t,
        make_entity<Test>(make_property("a", &Test::a))));
```