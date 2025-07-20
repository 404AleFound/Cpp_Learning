// dma.cpp -- define the functions in dma.h

#include<iostream>
#include<string>
#include"code-list-13-14-dma.h"

//======================================友元函数======================================
std::ostream& operator<<(std::ostream& os, const baseDMA& rs)
{
	os << "Label: " << rs.label << std::endl;
	os << "Rating: " << rs.rating << std::endl;
	return os;
}

std::ostream& operator<<(std::ostream& os, const lackDMA& ls)
{
	os << (const baseDMA&)ls;
	os << "Color: " << ls.color << std::endl;
	return os;
}

std::ostream& operator<<(std::ostream& os, const hasDMA& hs)
{
	os << (const baseDMA&)hs;
	os << "Style: " << hs.style << std::endl;
	return os;
}

//======================================基类baseDMA======================================
baseDMA::baseDMA(const char* la, int ra)
{
	label = new char[std::strlen(la) + 1];
	strcpy_s(label, std::strlen(la) + 1, la);
	rating = ra;
}

baseDMA::baseDMA(const baseDMA& rs)
{ 
	label = new char[std::strlen(rs.label) + 1];
	strcpy_s(label, std::strlen(rs.label) + 1, rs.label);
	rating = rs.rating;
}

baseDMA::~baseDMA()
{
	delete[] label;
}

baseDMA& baseDMA::operator=(const baseDMA& rs)
{
	if (this == &rs)
		return *this;
	label = new char[std::strlen(rs.label) + 1];
	strcpy_s(label, std::strlen(rs.label) + 1, rs.label);
	rating = rs.rating;
	return *this;
}


//======================================派生类lackDMA======================================
lackDMA::lackDMA(const char* la, int ra, const char* co) : baseDMA(la, ra)
{
	strcpy_s(this->color, COL_LEN,co);
	this->color[COL_LEN - 1] = '\0';
}

lackDMA::lackDMA(const baseDMA& dma, const char* co) : baseDMA(dma)
{
	strcpy_s(this->color, COL_LEN, co);
	this->color[COL_LEN - 1] = '\0';
}


//======================================派生类hasDMA======================================
hasDMA::hasDMA(const char* la, int ra, const char* st) : baseDMA(la, ra)
{
	style = new char[std::strlen(st) + 1];
	strcpy_s(style, std::strlen(st) + 1, st);
}

hasDMA::hasDMA(const baseDMA& dma, const char* st) : baseDMA(dma)
{
	style = new char[std::strlen(st) + 1];
	strcpy_s(style, std::strlen(st) + 1, st);
}

hasDMA::hasDMA(const hasDMA& hdma) : baseDMA(hdma)
{
	style = new char[std::strlen(hdma.style) + 1];
	strcpy_s(style, std::strlen(hdma.style) + 1, hdma.style);
}

hasDMA::~hasDMA()
{
	delete[] style;
}

hasDMA& hasDMA::operator=(const hasDMA& hdma)
{
	if (this == &hdma)
		return *this;
	baseDMA::operator=(hdma);
	delete[] style;
	style = new char[std::strlen(hdma.style) + 1];
	strcpy_s(style, std::strlen(hdma.style) + 1, hdma.style);
	return *this;
}