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

class Stock
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

现在需要创建Stock的构造函数。由于Stock变量中有三个需要填值的私有成员，因此也应当为构造函数提供三个参数，通过默认参数方法，函数原型如下：

```c++
class Stock
{
    private:
    std::string company;
    long shares;
    double share_val;
    double total_val;
    void set_tot() { total_val = shares * share_val;}// private成员函数只能在类中定义
    ...
...
```

```c++
Stock(const string & co, long n = 0, double pr = 0.0)
```

构造函数和之前的acquire()函数相同，区别在于构造函数在声明变量时被自动调用，而acquire()需要被手动调用。

注意，不能将类成员作为构造函数的参数，这会导致赋值符号左右的变量名相同，进而导致代码混乱。常见的作法是在构造函数参数的前面添加前缀`m_`，或在成员变量的名称的后面添加后缀`_`。

### 10.2.2 使用构造函数

C++提供了两种使用构造函数的方法，一种是显示地调用构造函数，另一种是隐式地调用构造函数。

```C++
// 方法1
Stock food = Stock("World Cabbage", 250, 1.25);
// 方法2
Stock food("World Cabbage", 250, 1.25)
```

每次声明类对象的实例时，C++都将使用构造函数。下面是将构造函数和new一起使用的方法。

```C++
Stock * pfood = new Stock("World Cabbage", 250, 1.25);
```

这条语句创建一个Stock对象，将其初始化参数提供的值，并将该指针的地址赋给pfood指针。在这种情况下，该对象没有名字，仅仅有一个指向它的指针`pfood`，可以使用该对象指针来管理它。

对于一般的类中的成员方法，通过类对象来对其进行调用，但是无法使用类对象来调用构造函数，因为在使用构造函数构造对象之前，类对象是不存在的，因此构造函数被同来创建类对象，但不能通过对象被调用。

### 10.2.3 默认构造函数

默认构造函数是在程序员未显示提供显示初始值时，用来创建对象的构造函数，适用于如下情况。

```C++
Stock fluffy_the_cat;
```

如果没有提供任何构造函数，则C++将自动提供默认的构造函数。它是默认构造函数的隐式版本，对于被例来说，默认构造函数可能如下：

```C++
Stock() {}
```

因此将创建对应的Stock类对象fluffy_the_cat，而不初始化其成员。

注意！当且仅当没有定义任何构造函数时，编译器才会提供默认构造函数。当为类对象提供了构造函数之后，程序员必须为它提供默认构造函数。如果仅仅提供了非默认构造函数`Stock(const char* co, int n, double pr)`，而没有提供默认构造函数，下面语句就会报错。

```C++
Stock fluffy_the_cat;
```

创建默认构造函数的方法有两种，一种是给所有已有的构造函数提供默认值；另一只是通过函数重载的方式来重新定义另一个构造函数，一个没有参数的构造函数。由于只能有一个构造函数，因此不要同时使用上述两种方法，因为这样在`Stock fluffy_the_cat;`声明变量时，程序会不知道要使用那个构造函数。

```
Stock first("World Cabbage", 250, 1.25); // 使用自定义的构造函数创建一个Stock对象
Stock second(); // 声明一个没有任何参数的且返回Stock对象的函数
Stock third; // 使用默认构造函数创建一个Stock对象
```

### 10.2.4 析构函数

用构造函数创建对象后，程序负责跟踪该对象，直到其过期为止。对象过期时，程序将自动调用一个特殊的成员函数，该函数的名称令人望而生畏——析构函数。该函数完成清理工作。由于本章节的Stock的构造函数没有使用new创建动态内存，因此只需要创建一个空的析构函数，这种析构函数若程序员没有设定，一般由程序自动生成。

和构造函数类似，析构函数的名称也很特殊，为类名前加上`~`。因此，Stock类的析构函数为`~Stock()`。另外和构造函数一样，析构函数也可以没有返回值和声明类型。但是析构函数没有任何参数，因此析构函数原型如下：

```C++
~Stock();
```

