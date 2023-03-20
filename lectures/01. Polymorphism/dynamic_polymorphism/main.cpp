#include <iostream>

struct Base
{
    virtual void f(int) {}
};

struct Derived : Base
{
    void f(int) override
    {
        std::cout << "Derived::foo(int)" << std::endl;
    }
};

struct SecondDerived: Derived
{
    void foo(int)
    {
        std::cout << "SecondDerived::foo(int)" << std::endl;
    }
};

int main()
{
    SecondDerived d{};
    d.f(1);
    Base& b = d;
    b.f(1);
}
