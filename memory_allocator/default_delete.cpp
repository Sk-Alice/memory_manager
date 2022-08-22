#include <iostream>

using namespace std;

class Foo {
public:
    long _x;
public:
    Foo(long x = 0) : _x(x) {}

    // static void* operator new(size_t size) = default;   //  error: 'static void Foo::operator delete(void*)' cannot be defaulted
    // static void  operator delete(void* p) = default;
    static void* operator new(size_t size) = delete;
    static void  operator delete(void* p) = delete;
};

int main()
{
    // Foo* p1 = new Foo(5);       // error: use of deleted function 'static void* Foo::operator new(size_t)'
    // delete p1;

    system("pause");
    return 0;
}