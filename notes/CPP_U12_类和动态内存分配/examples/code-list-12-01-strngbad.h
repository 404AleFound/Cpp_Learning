// strngbad.h -- flawed string class definition
# include <iostream>
# ifndef STRNGBAD_H_
# define STRNGBAD_H_

class StringBad
{
private:
    char* str;
// 使用char指针来表示姓名，意味着类声明并没有为字符串本身分配空间，而需要在构造函数中使用new运算符来声明，避免了在类声明中提前固定了字符串的长度
    int len;
    static int num_strings;
// 所有的类成员使用同一个静态成员变量
public:
    StringBad();
    StringBad(const char* s);
    ~StringBad();

    // friend functiuon
    friend std::ostream & operator <<(std::ostream& os, const StringBad& st);
};

# endif