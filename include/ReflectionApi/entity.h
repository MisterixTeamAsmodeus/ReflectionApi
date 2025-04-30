#pragma once

#include "helper/tuplealgoritm.h"

#include <string>
#include <tuple>

namespace reflection_api {

/**
 * Класс отвечающий за представление обобщенного доступа к любой структуре данных
 * @note Для использования необходимо, чтобы у объекта был конструктор по умолчанию
 * @tparam ClassType Тип объекта
 * @tparam Properties Список пропертей объекта
 */
template<typename ClassType, typename... Properties>
class entity
{
public:
    /// Создать объект сущности
    static ClassType empty_entity()
    {
        return ClassType();
    }

public:
    explicit entity(Properties... properties)
        : _properties(std::make_tuple<Properties...>(std::move(properties)...))
    {
    }

    entity(const entity& other)
        : _properties(other._properties)
    {
    }

    entity(entity&& other) noexcept
        : _properties(std::move(other._properties))
    {
    }

    entity& operator=(const entity& other)
    {
        if(this == &other)
            return *this;
        _properties = other._properties;
        return *this;
    }

    entity& operator=(entity&& other) noexcept
    {
        if(this == &other)
            return *this;
        _properties = std::move(other._properties);
        return *this;
    }

    /**
     * Выполнить действие над проеперти с заданным названием
     * @param property_name Название проеперти
     * @param action Действие которое необходимо выполнить
     */
    template<typename Action>
    void visit_property(const std::string& property_name, Action&& action)
    {
        helper::perform_if(
            _properties,
            [&](const auto& column) {
                return column.name() == property_name;
            },
            std::forward<Action>(action));
    }

    /// Выполнить действия над всеми проеперти в объекте
    template<typename Action>
    void for_each(Action&& action)
    {
        helper::for_each(
            _properties,
            std::forward<Action>(action));
    }

private:
    /// Список проерти в сущности
    std::tuple<Properties...> _properties = {};
};

template<typename ClassType, typename... Properties>
auto make_entity(Properties&&... properties)
{
    return entity<ClassType, Properties...>(std::move(properties)...);
}

} // namespace reflection_api
