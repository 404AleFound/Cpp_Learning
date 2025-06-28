# 8 函数探幽

### 8.1 内联函数

内联函数是C++为提高程序运行速度所做的一项改进。常规函数和内联函数之间的主要区别不在于编写方式，而在于C++编译器如何将它们组合到程序中。

编译过程的最终产品是可执行程序——由一组机器语言指令组成的。运行程序时，操作系统将这些指令载入到计算机内存中，因此每条指令都有特定的内存地址。计算机随后将逐步执行这些命令。在执行到函数调用指令时，程序将在函数调用后立即存储该指令的内存地址，程序将立即存储该指令的内存地址，并将函数参数复制到堆栈，跳到函数起点的内存块，执行函数代码，然后跳回到地址被保存的指令处。这就好像阅读文章时停下来看脚注，并在阅读完脚注后返回到以前阅读的地方。这种来回跳跃的函数阅读方式，意味着在使用函数时需要一定开销。

C++内联函数提供了另一种选择。内联函数的编译代码与其他程序代码内联起来了，也就是说，编译器将使用相应的函数代码替换函数调用，程序无需跳到另一个位置处执行代码，再跳回来。因此内联函数的运行速度通常比常规函数快，但代价是需要占用更多内存。如果程序在多个地方使用相同的内联函数，则意味着该内联函数将要被复制10份。

对于内联函数，应当有选择的使用。如果执行函数代码的时间比处理函数调用机制的时间长，则节省的时间将只占整个过程的很小一部分。如果代码执行时间很短，则内联调用就可以节省非内联调用使用的大部分时间。

使用该特性，采取措施：

* 在函数声明前面加上关键字`inline`；
* 在函数定义前面加上关键字`inline`。

```C++
#include <iostream>

inline double square(double);

int main()
{
    double a,b;
    double c = 13.0;
    
    a = square(5.0);
    b = square (4.5 + 7.5);
    std::cout << "a = " << a << ", b = " << b << "\n";
    std::cout << "c = " << c;
    std::cout << ", c squared = " << square(c++) << "\n";
    std::cout << "Now c = " << c << "\n";
    return 0;
}
```

注意，程序员请求将函数作为内联函数调用时，编译器不一定会满足这种要求。其可能注意到函数过大，或者函数调用了自己，因此不将其作为内联函数。上述代码输出。

```
a = 25, b = 144
c = 13, c squared = 169
Now c = 14
```

在函数声明位置，使用内联函数的定义顶替，且将整个函数的定义放在一行中，但并不一定非得这样做。然而，函数定义如果占用多行，说明其内容过长，使用内联函数就不太合适了。

### 8.2 引用变量

C++新增了一种符合类型——引用变量。引用是已定义的变量的别名。引用变量的主要用途是用作函数的形参。通过将引用变量作为参数，函数将使用原始数据，而不是其副本，也就是说引用变量和指针的作用相似。

#### 8.2.1 创建引用变量

C++给&符号赋予了另外一个含义，将其来声明引用。

```C++
int rats;
int& rodents = rats;
```

int&指这是一个指向int的引用。上述引用声明允许将rats和rodents互换————它们指向相同的值和内存单元。

```C++
#include <iostream>
int main()
{
    int rats = 101;
    int& rodents = rats;
    std::cout << "rats address = "<< &rats << " , rats = :" << rats << std::endl;
    std::cout << "rodents address = " << &rodents << " , rodents = :" << rodents << std::endl;

    std::cout << "add 1 to rats.\n";
    rats++;
    std::cout << "rats address = " << &rats << " , rats = :" << rats << std::endl;
    std::cout << "rodents address = " << &rodents << " , rodents = :" << rodents << std::endl;
    return 0;
}
```

输出，如下：

```
rats address = 00000033B62FFA44 , rats = :101
rodents address = 00000033B62FFA44 , rodents = :101
add 1 to rats.
rats address = 00000033B62FFA44 , rats = :102
rodents address = 00000033B62FFA44 , rodents = :102
```

从中可知，rats和rodents的值和地址均相同，改变其中一个的值，另一个值也会随之发生变化。

