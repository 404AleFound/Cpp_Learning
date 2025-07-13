# U9-编程练习

## project1

下面是一个头文件：

```C++
// golf.h -- for pe9-1.cpp
const int Len = 40;
struct golf
{
    char fullname[Len];
    int handicap;
};

// non-interactive version:
// function sets golf structure to provided name, handicap
// using values passed as arguments to the function
void setgolf(golf & g, const char * name, int hc);

// interactive version:
// function solicits name and handicap from user
// and sets the member of g to the values entered
// returns 1 if name is entered, 0 if name is empty string
int setgolf(golf & g);

// function resets handicap to new value
void handicap(golf & g, ing hc);

// function displays contents of golf structure
void showgolf(const golf & g);
```

根据这个头文件，创建一个多文件程序。其中的一个文件名为`golf.cpp`，它提供了与头文件中的原型匹配的函数定义；另一个文件应包含`main()`，并演示原型化函数的所有特性。例如，包含一个让拥护输入的循环，并使用输入的数据来填充一个由`golf`结构组成的数组，数组被填充或拥护将高尔夫选手的姓名设置为空字符串时，循环将结束。`main()`函数只是用头文件中原型化的函数来访问`golf`结构。

## project2

修改程序清单9.9：用string对象代替字符数组。这样程序将不再需要检查输入的字符串是否过长，同时可以将输入字符串同输出字符串进行比较，以判断是否为空行。

## project3

下面是一个结构声明：

```C++
struct chaff
{
    char dross[20];
    int slag;
}
```

编写一个程序，使用定位`new`运算符将一个包含两个这种结构的数组放在一个缓冲区。然后，给结构成员的赋值（对于`char`数组，使用函数`strcpy()`），并使用一个循环来显示内容。一种方法是像程序清单9.10那样将一个静态数组用作缓冲区；另一种方法是使用常规`new`运算符来分配缓冲区。

## project4

请基于下面这个名称空间编写一个由3个文件组成的程序。

```C++
namespace SALES
{
	const int QUARTERS = 4;
    struct Sales {
		double sales[QUARTERS];
        double average;
        double max;
        double min;
    };
    
    // copies the lesser of 4 or n items from the array ar
    // to the sales member of s and computes and stores the
    // average, maximum, and minimum values of the entered items;
    // remaining elements of sales, if any, set to 0
    void setSales(Sales & s, const double ar[], int n);
    
    // gathers sales for 4 quarters interactively, store them
    // in the sales member of s and computess and stores the
    // average, maxium, and minimum values
    void setSales(Sales & s);
    
    // display all infromation in structure s
    void showSales(const Sales & s);
}
```

第一个文件是一个头文件，其中包含名称空间；第二个文件是一个源代码文件，它对这个名称空间进行扩展，以提供这三个函数的定义；第三个文件声明两个`Sales`对象，并使用`SetSales()`交互版本为一个结构提供值，然后使用`setSales()`的非交互版本为另一个结构提供值。另外它还使用`showSales()`来显示这两个结构的内容。