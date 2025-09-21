#ifndef QUEUE_H_
#define QUEUE_H_

class Customer
{
private:
	long arrive;
	int processtime;
public:
	Customer() { arrive = processtime = 0; }
	void set(long when);
	long when() const { return arrive; }
	int ptime() const { return processtime; }
};

typedef Customer Item;

//首先需要设计一个Queue类，这里列出队列的特征：
//* 队列存储有限的项目序列
//* 队列所能容纳的项目数有一定限制
//* 应当能够创建空队列
//* 应当能够检查队列是否为空
//* 应当能够检查队列是否为满
//* 应当能够在队尾添加项目
//* 应当能够在队首删除项目
//* 应当能够确定队列中项目数

class Queue
{
// 链表结构可以很好地满足队列的要求。
// 链表由节点序列构成，每一个节点都包含要保存到链表中的信息以及一个指向下一个节点的指针
	struct Node { Item item; struct Node* next; };
	enum {Q_SIZE = 10};
private:
	Node* front;// 包含一个队首的Node对象，指向下一个Node
	Node* rear;// 包含一个队尾的Node对象，指向NUll
	int items;// 当前的节点数
	const int qsize;// 最大的节点数
	Queue(const Queue & q) : qsize(0) {}
	Queue& operator=(const Queue& q) { return *this; }
public:
// 构造函数创建一个空队列。默认情况下，队列最多可存储10个项目，但是可以用显示初始化覆盖该默认值
	Queue(int qs = Q_SIZE);
	~Queue();
	bool isempty() const;
	bool isfull() const;
	int queuecount() const;
	bool enqueue(const Item& Item);
	bool dequeue(Item& iemt);
};

#endif