引用看上去和指针的功能类似，但是引用必须在声明时对其进行初始化，与普通指针又略有不同。实际上，引用更接近const指针，都要在声明时进行初始化，且一旦与某个变量关联起来，就一直指向它。

```C++
int & rodents = rats;
int * const pr = &rats;
```

rodents扮演的角色和*pr相同。

```C++
// 试图将rats变量的引用改为bunnies变量的引用。
#include <iostream>

int main()
{
    int rats = 101;
    int& rodents = rats;
    int bunnies = 50;

    std::cout << "rats's address = " << &rats << ", rats = " << rats << std::endl;
    std::cout << "rodents's address = " << &rodents << ", rodents = " << rodents << std::endl;
    std::cout << "bunnies's address = " << &bunnies << ", bunnies = " << bunnies << std::endl;

    rodents = bunnies;
    std::cout << "\nchange: rodents = bunnies; \n";
    std::cout << "\nrats's address = " << &rats << ", rats = " << rats << std::endl;
    std::cout << "rodents's address = " << &rodents << ", rodents = " << rodents << std::endl;
    std::cout << "bunnies's address = " << &bunnies << ", bunnies = " << bunnies << std::endl;

    rodents ++;
    std::cout << "\nchange: rodents ++; \n";
    std::cout << "\nrats's address = " << &rats << ", rats = " << rats << std::endl;
    std::cout << "rodents's address = " << &rodents << ", rodents = " << rodents << std::endl;
    std::cout << "bunnies's address = " << &bunnies << ", bunnies = " << bunnies << std::endl;

    return 0;
}
```

输出如下：

```
rats's address = 00000061422FFA84, rats = 101
rodents's address = 00000061422FFA84, rodents = 101
bunnies's address = 00000061422FFAC4, bunnies = 50

change: rodents = bunnies;

rats's address = 00000061422FFA84, rats = 50
rodents's address = 00000061422FFA84, rodents = 50
bunnies's address = 00000061422FFAC4, bunnies = 50

change: rodents ++;

rats's address = 00000061422FFA84, rats = 51
rodents's address = 00000061422FFA84, rodents = 51
bunnies's address = 00000061422FFAC4, bunnies = 50
```

上述代码中，rodents是rats的引用变量，但随后程序试图将rodents作为bunnies的引用：

```c++
rodents = bunnies;
```

编译器可以执行这串代码，但是相应的rats（rodents指向）的值也发生改变，等效于`rats= bunnies;`。总之，rodents实际上相当于一个const指针，程序在其完成声明之后就不能改变其指向，其指向的地址是固定的。**该指向只能通过声明初始化完成，不能通过赋值语句完成。**

#### 8.2.2 将引用用作函数参数

引用经常被作为函数参数，使得函数中的变量名成为调用程序中的变量名的别名。这种传递参数的方式成为按引用传递。**按引用传递允许被调用的函数能够访问调用函数中的变量。**

```C++
// 该代码展示了函数传递变量，传递指针，传递引用这三种函数参数方式的不同。
#include <iostream>

void swap_r(int& a, int& b);
void swap_p(int* p, int* q);
void swap_v(int a, int b);
void show(int& wallet_1, int& wallet_2);

int main()
{
    int wallet_1 = 300;
    int wallet_2 = 500;
    std::cout << "Before changing:\n";
    show(wallet_1, wallet_2);

    std::cout << "\nUsing reference to swap:\n";
    swap_r(wallet_1, wallet_2);
    show(wallet_1, wallet_2);

    std::cout << "\nUsing pointer to swap:\n";
    swap_p(&wallet_1, &wallet_2);
    show(wallet_1, wallet_2);

    std::cout << "\nUsing value to swap:\n";
    swap_v(wallet_1, wallet_2);
    show(wallet_1, wallet_2);

    return 0;
}

void show(int& wallet_1, int& wallet_2)
{
    std::cout << "wallet_1' address = " << &wallet_1 << std::endl;
    std::cout << "wallet_1 = " << wallet_1 << std::endl;
    std::cout << "wallet_2' address = " << &wallet_2 << std::endl;
    std::cout << "wallet_2 = " << wallet_2 << std::endl;
}
void swap_r(int& a, int& b)
{
    int temp;
    temp = a;
    a = b;
    b = temp;
}
void swap_p(int* p, int* q)
{
    int temp;

    temp = *p;
    *p = *q;
    *q = temp;
}
void swap_v(int a, int b)
{
    int temp;

    temp = a;
    a = b;
    b = temp;
}
```

