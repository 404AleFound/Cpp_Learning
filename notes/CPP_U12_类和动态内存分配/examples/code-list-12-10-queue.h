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

//������Ҫ���һ��Queue�࣬�����г����е�������
//* ���д洢���޵���Ŀ����
//* �����������ɵ���Ŀ����һ������
//* Ӧ���ܹ������ն���
//* Ӧ���ܹ��������Ƿ�Ϊ��
//* Ӧ���ܹ��������Ƿ�Ϊ��
//* Ӧ���ܹ��ڶ�β�����Ŀ
//* Ӧ���ܹ��ڶ���ɾ����Ŀ
//* Ӧ���ܹ�ȷ����������Ŀ��

class Queue
{
// ����ṹ���Ժܺõ�������е�Ҫ��
// �����ɽڵ����й��ɣ�ÿһ���ڵ㶼����Ҫ���浽�����е���Ϣ�Լ�һ��ָ����һ���ڵ��ָ��
	struct Node { Item item; struct Node* next; };
	enum {Q_SIZE = 10};
private:
	Node* front;// ����һ�����׵�Node����ָ����һ��Node
	Node* rear;// ����һ����β��Node����ָ��NUll
	int items;// ��ǰ�Ľڵ���
	const int qsize;// ���Ľڵ���
	Queue(const Queue & q) : qsize(0) {}
	Queue& operator=(const Queue& q) { return *this; }
public:
// ���캯������һ���ն��С�Ĭ������£��������ɴ洢10����Ŀ�����ǿ�������ʾ��ʼ�����Ǹ�Ĭ��ֵ
	Queue(int qs = Q_SIZE);
	~Queue();
	bool isempty() const;
	bool isfull() const;
	int queuecount() const;
	bool enqueue(const Item& Item);
	bool dequeue(Item& iemt);
};

#endif