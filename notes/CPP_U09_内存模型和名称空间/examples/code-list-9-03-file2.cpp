// file2.cpp
#include <iostream>
#include <cmath>
#include "coordin.h"

polar rect2polar(rect xy)
{
    polar answer;
    answer.dist = sqrt(xy.x * xy.x + xy.y * xy.y);
    answer.angle = atan(xy.y / xy.x);
    return answer;
};

void show_polar(polar da)
{
    const double Rad2degree = 180/M_PI;
    std::cout << "distance = " << da.dist;
    std::cout << ", angle(rad) = " << da.angle;
    std::cout << ", angle(degree) = " << da.angle * Rad2degree << ".\n";
}
