# 10 类和对象

* 抽象
* 封装和数据隐藏
* 多态
* 继承
* 代码的可重用性

以上是面向对象编程的重要特性，C++通过改进类，实现面向对象的编程。

## 10. 1 抽象和类

指定

* 决定数据对象需要的内存数量
* 决定如何解释内存中的位
* 决定可使用数据对象执行的操作或方法

### 10.1.1 C++中的类

类是一种将抽象转化内为用户定义类型的C++工具，它将数据表示和操纵数据的方法组合成一个整洁的包。

定义类中，类规范由两个部分组成，类声明提供了类的蓝图，类方法定义了实现细节。

* 类声明：以数据成员的方式描述数据部分，以成员函数的方方式描述公有接口。
* 类方法定义：描述如何实现类成员函数。

为开发一个类并编写一个使用它的程序，需要完成多个步骤。通常C++程序员将接口（类定义）放在头文件中，并将实现（类方法的代码）放在源代码文件中。以这种典型的做法为例，下面类声明第一阶段的代码。使用`#ifndef`来防止多次包含同一个文件。

```C++
// stock00.h
#ifndef STOCK00_H_
#define STOCK00_H_

#include <string>

class Srock
{
    private:
    std::string company;
    long shares;
    double share_val;
    double total_val;
    void set_tot() { total_val = shares * share_val;}// private成员函数只能在类中定义
    public:
    void acquire(const std::string  & co, long n, double pr);
    void buy(long num, double price);
    void sell(long num, double price);
    void update(double price);
    void show();
};

#endif
```

**访问控制**

关键字private和public实现了对类成员的访问控制。使用类对象的程序都可以直接访问共有部分，但是只能通过公有成员函数来访问对象的私有成员。公有成员函数是程序和对象的私有成员之间的桥梁，提供了对象和程序之间的接口。防止程序直接访问数据被称为数据隐藏。C++还提供了第三个访问控制关键字protected。

类设计应当尽可能将公有接口与实现细节分开。公有接口表示设计的抽象组件。将实现细节放在一起并将它们与抽象分开被称为封装。封装可以将数据放在私有中，也可以将实现方法放在私有中。将类函数定义和类声明放在不同文件中也是一种封装。

**控制对成员的访问**

无论类成员是数据成员还是成员还是，都可以在类的共有部分或私有部分声明它，但为了有效封装，通常将其放在私有部分。不必在类声明时使用关键字private，因为这是类对象的默认访问控制。

### 10.1.2 实现类

* 定义成员函数时，使用作用域解析运算符::来标识函数所属的类。

* 类方法可以访问类的private组件

如果在类声明中直接对成员函数进行定义，则无需使用作用域解析符，因为该成员函数属于这个类，类中变量或方法对本类中的方法调用无需作用域解析符。如果在类声明中仅仅对函数进行声明，而在类外对成员函数进行定义，则需要在成员函数之前添加类名称和作用域解析符。

```C++
void Stock::update(double price)
{
	...
}
```

下面是对之前类声明代码块的进一步补充。

```C++
// stock00.cpp
#include <iostream>
#include "stock00.h"
// 需要包含含有类声明的头文件

void Stock::acquire(const std::string  & co, long n, double pr)
{
    // acquire()管理对某个公司股票的首次购买
	company = co;
    if (n < 0)
    {
        std::cout << "Number of shares can't be negative; "
            << company << " shares aet to 0.\0";
        shares = 0;// 可以直接使用private的成员变量
    }
    else
        shares = 0;// 可以直接使用private的成员变量
    share_val pr;
    set_tot();// 可以直接使用private的成员函数
}
void Stock::buy(long num, double price)
{
    if(num < 0)
    {
        std::cout << "Number of shares purchased cna't be negative. "
            << "Transaction is aborted.\n";
    }
    else 
    {
        shares += num;
        share_val = price;
        set_tot();
    }
}
void Stock::sell(long num, double price)
{
	using std::cout;
    if(num < 0)
    {
        std::cout << "Number of shares purchased cna't be negative. "
            << "Transaction is aborted.\n";
    }
    else if (num > shares)
    {
  		std::cout << "You can't sell more than you have! "
            << "Transaction is aborted.\n";
	}
    else
    {
		shares -= num;
        share_val = price;
        set_tot();
    }
}
void Stock::update(double price)
{
	share_val = price;
    set_tot();
}
void Stock::show()
{
	std::cout << "Company: " << company
        << " Shares: " << shares << '\n'
        << " Share Price: $" << share_val
        << " Total Worth: $" << total_val << '\n';
}
```

