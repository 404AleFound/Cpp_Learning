// dma.h -- inheritance and dynamic memory allocation
#ifndef DMA_H_
#define DMA_H_

#include<iostream>

//======================================基类baseDMA======================================
class baseDMA
{
private:
	char* label;
	int rating;
public:
	baseDMA(const char* la = "null", int ra = 0);
	baseDMA(const baseDMA& rs);
	virtual ~baseDMA();
	baseDMA& operator=(const baseDMA& rs);
	friend std::ostream& operator<<(std::ostream& os, const baseDMA& rs);
};

//======================================派生类lackDMA======================================
class lackDMA : public baseDMA
{
private:
	enum { COL_LEN = 40};
	char color[COL_LEN];

public:
	lackDMA(const char* la = "null", int ra = 0, const char* co = "blank");
	lackDMA(const baseDMA & dma, const char* s = "blank");
	friend std::ostream& operator<<(std::ostream& os, const lackDMA& ls);
};

//======================================派生类hasDMA======================================
class hasDMA : public baseDMA
{
private:
	char* style;
public:
	hasDMA(const char* la = "null", int ra = 0, const char* st = "none");
	hasDMA(const baseDMA& dma, const char* st = "none");
	hasDMA(const hasDMA& hdma);
	~hasDMA();
	hasDMA& operator=(const hasDMA& hdma);
	friend std::ostream& operator<<(std::ostream& os, const hasDMA& hs);
};

#endif // !DMA_H_
