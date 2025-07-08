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
    void set_tot() { total_val = shares * share_val;}
    public:
    void acquire(const std::string  & co, long n, double pr);
    void buy(long num, double price);
    void sell(long num, double price);
    void update(double price);
    void show();
};

#endif
```





## 运算符重载

 
