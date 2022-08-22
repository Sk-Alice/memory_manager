#ifndef __MYALLOCATOR__
#define __MYALLOCATOR__

// static allocator

// 将分配特定大小区块的memory allocator包装成一个class allocator
// 这样每个allocator object都是个分配器，体内维护一个freeStore lists
// 案例使用：查看 Foo.h

class allocator_ {
private:
    struct obj {
        struct obj* next;   // embedded pointer 嵌入式指针
    };
public:
    void* allocate(size_t);
    void deallocate(void*);
private:
    obj* freeStore = nullptr;
    const int CHUNK = 5;    // 标准库大小为20
};

void* allocator_::allocate(size_t size)
{
    obj* p;
    if (!freeStore) {
        size_t chunk = CHUNK * size;
        freeStore = p = (obj*)malloc(chunk);

        for (int i = 0; i < CHUNK; i++) {
            p->next = (obj*)((char*)p + size);
            p = p->next;
        }
        p->next = nullptr;
    }
    p = freeStore;
    freeStore = freeStore->next;
    return p;
}

void allocator_::deallocate(void* p)
{
    ((obj*)p)->next = freeStore;
    freeStore = (obj*)p;
}

#endif