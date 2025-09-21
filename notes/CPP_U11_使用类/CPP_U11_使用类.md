# 使用类

## 再谈重载

本部分介绍一种使用运算符重载和友元设计矢量类的案例。处于简化目的，本章节实现一个二维矢量。

类设计中将分别实现使用极坐标和直角坐标的矢量表达形式。

```C++
// vect.h
#ifndef VECTOR_H_
#define VECTOR_H_
#include<iostream>
namespace VECTOR
{
	class Vector
	{
	public:
		enum Mode {RECT, POL};
	private:
		double x;
		double y;
		double mag;
		double ang;
		Mode mode;
	// private methods for setting values
		void set_mag();
		void set_ang();
		void set_x();
		void set_y();
	public:
		Vector();
		Vector(double n1, double n2, Mode form = RECT);
		void reset(double n1, double n2, Mode form = RECT);
		~Vector();
		double xval() const { return x; }
		double yval() const { return y; }
		double magval() const { return mag; }
		double angval() const { return ang; }
		void ploar_mode();
		void rect_mode();
	// operator overloading
		Vector operator+(const Vector& b) const;
		Vector operator-(const Vector& b) const;
		Vector operator-() const;
		Vector operator*(double n) const;
	// friends
		friend Vector operator*(double n, const Vector& a);
		friend std::ostream& operator<<(std::ostream& os, const Vector& v);
	};
}

#endif
```

```C++
// vect.cpp
#include<iostream>
#include"vect.h"
#include<cmath>

using std::sqrt;
using std::sin;
using std::cos;
using std::atan;
using std::atan2;
using std::cout;

namespace VECTOR{
	const double Rad_to_deg = 45.0 / atan(1.0);

	void Vector::set_mag(){
		mag = sqrt(x * x + y * y);
	}

	void Vector::set_ang(){
		if (x == 0.0 && y == 0.0)
			ang = 0.0;
		else
			ang = atan2(y, x);
	}

	void Vector::set_x(){
		x = mag * cos(ang);
	}

	void Vector::set_y(){
		y = mag * sin(ang);
	}

	Vector::Vector(){
		x = y = mag = ang = 0.0;
		mode = RECT;
	}

	Vector::Vector(double n1, double n2, Mode form){
		mode = form;
		if (form == RECT){
			x = n1;
			y = n2;
			set_ang();
			set_mag();
		}
		else if (form == POL){
			mag = n1;
			ang = n2;
			set_x();
			set_y();
		}
		else {
			cout << "Incorrect 3rd argument to Vector() -- ";
			cout << "vector set to 0\n";
			x = y = ang = mag = 0.0;
			mode = RECT;
		}
	}
	Vector::~Vector() {
	}

	void Vector::reset(double n1, double n2, Mode form) {
		mode = form;
		if (form == RECT) {
			x = n1;
			y = n2;
			set_ang();
			set_mag();
		}
		else if (form == POL) {
			mag = n1;
			ang = n2;
			set_x();
			set_y();
		}
		else {
			cout << "Incorrect 3rd argument to Vector() -- ";
			cout << "vector set to 0\n";
			x = y = ang = mag = 0.0;
			mode = RECT;
		}
	}

	void Vector::ploar_mode() {
		mode = POL;
	}

	void Vector::rect_mode() {
		mode = RECT;
	}

	// operator overloading
	Vector Vector::operator+(const Vector& b) const {
		return Vector(this->x + b.x, this->y + b.y);
	}
	Vector Vector::operator-(const Vector& b) const {
		return Vector(this->x - b.x, this->y - b.y);
	}
	Vector Vector::operator-() const {
		return Vector(-this->x, -this->y);
	}
	Vector Vector::operator*(double n) const {
		return Vector(this->x * n, this->y * n);
	}

	Vector operator*(double n, const Vector& a) {
		return Vector(n * a.x, n * a.y);
	}
	std::ostream& operator<<(std::ostream& os, const Vector& v) {
		if (v.mode == Vector::RECT) {
			os << "(x,y) = (" << v.x << ", " << v.y << ")";
		}
		else if (v.mode == Vector::POL){
			os << "(m,a) = (" << v.mag << ", " << v.ang << ")";
		}
		else {
			os << "Vector object mode is invaild";
		}
		return os;
	}

}


```



```C++
// randwalk.cpp
#include<iostream>
#include"vect.h"
#include<cstdlib>
#include<ctime>

int main() {
	using namespace std;
	using VECTOR::Vector;

	srand(time(0)); // seed random-number generator
	double direction;
	Vector step;
	Vector result(0.0, 0.0);
	unsigned long steps = 0;
	double target;
	double dstep;

	cout << "Enter target distance (q to quit): ";
	while (cin >> target)
	{
		cout << "Enter step length: ";
		if (!(cin >> dstep))
			break;

		while (result.magval() < target)
		{
			direction = rand() % 360;
			step.reset(dstep, direction, Vector::POL);
			result = result + step;
			steps++;
		}
		cout << "After " << steps << " steps, the subject has the following location:\n";
		cout << result << endl;
		result.ploar_mode();
		cout << "or\n" << result << endl;
		cout << "Average outward distance per step = " << result.magval() / steps << endl;
		steps = 0;
		result.reset(0.0, 0.0);
		cout << endl << "Enter target distance (q to quit): ";
	}
	cout << "Bye!\n";
	cin.clear();
	while (cin.get() != '\n')
		continue;
	return 0;
}
```

