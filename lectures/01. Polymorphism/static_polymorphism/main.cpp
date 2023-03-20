#include <iostream>

int foo(int)
{
    std::cout << "foo(int)" << std::endl;
}

int foo(int, int)
{
    std::cout << "foo(int, int)" << std::endl;
}

void foo(double)
{
    std::cout << "foo(double)" << std::endl;
}

struct A
{
    int a;
    mutable int b;
    void foo(int)
    {
        std::cout << "A::foo(int)" << std::endl;
    }

    void foo(int) const
    {
        std::cout << "A::foo(int) const" << std::endl;
        b = 1;
    }

    void foo(float)
    {
        std::cout << "A::foo(float)" << std::endl;
    }
};

struct B : A
{
    using A::foo;
    int foo(int)
    {
        std::cout << "B::foo(int)" << std::endl;
    }
    B& operator*(const B&)
    {
        std::cout << "B::operator(B&)" << std::endl;
        return *this;
    }

    B& operator*(int)
    {
        std::cout << "B::operator(int)" << std::endl;
        return *this;
    }
};

B& operator*(int a, B& b)
{
   return b * a;
}

int main()
{
    foo(2);
    foo(2.0);
    foo(1, 3.0);
    A a{};
    a.foo(1);
    a.foo(2.0f);
    const A aa{};
    aa.foo(3.0);
    B b{};
    b.foo(1);
    const B bb{};
    bb.foo(1);

    B wynik = b * bb;
    b * 2;
    2 * b;
}
