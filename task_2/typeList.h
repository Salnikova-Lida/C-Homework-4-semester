#ifndef __TYPELIST_H__
#define __TYPELIST_H__

#include <cstddef>
#include <iostream>
#include <string>
#include <typeinfo>
#include <type_traits>

template <typename... T>
struct TypeList;
namespace TypeList_inner{
    //Получение элемента списка по его индексу
    template <size_t i, typename List>
    struct Get;

    template <typename T1, typename... T2>
    struct Get<0, TypeList<T1, T2...>>{
        using type = T1;
    };

    template <size_t i, typename T1, typename... T2>
    struct Get<i, TypeList<T1, T2...>>{
        using type = typename Get<i - 1, TypeList<T2...>>::type;
    };

    template <size_t i>
    struct Get<i, TypeList<>>{
        static_assert(i < 0, "List index is out of range");
    };

    //Получение размера списка
    template <typename List>
    struct Size;

    template <typename... T>
    struct Size<TypeList<T...>>{
        static constexpr size_t size = sizeof...(T);
    };

    //Проверка наличия типа в списке
    template <typename Type, typename List>
    struct IsContained;

    template <typename Type, typename... T>
    struct IsContained<Type, TypeList<T...>>{
        static constexpr bool value = (std::is_same_v<Type, T> || ...);
    };

    //Получение индекса типа в списке
    template <typename Type, int i, typename List>
    struct Index;

    template <typename Type, int i, typename T1, typename... T2>
    struct Index<Type, i, TypeList<T1, T2...>>{
        static constexpr int index = std::is_same_v<Type, T1> ? i : Index<Type, i + 1, TypeList<T2...>>::index;
    };

    template <typename Type, int i>
    struct Index<Type, i, TypeList<>>{
        static constexpr int index = -1;
    };

    //Добавление типа в конец списка
    template <typename Elem, typename List>
    struct PushBack;

    template <typename Elem, typename... T>
    struct PushBack<Elem, TypeList<T...>>{
        using type = TypeList<T..., Elem>;
    };

    //Добавление типа в начало списка
    template <typename Elem, typename List>
    struct PushFront;

    template <typename Elem, typename... T>
    struct PushFront<Elem, TypeList<T...>>{
        using type = TypeList<Elem, T...>;
    };
};

template <size_t i, typename List>
using get = typename TypeList_inner::Get<i, List>::type;

template <typename List>
inline constexpr size_t size = TypeList_inner::Size<List>::size;

template <typename Type, typename List>
inline constexpr bool is_contained = TypeList_inner::IsContained<Type, List>::value;

template <typename Type, typename List>
inline constexpr int index = TypeList_inner::Index<Type, 0, List>::index;

template <typename Elem, typename List>
using pushback = typename TypeList_inner::PushBack<Elem, List>::type;

template <typename Elem, typename List>
using pushfront = typename TypeList_inner::PushFront<Elem, List>::type;

#endif