## 类的自动转换和强制类型转化

可以将类定义成与基本类型或另一个类相关，使得从一种类型转换为另一种类型是有意义的。在这种情况下，程序员可以指示C++如何自动进行转化内，或通过强制类型转化来完成，如下。

```C++
// stonewt.h -- definition for the Stonewt class
#ifndef STONEWT_H_
#define STONEWT_H_
class Stonewt
{
private:
    enum {Lbs_per_stn = 14};
    int stone;
    double pds_left;
    double pounds;
public:
    Stonewt(double lbs);
    Stonewt(int stn, double lbs);
    Stonewt();
    ~Stonewt();
    void show_lbs() const;
    void show_stn() const;
}
#endif
```

**引子：**当在编写C++程序时，如果将一个标准类型变量的值赋给另一种标准类型的变量时，如果这两种类型兼容，则C++可以自动将这个值转换为接受变量的类型。C++内置了一套用于数据类型转换的规则。

```C++
long count = 8;
double time = 11;
int side = 3.3 // 3.3将被转换为3后赋值给side
```

但是，如果两种类型不能互相兼容，也就是不满足内置的数据类型转换的规则，则C++不会自动进行转换。如下案例，虽然计算机内部可以使用整数来表示地址，但从概念上来说整数和指针完全不同。

```C++
int * p = 10; // 无法进行转换
```

然而，当在无法自动转换时，可以使用强制类型转换。

```C++
int * p = (int *) 10;
```

综上，对于用户自定义的类是否也可以自定义地设计一套转换规则，使得其能与C++的基本数据类型或其它类之间进行转换呢？同时，如果无法自动转换，是否可以如上面代码一样，对不同类的对象进行强制转换呢？



**利用构造函数，实现自动转换。**

在C++中，接受一个参数的构造函数可以实现类型与该参数相同的基本类型数据向该类的转换的功能。

例如，对于如此的构造函数`Stonewt(double lbs)`，可以编写如下代码：

```C++
Stonewt myCat;
mtCat = 19.6; // 有效，定义对应的单形参构造函数
```

在第二行代码中，数据`19.6`可以和`double`类型匹配，之后C++将创建一个临时的`Stonewt`对象，并将`19.6`作为初始化值，随后采用逐成员赋值方式将该临时对象的内容复制到`myCat`中。这一过程称为隐式转换，因为其是自动进行的，不需要显示强制类型转换。

注意，只有接受一个参数的构造函数才能作为转换函数。当构造函数出现多个参数时，不能用来转换类型。然而，若第二个参数为默认参数，则仍可以这样做。隐式转换类型如下：

* 将类对象初始化为对应的基本数据类型
* 将基本数据类型值赋给类对象
* 将基本数据类型值传递给接受某类对象参数的函数
* 返回值被声明为类对象的函数返回这一基本数据类型值
* 在上述任意一种情况下，使用可转换为该基本数据类型的内置类型。这种情况下，例如定义了`double`向`Stonewt`转换的构造函数，此时给类对象赋值int，则int会先被转换为`double`，之后转换为`Stonewt`对象。当且仅仅当转换不存在二义性时可以转换。假如，`Stonewt`有可以和`double`转换的构造函数，也有可以和`long`转换的构造函数，此时`int`既可以被转换为`long`后转换为类，又可以被转换为`double`后转换为类，就不可以了。

同时，为了防止构造函数的自动转换功能导致意外的类型转换，C++新增了关键字`explicit`，用于关闭这种自动转换的特性。在相应的构造函数之前加上关键字`explicit`，可以关闭隐式转换功能，但是仍然允许显示转换。

```C++
explicit Stonewt(double lbs);
```

```C++
Stonewt myCat;
myCat = 19.6;// 无效，对于使用关键字explicit的构造函数
myCat = Stonewt(19.6);// 可行，显示转换
myCat = (Stonewt) 19.6;// 可行，老版本的显示转换
```



**利用转换函数，实现强制转换。**

利用构造函数的弊端有两点。一是，只能实现其他基本类型向该类的转换；二是，只能用于隐式转换。转换函数可以实现从某种类型到类类型的转换，也可以像使用强制类型转换那样使用它们。 

```C++
Stonewt wolfe(285.7);
double host = double (wolfe);
double thinker = (double) wolfe;
```

那么如何创建转换函数呢？要转换为某特定的数据类型，需要使用这种形式的转换函数：

```C++
operator typeName();
```

注意，转换函数必须是类方法。转换函数不能指定返回类型。转换函数不能有参数。`typeName`指出了要转换的类型，因此不需要指定返回类型。转换函数必须是类方法，因此必须将原型添加到类中。转换函数通过类对象调用，因此不用指定参数。

```C++
operator int(); // 添加到类声明中
operator double(); // 添加到类声明中
```

 