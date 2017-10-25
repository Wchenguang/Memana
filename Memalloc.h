#ifndef _MEMALLOC_H
#define _MEMALLOC_H
#include "Memana.h"

#include <iostream>

//默认为 类 类型
template <typename Type>
class MemAlloc{
public:
    //单个对象的申请
    static Type *Allocate(){
        Type *res = (Type*)__Wpool.allocate(sizeof(Type));
        //构造
        ::new(res) Type();
        return res;
    }
    //对象数组的申请
    static Type *Allocate(size_t num){
        Type *res = (Type*)__Wpool.allocate(sizeof(Type) * num);
        Type *temp = res;
        for(int i = 0; i < num; ++i, ++temp)
            ::new(temp) Type();
        return res;
    }
    //单个对象的销毁
    static void Dellocate(Type *data){
        //析构
        data->~Type();
        __Wpool.dellocate(data, sizeof(Type));
    }
    //对象数组的销毁
    static void Dellocate(Type *data, size_t num){
        Type *temp = data;
        for(int i =0; i < num; ++i, ++temp)
            temp->~Type();
        __Wpool.dellocate(data, sizeof(Type) * num);
    }
};

/*******************************************************************************************/
//偏特化 指针 类型
template <typename Type>
class MemAlloc<Type*>{
public:
    typedef Type** pArrType;
    //单个对象的申请
    static Type**Allocate(){
        return (Type**) __Wpool.allocate(sizeof(Type*));
    }
    //对象数组的申请
    static pArrType Allocate(size_t num){
        return (pArrType) __Wpool.allocate(sizeof(bool) * num);
    }
    //单个对象的销毁
    static void Dellocate(Type **data){
        __Wpool.dellocate(data, sizeof(Type*));
    }
    //对象数组的销毁
    static void Dellocate(pArrType data, size_t num){
        __Wpool.dellocate(data, sizeof(Type*) * num);
    }
};

/*******************************************************************************************/
//偏特化 bool 类型
template <>
class MemAlloc<bool>{
public:
    //单个对象的申请
    static bool *Allocate(){
        return (bool*)__Wpool.allocate(sizeof(bool));
    }
    //对象数组的申请
    static bool *Allocate(size_t num){
        return (bool*)__Wpool.allocate(sizeof(bool) * num);
    }
    //单个对象的销毁
    static void Dellocate(bool *data){
        __Wpool.dellocate(data, sizeof(bool));
    }
    //对象数组的销毁
    static void Dellocate(bool *data, size_t num){
        __Wpool.dellocate(data, sizeof(bool) * num);
    }
};

/*******************************************************************************************/
//偏特化 char 类型
template <>
class MemAlloc<char>{
public:
    //单个对象的申请
    static char *Allocate(){
        return (char*)__Wpool.allocate(sizeof(char));
    }
    //对象数组的申请
    static char *Allocate(size_t num){
        return (char*)__Wpool.allocate(sizeof(char) * num);
    }
    //单个对象的销毁
    static void Dellocate(char *data){
        __Wpool.dellocate(data, sizeof(char));
    }
    //对象数组的销毁
    static void Dellocate(char *data, size_t num){
        __Wpool.dellocate(data, sizeof(char) * num);
    }
};

/*******************************************************************************************/
//偏特化 signed char 类型
template <>
class MemAlloc<signed char>{
public:
    //单个对象的申请
    static signed char *Allocate(){
        return (signed char*)__Wpool.allocate(sizeof(signed char));
    }
    //对象数组的申请
    static signed char *Allocate(size_t num){
        return (signed char*)__Wpool.allocate(sizeof(signed char) * num);
    }
    //单个对象的销毁
    static void Dellocate(signed char *data){
        __Wpool.dellocate(data, sizeof(signed char));
    }
    //对象数组的销毁
    static void Dellocate(signed char *data, size_t num){
        __Wpool.dellocate(data, sizeof(signed char) * num);
    }
};