如果创建的是静态存储类的对象，则其析构函数在程序结束时被调用；

如果创建的是自动存储类的对象，则其析构函数在执行玩对应代码块后被自动调用；

如果创建的是动态存储类的对象，则其析构函数在使用delete释放内存时被调用。

### 10.2.5 构造函数析构函数案例

下面将构造函数和析构函数加入到类和方法的定义中。

```c++
// stock01.h -- 根据Stock01.h修改
#ifndef STOCK00_H_
#define STOCK00_H_

#include <string>

class Stock
{
    private:
    std::string company;
    long shares;
    double share_val;
    double total_val;
    void set_tot() { total_val = shares * share_val;}// private成员函数只能在类中定义
    public:
    // void acquire(const std::string  & co, long n, double pr);
    // 使用构造函数代替acquire()函数
    Stock();// 创建默认构造函数
    Stock(const std::string  & co, long n = 0, double pr = 0.0);// 创建含参数的构造函数
    ~Stock();// 创建析构函数
    // 下面内容保持不变
    void buy(long num, double price);
    void sell(long num, double price);
    void update(double price);
    void show();
};

#endif
```

下面创建类的具体实现。

```C++
// stock01.cpp
#include <iostream>
#include "stock01.h"
// 需要包含含有类声明的头文件

Stock::Stock()
{
    std::cout << "Default constructor called\n";
    company = "no name";
    shares = 0;
    share_val = 0.0;
    total_val = 0.0;
}

Stock::Stock(const std::string  & co, long n, double pr)
{
    std::cout << "Constructor using " << co << " called\n";
    company = co;
    if (n < 0)
    {
        std::cout << "Number of shares can't be negative; "
            << company << " shares set to 0.\n";
        shares = 0;
    }
    else 
        shares = n;
    share_val = pr;
    set_tot();
}
Stock::~Stock()
{
    std::cout << "Bye, " << company << "!\n";
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

下面程序对改进的Stock类进行测试。

```C++
// main.cpp
#include <iostream>
#include "stock01.h"

int main()
{
    {
     	using std::cout;
    	cout << "Using constructors to create new objects\n";
    	Stock stock1("NanoSmart", 12, 20.0);
        stock1.show();
    	Stock stock2 = Stock("Boffo Objects", 2, 2.0);
   	 	stock2.show();
    
    	cout << "Assigning stock1 to stock2:\n";
    	stock2 = stock1;
    	cout << "Lisiting stock1 and stock2:\n";
    	stock1.show();
    	stock2.show();
    
    	cout << "Using constructor to reset an object\n";
    	stock1 = Stock("Nifty Foods", 10, 50.0);
    	cout << "Revised stock1:\n";
    	stock1.show();
    	cout << "Done\n";  
    }
    return 0;  
}
```

输出如下：

```
Using constructors to create new objects
Constructor using NanoSmart called
Company: NanoSmart Shares: 12
 Share Price: $20 Total Worth: $240
Constructor using Boffo Objects called
Company: Boffo Objects Shares: 2
 Share Price: $2 Total Worth: $4
Assigning stock1 to stock2:
Lisiting stock1 and stock2:
Company: NanoSmart Shares: 12
 Share Price: $20 Total Worth: $240
Company: NanoSmart Shares: 12
 Share Price: $20 Total Worth: $240
Using constructor to reset an object
Constructor using Nifty Foods called
Bye, Nifty Foods!
Revised stock1:
Company: Nifty Foods Shares: 10
 Share Price: $50 Total Worth: $500
