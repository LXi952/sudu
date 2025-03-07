/*************************************************************************
    > File Name: command.h
    > Author: 
    > Mail: 
    > Created Time: Mon 03 Mar 2025 03:55:40 PM CST
 ************************************************************************/

#ifndef COMMAND_H
#define COMMAND_H

#include "../common/common.h"

//类CCommand要用到 CScene
//但类CScene中也会用到 CCommand
//因此一个头文件中声明另一个类
//声明类的头文件不能再引用另一个类的头文件
//实现函数的文件可以引用
//未声明类的头文件必须引用声明类的头文件
class CScene;

class CCommand
{
public:
	CCommand(CScene* point_owner);
	CCommand(CScene* point_owner, const point_t& point, int prev_value, int curr_value);
	CCommand(const CCommand&);
	~CCommand();

	bool execute(int input_value);
	void undo();
	point_t getPoint();
	int getPrevValue();
	int getCurrValue();
	void setPoint(const point_t& point);
	void setPrevValue(int prev_value);
	void setCurrValue(int curr_value);

private:
	CScene* m_point_owner;
	point_t m_st_point;
	int m_prev_value;
	int m_curr_value;
};

#endif
