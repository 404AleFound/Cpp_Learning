// queue.cpp -- Queue and Customer methods
#include<iostream>
#include"code-list-12-10-queue.h"
#include<cstdlib>

Queue::Queue(int qs) : qsize(qs)
{
	front = rear = NULL;
	items = 0;
}

Queue::~Queue()
{
	Node* temp;
// while循环删除队列中所有指针
	while (front != NULL)
	{
		temp = front;
		front = front->next;
		delete temp;
	}
}

bool Queue::isempty() const
{
	return items == 0;
}

bool Queue::isfull() const
{
	return items == qsize;
}

int Queue::queuecount() const
{
	return items;
}

// 向队尾中添加项目
//1. 如果队列已满，则直接结束
//2. 创建1个新节点
//3. 在节点中放入正确的值
//4. 将项目计数加1
//5. 将节点附加到队尾
//		5.1 将节点与列表中另一个节点链接
//		5.2 将Queue的成员你指针rear设置为指向新节点
bool Queue::enqueue(const Item& item)
{
// 如果队列已满，则不添加项目，返回false
	if (isfull())
		return false;
// 创建一个Node*指针
	Node* add = new Node;
	add->item = item;
	add->next = NULL;
	items++;
// 如果队首是空，说明原队列是空的，把front与add合并
	if (front == NULL)
		front = add;
	else
// 否则则将队尾与下一个add链接
		rear->next = add;
// 更新队尾
	rear = add;
	return true;
}

// 在队首中删除项目
//1. 如果队列为空，直接结束
//2. 将队列的第一个项目提供给函数
//3. 将项目计数减1
//4. 爆粗一年front节点为位置，以供后续删除
//5. 让节点出队
//6. 为节省内存，删除以前的第一个节点
//7. 如果此时链表为空，需要将rear设置为NULL
bool Queue::dequeue(Item& item)
{
// 如果队列为空，则不进行删除，返回false
	if (front == NULL)
		return false;
	item = front->item;
	items--;
	Node* temp = front;
	front = front->next;
	delete temp;
	if (items == 0)
		rear = NULL;
	return true;
}

void Customer::set(long when)
{
	processtime = std::rand() % 3 + 1;
	arrive = when;
}