/*******************************************************************************************/
//偏特化 unsigned char 类型
template <>
class MemAlloc<unsigned char>{
public:
    //单个对象的申请
    static unsigned char *Allocate(){
        return (unsigned char*)__Wpool.allocate(sizeof(unsigned char));
    }
    //对象数组的申请
    static unsigned char *Allocate(size_t num){
        return (unsigned char*)__Wpool.allocate(sizeof(unsigned char) * num);
    }
    //单个对象的销毁
    static void Dellocate(unsigned char *data){
        __Wpool.dellocate(data, sizeof(unsigned char));
    }
    //对象数组的销毁
    static void Dellocate(unsigned char *data, size_t num){
        __Wpool.dellocate(data, sizeof(unsigned char) * num);
    }
};

/*******************************************************************************************/
//偏特化 wchar_t 类型
template <>
class MemAlloc<wchar_t>{
public:
    //单个对象的申请
    static wchar_t *Allocate(){
        return (wchar_t*)__Wpool.allocate(sizeof(wchar_t));
    }
    //对象数组的申请
    static wchar_t *Allocate(size_t num){
        return (wchar_t*)__Wpool.allocate(sizeof(wchar_t) * num);
    }
    //单个对象的销毁
    static void Dellocate(wchar_t *data){
        __Wpool.dellocate(data, sizeof(wchar_t));
    }
    //对象数组的销毁
    static void Dellocate(wchar_t *data, size_t num){
        __Wpool.dellocate(data, sizeof(wchar_t) * num);
    }
};

/*******************************************************************************************/
//偏特化 short 类型
template <>
class MemAlloc<short>{
public:
    //单个对象的申请
    static short *Allocate(){
        return (short*)__Wpool.allocate(sizeof(short));
    }
    //对象数组的申请
    static short *Allocate(size_t num){
        return (short*)__Wpool.allocate(sizeof(short) * num);
    }
    //单个对象的销毁
    static void Dellocate(short *data){
        __Wpool.dellocate(data, sizeof(short));
    }
    //对象数组的销毁
    static void Dellocate(short *data, size_t num){
        __Wpool.dellocate(data, sizeof(short) * num);
    }
};

/*******************************************************************************************/
//偏特化 unsigned short 类型
template <>
class MemAlloc<unsigned short>{
public:
    //单个对象的申请
    static unsigned short *Allocate(){
        return (unsigned short*)__Wpool.allocate(sizeof(unsigned short));
    }
    //对象数组的申请
    static unsigned short *Allocate(size_t num){
        return (unsigned short*)__Wpool.allocate(sizeof(unsigned short) * num);
    }
    //单个对象的销毁
    static void Dellocate(unsigned short *data){
        __Wpool.dellocate(data, sizeof(unsigned short));
    }
    //对象数组的销毁
    static void Dellocate(unsigned short *data, size_t num){
        __Wpool.dellocate(data, sizeof(unsigned short) * num);
    }
};

/*******************************************************************************************/
//偏特化 unsigned int 类型
template <>
class MemAlloc<unsigned int>{
public:
    //单个对象的申请
    static unsigned int *Allocate(){
        return (unsigned int*)__Wpool.allocate(sizeof(unsigned int));
    }
    //对象数组的申请
    static unsigned int *Allocate(size_t num){
        return (unsigned int*)__Wpool.allocate(sizeof(unsigned int) * num);
    }
    //单个对象的销毁
    static void Dellocate(unsigned int *data){
        __Wpool.dellocate(data, sizeof(unsigned int));
    }
    //对象数组的销毁
    static void Dellocate(unsigned int *data, size_t num){
        __Wpool.dellocate(data, sizeof(unsigned int) * num);
    }
};