Done
Bye, NanoSmart!
Bye, Nifty Foods!
```

列表初始化。在C++11，中**只要提供与某个构造函数的参数列表匹配的内容**，并用大括号将其括起来，就可以使用列表初始化。

```C++
Stock hot_tip = {"Derivatives plus plus", 100, 45.0};
Stock jock {"Sport Age Storage, Inc"};
Stock temp {};
```

const成员函数。

```C++
const Stock land = Stock("Kludgehorn");
land.show();
```

此时第二行会报错，因为第一行声明`land`是一个`const`不能被改变的变量，而当调用`land.show()`时，编译器无法判断`show()`是否改变了对象，因此报错，需要程序员手动标定，更改如下：

```c++
const Stock land = Stock("Kludgehorn");
land.show() const;
```

t同样在函数声明和定义时也要修改。

```C++
void show() const;
void Stock::show() const
{
    ...;
}
```

故，以这种方式被声明和定义的类函数被称为`const`成员函数。只要类方法不改变调用对象，就应当将其声明为`const`。

## 10.3 this指针

当出现两个类对象时，且类方法可能涉及两个类对象时，需要使用`this`指针表明类方法中的对象分别是谁。

  C++使用被称为this的特殊指针，this指针指向用来调用成员函数的对象。

每个成员函数（包括析构函数和构造函数）都有一个this指针。this指针指向调用对象。如果方法需要引用整个调用对象，则可以使用表达式`*this`。在函数的括号后面使用`const`限定符将`this`限定为从const，这样将不适用`this`来修改对象的值。

注意，this是指向调用该函数的对象的指针，*this才是调用该函数的对象。

```C++
// stock02.h -- 根据Stock01.h修改
#ifndef STOCK00_H_
#define STOCK00_H_

#include <string>

class Stock
{
    private:
    std::string company;
    long shares;
    double share_val;
    double total_val;
    void set_tot() { total_val = shares * share_val;}// private成员函数只能在类中定义
    public:
    // void acquire(const std::string  & co, long n, double pr);
    // 使用构造函数代替acquire()函数
    Stock();// 创建默认构造函数
    Stock(const std::string  & co, long n = 0, double pr = 0.0);// 创建含参数的构造函数
    ~Stock();// 创建析构函数
    // 下面内容保持不变
    void buy(long num, double price);
    void sell(long num, double price);
    void update(double price);
    void show();
    const Stock & topval(const Stock & s) const;
};

#endif
```

```c++
// 单独topval()
const Stock & topval(const Stock & s) const
{
	if (s.total_val > total_val)
        return s;
    else
        return *this;
}
```

## 10.4 对象数组

和Stock示例一样，用户通常要创建同一个类的多个对象，此时使用对象数组将更加合适。声明对象数组的方法与声明标准类型数组相同。

```C++
Stock mystuff[4];
```

当程序创建未被显示初始化的类对象时，总是调用默认构造函数。上述声明要求，这个类要么没有显示地定义任何构造函数，要么定义了一个显示的默认构造函数。

对象数组的每一个元素都可以使用该对象的成员函数。

可以用构造函数来初始化数组元素。在这种情况下，必须为每个元素调用构造函数。

```C++
const int STKS = 4;
Stock stocks[STKS] = {
    Stock("NanoSmart", 12.5, 20),
    Stock("Boffo Objects", 200, 2.0),
    Stock("Monolithic Obelisks", 130, 3.25),
    Stock("Fleep Enterprises", 60, 6.5)
};
```

这里使用标准格式对数组进行初始化：用括号括起的、以逗号分隔的值列表。其中，每次构造函数调用表示一个值。如果类包含多个构造函数，则可以对不同元素使用不同的构造函数：

```C++
const int STKS = 10;
Stock stocks[STKS] = {
    Stock("NanoSmart", 12.5, 20),
    Stock(),
    Stock("Monolithic Obelisks", 130, 3.25),
};
```

上述代码仅仅初始化了数组对象中的3个元素，剩下的7个元素将使用类默认的构造函数进行初始化。

初始化对象数组的方案是，首先使用默认构造函数创建数组元素，然后花括号中的构造函数将创建临时对象，然后将临时对象的内容复制到相应元素中。**因此要创建类对象数组，则这个类必须有默认构造函数。**

```C++
#include <iostream>
#include "stock20.h"
```



## 10.5 类作用域

在类中定义的名称的作用域为整个类，作用域为整个类的名称只在该类中是已知的，在类外是不已知的。

* 可以在不同类中使用相同的类成员名而不会引起冲突。
* 不能从外部直接访问类的成员，必须通过对象。
* 在定义成员函数时，必须使用作用域解析符。
* 在类中声明或成员函数定义中，可以使用未修饰的成员名称（未限定类的名称），。构造函数名称被调用时，才能被识别，因为它的名称与类名相同。其他情况下，使用类成员名时，必须更具上下文使用直接成员运算符(.)、间接成员运算符(->)或作用域解析运算符(::)。

**所用域为类的常量**

当类的所有对象公用某一常量值时，可以创建一个由所有对象共享的常量。注意声明对象只是描述了对象的形式，没有创建对象。因此在创建对象前，将没有用于存储值的空间，故下面代码是不可行的。

```C++
class Bakery
{
private:
    const int Months = 12;
    double cost[Months];
    ...
}
```

C++使用两种方式实现这个目标。

一种是在类中声明一个枚举。

```C++
class Bakery
{
private:
    enum {Months = 12};
    double cost[Months];
    ...
}
```

在类声明中声明的枚举的作用域为整个类，因此可以用枚举为整型常量提供作用域为整个类的符号名称。

注意这种方法声明的枚举并不会创建类数据成员。也就是说，所有对象中都不包含枚举。

由于这里使用枚举只是为了创建符号常量，并不打算创建枚举类型的变量，因此不需要提供枚举名。

另一种方法是在类中创建静态成员变量。

```c++
class Bakery
{
private:
    static const int Months = 12;
    double cost[Months];
    ...
}
```

## 10.6 抽象数据类型

栈的特征，首先栈存储了多个数据项，其次栈由可对它执行的操作进行描述。

* 可创建空栈
* 可将数据项添加到栈顶
* 可从栈顶删除数据项
* 可查看栈是否填满
* 可查看栈是否为空

就计算机专家们所说的抽象数据类型而言，使用类是一种非常好的方法。

```c++
#ifndef STACK_H_
#define StACK_h_

