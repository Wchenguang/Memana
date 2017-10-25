#ifndef _MEMANA_H
#define _MEMANA_H


#include <cstddef>
#include <cstdlib>
#include <iostream>


//内存块封装
class Block{
public:
    void *res;
    Block *next;

    Block();
};

//内存池
class Memana{

private:

    enum {
        MAX_BYTES = 128,                                        //大于MAX以 malloc 分配
        MINI_BYTES = 8,
        ALIGN = 8,                                              //粒度
        BLOCK_LIST_SIZE = (MAX_BYTES - MINI_BYTES)/ALIGN + 1,   //block 链表长度
    };

    //左闭右开 tail不可访问
    char *resHead;
    char *resTail;

    //内存块链 用于存储 8-128 的零散内存
    Block *blocklist[BLOCK_LIST_SIZE];

    //向上 取小于128的 ALIGN的倍数
    size_t RoundUp(size_t num);

    //向下 取小于12
    size_t RoundDown(size_t num);

    //获取相应 规范size 对应链表的下标
    size_t getIndexInList(size_t size);

    //建立一个内存块 并添加至表中
    void appendBlock(int index, void *data);

    //当 一个内存块链 为空 重新充满
    //默认添加 20 个内存块
    void refillTargetBlocks(size_t index, size_t num = 20);

    //获取 相应大小 与 个数的内存块
    char *getBlocksFromPool(size_t blockSize, size_t &blockNum);

    //获取 相应适合大小的内存块
    Block *getBlock(size_t size);

    static Memana *self;


    //初始化内存块链表
    explicit Memana(size_t initNum = ALIGN);

    //不可拷贝
    Memana(const Memana &m);

public:

    //单例模式
    static Memana * GetInstance();

    //销毁
    virtual ~Memana();

    //分配内存
    void *allocate(size_t size);

    //回收内存 只回收到链表中 否则不连续
    void dellocate(void *data, size_t size);


};

//尝试单例模式下的显式调用析构函数
/*class MemPool{
public:
    static Memana *m;
    MemPool(){
        m = Memana::GetInstance();
    }
    ~MemPool(){
        if(m)
            m->~Memana();
    }
};*/

extern Memana &__Wpool;

#endif

