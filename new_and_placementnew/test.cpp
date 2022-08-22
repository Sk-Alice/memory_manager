#include "Foo.h"

void test_new_and_array_new()
{
    cout << "test_new_and_array_new()......" << endl;
    cout << "sizeof(Foo) = " << sizeof(Foo) << endl;

    Foo* p = new Foo;
    delete p;

    Foo* pArray = ::new Foo[5];
    delete[] pArray;
}

void test_placement_new()
{
    cout << "test_placement_new()......." << endl;
    Foo start;

    Foo* p1 = new Foo;
    Foo* p2 = new(&start) Foo;
    Foo* p3 = new(&start) Foo(1);
    Foo* p4 = new Foo(1);
}

int main()
{
    // test_new_and_array_new();
    test_placement_new();

    system("pause");
    return 0;
}