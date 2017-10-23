#include <iostream>
#include "Memana.h"


Memana allocator;

class A{
public:
    char *b;

    A(){
        std::cout<<"construct"<<std::endl;
        b = (char *)allocator.allocate(10);
    }
    virtual ~A() {
        std::cout<<"destruct"<<std::endl;
        if(b)
            allocator.dellocate(b, 10);
    }
    void *operator new(size_t size){
        std::cout<<"allocate"<<std::endl;
        return allocator.allocate(size);
    }

    void operator delete(void *p){
        std::cout<<"dellocate"<<std::endl;
        allocator.dellocate(p, sizeof(A));
    }
};

int main(){


    char *str = (char*)allocator.allocate(10);
    memset(str,0,10);
    strcpy(str, "hello");

    allocator.dellocate(str, 10);

    str = (char*)allocator.allocate(10);
    memset(str,0,10);
    strcpy(str, "hello");

    allocator.dellocate(str, 10);

    str = (char*)allocator.allocate(10);
    memset(str,0,10);
    strcpy(str, "hello");

    allocator.dellocate(str, 10);

    std::cout<<str<<std::endl;
/*******************************/

    //类的构造函数无法运行
    //STL 用萃取技术 型别
    //可以标志指定

    //分配内存
    A *a = (A*)A::operator new(sizeof(A));
    //构造函数
    ::new(a) A();

    a->~A();

    //释放内存
    A::operator delete(a);

    return 0;
}