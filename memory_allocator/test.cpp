#include <iostream>
#include <unordered_map>
#include "Screen.h"
#include "Airplane.h"
#include "Foo.h"
#include "allocator.h"

using namespace std;

void test_per_class_allocator_1()
{
    cout << sizeof(Screen) << endl;

    size_t const N = 100;
    Screen* p[N];

    for (int i = 0; i < N; i++) {
        p[i] = new Screen(i);
    }

    // 输出前10个pointers，比较其间隔
    for (int i = 0; i < 10; i++) {
        cout << p[i] << endl;
    }

    for (int i = 0; i < 10; i++) {
        delete p[i];
    }
}

void test_per_class_allocator_2()
{
    cout << sizeof(AirPlane) << endl;

    size_t const N = 100;
    AirPlane* p[N];

    for (int i = 0; i < N; i++) {
        p[i] = new AirPlane;
    }

    p[1]->set(1000, 'A');
    p[5]->set(5000, 'B');
    p[9]->set(9000, 'C');
    cout << p[1] << ' ' << p[1]->getType() << ' ' << p[1]->getMiles() << endl;
  	cout << p[5] << ' ' << p[5]->getType() << ' ' << p[5]->getMiles() << endl;
  	cout << p[9] << ' ' << p[9]->getType() << ' ' << p[9]->getMiles() << endl; 

    // 输出前10个pointers，比较其间隔
    for (int i = 0; i < 10; i++) {
        cout << p[i] << endl;
    }

    for (int i = 0; i < N; i++) {
        delete p[i];
    }
}

void test_static_allocator()
{
    Foo* p[100];
    cout << "sizeof(Foo) = " << sizeof(Foo) << endl;
    cout << "sizeof(allocator_) = " << sizeof(allocator_) << endl;
    for (int i = 0; i < 23; i++) {
        p[i] = new Foo(i);
        cout << p[i] << " " << p[i]->L << endl;
    }

    for (int i = 0; i < 23; i++) {  // 比较地址间隔，注意观察每组（CHUNK=5,5个一组）之间的间隔
        delete p[i];
    }

}

int main()
{
    test_per_class_allocator_1();
    // test_per_class_allocator_2();
    // test_static_allocator();

    system("pause");
    return 0;
}