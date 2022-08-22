#ifndef __MYFOO__
#define __MYFOO__
#include <iostream>

using namespace std;

class Bad {};

class Foo {
public:
    int _id;
    long _data;
    string _str;

public:
    Foo() : _id(0) { cout << "default ctor. this = " << this << " id = " << _id << endl; }
    // 模拟在调用operator new分配内存后，调用构造函数时出现异常并抛出，造成内存泄露，调用对应的“placement delete”
    Foo(int i) : _id(i) { cout << "ctor. this = " << this << " id = " << _id << endl; throw Bad(); }
    virtual ~Foo() { cout << "dtor. this = " << this << " id = " << _id << endl; }

    // size_t: unsigned int
    // 根据new的作用，分配内存然后构造，所以在对象构造前调用operator new，故使其为static
    static void* operator new(size_t size);
    static void  operator delete(void* p, size_t size);
    static void* operator new[](size_t size);
    static void  operator delete[](void* p, size_t size);

    // placement new
    // 第一参数必须为size_t
    static void* operator new(size_t size, void* start);
    static void  operator delete(void*,void*);
};

void* Foo::operator new(size_t size)
{
    Foo* p = (Foo*)malloc(size);
    cout << "Foo::operator new(), size = " << size << " return: " << p << endl;
     return p;
}

void Foo::operator delete(void* p, size_t size)
{
    cout << "operator delete(), p = " << p << " size = " << size << endl;
    free(p);
}

void* Foo::operator new[](size_t size)
{
    Foo* p = (Foo*)malloc(size);
    cout << "Foo::operator new[](), size = " << size << " return: " << p << endl;
    return p;
}

void Foo::operator delete[](void* p, size_t size)
{
    cout << "operator delete(), p = " << p << " size = " << size << endl;
    free(p);
}

void* Foo::operator new(size_t size, void* start)
{
    cout << "Foo::operator new(size_t, void*), size = " << size << " return: " << start << endl;
    return start;
}

void Foo::operator delete(void* p, void*)
{
    cout << "operator delete(void* p, void*), p = " << p << " size = " << sizeof(p) << endl;
    free(p);
}

#endif