
#include <cstddef>
#include <cstdlib>
#include <iostream>

typedef short LIMIT_TYPE;

//内存块封装
class Block{
public:
    void *res;
    Block *next;

    Block() : res(NULL), next(NULL) {};
};

//内存池
class Memana{

private:

    enum {
        MAX_BYTES = 128,                                        //大于MAX以 malloc 分配
        MINI_BYTES = 8,
        ALIGN = 8,                                              //粒度
        BLOCK_LIST_SIZE = (MAX_BYTES - MINI_BYTES + 1)/ALIGN,   //block 链表长度
    };

    //左闭右开 tail不可访问
    char *resHead;
    char *resTail;

    //内存块链 用于存储 8-128 的零散内存
    Block *blocklist[BLOCK_LIST_SIZE];

    //向上 取小于128的 ALIGN的倍数
    size_t RoundUp(size_t num){
        return (num + ALIGN - 1) & ~(ALIGN - 1);
    }

    //向下 取小于12
    size_t RoundDown(size_t num){
        return num &  ~(ALIGN - 1);
    }

    //获取相应 规范size 对应链表的下标
    size_t getIndexInList(size_t size){
        return size / ALIGN - 1;
    }

    //建立一个内存块 并添加至表中
    void appendBlock(int index, void *data){
        Block *block = new Block;
        block->next = blocklist[index];
        block->res = data;
        blocklist[index] = block;
    }

public:

    //初始化内存块链表
    Memana(size_t initNum = ALIGN){
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

    //当 一个内存块表 为空 重新充满
    void refillTargetBlocks(size_t index, size_t num = 20){
        size_t blockSize = (index + 1) * ALIGN;
        char *data = getBlocksFromPool(blockSize, num);
        for(int i = 0; i < num; ++i){
            appendBlock(index, data);
            data += blockSize;
        }
    }

    //获取 相应大小 与 个数的内存块
    char *getBlocksFromPool(size_t blockSize, size_t &blockNum){
        size_t leftBytes = resTail - resHead;

        while (1){
            //应保证至少由ALIGN个字节剩余
            //如果剩余字节无法满足一个block 则处理剩余后，向系统请求扩容内存池
            if(leftBytes < (blockSize + ALIGN)){
                size_t expectSum = blockSize * blockNum;
                //将剩余字节添加至block表
                size_t index = getIndexInList(RoundDown(leftBytes));
                appendBlock(index, resHead);
                //申请 1+1,1+1/2,1+1/4,1+1/8的内存 失败就退出
                float multi = 1.0;
                char *res = NULL;
                while (!res && (multi - 1/8) > 0.0000001){
                    res = (char*)malloc(expectSum * (1 + multi));
                    multi /= 2;
                }
                if(res){
                    resHead = res;
                    leftBytes = expectSum * (1 + multi * 2);
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
    Block *getBlock(size_t size){
        size_t blockSize = RoundUp(size);
        size_t index = getIndexInList(blockSize);
        //应向上取 待完善*******************************************-->>>>>>>
        while (NULL == blocklist[index])
            refillTargetBlocks(index, blockSize);

        Block *block = blocklist[index];
        blocklist[index] = block->next;
        return block;

    }

    //分配内存
    void *allovate(size_t size){
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
    void dellocate(){

    }

    //销毁有问题
    virtual ~Memana(){
        /*for(int i = 0; i < BLOCK_LIST_SIZE; ++i){
            Block *block = blocklist[i];
            while (block){
                Block *temp = block->next;
                delete block;
                block = temp;
            }
        }

        delete resHead;*/
    }
};

