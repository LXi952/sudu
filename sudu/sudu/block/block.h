/*************************************************************************
    > File Name: block.h
    > Author: 
    > Mail: 
    > Created Time: Mon 03 Mar 2025 03:55:19 PM CST
 ************************************************************************/

#ifndef BLOCK_H
#define BLOCK_H

#include "../common/common.h"
#include "../color/color.h"
#include "../displaysymbol/display_symbol.h"

class CBlock
{
	static const int MAX_COUNT = 9;

public:
	CBlock();

	bool isValid() const;
	bool isFull() const;
	void print() const;
	void push_back(point_value_t* point);

private:
	int m_count;
	//保存一行或一列或一个九宫格的数字
	point_value_t *m_number[MAX_COUNT];
};

#endif