typedef unsigned long Item;

class Stack
{
private:
    enum {MAX = 10};
    // 定义了一个枚举常量MAX，其值为10。这表示栈的最大容量为10个元素。
    Item items[MAX];
    // 是一个数组，用于存储栈中的元素，其类型为Item，大小为MAX。
    int top;
    // 是一个整型变量，用于表示栈顶的索引。初始时，栈为空，top的值通常为-1。
public:
    Stack();
    // 是一个整型变量，用于表示栈顶的索引。初始时，栈为空，top的值通常为-1。
    bool isempty() const;
    // 是一个函数，用于判断栈是否为空。如果栈为空，返回true；否则返回false。
    bool isfull() const;
    // 是一个函数，用于判断栈是否已满。如果栈已满，返回true；否则返回false。
    bool push(const Item & item);
    // 是一个函数，用于将元素item压入栈中。如果压栈成功，返回true；如果栈已满，无法压栈，返回false。
    bool pop(Item & item);
    // 是一个函数，用于从栈中弹出栈顶元素，并将其存储在item中。如果出栈成功，返回true；如果栈为空，无法出栈，返回false。
}
#endif
```

私有部分表明，栈是使用数组实现的；而公有部分隐藏了这一点。因此，可以使用动态数组来代替数组，而不会改变类的接口。这意味着修改栈的实现后，不需要重新编写使用栈的程序，而只需要重新编译栈代码，并将其与已有的程序代码链接起来即可。

以下为栈类的具体实现方法。

```C++
#include "stack.h"
Stack::Stack()
{
    top = 0;
}

bool Stack::isempty() const
{
    return top == 0;
}
// 默认构造函数确保所有栈被创建时都为空

bool Stack::isfull() const
{
    return top == MAX;
}

bool Stack::push(const Item & item)
{
	if (top < MAX)
    {
        items[top++] = item;
        return true;
    }
    else
        return false;
}

bool Stack::pop(Otem & item)
{
	if (top > 0)
    {
		item = items[--top];
        return true;
    }
    else
        return false;
}
```

