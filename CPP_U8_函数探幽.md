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

下面例子创建一个函数，将指定的字符串加入到另一个字符串的前面和后面。下述程序提供了三个这样的函数，然而其中一个存在很大的缺陷，甚至导致程序崩溃无法运行。

```C++
#include <iostream>
#include <string>

using namespace std;
string version_1(const string& s1, const string& s2);
// 传入一个指向string的const引用s1，和一个指向string的const引用s2，返回一个string类对象。
const string& version_2(string& s1, const string& s2);
// 传入一个指向string的引用s1，和一个指向string的const引用s2，返回一个指向string的const引用。
const string& version_3(string& s1, const string& s2);
// 传入一个指向string的引用s1，和一个指向string的const引用s2，返回一个指向string的const引用。

int main()
{
    // 创建三个string对象。
    string input;
    string copy;
    string result;

    cout << "Enter a string: ";
    getline(cin, input);
    copy = input;
    cout << "Your string as entered: " << input << endl;
    result = version_1(input, "***");
    // version_1 返回一个临时值，这个值被存储在result中
    cout << "Your string enhanced: " << result << endl;
    cout << "Your original string: " << input << endl;

    result = version_2(input, "###");
    // version_2 返回修改后的input，通过const指针实现
    cout << "Your string enhanced: " << result << endl;
    cout << "Your original string: " << input << endl;

    cout << "Resetting original string.\n";
    input = copy;
    result = version_3(input, "###");
    // version_3 返回一个临时变量的引用，但是由于该临时变量在函数结束后就失效了，因此出现错误
    cout << "Your string enhanced: " << result << endl;
    cout << "Your original string: " << input << endl;

    return 0;
}

string version_1(const string& s1, const string& s2)
{
    string temp;
    temp = s2 + s1 + s2;
    return temp;
}

const string& version_2(string& s1, const string& s2)
{
    s1 = s2 + s1 + s2;
    return s1;
}

const string& version_3(string& s1, const string& s2)
{
    string temp;
    temp = s2 + s1 + s2;
    return temp;
}
```

返回如下：

```
Enter a string: jiangle
Your string as entered: jiangle
Your string enhanced: ***jiangle***
Your original string: jiangle
Your string enhanced: ###jiangle###
Your original string: ###jiangle###
Resetting original string.
Your string enhanced:
Your original string: jiangle
```

版本1的函数，将s1和s2传入函数，这个值均作为只读值，无法修改，返回一个常规的string变量。相较于`string version_4(string s1, string s2)`将引用作为参数，函数的运行速度更快。

```
string version_1(const string& s1, const string& s2)
{
    string temp;
    temp = s2 + s1 + s2;
    return temp;
}
```

将C风格字符串用于string对象引用参数

对于函数version_1，可以看到该函数的两个形参(s1和s2)的类型均为const string&，但实参的类型分别为string和const char*。由于input的类型为string，有哪次让s1指向它没有任何问题。单数对于const char * 是如何解决的呢？

这里有两点需要说明。首先，string类定义了一种能够将char * 转换为string的功能，这使得可以使用C风格字符串来初始化string对象。其次，之前讨论过，假设实参的类型与引用参数类型不同，但是可以相互转换，C++会创建一个正确类型的临时变量，使用转换后的实参值来初始化它，然后传递一个指向该临时变量的引用。

```
#include <iostream>
#include <string>

using namespace std;

void tran(const string & a);

int main()
{
	cout << "The address of C-style-string is: " << &"***" << endl;
	tran("***");

	string a = "***";
	cout << "The address of string class object is: " << &a << endl;
	tran(a);

	return 0;
}

void tran(const string & a)
{
	cout << "The address inside the function is: " << &a << endl;
}
```

这一段代码输出如下：

```
The address of C-style-string is: 00007FF617B42948
The address inside the function is: 00000027172FF8F8
The address of string class object is: 00000027172FF7F8
The address inside the function is: 00000027172FF7F8
```

