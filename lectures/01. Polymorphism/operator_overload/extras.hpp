#include <iostream>
#pragma once

struct Char
{
    int a;
    Char(int a) : a (a) {}
};

int operator+(Char& a, const Char& b)
{
    int result = a.a * b.a;
    a.a = b.a;
    return result;
}

std::ostream& operator<<(std::ostream& os, const Char& a)
{
    return os<<a.a;
}

#define char Char
