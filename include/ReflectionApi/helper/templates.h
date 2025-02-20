#pragma once

namespace ReflectionApi {
namespace Helper {

/**
 * @brief Шаблонные псевдонимы типа для указателей на члены-функции, возвращающие значения.
 *
 * @tparam ClassType Тип класса, к которому принадлежат члены-функции.
 * @tparam ColumnType Тип значения членов-функции.
 * @note Описание константного геттера.
 */
template<typename ClassType, typename ColumnType>
using ConstGetter_t = ColumnType (ClassType::*)() const;

/**
 * @brief Шаблонные псевдонимы типа для указателей на члены-функции, возвращающие значения.
 *
 * @tparam ClassType Тип класса, к которому принадлежат члены-функции.
 * @tparam ColumnType Тип значения членов-функции.
 * @note Описание mutable геттера.
 */
template<typename ClassType, typename ColumnType>
using MutableGetter_t = ColumnType& (ClassType::*)();

/**
 * @brief Шаблонные псевдонимы типа для указателей на члены-функции, возвращающие значения.
 *
 * @tparam ClassType Тип класса, к которому принадлежат члены-функции.
 * @tparam ColumnType Тип значения членов-функции.
 * @note Описание геттера с изменяемым значением.
 */
template<typename ClassType, typename ColumnType>
using Getter_t = ColumnType (ClassType::*)();

/**
 * @brief Шаблонные псевдонимы типа для указателей на члены-функции, устанавливающие значение.
 *
 * @tparam ClassType Тип класса, к которому принадлежат члены-функции.
 * @tparam ColumnType Тип значения членов-функции.
 * @tparam Params Тип параметра, который принимает член-функция. По умолчанию это const ColumnType &.
 */
template<typename ClassType, typename ColumnType, typename Params = const ColumnType&>
using Setter_t = void (ClassType::*)(const Params&);

/**
 * @brief Шаблонные псевдонимы типа для указателей на члены-функции, устанавливающие значение.
 *
 * @tparam ClassType Тип класса, к которому принадлежат члены-функции.
 * @tparam ColumnType Тип значения членов-функции.
 * @tparam Params Тип параметра, который принимает член-функция. По умолчанию это ColumnType.
 */
template<typename ClassType, typename ColumnType, typename Params = ColumnType>
using BaseSetter_t = void (ClassType::*)(Params);

/**
 * @brief Шаблонные псевдонимы типа для указателей на члены-переменные.
 *
 * @tparam ClassType Тип класса, к которому принадлежат члены-переменные.
 * @tparam ColumnType Тип значения членов-переменных.
 */
template<typename ClassType, typename ColumnType>
using Variable_t = ColumnType ClassType::*;

} // namespace Helper
} // namespace ReflectionApi
