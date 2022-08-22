#include <iostream>
#include <cassert>

using namespace std;

// 此处为一个 new handler
void no_more_memory()
{
    cerr << "out of memory" << endl;
    abort();
}

int main()
{
    // 该函数由标准库提供
    // typedef void (*new_handler)();
    // new_handler set new_handler(new_handler p) throw();      传入一个new_handler,返回一个new_handler
    // 设计原因，先前有一个new_handler_A,再传入一个new_handler_B,返回以前的new_handler_A以便记录
    set_new_handler(no_more_memory);

    int* p = new int[10000000000];
    assert(p);      // 其作用是如果它的条件返回错误，则终止程序执行

    system("pause");
    return 0;
}