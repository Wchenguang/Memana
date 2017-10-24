#include "Memana.h"

#include <cstdio>

//Memana *__pWpool = Memana::GetInstance();
Memana __Wpool;



Block::Block() : res(NULL), next(NULL) {};

/**************************************************************************/

//单例模式
Memana *Memana::self = NULL;

Memana *Memana::GetInstance()
{
    if(Memana::self == NULL)  //判断是否第一次调用
        Memana::self = new Memana();
    return Memana::self;
}

//向上 取小于128的 ALIGN的倍数
size_t Memana::RoundUp(size_t num){
    return (num + ALIGN - 1) & ~(ALIGN - 1);
}

//向下 取小于12
size_t Memana::RoundDown(size_t num){
    return num &  ~(ALIGN - 1);
}

//获取相应 规范size 对应链表的下标
size_t Memana::getIndexInList(size_t size){
    return size / ALIGN - 1;
}

//建立一个内存块 并添加至表中
void Memana::appendBlock(int index, void *data){
    Block *block = new Block;
    block->next = blocklist[index];
    block->res = data;
    blocklist[index] = block;
}

//当 一个内存块链 为空 重新充满
//默认添加 20 个内存块
void Memana::refillTargetBlocks(size_t index, size_t num){
    size_t blockSize = (index + 1) * ALIGN;
    char *data = getBlocksFromPool(blockSize, num);
    for(int i = 0; i < num; ++i){
        appendBlock(index, data);
        data += blockSize;
    }
}

//获取 相应大小 与 个数的内存块
char *Memana::getBlocksFromPool(size_t blockSize, size_t &blockNum){
    size_t leftBytes = resTail - resHead;

    while (1){
        //应保证至少由ALIGN个字节剩余
        //如果剩余字节无法满足一个block 则处理剩余后，向系统请求扩容内存池
        if(leftBytes < (blockSize + ALIGN)){
            size_t expectSum = blockSize * blockNum;
            //将剩余字节添加至block表
            size_t index = getIndexInList(RoundDown(leftBytes));
            appendBlock(index, resHead);
            //申请 2，1，1／2，1／4， 1／8倍的内存 失败就退出
            float multi = 2.0;
            char *res = NULL;
            while (!res && (multi - 1/8) > 0.0000001){
                res = (char*)malloc(expectSum * multi);
                multi /= 2;
            }
            if(res){
                resHead = res;
                leftBytes = expectSum * multi * 2;
                resTail = resHead + leftBytes;

            }else{
                std::cerr<<"allocate from system err";
                exit(-1);
            }
        }
            //如果可以至少满足一个 则 尽力 返回 ，个数由引用参数返回
        else{
            size_t num = (leftBytes - ALIGN) / blockSize;
            if(num < blockNum)
                blockNum = num;
            resTail -= (blockNum * blockSize);
            return resTail;
        }
    }

}

//获取 相应适合大小的内存块
Block *Memana::getBlock(size_t size){
    size_t blockSize = RoundUp(size);
    size_t index = getIndexInList(blockSize);
    //应向上取 待完善*******************************************-->>>>>>>
    int tempIndex = index;
    //如若为空 则向上寻找
    while (tempIndex < BLOCK_LIST_SIZE && NULL == blocklist[tempIndex])
        ++tempIndex;
    if(tempIndex < BLOCK_LIST_SIZE){
        index = tempIndex;
    }else{
        //保证重新填充该块链 否则 则进入循环等待
        refillTargetBlocks(index, blockSize);
    }
    Block *block = blocklist[index];
    blocklist[index] = block->next;
    return block;

}

//初始化内存块链表
Memana::Memana(size_t initNum){

    std::cerr<<"MEMANA CONSTRUCT"<<std::endl;

    for(int index = 0;  index < BLOCK_LIST_SIZE; ++index)
        blocklist[index] = NULL;

    resHead = (char*)malloc(initNum);
    if(NULL == resHead){
        std::cerr<<"can not Initialize";
        exit(-1);
    }else{
        resTail = resHead + initNum;
    }

    for(int index = 0; index < BLOCK_LIST_SIZE; ++index){
        refillTargetBlocks(index);
    }


}

//解决池扩充后 原内存池无法销毁----------------------------------------------------》》》》》》》》》》》》》》》
//销毁
Memana::~Memana(){

    std::cerr<<"MEMANA DESTRUCT leave it to system"<<std::endl;

    /*for(int i = 0; i < BLOCK_LIST_SIZE; ++i){
        Block *block = blocklist[i];
        while (block){
            Block *temp = block->next;
            delete block;
            block = temp;
        }
    }

    free(resHead);*/
}

//分配内存
void *Memana::allocate(size_t size){
    if(size <= 0)
        return NULL;
    if(size > MAX_BYTES)
        return malloc(size);
    else{
        Block *block = getBlock(size);
        void *data = block->res;
        delete block;
        return data;
    }
}

//回收内存 只回收到链表中 否则不连续
void Memana::dellocate(void *data, size_t size){
    if(size <= 0)
        return;
    if(size > MAX_BYTES)
        free(data);
    else{
        size_t blockSize = RoundUp(size);
        size_t index = getIndexInList(blockSize);
        appendBlock(index, data);
    }
}