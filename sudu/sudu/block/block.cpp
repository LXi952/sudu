/*************************************************************************
    > File Name: block.cpp
    > Author: 
    > Mail: 
    > Created Time: Mon 03 Mar 2025 04:26:41 PM CST
 ************************************************************************/

#include "block.h"

CBlock::CBlock() : m_count(0) {}

//判断同行或同列或同一个九宫格是否出现相同的数
//出现相同的数返回false
//依次往后比
bool CBlock::isValid() const
{
	assert(MAX_COUNT == m_count);

	for (int i = 0; i < m_count - 1; ++i)
	{
		for (int j = i + 1; j < m_count; ++j)
		{
			//UNSELECTED代表未填数字 空格
			if (UNSELECTED == m_number[i]->value || UNSELECTED == m_number[j]->value)
			{
				continue;
			}
			if (m_number[i]->value == m_number[j]->value)
			{
				return false;
			}
		}
	}
	return true;
}

//判断格子是否填满
//未填满返回false
bool CBlock::isFull() const
{
	for (int i = 0; i < m_count; ++i)
	{
		point_value_t *p_point_value = m_number[i];
		if (nullptr == p_point_value || UNSELECTED == p_point_value->value)
		{
			return false;
		}
	}
	return true;
}

//输出表格
//未填处输出空格
void CBlock::print() const
{
	std::cout << Color::Modifier(Color::BOLD, Color::BG_DEFAULT, Color::FG_RED) << PIPE << Color::Modifier() << " ";
	for (int i = 0; i < m_count; ++i)
	{
		auto number = *(m_number[i]);
		//九宫格或边上用红线
		if ((i + 1) % 3 == 0)
		{
			if (0 == number.value)
			{
				std::cout << ' ' << " " << Color::Modifier(Color::BOLD, Color::BG_DEFAULT, Color::FG_RED) << PIPE << Color::Modifier() << " ";
			}
			else
			{
				if (number.state == State::ERASED)
				{
					std::cout << Color::Modifier(Color::BOLD, Color::BG_DEFAULT, Color::FG_GREEN) << number.value
							  << Color::Modifier() << " "
							  << Color::Modifier(Color::BOLD, Color::BG_DEFAULT, Color::FG_RED) << PIPE 
							  << Color::Modifier() << " ";
				}
				else
				{
					std::cout << number.value << " " << Color::Modifier(Color::BOLD, Color::BG_DEFAULT, Color::FG_RED)
							  << PIPE << Color::Modifier() << " ";
				}
			}
		}
		else
		{
			if (0 == number.value)
			{
				std::cout << ' ' << " " << PIPE << " ";
			}
			else 
			{
				if (number.state == State::ERASED)
				{
					std::cout << Color::Modifier(Color::BOLD, Color::BG_DEFAULT, Color::FG_GREEN) << number.value
							  << Color::Modifier() << " " << PIPE << " ";
				}
				else 
				{
					std::cout << number.value << " " << PIPE << " ";
				}
			}
		}
	}
	std::cout << std::endl;
}

//后插
void CBlock::push_back(point_value_t *p) 
{
	assert(nullptr != p);
	m_number[m_count++] = p;
}
