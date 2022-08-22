#ifndef __MYAIRPLANE__
#define __MYAIRPLANE__

// pre-class allocator_2

// 解决版本1（Screen.h）缺点：通过union关键字来减少使用next而所占耗的内存
// 前两种有共同缺点，
// 就是当第一次分配的内存池使用完后，会再次分配一块大的内存，然后所有内存链接在一起，而不会归还给操作系统
// 并且当多个类时，需要重复的重载operator new
// 查看版本3（allocator.h）：将该动作包装起来

class AirPlane {
private:
    struct AirPlaneRep {
        unsigned long miles;
        char type;
    };
private:
    union {
        AirPlaneRep rep;
        AirPlane* next;
    };
public:
    unsigned long getMiles() { return rep.miles; }
    char getType() { return rep.type; }
    void set(unsigned long m, char t) {
        rep.miles = m;
        rep.type = t;
    }
public:
    static void* operator new(size_t size);
    static void operator delete(void* deadObject, size_t size);
private:
    static const int BLOCK_SIZE;
    static AirPlane* headOfFreeList;
};

AirPlane* AirPlane::headOfFreeList = nullptr;
const int AirPlane::BLOCK_SIZE = 512;

void* AirPlane::operator new(size_t size)
{
    if (size != sizeof(AirPlane)) { // 如果由于继承关系传入的size=sizeof(Airplane)大小不等于sizeof(Airplane)时，则调用::operator new!!
        return ::operator new(size);
    }

    AirPlane* p = headOfFreeList;
    if (p) {    // 已经分配空间，移动链表指针
        headOfFreeList = p->next;
    } else {    // 分配空间已空，分配一大块memory
        AirPlane* newBlock = static_cast<AirPlane*>(::operator new(BLOCK_SIZE * sizeof(AirPlane)));
        // 将大块内存分成小块内存
        for (int i = 0; i < BLOCK_SIZE; i++) {
            newBlock[i].next = &newBlock[i + 1];
        }
        newBlock[BLOCK_SIZE - 1].next = nullptr;
        p = newBlock;
        headOfFreeList = &newBlock[1];
    }
    return p;
}

void AirPlane::operator delete(void* deadObject, size_t size)
{
    if (deadObject == nullptr) return;
    if (size != sizeof(AirPlane)) {
        ::operator delete(deadObject);
        return;
    }

    AirPlane* carcass = static_cast<AirPlane*>(deadObject);
    carcass->next = headOfFreeList;
    headOfFreeList = carcass;
}
#endif