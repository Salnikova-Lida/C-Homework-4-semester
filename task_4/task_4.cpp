#include "mixIn.h"

class Number : public less_than_comparable<Number>, public MixInCounter<Number> {
  public:
    Number(int value) : m_value{value}{}
    int value() const {return m_value;}
    bool operator<(Number const& other) const {
        return m_value < other.m_value;
    }

  private:
    int m_value;
};

void assert(bool ass){
    std::string answer = (ass) ? "True" : "False";
    std::cout << answer << std::endl;
}


int main(){
    Number one{1};
    Number two{2};
    Number three{3};
    Number four{4};
    assert(one >= one);
    assert(three <= four);
    assert(two == two);
    assert(three > two);
    assert(one < two);
    std::cout << "Count: " << MixInCounter<Number>::count() << std::endl;
    return 0;
}