

# 9 内存模型和名称变量

## 9.1 单独编译

和C语言一样，C++也允许甚至鼓励程序员将组件函数放在独立的文件中，可以单独编译这些文件，然后将它们链接成可执行的程序。

目前，程序员常常将原来的程序分为三个部分L:

* 头文件：包含结构声明和使用这些结构的函数的原型
* 源代码文件：包含与结构有关的函数的代码
* 源代码文件：包含调用与结构相关的函数的代码

不要将函数定义或者变量声明放到头文件中。如果在头文件中包含一个函数定义，然后在同属于这个程序的另外两个文件中包含该头文件，会导致一个程序包含同一个函数的两个定义，除非函数内联，这通常会出错。以下是头文件中常常包含的内容。

* 函数原型
* 使用#define或const定义的符号常量
* 结构声明（将结构声明放在头文件中是可以的，因为结构的声明不会创建变量）
* 类声明
* 模板声明
* 内联函数

```c++
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

int main()
{
    rect rplace;
    polar pplace;

    std::cout << "Enter the x and y values: ";
    while (std::cin >> rplace.x >> rplace.y)
    {
        pplace = rect2polar(rplace);
        show_polar(pplace);
        std::cout << "Next two number (q to quit):";
    }
    std::cout << "Done.\n";
    system("pause");
    return 0;
}

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

```

分解为`coordin.h`，`file1.cpp`和`file2.cpp`三个文件，相关文件内容如下：

```C++
// coordin.h
#ifndef COORDIN_H_
#define COORDIN_H_
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
```

使用

```
#ifndef COORDIN_H_
...
#ENDIF
```

确保头文件在一个工程文件中，仅仅被包含一次。

```c++
// file1.cpp
#include <iostream>
#include "coordin.h"
// 使用""则优先在工程文件中查找，若找不到，则之后再系统变量中查找。
// 使用<>仅在系统变量中查找。
using namespace std;

int main()
{
    rect rplace;
    polar pplace;

    std::cout << "Enter the x and y values: ";
    while (std::cin >> rplace.x >> rplace.y)
    {
        pplace = rect2polar(rplace);
        show_polar(pplace);
        std::cout << "Next two number (q to quit):";
    }
    std::cout << "Done.\n";
    system("pause");
    return 0;
}
```

```c++
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

```

## 9.2 内存模型

### 9.2.1 基本概念

持续性。C++使用四种不同的方案来存储数据，这些方案的区别就在于数据保留在内存中的时间。

* 自动存储持续性：在函数定义中声明的变量（包括函数参数）的存储持续时间为自动。它们在程序开始执行其所属的函数或代码块时被创建，在执行完函数或代码块时，它们使用的内存被释放。
* 静态存储持续性：在函数定义外定义的变量和使用关键字static定义的变量的存储持续时间都为静态。它们在程序整个运行过程中都存在。
* 线程序存储持续性：当前，多核处理器非常常见，这些CPU可以同时处理多个执行任务。这让程序能够将计算放在可并行处理的不同线程中。如果变量是使用关键字thread_local声明的，则其生命周期与所属的线程一样长。
* 动态存储持续性：用new运算符分配的内存将一直存在，直到使用delete运算符将其释放或程序结束为止。这种内存的存储持续时间为动态，有时被称为自由存储或堆。

作用域（scope）描述了名称在文件的多大范围内可见。作用域为局部的变量只在定义它的代码块中可用。代码块是由花括号括起的一系列语句。例如函数体就是代码块，但可以在函数体中嵌入其他代码块。作用域为全局的变量在定义变量位置到文件结尾之间都可用。自动变量的作用域为局部，静态变量的作用域是全局还是局部取决于其是如何被定义的。在函数原型作用域中使用的抿成只在包含参数列表的括号内可用。在类中声明的成员的作用域为整个类。在名称空间中声明的变量的作用域为整个名称空间。

链接。链接性为外部的名称可在文件间共享，链接性为内部的名称只能由一个文件中的函数共享。自动变量的名称没有链接性，因为它们不能共享。

### 9.2.2 自动变量

在默认情况下，在函数中声明的函数参数和变量的存储持续性为自动，作用域为局部，没有链接性。如果在代码块中定义了变量，则该变量的存在时间和作用域将被限制在该代码块内。

但代码块内的变量和代码块外的变量名相同，内部的变量会自动覆盖外部变量的定义，新定义可见，旧定义暂时不可见。在程序离开该代码块后，新定义失效，旧定义重新可见。

