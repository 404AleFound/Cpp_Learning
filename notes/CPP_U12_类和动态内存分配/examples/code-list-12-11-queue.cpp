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
// whileѭ��ɾ������������ָ��
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

// ���β�������Ŀ
//1. ���������������ֱ�ӽ���
//2. ����1���½ڵ�
//3. �ڽڵ��з�����ȷ��ֵ
//4. ����Ŀ������1
//5. ���ڵ㸽�ӵ���β
//		5.1 ���ڵ����б�����һ���ڵ�����
//		5.2 ��Queue�ĳ�Ա��ָ��rear����Ϊָ���½ڵ�
bool Queue::enqueue(const Item& item)
{
// ��������������������Ŀ������false
	if (isfull())
		return false;
// ����һ��Node*ָ��
	Node* add = new Node;
	add->item = item;
	add->next = NULL;
	items++;
// ��������ǿգ�˵��ԭ�����ǿյģ���front��add�ϲ�
	if (front == NULL)
		front = add;
	else
// �����򽫶�β����һ��add����
		rear->next = add;
// ���¶�β
	rear = add;
	return true;
}

// �ڶ�����ɾ����Ŀ
//1. �������Ϊ�գ�ֱ�ӽ���
//2. �����еĵ�һ����Ŀ�ṩ������
//3. ����Ŀ������1
//4. ����һ��front�ڵ�Ϊλ�ã��Թ�����ɾ��
//5. �ýڵ����
//6. Ϊ��ʡ�ڴ棬ɾ����ǰ�ĵ�һ���ڵ�
//7. �����ʱ����Ϊ�գ���Ҫ��rear����ΪNULL
bool Queue::dequeue(Item& item)
{
// �������Ϊ�գ��򲻽���ɾ��������false
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