#include "typeList.h"

int main(){
    //Создание списков путем добавления типов в начало и конец списка
    using List0 = TypeList<>;
    using List1 = pushback<std::string, List0>;
    using List2 = pushback<int, List1>;
    using List3 = pushfront<double, List2>;
    using List4 = pushfront<float, List3>;
    using List5 = pushfront<char, List4>;

    //Проверка получения размера списка    
    static_assert(size<List0> == 0);
    static_assert(size<List1> == 1);
    static_assert(size<List2> == 2);
    static_assert(size<List3> == 3);
    static_assert(size<List4> == 4);
    static_assert(size<List5> == 5);

    //Проверка наличия типа в списке
    static_assert(is_contained<float, List0> == false);
    static_assert(is_contained<double, List1> == false);
    static_assert(is_contained<int, List2> == true);
    static_assert(is_contained<char, List3> == false);
    static_assert(is_contained<std::string, List4> == true);
    static_assert(is_contained<char, List5> == true);

    //Проверка получения индекса типа в списке
    static_assert(std::is_same_v<get<0, List1>, std::string>);
    static_assert(std::is_same_v<get<0, List2>, std::string>);
    static_assert(std::is_same_v<get<2, List3>, int>);
    static_assert(std::is_same_v<get<1, List4>, double>);
    static_assert(std::is_same_v<get<4, List5>, int>);

    //Получение индекса типа в списке
    static_assert(index<std::string, List1> == 0);
    static_assert(index<std::string, List2> == 0);
    static_assert(index<int, List3> == 2);
    static_assert(index<double, List4> == 1);
    static_assert(index<int, List5> == 4);
}