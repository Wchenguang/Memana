#include <iostream>

#include "Memalloc.h"

class A{
public:
     int b;

    A(){
        b = 0;
        std::cout<<"construct"<<std::endl;
    }
    virtual ~A() {
        std::cout<<"destruct"<<std::endl;
    }
    void *operator new(size_t size){
        std::cout<<"allocate"<<std::endl;
    }

    void operator delete(void *p){
        std::cout<<"dellocate"<<std::endl;
    }
};

int main(){

    /*
     * 内存池 不可拷贝 不可构造
     * Memana m1;
     * Memana m2 = __Wpool;
     */

    A *gclass = MemAlloc<A>::Allocate(4);
    for(int i = 0; i < 4; ++i){
        std::cout<<gclass[i].b<<std::endl;
    }
    MemAlloc<A>::Dellocate(gclass, 4);

    std::cout<<"**********************************************************"<<std::endl;

    bool *gbool = MemAlloc<bool >::Allocate(4);
    for(int i = 0; i < 4; ++i){
        std::cout<<(int)gbool[i]<<std::endl;
    }
    MemAlloc<bool >::Dellocate(gbool, 4);

    std::cout<<"**********************************************************"<<std::endl;

    char *gchar = MemAlloc<char >::Allocate(4);
    for(int i = 0; i < 4; ++i){
        std::cout<<gchar[i]<<std::endl;
    }
    MemAlloc<char>::Dellocate(gchar, 4);

    std::cout<<"**********************************************************"<<std::endl;

    wchar_t *gwchar = MemAlloc<wchar_t >::Allocate(4);
    for(int i = 0; i < 4; ++i){
        std::cout<<gwchar[i]<<std::endl;
    }
    MemAlloc<wchar_t>::Dellocate(gwchar, 4);

    std::cout<<"**********************************************************"<<std::endl;

    int *gint = MemAlloc<int >::Allocate(4);
    for(int i = 0; i < 4; ++i){
        std::cout<<gint[i]<<std::endl;
    }
    MemAlloc<int>::Dellocate(gint, 4);

    return 0;
}