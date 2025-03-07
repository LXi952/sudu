/*************************************************************************
    > File Name: command.cpp
    > Author: 
    > Mail: 
    > Created Time: Tue 04 Mar 2025 01:35:54 PM CST
 ************************************************************************/

#include "command.h"
#include "../scene/scene.h"

//构造函数
CCommand::CCommand(CScene* point_owner) : m_point_owner(point_owner) {}

CCommand::CCommand(CScene* point_owner, const point_t &point, int prev_value, int curr_value)
	: m_point_owner(point_owner), m_st_point(point), m_prev_value(prev_value), m_curr_value(curr_value) {}

CCommand::CCommand(const CCommand &rhs)
	: m_point_owner(rhs.m_point_owner),
	  m_st_point(rhs.m_st_point),
	  m_prev_value(rhs.m_prev_value),
	  m_curr_value(rhs.m_curr_value)
	{}

CCommand::~CCommand() {}

//输入数字
bool CCommand::execute(int input_value)
{
	if (!m_point_owner)
	{
		return false;
	}
	m_st_point = m_point_owner->getCurrPoint();
	return m_point_owner->setCurrValue(input_value, m_prev_value);
}

//撤销操作
void CCommand::undo()
{
	if (m_point_owner) 
	{
		m_point_owner->setPointValue(m_st_point, m_prev_value);
	}
	return;
}

point_t CCommand::getPoint() 
{
	return m_st_point;
}

int CCommand::getPrevValue() 
{
	return m_prev_value;
}

int CCommand::getCurrValue()
{
	return m_curr_value;
}

void CCommand::setPoint(const point_t& point)
{
	m_st_point = point;
}

void CCommand::setPrevValue(int prev_value)
{
	m_prev_value = prev_value;
}

void CCommand::setCurrValue(int curr_value)
{
	m_curr_value = curr_value;
}