/*******************************************************************************************/
//偏特化 int 类型
template <>
class MemAlloc<int>{
public:
    //单个对象的申请
    static int *Allocate(){
        return (int*)__Wpool.allocate(sizeof(int));
    }
    //对象数组的申请
    static int *Allocate(size_t num){
        return (int*)__Wpool.allocate(sizeof(int) * num);
    }
    //单个对象的销毁
    static void Dellocate(int *data){
        __Wpool.dellocate(data, sizeof(int));
    }
    //对象数组的销毁
    static void Dellocate(int *data, size_t num){
        __Wpool.dellocate(data, sizeof(int) * num);
    }
};

/*******************************************************************************************/
//偏特化 long 类型
template <>
class MemAlloc<long>{
public:
    //单个对象的申请
    static long *Allocate(){
        return (long*)__Wpool.allocate(sizeof(long));
    }
    //对象数组的申请
    static long *Allocate(size_t num){
        return (long*)__Wpool.allocate(sizeof(long) * num);
    }
    //单个对象的销毁
    static void Dellocate(long *data){
        __Wpool.dellocate(data, sizeof(long));
    }
    //对象数组的销毁
    static void Dellocate(long *data, size_t num){
        __Wpool.dellocate(data, sizeof(long) * num);
    }
};

/*******************************************************************************************/
//偏特化 unsigned long 类型
template <>
class MemAlloc<unsigned long>{
public:
    //单个对象的申请
    static unsigned long *Allocate(){
        return (unsigned long*)__Wpool.allocate(sizeof(unsigned long));
    }
    //对象数组的申请
    static unsigned long *Allocate(size_t num){
        return (unsigned long*)__Wpool.allocate(sizeof(unsigned long) * num);
    }
    //单个对象的销毁
    static void Dellocate(unsigned long *data){
        __Wpool.dellocate(data, sizeof(unsigned long));
    }
    //对象数组的销毁
    static void Dellocate(unsigned long *data, size_t num){
        __Wpool.dellocate(data, sizeof(unsigned long) * num);
    }
};

/*******************************************************************************************/
//偏特化 float 类型
template <>
class MemAlloc<float>{
public:
    //单个对象的申请
    static float *Allocate(){
        return (float*)__Wpool.allocate(sizeof(float));
    }
    //对象数组的申请
    static float *Allocate(size_t num){
        return (float*)__Wpool.allocate(sizeof(float) * num);
    }
    //单个对象的销毁
    static void Dellocate(float *data){
        __Wpool.dellocate(data, sizeof(float));
    }
    //对象数组的销毁
    static void Dellocate(float *data, size_t num){
        __Wpool.dellocate(data, sizeof(float) * num);
    }
};

/*******************************************************************************************/
//偏特化 double 类型
template <>
class MemAlloc<double>{
public:
    //单个对象的申请
    static double *Allocate(){
        return (double*)__Wpool.allocate(sizeof(double));
    }
    //对象数组的申请
    static double *Allocate(size_t num){
        return (double*)__Wpool.allocate(sizeof(double) * num);
    }
    //单个对象的销毁
    static void Dellocate(double *data){
        __Wpool.dellocate(data, sizeof(double));
    }
    //对象数组的销毁
    static void Dellocate(double *data, size_t num){
        __Wpool.dellocate(data, sizeof(double) * num);
    }
};

/*******************************************************************************************/
//偏特化 long double 类型
template <>
class MemAlloc<long double>{
public:
    //单个对象的申请
    static long double *Allocate(){
        return (long double*)__Wpool.allocate(sizeof(long double));
    }
    //对象数组的申请
    static long double *Allocate(size_t num){
        return (long double*)__Wpool.allocate(sizeof(long double) * num);
    }
    //单个对象的销毁
    static void Dellocate(long double *data){
        __Wpool.dellocate(data, sizeof(long double));
    }
    //对象数组的销毁
    static void Dellocate(long double *data, size_t num){
        __Wpool.dellocate(data, sizeof(long double) * num);
    }
};


#endif