定义位于类声明内的函数都将自动编程内联函数，因此`Stock::set_tot()`是一个内联函数。类声明通常将短小的成员函数作为内联函数，set_tot()符合这种要求。

如果愿意，也可以在类声明外定义成员函数，并使其称为内联函数。只需要在类实现部分中定义函数时使用关键字inline限定符即可。

```C++
inline void Stock::set_tot()
{
    ...
}
```

内联函数的特殊规则要求每个在使用它们的文件中都对其进行定义。确保定义对多文件程序中的所有文件都可用、最简便的方法是将内联定义放在定义类的头文件中。

在类声明中定义方法等同于用原型替换方法定义，然后类声明的后面将定义改写为内联函数，有就是内联定义与定义紧紧跟在类声明是等价的。

所创建的每个新对象都有自己的存储空间，用于存储其内部变量和类成员；但同一个类的所有对象共享同一组方法，即每种方法只有一个副本。

### 10.1.3 使用类

要创建类对象，可以声明类变量，也可以使用new为类对象分配存储空间。可以将对象作为函数的返回值和参数，也可以将一个对象赋给另一个。

```C++
#include <iostream>
#include "stock00.h"

int main()
{
	Stock fluffy_the_cat;
	fluffy_the_cat.acquire("NanoSmart", 20, 12.50);
	fluffy_the_cat.show();
	fluffy_the_cat.buy(15, 18.125);
	fluffy_the_cat.show();
	fluffy_the_cat.sell(400, 20.00);
	fluffy_the_cat.show();
	fluffy_the_cat.buy(300000, 40.125);
	fluffy_the_cat.show();
	fluffy_the_cat.sell(300000, 0.125);
}
```

输出如下：

```
Company: NanoSmart Shares: 0
 Share Price: $12.5 Total Worth: $0
Company: NanoSmart Shares: 15
 Share Price: $18.125 Total Worth: $271.875
You can't sell more than you have! Transaction is aborted.
Company: NanoSmart Shares: 15
 Share Price: $18.125 Total Worth: $271.875
Company: NanoSmart Shares: 300015
 Share Price: $40.125 Total Worth: $1.20381e+07
```

`ostream`类包含一些可用于控制格式的成员函数，可在方法`show()`添加一些优化数字格式的方式。

```C++
std::cout.setf(std::ios_base::fixed, std::ios_base::floatfiled);
//显示时显示三位小数
std::cout.precision(3);
```

将show()函数改写为如下：

```c++
void Stock::show()
{
    using std::cout;
    using std::ios_base;
    ios_base::fmtflags orig =
        cout.setf(ios_base::fixed, ios_base::floatfield);
    std::streamsize prec = cout.precision(3);

    cout << "Company: " << company;
    cout << " Shares: " << shares << '\n';
    cout << " Share Price: $" << share_val;
    cout.precision(2);
    cout << " Total Worth: $" << total_val << '\n';
    cout.setf(orig, ios_base::floatfield);
    cout.precision(prec);
}     
```

指定类设计的第一步是提供类声明。类声明类似结构声明，可以包括数据成员和函数成员。声明有私有部分，在其中声明的成员只能通过成员函数进行访问；声明还有公有部分，在其中声明的成员可能被使用类对象的程序直接访问。通常，数据成员被放在私有部分，成员函数被放在公有部分中，因此典型的类声明的格式如下：

```
class className
{
private:
	data memeber declarations;
public:
	memeber function prototypes;
};
```

公有部分的内容构成了设计的抽象部分——公有接口。将数据封装到私有部分中可以保护数据的完整性，这被称为数据隐藏。

指定类设计的第二部是实现类成员函数。可以在类声明中提供完整的函数定义，而不是函数原型，但是通常做法是单独提供函数定义。这种情况下，需要使用域解析符运算符来指出成员函数属于哪个类。

类成员函数可以通过类对象来调用，为此需要成员运算符句点。

## 10.2 类的构造函数和析构函数

还应当为类提供析构函数和构造函数。

C++的目标之一是让使用类对象就像使用标准类型一样，然而，到现在为止，并不能做到像初始化int或结构那样来初始化Stock对象。处于设计需要，类成员通常是私有的，因此需要通过一个特殊的函数对其进行初始化。这和函数就被称为类构造函数。该函数专门用于构造新对象、将值赋给它们的数据成员。更准确地说，C++为这些成员函数提供了名称和使用语法，而程序员需要提供方法定义。

### 10.2.1 声明和定义构造函数

现在需要创建Stock的构造函数。

### 10.2.2 使用构造函数

### 10.2.3 默认构造函数

### 10.2.4 析构函数

### 10.2.5构造函数析构函数案例

## 10.3 this指针

## 运算符重载

 
