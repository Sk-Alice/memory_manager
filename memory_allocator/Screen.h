#ifndef __MYSCREEN__
#define __MYSCREEN__

#include <cstddef>
#include <iostream>

using namespace std;

//ref. C++Primer 3/e, p.765
// per-class allocator_1

// 利用内存池的观念【即创建出一大段连续空间的内存，然后将其切割成一小段一小段】,减少使用malloc的次数，以此来避免分配cookie所占用不必要的内存
// 该版本缺点：next指针多占用了内存
// 查看版本2（AirPlane.h）：使用union解决

class Screen {
public:
    Screen(int x) : i(x) { }
    int get() { return i; }

    static void* operator new(size_t);
    static void operator delete(void*);

private:
    Screen* next;
    static Screen* freeStore;
    static const int screenChunk;

private:
    int i;
};

Screen* Screen::freeStore = nullptr;
const int Screen::screenChunk = 24;

void* Screen::operator new(size_t size) 
{
    Screen* p;
    if (!freeStore) {    // 如果linked list为空，所以申请一大块内存
        size_t chunk = screenChunk * size;
        freeStore = p =
             reinterpret_cast<Screen*>(new char[chunk]);

        // 将一大块内存分成片片，当做linked list串联起来
        while ( p != &freeStore[screenChunk - 1]) {
            p->next = p + 1;
            p++;
        }
        p->next = nullptr;
    }
    p = freeStore;
    freeStore = freeStore->next;

    return p;
}

void Screen::operator delete(void* p)
{
    // 将delete object 插回 free list 前端
    (static_cast<Screen*>(p))->next = freeStore;
    freeStore = static_cast<Screen*>(p);
}

#endif