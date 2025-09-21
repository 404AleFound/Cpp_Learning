// coordin.h -- structure template and function prototypes
#ifndef COORDIN_H_
#define COORDIN_H_

#include <iostream>
#include <cmath>

struct rect
{
    double x;
    double y;
};

struct polar 
{
    double dist;
    double angle;
};

polar rect2polar(rect xy);
void show_polar(polar da);

#endif

// 一个文件只能将同一个头文件包含一次。
// 但可能在不知不觉下将头文件包含多次
// 使用
// ifndef COORDIN_H_
// ...
// endif
// 避免将一个头文件被包含多次