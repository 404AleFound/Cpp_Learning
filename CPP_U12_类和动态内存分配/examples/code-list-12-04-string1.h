// strngbad.h -- flawed string class definition
# ifndef STRING1_H_
# define STRING1_H_
# include <iostream>

using std::ostream;
using std::istream;

class String
{
private:
    char* str;
    int len;
    static int num_strings;
    static const int CINLIM = 80;

public:
// 构造函数和其他类的特殊方法
    String();
    String(const char *);
    String(const String &);
    ~String();
    int length() { return len; }

// 重载运算符法 
    String& operator=(const String &);
    String& operator=(const char*);
    char & operator[](int i);
    const char& operator[](int i) const;

// 重载运算符，使用友元
    friend bool operator<(const String& st1, const String& st2);
    friend bool operator>(const String& st1, const String& st2);
    friend bool operator==(const String& st1, const String& st2);
    friend std::ostream& operator <<(ostream& os, const String& st);
    friend std::istream& operator >>(istream& os, String& st);

// 静态函数
    static int HowMany();
};

# endif