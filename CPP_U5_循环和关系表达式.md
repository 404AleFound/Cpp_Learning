```markmap
---
markmap:
  zoom: false
  pan: false
  height: 700px
  backgroundColor: "#f8f8f8"
---

# 循环和关系表达式
## for循环
### for循环的组成部分
### 修改步长
### 递增运算符和递减运算符
### 副作用和顺序点
### 前缀格式和后缀格式
### 递增/递减运算符和指针
### 组合赋值运算
### 复合语句
### 逗号运算符
### 关系表达式
### C风格字符串的比较
### string类字符串的比较
## while循环
## do while循环
```

# 循环和关系表达式



## for循环

<img src="./figures/image-20250531152828723.png" alt="image-20250531152828723" style="zoom:50%;" />

### for循环的组成部分

```C++
for (initialization; test-expression; update-expression)
    body;
```

初始化、测试和更新操作构成了控制部分，这些操作由括号括起，每一个部分都是一个表达式，彼此之间由分号分开。控制部分后面叫循环体，只要测试部分表达式为True，它便被执行。

C++语法将整个for看作一个语句，虽然循环体可以包含一条或者多条语句。

C++并没有将test-expression的值限制为只能为真或者为假，可以使用任意表达式，C++将把结果强制转换为bool类型。因此值为0的表达式将被转换为bool值false，而非零值将被转换为bool值true。

**表达式和语句**

for语句的控制部分由3个表达式组成。任何值或任何有效的值和运算符的组合都是表达式。在C++中每一个表达式都有值。

C++将赋值表达式的值定义为等号左侧变量的值，例如对于表达式`x = 20`，其值为20。由于赋值表达式有值，因此可以编写以下的语句：

`maids = (cooks = 4) + 4`

该语句将8赋给变量maids。

然而C++虽然允许这样做，但并不意味着鼓励这种做法。允许上述语句存在的原则也允许编写以下语句：

`x = y = z = 0`

这种方法可以快速将值0赋给x，y，z。

对于像`x<y`这样的关系表达式式，将被判定为bool值（false或者true）。

为了判定表达式`x=100`，C++必须将100赋给变量x，判定表达式的这种操作改变了变量x的值，因此说变量x具有副作用。

当判定表达式的值的同时改变了内存中数据的值时，称表达式具有副作用（side effect）

从表达式到语句的变化非常简单，只要在表达式后面加上分号，就可以将表达式变换为语句。

`rodents+6;`

对于如上语句，其实际上并没有执行某种操作，程序仅仅是计算和，并没有使用得到的计算结果，某些智能编译器甚至会将跳过这种语句。

**非表达式和语句**

对任何表达式加上分号就可以将其变为表达式，但是这句话反过来并不能这么理解，将语句的分号拿走后，剩下的不一定为表达式。

**修改规则**

之前的for循环句法为：

```
for (expression; expression; expression)
    body
```

目前修改后的for语句句法如下：

```
for (for-init-statement condition-expression; updata-expression)
    body
```

注意，此时for语句的控制部分只有一个分号，这是因为`for-init-statement`被视为一个语句，而语句有自己的分号；在`for-init-statement`中声明变量还有其实用一面，就是该变量仅仅存在于循环体中，当程序离开循环后，该变量消失。

```C++
#include <iostream>
using namespace std;
const int Arsize = 16;
int main() {
    long long factorials[Arsize];
    factorials[0] = factorials [1] = 1LL;
    for (int i = 2; i < Arsize; i++)
        factorials[i] = factorials[i-1] * i;
    for (int i = 0; i < Arsize; i++)
        cout <<i<< "! = "<<factorials[i] << endl;
    return 0;

}
```



### 修改步长



### 递增运算符和递减运算符

递增运算符和递减运算符的前缀（prefix）版本为`++A`和`--A`，后缀（postfix）版本为`A--`和`A++`。两个版本对于操作数的影响是一样的，但是影响的时间不同。

粗略地讲，`A++`意味着先使用A当前的值，后再将其+1；`++A`意味着先将A的值加1后，再使用他的值。

```C++
int x = 5;
int y = ++x;//y  = 6, x = 6

int z = 5;
int y = z++;//y = 5, z = 6
```

