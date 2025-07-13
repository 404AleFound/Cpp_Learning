# U10-编程练习

## project1

下面是一个简单的类定义：

```C++
class Person {
private:
    static const int LIMIT = 25;
    string lname; // Person's last name
    char fname[LIMIT]; // Person's first name
public:
    Person() {lname = ''; fname[0] = '\0';}
    Person(const string & ln, const char * fn = "Heyyou");
// the following methods display lname and fname
    void show() const; // firstname lastname format
    void FormalShow() const; // lastname, firstname format
}
```

它使用一个string对象和一个字符数组，让您能够比较它们的用法。请提供未定义的方法代码，已完成这个类的实现。再编写一个使用这个类的程序，它使用了三种可能的构造函数调用（没有参数、一个参数和两个参数）以及两种显示方法。

## project2

完成第9章的编程练习1，但要用正确的golf类声明替换哪里的代码。用带合适参数的构造函数替换`setgolf(golf&, const char*, int)`，以提供初始值。保留`setgolf()`的交互版本，但要用构造函数来实现它。

## project3

完成第9章的编程练习4，但将Sales结构及相关的函数转换为一个类及其方法。用构造函数替换`setSales(sales &, double [], int)`

。用构造函数实现`setSales(Sales &)`方法的交互版本。将类保留再名称空间SALES中。

## project4

考虑下面的结构声明：

```C++
struct customer {
    char fullname[35];
    double payment;
}
```

编写一个程序，它从栈中添加和删除`customer`结构（栈用`Stack`类声明表示）。每次`customer`结构被删除时，其`payment`的值都被加入到总数中，并报告总数。注意：应该可以直接使用`Stack`类而不做修改；只需修改`typedef`声明，使`Item`的类型为`customer`，而不是`unsigned long`即可。

## project5

下面是一个类声明：

```C++
class Move
{
private:
    double x;
    double y;
public:
    Move(double a = 0,, double b = 0); // sets x, y to a, b
    void showmore() const;
    Move add(const Move & m) const;
// this function adds x of m to x of invoking object to get new x,
// adds y of m to y of invoking object to get new y, create a new
// move object initializaed to new x, y values and returns it
    void reset(double a = 0, double b = 0); // reset x,y to a, b
}
```

请提供成员函数定义和测试这个类的程序。

## project6

`Betelgeusean plog`有这种特征。

数据：

* `plorg`的名称不超过19个字符；
* `plorg`有满意指数（CI），这是一个整数。

操作：

* 新的`plorg`将有名称，其CI值为50；
* `plorg`的CI值可以修改；
* `plorg`可以爆改其名称和CI；
* `plorg`的默认名称为`“Plorga”`。

请编写一个`Plorg`类声明（包括数据成员和成员函数原型）来表示`plorg`，并编写成员函数的函数定义。然后编写一个小程序，以演示`Plorg`类的所有特性。

## project8

可以将简单列表描述册灰姑娘下面这样：

* 可存储0或多个某种类型的列表；
* 可创建空列表；
* 可在列表中添加数据项；
* 可确定列表是否为空；
* 可确定列表是否为满；
* 可访问列表中的每一个数据项，并对它执行某种操作。

可以看到，这个列表非常简单。例如，它不允许插入或删除数据项。

请设计一个List类来表示这种抽象类型。您应提供头文件`list.h`和实现文件`list.cpp`，前者包括类定义，后者包含类方法的直线。您还应当创建一个简短的程序来使用这个类。

该列表的规范很简单，这主要只在简化这个编程练习。可以选择使用数组或链表来实现该列表，但公有接口不应依赖于所做的选择。也就是说，公有接口不应有数组索引、节点指针等。应使用通用概念来表达创建列表、在列表中添加数据项等操作。对于访问数据项即执行操作，通常应使用将函数指针作为参数的函数来处理。

`void visit(void (*pf) (Item &))`

其中，`pf`指向一个将Item引用作为参数的函数（不是成员函数），`Item`是列表中数据项的类型。`visit()`函数将该函数用于列表中的每个数据项。