```c++
#include <iostream>
void oil(int x);
int main()
    
{
    using namespace std;
    int texas = 31;
    int year = 2011;
    
    cout << "t1: In main(), texas = " << texas << ", &texas = ";
    cout << &texas << endl;
    cout << "t1: In main(), year = " << year << ", &year = ";
    cout << &year << endl;
    
    oil(texas);
    
    cout << "t2: In main(), texas = " << texas << ", &texas = ";
    cout << &texas << endl;
    cout << "t2: In main(), year = " << year << ", &year = ";
    cout << &year << endl;

    return 0;
}

void oil(int x)
{
    using namespace std;
    int texas = 5;

    cout << "t1: In oil(), texas = " << texas << ", &texas = ";
    cout << &texas << endl;
    cout << "t1: In oil(), x = " << x << ", &x = ";
    cout << &x << endl;

    {
        int texas = 113;
        cout << "In block, texas = " << texas << ", &texas = ";
        cout << &texas << endl;
        cout << "In block, x = " << x << ", &x = ";
        cout << &x << endl;
    }

    cout << "t2: In oil(), texas = " << texas << ", &texas = ";
    cout << &texas << endl;
    cout << "t2: In oil(), x = " << x << ", &x = ";
    cout << &x << endl;

}
```

输出如下：

```
t1: In main(), texas = 31, &texas = 000000A7040FFB44
t1: In main(), year = 2011, &year = 000000A7040FFB64
t1: In oil(), texas = 5, &texas = 000000A7040FFA04
t1: In oil(), x = 31, &x = 000000A7040FFB20
In block, texas = 113, &texas = 000000A7040FFA24
In block, x = 31, &x = 000000A7040FFB20
t2: In oil(), texas = 5, &texas = 000000A7040FFA04
t2: In oil(), x = 31, &x = 000000A7040FFB20
t2: In main(), texas = 31, &texas = 000000A7040FFB44
t2: In main(), year = 2011, &year = 000000A7040FFB64
```

解析：

1. 当在同一段代码块中，存在两个名称相同，但是作用域不同的变量时。新的变量会覆盖旧的变量，在该段代码块结束后，新变量小时，变量自动回到旧变量。
2. 自动变量仅仅在创建时的代码块中可用，不同代码块之间不能互用自动变量。

**自动变量初始化**

可以使用人格在声明时其值为已知的表达式来初始化自动变量。

**自动变量和栈**

由于自动变量的数目会随着程序的进行而发生改变，因此在程序运行时需要对其进行管理。常用的方法是留出一段内存，并将其视为栈，以管理变量的增减。

在栈中，新数据被象征性的放在原有的数据之上，当程序使用完后，自动将数据删除，此时该内存中的数据恢复到调用之前的值（也就是自动变量中的：新定义覆盖旧定义，新定义结束，旧定义恢复）。

程序使用两个指针来跟踪栈，一个指针指向栈底，另一个指针指向栈顶。

栈空间是先进后出，后进先出的。

**寄存器变量**

关键字register是由C语言引入的，其建议编译器使用CPU寄存器来存储自动变量：

```C++
register int count_fast;
```

旨在提高访问变量的速度。

### 9.2.3 静态变量

静态变量的存储持续性为静态，其作用域随着变量创建位置的不同而有所不同，链接性也与创建变量时的关键字有关。可以分为如下三类：静态持续性、外部链接性；静态持续性、内部链接性；静态持续性、无链接性；静态变量的初始化。

这三种链接性在整个代码执行间存在，与自动变量相比，它们的寿命更长。

由于静态变量的数目在程序运行期间是不变的，因此不需要使用特殊的装置来管理它们。

编译器将分配固定的内存块来存储所有的静态变量，这边变量在程序整个执行期间内一直存在，也就是静态持续性。

```c++
...
int global = 100;// 定义静态变量，外部链接性
// 作用域为整个文件，且由于外部链接性，因此其可以被程序的其他文件使用
static int one_file = 50;// 定义静态变量，内部链接性
// 作用域为整个文件，且由于内部链接性，其不能被程序的其他文件使用

int main()
{...}

void funct1(int n)
{
	static int count = 0;// 定义静态变量，无链接性
    // 作用域为代码块内，且无链接性，其和自动变量一样，只能在该代码块内使用
	int llama = 0;// 定义自动变量，无链接性
	...
}

void funct2(int q)
{
...
}

```

要想创建链接性为外部的静态持续变量，必须在代码块的外面声明它；要创建链接性为内部的静态持续变量，必须在代码块外面声明它，并使用static关键字；要创建无链接性的变量，必须在代码块内部声明它，并使用关键字static。这里变量声明的位置不同，关键字static代表的含义也不同，有人称之为关键字重载，即关键字的含义取决于上下文。

