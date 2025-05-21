#ifndef __TYPEMAP_H__
#define __TYPEMAP_H__

#include "typeList.h"

namespace TypeMap_inners{
    struct node_outer{
        node_outer* next{nullptr};
        bool defined{false};

        virtual void SetData(const void* _data) = 0;
        virtual void GetData(void* _data) = 0;
        virtual ~node_outer() = default;
    };

    template <typename T, typename... T2>
    struct node : node_outer{
        node(){
            if constexpr (sizeof...(T2) > 0) {next = new node<T2...>();} else {next = nullptr;}
        }
        
        T data{};
        virtual void SetData(const void* _data) override{
            defined = true;
            data = *static_cast<const T*>(_data);
        }
        virtual void GetData(void* _data) override{
            *static_cast<T*>(_data) = data;
        }
    };
};

template <typename... T>
class TypeMap{
    using node_outer = typename TypeMap_inner::node_outer;
    using Keys = TypeList<T...>;

    template <typename... Types>
    using node = typename TypeMap_inner::node<Types...>;

  public:
    TypeMap(){
        first = new node<T...>();
        node_outer* elem = first;
        node_outer* buffer;
    }

    ~TypeMap(){
        node_outer* next;
        for (int i = 0; i < Size(); ++i){
            next = first->next;
            first = next;
        }
        delete first;
    }

    constexpr size_t Size() const{
        return TypeList_inner::Size<Keys>::size;
    }
    
    //Добавление элемента в контейнер с указанием типа в качестве ключа
    template <typename Type>
    void AddValue(const Type& value){
        node_outer* n = GetNode<Type>();
        static_cast<node<Type>*>(n)->SetData(&value);
    }

    //Получение значения по заданному типу ключа
    template <typename Type>
    Type GetValue(){
        node_outer* n = GetNode<Type>();
        if (n->defined){
            Type ret;
            static_cast<node<Type>*>(n)->GetData(&ret);
            return ret;
        }
        std::cout << "Can't get deleted element" << std::endl;
        return Type();
    }

    //Проверка наличия элемента по типу ключа
    template <typename Type>
    bool Contains(){
        return GetNode<Type>()->defined;
    }

    //Удаление элемента по типу ключа
    template <typename Type>
    void RemoveValue(){
        GetNode<Type>()->defined = false;
    }

  private:
    node_outer* first;

    template <typename Type>
    node_outer* GetNode() const{
        node_outer* elem = first;
        for (int i = 0; i < index<Type, Keys>; ++i){
            elem = elem->next;
        }
        return elem;
    }
};

#endif