### 副作用和顺序点

副作用定义见之前，就是当表达式会改变内存中的值时，称该表达式具有副作用；顺序点（sequence point）指程序执行中的一个点，在这里，进入下一步之前将确保对所有的副作用都进行了评估。

C++中，语句的分号就是一个顺序点，意味着程序在处理下一条语句前，赋值运算符、递增运算符和递减运算符执行的所有修改都必须完成。另外完整表达式的末尾都是一个顺序点。

何为完整表达式？其不是另一个更大表达式的子表达式。完整表达式的例子有：表达式语句中的表达式部分以及用作while循环中检测条件的表达式。

### 前缀格式和后缀格式

### 递增/递减运算符和指针

可以将递增和递减运算符用于指针和基本变量。将递增运算符用于指针时，将把指针的值增加其指向的数据类型的字节数，这种规则适用于对指针递增和递减。

前缀递增、前缀递减和解除引用运算符的优先级相同，以从右到左的方式进行结合。后缀递增和后缀递减的优先级相同，但比前缀运算符的优先级高，这两个运算符以从左到右的方式进行结合。

```C++
double arr[5] = {21.1, 32.8, 23.4, 45.2, 37.4};
double *pt = arr;
++pt;// pt points to arr[1], 32.8
double x = *++pt;// pt points to arr[2], x = 23.4
++*pt;//pt points to arr[2], arr[2] = 24.4
(*pt)++;//pt points to arr[2], arr[2] = 25.4
x = *pt++;//pt points to arr[3], arra[2] = 25.4, x = 25.4
```

### 组合赋值运算

C++有一种合并了加法和赋值操作的运算符，能够简洁地完成这种任务。

| 操作符 | 作用（L为左操作数，R为右操作数） |
| ------ | -------------------------------- |
| +=     | 将L+R赋给L                       |
| -=     | 将L-R赋给L                       |
| *=     | 将L*R赋给L                       |
| /=     | 将L/R赋给L                       |
| %=     | 将L%R赋给L                       |

### 复合语句

C++编写的for语句看上去比较严格，其循环体必须为一条语句。如果要在循环体中包含多条语句，可以使用两个花括号来构造一条符合语句（代码块）。代码块由一对花括号和它们包含的语句组成，被视为一条语句，从而满足句法的要求

如果在语句块中定义一个新的变量，则仅当程序执行该语句块中的语句时，该变量才存在，执行完该语句之后，变量将被释放。

```C++
#include <iostream>
int main()
{
    using namespace std;
    int x = 20;
    {
      	int y = 100;
    	cout << x << endl;//cout 20
    	cout << y << endl;//cout 100
    }
	cout << x << endl;//cout 20
    cout << y << endl;//won't compile
    return 0;
}
```

如果在一个语句中声明一个变量，而外部语句块中也有这样一个变量，那么在声明位置到内部语句块结束的范围之内，新变量将隐藏旧变量；然后旧变量再次可见。

```C++
#include <iostream>
int main()
{
    using namespace std;
    int x = 100;
    {
        cout << x <<endl;//100
        x = 20;
        cout << x <<endl;//20
    }
    cout << x << endl;//100
    return 0;
}
```

### 逗号运算符

语句块允许把两条甚至多条语句放到按C++语法只能放一条语句的地方。

逗号运算符对表达式完成同样的任务，允许将两个表达式放到C++句法允许放一个表达式的地方。

例如，假设有一个循环，每轮都将一个变量加1，而将另一个变量减1。在for循环控制部分的更新部分中完成这两项工作将非常方便，但循环句法只允许这里包含一个表达式，在这种情况下，可以使用逗号运算符将两个表达式合为一个表达式。

```C++
++j, --i;
```

逗号并不总是逗号运算符。

```C++
#include <iostream>
#include <string>
int main()
{
	using namespace std;
    cout << "Enter a word"<<endl;
    string word;
    cin >> word;
    
    char temp;
    int i;
    int j;
  	for (i = 0, j = word.size() - 1; i < j ;i++, j--)
    {
        temp = word[i];
        word[i] = word[j];
        word[j] = temp;
    }
    cout << "reserved word: "<<word<<endl;
    return 0;
}
```