**静态变量的初始化**

静态变量常见的初始化手段有：静态初始化和动态初始化，其中静态初始化又分为默认初始化和常量表达式初始化。静态初始化指局部变量在编译阶段初始化该变量，动态初始化指程序在编译完成后的运行阶段初始化。

默认初始化，即零初始化。对于标量类型，零将被强制转换为合适类型。例如，对于指针，其被默认初始化为0，但这个0是指指针意义中的0，并非数字0.

首先，所有静态变量都被零初始化，而不管程序员是否显示地初始化了它。接下来，如果使用了常量表达式进行了初始化，且编译器仅仅根据本文件内容（包含被包括的头文件）就可计算表达式，编译器将执行常量表达式初始化。如果没有足够的信息进行初始化，变量则将被动态初始化。

**静态持续性、外部链接性**

链接性为外部的变量通常简称为外部变量，它们的存储持续性为静态，作用域为整个文件。外部变量是在函数外面定义的，因此对所有函数而言都是外部的。在头文件中定义它们，也可以在文件中位于任何函数中使用它。

**单定义规则(One Definition)：**该规则指出，变量只能有一次定义。

为满足这种需要，C++提供了两种变量声明。一种是定义声明（defining declaration）或简称为定义（definition），它给变量分配存储空间；另一种是引用声明（referencing declaration）或简称为声明（declaration），它不给变量分配存储空间，因为其引用已有的变量。

引用声明使用关键字extern，且不进行初始化。若使用关键字extern的同时，还进行了初始化，则该操作自动转为定义声明。

如果要在多个文件中使用外部变量，只需要在一个文件中包含该变量的定义，但在使用该变量的其他文件中，都必须使用关键字extern声明它。

```c++
// file01.cpp
extern int cats = 20;// 虽使用extern关键字，但进行了初始化，仍然为定义
// 对于定义声明，关键字extern并非必不可少，省略它反而更加清晰，且效果相同
int dogs = 22;// 定义可外部链接的静态变量dogs
int fleas;// 定义可外部链接的静态变量fleas

// file02.cpp
extern int cats;//  由于file01.cpp中的cats是可以外部链接的，因此使用extern声明引用该变量。
extern int dogs;// 同上

// files98.cpp
extern int cats;// 同上
extern int dogs;// 同上
extern int fleas;// 同上
```

注意单定义规则（One Definition）并非意味多个变量名称不能相同。例如之前提到的新定义覆盖旧定义，新定义结束，旧定义恢复。虽然程序可包含多个同名的变量，但每个变量的定义只能有一个。

下面是使用静态变量的例子，为外部链接的。

```C++
#include <iostream>

extern double warming;

void update(double dt);
void local();

using namespace std;

void update(double dt)
{
	extern double warming;
	warming += dt;
	cout << "Update global warming to " << warming;
	cout << " degree.\n";
}

void local()
{
	double warming = 0.8;
	cout << "Local warming = " << warming << " degree.\n";
	cout << "But global warming = " << ::warming;
	cout << ": degree.\n";
}
```

```c++
#include  <iostream>

using namespace std;

double warming = 0.3;

void update(double dt);
void local();

int main()
{
	cout << "Global warming is " << warming << " degrees.\n";
	update(0.1);
	cout << "Global warming is " << warming << " degrees.\n";
	local();
	cout << "Global warming is " << warming << " degrees.\n";

	return 0;
}
```

**静态持续性、内部链接性**

在多文件程序中，内部链接和外部链接具有的差别是很有意义的。添加extern设置变量为内部链接性。链接性为内部的变量只能在其所属的文件内使用；但常规外部变量具有外部链接性，即可以在其他文件中使用。

注意，对于内部链接的静态变量，如果要在其他文件中使用相同名称的变量时，将无法通过关键字使用

```c++
// file1
int errors = 20;
...
--------------------------------
//file2
int errors = 5
// 这种声明是非法的，因为违反了单定义规则  
--------------------------------
//file3
static int errors = 5;
// 这种声明是合法的，虽然其名字和另一个文件中声明的常规外部变量相同。
// 该文件中，静态变量将隐藏常规的外部变量
// 没有违反单定义规则，这里关键字static指出变量是内部的。

```

可使用接性为外部的静态变量在多文件程序的不同部分之间共享数据；可使用链接性为内部的静态变量在同一个文件中的多个函数之间共享数据。



**静态持续性、无链接性**

### 9.2.4 函数和链接性

### 9.2.5 语言链接性

### 9.2.6 存储方案和动态分配  

## 9.3 名称空间