输出如下：

```
Before changing:
wallet_1' address = 000000E8ABF7F884
wallet_1 = 300
wallet_2' address = 000000E8ABF7F8A4
wallet_2 = 500

Using reference to swap:
wallet_1' address = 000000E8ABF7F884
wallet_1 = 500
wallet_2' address = 000000E8ABF7F8A4
wallet_2 = 300

Using pointer to swap:
wallet_1' address = 000000E8ABF7F884
wallet_1 = 300
wallet_2' address = 000000E8ABF7F8A4
wallet_2 = 500

Using value to swap:
wallet_1' address = 000000E8ABF7F884
wallet_1 = 300
wallet_2' address = 000000E8ABF7F8A4
wallet_2 = 500
```

在函数`swap_v()`中，变量a，b是wallet_1和wallet_2的复制，因此交换a和b不影响实际的wallet_1和wallet_2的值。

#### 8.2.3 引用的属性和特别之处

使用引用参数时，需要了解其一些特点。 

* `const double & x`相当于`const double * const pt`。
* 使用引用作为参数进行传递的限制条件更加严格。

```C++
#include <iostream>

double cube(double a);
double refcube(double & ra);

int main()
{
    double x = 3.0;
    std::cout << cube(x);
    std::cout << " = cube of " << x << std::endl;
    std::cout << refcube(x);
    std::cout << " = refcube of " << x << std::endl;
    return 0;
}

double cube(double a)
{
    a *= a * a;
    return a;
}

double refcube(double & ra)
{
    ra *= ra * ra;
    return ra;
}
```

输出如下：

```
7 = cube of 3
27 = refcube of 27
```

可以看到使用引用会修改输入值。如果程序员的意图是让函数使用传递给它的信息，而非对这些信息进行修改，需要使用const引用。

即，`const double & ra`。

<img src="D:\JiangLe\CPP_Note\assets\image-20250628132752787.png" alt="image-20250628132752787" style="zoom:67%;" />

此时，报错如上。该引用为一个const引用，不能通过引用对该地址上的值进行修改，也就是上图中报错的“表达式必须是可修改的左值”。

**临时变量、引用参数和const。**如果实参与引用参数不匹配，C++将生成临时变量。当前，仅当参数为const引用时，C++才允许这样做，但之前版本的C++不是这样做的。本节将介绍在何种情况下将出现临时变量，以及为什么仅仅在const引用时才会出现临时变量。

首先，何时会创建临时变量？

* 实参的类型正确，但不是左值
* 实参的类型不正确，但可以转换为正确的类型。

什么是左值？左值参数是可以被引用的数据类型，例如变量、数组元素、结构成员、引用和接触引用的指针。非左值包括字面常量（用引号扩起的字符串除外，它们由其地址表示）和包含多项的表达式。常规变量属于可以修改的左值，const变量为不可修改的左值。之所以叫左值，因为这些参数可以位于等号左边，对其进行赋值操作。

对refcube()函数进行修改，如下

```C++
double refcube(const double & ra)
{
	return ra * ra * ra;
}
```

现在考虑如下代码：

```c++
double side = 3.0
double * pd = &side;
double & rd = side;
long edge = 5L;
double lens[4] = {2.0, 5.0, 10.0, 12.0};
double c1 = refcube(side); // ra就是side
double c2 = refcube(lens[2]); // ra就是lens[2]
double c3 = refcube(rd); // ra就是rd，rd就是side
double c4 = refcube(*pd); // ra就是pa指向的值，pa指向side
double c5 = refcube(edge); // ra是一个临时变量
double c6 = refcube(7.0); // ra是一个临时变量
double c7 = refcube(side + 10.0); // ra是一个临时变量
```