不能使用逗号运算符将两个声明组合起来，这是因为C++规定中，声明已经将逗号用于其他用途了-分割列表中的变量，如下：

```C++
int i = 0, j = word.size();
```

此时逗号只是一个列表分隔符，而不是逗号运算符，因此该式对i和j进行声明和初始化。

到目前，逗号运算符最常见的用途是将两个或者更多表达式放到一个for循环表达式中，不过C++还为这个运算符提供了另外两个特性：

* 首先逗号运算符是一个顺序点，先计算第一个表达式，后计算第二个表达式
* 其次，逗号表达式的值是第二个表达式的值
* 最后，逗号运算符的计算级是最低的

### 关系表达式

计算机还可以对值进行比较，关系表达式是这种能力的体现。

| 操作符 | 含义     |
| ------ | -------- |
| <      | 小于     |
| <=     | 小于等于 |
| ==     | 等于     |
| >      | 大于     |
| >=     | 大于等于 |
| !=     | 不等于   |

关系运算符的优先级比算术运算符低。

### C风格字符串的比较

```C++
word == "mate"
```

要判断word字符串数组中包含的字符串是否为`mate`上面的比较是无法有效判断的。因为在C++中，word表示数组的地址，同样用双引号括起来的字符串常量也是地址，上式相当于对地址进行比较，两个字符串的地址显然是不同的。

为了有效进行C风格字符串的比较，使用string库中的`strcmp`函数。

该函数接受两个字符串地址作为参数。这意味着参数可以是指针、字符串常量或者字符数组名。如果两个字符串相同则返回0；如果第一个字符串按字符顺序排在第二个字符串之前，则返回一个负数；如果第一个字符串按字母顺序排在第二个字符串之后，则返回一个正数值。

实际上与其说按“字符顺序排序”，不如说按”系统顺序排序”，这意味着字符是根据字符的系统编码比较的。例如使用ASCII码时，所有大写字母的编码均比小写字母小。

有些语言不同长度的数组中的字符串批次不相等，但是C风格字符串是通过结尾的空值字符表示定义的，而不是由其所在数组的长度定义的，这意味着两个字符串即使被存储在不同长度的数组中，也可能是相同的。

```C++
#include <cstring>
#include <iostream>
int main()
{
	using namespace std;
    char word[5] = "?ate";
    for (word[0]; strcmp(word, "mate"); word[0]++)
    {
        cout<< "word is: "<< word << endl;
    }
    cout<< "out of for, word is: "<< word << endl;
    return 0;
}
```

虽然字符串无法通过比较运算符进行比较，但是字符却可以通过比较运算符比较，因为字符运算符是整型，至少对于ASCII字符集和Unicode字符集是这样的。

### string类字符串的比较

string类字符串是一个类对象，其重载了运算符，因此可以直接使用比较运算符判断两个string类的字符串是否相等。

## while循环

<img src="./figures/image-20250531152945550.png" alt="image-20250531152945550" style="zoom:50%;" />

while循环是没有初始化和更新表达式的for循环，它只有判断表达式和循环体：

```C++
while (test-condition)
    body
```

首先程序计算圆括号内的测试条件（test_expr），如果该表达式为true，则执行循环体内的语句（statement 2）。与for循环一样，循环体也由一条语句或者两个花括号定义的语句块组成。执行完循环体后，再次执行测试条件（test_expr），若为true则重复上述过程，直到测试条件（test_expr）为false，跳出循环。

```C++
// while.cpp -- introducing the while loop
```



## do while循环

与之前的for循环和while循环不同，do while循环是一个出口条件循环（exit condition）。这意味着循环将首先执行循环体，之后再判定测试表达式，决定是否应该继续执行循环。

<img src="./figures/image-20250601093008591.png" alt="image-20250601093008591" style="zoom:50%;" />

通常入口条件循环比出口条件循环好，因为入口条件循环往往会先对条件进行检验。但是有时，do while更加合理，例如，请求用户输入时，程序必须先获得输入，然后对它进行测试。

## 基于范围的for循环

