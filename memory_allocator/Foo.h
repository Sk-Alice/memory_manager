#ifndef __MYFOO__
#define __MYFOO__

#include <cstring>
#include "allocator.h"

class Foo {
public:
    long L;
    string str;
    static allocator_ myAlloc;
public:
    Foo(long l) : L(l) {}
    static void* operator new(size_t size) {
        return myAlloc.allocate(size);
    }
    static void operator delete(void* pdead) {
        return myAlloc.deallocate(pdead);
    }
};

allocator_ Foo::myAlloc;

#endif