参数`side`、`lens[2]`、`rd`和`*pd`都是左值且类型正确。`edge`是左值，但是类型不正确，double引用不能指向`edge`；7.0虽然类型正确，但是为非左值；`side + 10.0`类型正确，但是也为非左值。这些三种情况都将创建临时变量，临时变量仅仅在函数调用期间存在，此后编译器便可以随意将其删除。

那么为什么只有const引用才会出现这种临时变量创建的情况，而非const引用则直接禁止了这种情况呢？

在C++早期版本中，非const引用在类型不匹配的情况下也可以创建临时变量。但是如果程序员本意是通过非const引用修改输入变量的值，那么这种临时变量创建的方式就禁止了这种情况的出现，其类似与按值传递，无法通过非const引用修改输入变量的值。解决方法就是禁止非const引用创建临时变量。

综上，尽可能使用const引用的理由：

* 使用const可以避免无意中修改数据的情况发生
* 使用const可以是函数能够处理const和非const实参，否则只能传入非const数据
* 使用const引用是函数能够正确生成并使用临时变量

C++11新使用了一种引用——右值引用（rvalue reference）。这种引用指向右值，是使用`&&`声明的，在后续内容详细介绍。

#### 8.2.4 将引用用于结构

引用非常适合用于结构和类。引入引用的主要目的就是用于这些类型的，而不是基本的内置类。

```C++
#include <iostream>
#include <string>

// 结构体罚球
struct free_throws
{
    std::string name;
    int made;
    int attempts;
    float percent;
};

void display(const free_throws& ft);
// 使用一个const引用参数，使用引用可以节省时间和内存
void set_pc(free_throws& ft);
free_throws& accumulate(free_throws& target, const free_throws& source);

int main()
{
    // initializations - remaining memebers set to 0
    free_throws one = { "Ifelsa Branch", 13, 14 };
    free_throws two = { "Andor Knott", 10, 16 };
    free_throws three = { "Minnie Max", 7, 9 };
    free_throws four = { "Whily Looper", 5, 9 };
    free_throws five = { "Long Long", 6, 14 };
    free_throws team = { "Throwgoods", 0, 0 };

    // no initialization
    free_throws dup = {};
    // 初始化中对与未提供值的值，默认为0，字符类则为'\0'
    std::cout << "Dup without initialization\n";
    display(dup);

    set_pc(one);
    display(one);

    accumulate(team, one);
    display(team);

    display(accumulate(team, two));
    accumulate(accumulate(team, three), four);
    display(team);

    dup = accumulate(team, five);
    std::cout << "Display team:\n";
    display(team);
    std::cout << "Display dup after assignment:\n";
    display(dup);
    set_pc(four);

    accumulate(dup, five) = four;
    std::cout << "Display dup after ill-advised assignment:\n";
    display(dup);

    return 0;
}

void display(const free_throws& ft)
{
    using std::cout;
    cout << "Name: " << ft.name << '\n';
    cout << "Made: " << ft.made << '\n';
    cout << "Attempts: " << ft.attempts << '\n';
    cout << "Percent: " << ft.percent << '\n';
    cout << std::endl;
}

void set_pc(free_throws& ft)
{
    if (ft.attempts != 0)
        ft.percent = 100.0f * float(ft.made) / float(ft.attempts);
    else
        ft.percent = 0;
}

free_throws& accumulate(free_throws& target, const free_throws& source)
{
    target.attempts += source.attempts;
    target.made += source.made;
    set_pc(target);
    return target;
}
```

输出如下：

```
Dup without initialization
Name:
Made: 0
Attempts: 0
Percent: 0

Name: Ifelsa Branch
Made: 13
Attempts: 14
Percent: 92.8571

Name: Throwgoods
Made: 13
Attempts: 14
Percent: 92.8571

Name: Throwgoods
Made: 23
Attempts: 30
Percent: 76.6667

Name: Throwgoods
Made: 35
Attempts: 48
Percent: 72.9167

Display team:
Name: Throwgoods
Made: 41
Attempts: 62
Percent: 66.129

Display dup after assignment:
Name: Throwgoods
Made: 41
Attempts: 62
Percent: 66.129

Display dup after ill-advised assignment:
Name: Whily Looper
Made: 5
Attempts: 9
Percent: 55.5556   
```