C++11新增了一种循环：基于范围（range-based）的for循环。这简化了一种常见的循环任务：对数组（或容器类，如vector和array）的每一个元素执行相同的操作，如下例所示：

```c++
double prices[5] = {4.99, 10.99, 6.87, 7.99, 8.49};
for (double x : prices)
    cout << x << std:endl;
```

## 循环和文本输入

循环最常见的一项任务就是逐字符地读取来自文件或者键盘的文本。

<img src="./figures/image-20250601120431595.png" alt="image-20250601120431595" style="zoom:67%;" />

### 使用原始的`cin`进行输入



如果程序要使用循环来读取来自键盘的文字输入，则必须要有办法直到何时停止读取。如何直到这一点呢？一种方法是选择某一个特殊字符——有时被称为哨兵字符（sentinel character），将其作为停止标记。

```c++
// textin1.cpp -- reading chars with a while loop
#include <iostream>
int main()
{
	using namespace std;
	char ch;
	int count = 0;
	cout << "Enter characters; enter # to quit:\n";
	cin >> ch;
	while (ch != '#')
	{
		cout << ch;
		++count;
		cin >> ch;
	}
	cout << endl << count << " characters read\n";
	return 0;
}
```

```
Enter characters; enter # to quit:
123456#1234#123456789
123456
6 characters read
```

可以看到，程序最终在输出时省略的空格，原因在于cin对象在读取char值时，与读取其他基本类型一样，cin将忽略空格和换行符。因此输入的空格没有被回显，也没有被包括在计数之内。

更为复杂的是，发送给cin的输入被缓冲。这意味着只有在用户按下回车键后，他输入的内容才会被发送给程序。这就是程序在运行该程序的时候，可以在#后面输入字符的原因。按下回车键后，整个字符序列将被发送给程序，但程序在遇到#字符后将结束对输入的处理。

### 使用cin.get(char)进行补救

通常，逐个字符读取输入的程序需要检查每一个字符，包括空格、制表符和换行符。cin所属的istream类中包含一个能够满足这种要求的成员函数。具体地说，成员函数cin.get(ch)读取输入中的下一个字符，即使他是空格，并将其赋给变量ch。使用这个函数调用替换cin，可以修补之前程序的问题。



```C++
// textin2.cpp -- using cin.get(char)
#include <iostream>
int main()
{
	using namespace std;
	char ch;
	int count = 0;
	cout << "Enter characters; enter # to quit:\n";
	cin.get(ch);
	while (ch != '#')
	{
		cout << ch;
		++count;
		cin.get(ch);
	}
	cout << endl << count << " characters read\n";
	return 0;
}
```



```
Enter characters; enter # to quit:
12 345 6#123465
12 345 6
8 characters read
```

### 好多cin.get()

cin.get()存在多个版本

```
//版本1
cin.get(name, Arsize)
//版本2
cin.get()
//版本3
cin.get(char)
```

函数重载允许对多个相关的函数使用相同的名称，这些函数以不同方式或针对不同类型执行相同的基本任务。

在C++中，函数重载允许创建多个同名函数，条件是他们的参数列表不同。

### 文件尾条件

前文通过诸如#等符号表示输入结束很难令人满意，因为这样的符号可能就是合法输入的组成部分。但是，如果输入来自文件，则可以使用一种功能更加强大的技术——检测文件尾（EOF）。C++输入工具和操作系统协同工作，来检测文件尾并将这中信息告知程序。



```
cin.get(ch);
while (cin.fail() == false)
{
	...
	cin.get(ch);
}
```

方法cin.get(char)的返回值是一个cin对象，然而istream类提供了一个可以将istream对象转换为bool值的函数；当cin出现在需要bool值的地方时，该转换函数将被调用。另外如果最后一次调用成功了，则转换得到的bool值为true，否则为false。

```
while (cin.get(ch))
{
	...
}
```

循环的三条要求（确定结束条件，对条件进行初始化以及更新条件）全部被放在循环测试条件中。

### 另一个cin.get()版本

不接受任何参数的cin.get()函数返回输入中的下一个字符

`ch=cin.get()`

cin.get(char)
返回一个cin对象

## 嵌套循环和二维数组