当实参和形参类型不一致，但是可以相互转换时，程序会自动创建一个转换好类型的临时变量，并令引用指向该临时变量。这也说明了当传入C风格的字符串时，函数内外输出的地址不同，而当类型正确时，输出的地址则是相同的。

版本2的函数不创建临时string对象，而是直接修改原来的string对象，并将其作为返回值。由于该函数可以修改s1，因此并没有使用一个const引用指向它。但是，该函数会修改输入值s1，因此要保持与原来的字符串不变，这种函数的写法是错误的。

- 当类型不匹配但可以隐式转换时，编译器会创建临时对象
- 临时对象是新创建的对象，所以地址不同
- 对于引用参数，临时对象的**生命周期？？？**会延长到函数调用结束
- 当类型完全匹配时，直接传递引用，不会创建临时对象

```
const string& version_2(string& s1, const string& s2)
{
    s1 = s2 + s1 + s2;
    return s1;
}
```

版本3的函数，将一个指向函数内临时变量的const引用返回，这个函数虽然能够通过编译，但是程序会试图引用已经释放的内存，虽然在更高级的C++版本中可能修复了程序崩溃的问题，但这个问题仍然是要避免的。

```
const string& version_3(string& s1, const string& s2)
{
    string temp;
    temp = s2 + s1 + s2;
    return temp;
}
```

#### 8.2.6 何时使用引用参数

* 原因1：程序员能够修改调用函数中的数据对象
* 原因2：通过传递引用而不是整个数据对象，可以提高程序的运行速度

对于何时使用按值传递，何时使用指针，何时使用引用传递，有如下原则和要求：

* 如果数据对象很小，如内置数据类型或小型结构，则按值传递
* 如果数据对象是数组，则使用指针，因为这是唯一的选择，并将指针声明为转向const的指针
* 如果数据对象是较大的结构，则使用const指针或者const引用，可以调高程序效率，节约内存空间
* 如果数据对象是类对象，则使用const引用。

对于修改调用函数中数据的函数：

* 如果数据对象是内置数据类型，则使用指针。
* 如果数据对象是数组，则之只能使用指针。
* 如果数据对象是结构，则使用指针或者引用。
* 如果数据对象是类对象，则使用引用。

### 8.3 默认参数

默认参数指当函数调用中省略了实参时，自动使用的一个值。

通过函数原型，编译器可以了解函数所需的参数数目，因此函数原型也必须将可能的默认参数告知程序，方法是将值赋给原型中的参数。

```C++
char * left (const char * str, int n = 1);
```

对于带参数列表的函数，必须从右向左添加默认值。也就是说，要为某个参数设置默认值，则必须为它右边的所有参数提供默认值。

```C++
int harpo(int n, int m = 4, int j = 5);//正确
int chico(int n, int m = 6, int j);//错误
int groucho(int k = 1, int m = 2, int n = 3);//正确
```

实参按从左到右的顺序依次被赋给相应的形参，而不能跳过任何参数。

```C++
beeps = harpo(3, , 8);//错误
```

 下面程序使用了漠然参数。请注意，只有原型指定了默认值。函数定义与没有参数时完全相同。

```C++
#include <iostream>

const int ArSize = 80;
char* left(const char* str, int n = 1);

int main()
{
    using namespace std;
    char sample[ArSize];
    cout << "Enter a string:\n";
    cin.get(sample, ArSize);
    char* ps = left(sample, 4);
    cout << ps << endl;
    delete[] ps;// free old string
    ps = left(sample);
    cout << ps << endl;
    delete[] ps;
    return 0;
}

char* left(const char* str, int n)
{
    if (n < 0)
        n = 0;
    char* p = new char[n + 1];
    int i;
    for (i = 0; i < n && str[i]; i++)
        p[i] = str[i];
    while (i <= n)
        p[i++] = '\0';
    return p;
}
```

该程序使用new创建了一个新的字符串，一存储被选择的字符。

当用户错误的输入导致字符数目为负数时，使用一个条件判断语句，将n设置为0。

