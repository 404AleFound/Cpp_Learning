# 处理数据

面向对象编程的本质是设计并扩展自己的数据类型。设计自己的数据类型就是让类型与数据相匹配。

内置的 C++数据类型分为两类：基本类型和复合类型。本章主要介绍 C++的基本类型：浮点数和整数。第四章将介绍在基本类型的基础上创建的复合类型，包括数组、字符串、指针和结构。 

## 变量名的命名规则

数据类型声明含义，为其变量分配合适的内存空间。

## 整型

作用：整型变量表示的是整数类型的数据

C++中能够表示整型的类型有以下集中，区别在于占用的内存空间不同。

一字节（byte）通常指的是8位的内存单位。从某种意义上说，字节指的就是描述计算机内存量的度量单位。

各个类型占用空间大小规定如下：

* short至少8位；
* int至少与short一样长；
* long至少32位，且至少与int与一样长；
* long long 至少64位，且至少与long一样长。

下表为常见的整型占用空间大小：

| 数据类型  | 占用空间                                                     | 取值范围             |
| --------- | ------------------------------------------------------------ | -------------------- |
| short     | 2字节                                                        | $[-2^{15},2^{15}-1]$ |
| **int**   | **4字节**                                                    | $[-2^{31},2^{31}-1]$ |
| long      | 4字节（windows），4字节（Linux，32位），8字节（Linux，64位） | $[-2^{31},2^{31}-1]$ |
| long long | 8字节                                                        | $[-2^{63},2^{63}-1]$ |

由于不同系统中各个整型的最大长度可能不一样，而记住不同系统对于整型的规定又不现实。但是C++提供`sizeof`关键字统计变量对应的数据类型所占的内存空间。

首先`sizeof`运算符返回类型或变量的长度，单位为字节，用法如下：

`sizeof(数据类型/变量)`

但是，仅仅知道字节是不够的，因为不同系统字节的位数可能是8位也可能是16位。通过`climits`头文件，可以获得整型的限制信息。

```c++
// limits.cpp -- some integer limits
#include <iostream>
#include <climits>
int main()
{
    using namespace std;
    int n_int = INT_MAX;
    short n_short = SHRT_MAX;
    long n_long = LONG_MAX;
    long long n_long_long = LLONG_MAX;
    
    // sizeof operator yield size of type or variable
    cout << "short:" << sizeof(short) << endl;
    cout << "int: " << sizeof(int) << endl;
    cout << "long: " << sizeof(long) << endl;
    cout << "long long: " << sizeof(long long) << endl;
    return 0;
}
```
## 浮点型

有效位（significant figure）是数字中有意义的位。

| 数据类型 | 占用空间 | 有效数字范围    |
| -------- | -------- | --------------- |
| float    | 4字节    | 7位有效数字     |
| double   | 8字节    | 15~16位有效数字 |



## 运算符

```C++	
// init.cpp -- type change in initialization
#include <iostream>

int main()
{
    using namespace std;
    cout.setf(ios_base::fixed, ios_base::floatfield);
    float tree = 3;
    int guess(3.9832);
    int debt = 7.2E12;
    cout << "tree = " << tree << endl;
    cout << "guess = " << guess << endl;
    cout << "debt = " << debt << endl;
    return 0;
}
```

下面是该程序在系统中的输出：

```cmd
tree = 3.000000
guess = 3
debt = 1634811904
```

## 类型转换

### 初始化和赋值进行的转换

### 以{ }方式初始化时进行的转换

### 表达式中的转换

### 传递参数时的转换

### 强制类型转换

 