`free_throws& accumulate(free_throws& target, const free_throws& source)`对于该函数，如果返回类型被声明为`free_throws`而不是`free_throw&`那么返回的是target的拷贝值，但返回类型为引用，意味着返回的是最初传递给accumulate()的对象。

为何要返回引用？

传统返回机制与按值传递函数参数类似，都是将返回值存储在一个临时的位置，然后调用程序使用这个值。

```C++
dup = accumulate(team, five);
```

如果accumulate()返回一个结构，而不是指向结构的引用，将把整个结构复制到一个临时位置，再将这个拷贝复制给dup。但在返回值为引用时，将直接把team复制到dup，效率更高。

返回引用时，要注意应当避免返回函数终止时，不再存在的内存单元引用，即应当避免如下代码：

```C++
const free_throws & clone2(free_throws & ft)
{
	free_throws newguy;
    newguy = ft;
    return newguy;
}
```

该函数指向一个临时变量`newguy`，在函数运行完毕后自动删除，虽然通过编译器的自动优化可以规避一些问题，但是这个优化是不稳定的。警告示意，以及终端输出如下：

![image-20250628200550177](D:\JiangLe\CPP_Note\assets\image-20250628200550177.png)

```
Display dup after ill-advised assignment:
Name: Whily Looper
Made: 5
Attempts: 9
Percent: 55.5556

newguy(in the function) address = 000000E8AF96F1A8
Display newguy copy from dup:
Name:
Made: 5
Attempts: 9
Percent: -2.74591e-10

newguy(out of function) address = 000000E8AF96F548
```

输出的复制值实际上与被复制的值并不是完全一样，故在编程中应当避免返回临时变量的指针。

但是若把函数修改为如下所示：

```c++
const free_throws clone2(free_throws& ft)
{
    free_throws newguy;
    newguy = ft;
    std::cout << "newguy(in the function) address = " << &newguy << std::endl;
    return newguy;
}
```

可以看到终端输出正常。

```
Display dup after ill-advised assignment:
Name: Whily Looper
Made: 5
Attempts: 9
Percent: 55.5556

newguy(in the function) address = 0000002E6B6FF648
Display newguy copy from dup:
Name: Whily Looper
Made: 5
Attempts: 9
Percent: 55.5556

newguy(out of function) address = 0000002E6B6FF648
```

同时可以将一个作为参数传入函数的引用作为返回值返回，源代码中正是这样操作的。也可以使用指针扩大变量的生命周期，如下：

```C++
const free_throws & clone(free_throws & ft)
{
	free_throws * pt;
    pt = &ft;
    return *pt;
}

...
delete pt
...
```

在教材中，将指针指向传入的参数时，是这样的`*pt = ft`，这种做法是错误的，一定要记住，在对指针进行接触引用操作时，一定要明确其指向的地址，这是指针调用的金科玉律。同时，由于当在函数内部进行使用`new`指令进行创建指针操作，在跳出函数时，可能会忘记清除指针。之后的相关内容会介绍自动释放指针的内容。

为何将const用于引用返回类型。

`free_throws& accumulate(free_throws& target, const free_throws& source)`这是初始版本中的语句，可以看到返回一个引用值。同时，`accumulate(dup, five) = four;`可以通过赋值操作对该函数的返回值进行赋值，说明函数返回的是一个可修改的左值。另一方面，常规的返回类型是右值——不能通过地址访问的值。这种表达式可以出现在赋值语句的右边，但不能出现在左边。常规函数返回值位于临时内存单元内，运行到下一条语句时，其可能不存在。

假设为了节约内存，使用引用返回值，但又不希望其被意外修改，因此可以在返回的引用之前加上`const`关键字进行修饰，返回一个不可修改的左值。

#### 8.2.5 将引用用于类对象

#### 8.2.6 对象、继承和引用

### 8.3 默认参数

### 8.4 函数重载

### 8.5 函数模板