```c++
    if (n < 0)
        n = 0;
```

当输入的字符数目多余字符串包含的字符数时，使用一个组合的表达式解决。表达式的第二部分`str[i]`，是要赋值的字符的编码。遇到空值字符（其编码为0）后，循环将结束。这样while循环将使字符串以空值字符结束，并将余下的空间设置为空值字符。

```C++
i < n && str[i]
```

### 8.4 函数重载

#### 8.4.1 函数重载基本方法

函数多态时C++在C语言的基础上新增的功能。默认参数让您能够使用不同数目的参数调用一个函数，而函数多态（函数重载）让您能够使用多个同名的函数。

函数重载的关键是函数的参数列表——也被称为函数特征标。如果两个函数的参数数目和类型相同，同时参数的排列顺序也相同，则它们的特征标相同，而变量名是无关紧要的。C++允许定义名称相同的函数，条件是它们的特征表不同。如果参数数目和/或参数类型不同，则特征标也不同。如下，定义一组原型。

```C++
void print(const cahr * str, int width); // #1
void print(double d, int width); // #2
void print(long l, int width); // #3
void print(int i, int width)l // #4
void print(const char * str); // #5
```

使用print()函数时，编译器将根据所采取的用法使用有相应参数列表的函数的原型。

```C++
print("Pancakes", 15);// 使用#1
print("Syrup");// 使用#2
print(1999.0, 10);// 使用#3
print(1999, 12);// 使用#4
print(1999L, 15);// 使用#5
```

但调用函数时，其参数列表无法和任何一个原型匹配时，其将尝试使用标准类型转换强制进行匹配。如果找到多个经过强制转换后可以使用的函数原型，C++也将拒绝这种函数调用，并将其视为错误。

一些看起来不同的特征，但是C++可以使用同一个实参对其进行调用的函数原型也是不可行的，如下：

```C++
double cube(doube x);
double cube(double & x);
```

虽然，参数列表看起来有所不同，但是在调用时，参数可能和这两个原型同时匹配，因此编译器无法确定究竟使用哪一个函数原型。故编译器将某种类型的引用和该类型是为用一个特征标。

函数重载，区分const变量和非const变量。之所以在这两个参数上有所区别，是因为将非const值赋给const变量是合法的，但反之则是非法的。

函数的返回值不能作为函数重载的特征标。  

重载引用参数

* 左值引用参数r1和可修改的左值参数匹配。
* const左值引用参数r2和可修改的左值参数、const左值参数和右值参数匹配。
* 右值引用参数r3和右值匹配。

#### 8.4.2 重载示例

下面程序返回整数的前n位。

```c++
#include <iostream>
unsigned long left(unsigned long num, unsigned ct);
char* left(const char* str, int n = 1);

int main()
{
    using namespace std;
    //char* trip = "Hawwii!!";
    unsigned long n = 12345678;
    int i;
    char* temp;

    for (i = 1; i < 10; i++)
    {
        cout << left(n, i) << endl;
        temp = left("Hawwii!!", i);
        cout << temp << endl;
        delete[] temp;
    }
    return 0;
}

unsigned long left(unsigned long num, unsigned ct)
{
    unsigned digits = 1;
    unsigned long n = num;

    if (ct == 0 || num == 0)
        return 0;
    while (n /= 10)
        digits++;// 计算数字有多少位
    if (digits > ct)// 当总位数大于需要取的位数时
    {
        ct = digits - ct;
        while (ct--)
            num /= 10;
        return num; // 返回剩下的数字
    }
    else
        return num;
}

char* left(const char* str, int n)
{
    if (n < 0)
        n = 0;
    char* p = new char[n + 1];
    int i;
    for (i = 0; i < n && str[i]; i++)
        p[i] = str[i];
    while (i <= n)
        p[i++] = '\0';
    return p;
}
```



#### 8.4.3 何时使用函数重载

函数重载切忌乱用，只有当函数基本上执行相同任务，但使用不同形式的数据时，才应采用函数重载。

### 8.5 函数模板