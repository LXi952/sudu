/*************************************************************************
    > File Name: input.cpp
    > Author: 
    > Mail: 
    > Created Time: Wed 05 Mar 2025 07:55:47 PM CST
 ************************************************************************/

#include "input.h"

//返回被删除的数的数量
//根据删除数量来设定难度
int inputDifficulty()
{
	cls();

	std::string cmd;
	int need_erase_grids = 0;
	while (true) 
	{
		message(I18n::Instance().Get(I18n::Key::ASK_DIFFICULTY));
		std::cin >> cmd;

		try
		{
			Difficulty difficulty = static_cast<Difficulty>(std::stoi(cmd));
			switch (difficulty)
			{
				case Difficulty::EASY:
				{
					need_erase_grids = 20;
					break;
				}
				case Difficulty::NORMAL:
				{
					need_erase_grids = 35;
					break;
				}
				case Difficulty::HARD:
				{
					need_erase_grids = 50;
					break;
				}
//				default:
//					need_erase_grids = 0;
			}
		}
		catch (...)
		{
			need_erase_grids = 0;
		}
		if (need_erase_grids > 0)
		{
			break;
		}
		message(I18n::Instance().Get(I18n::Key::INPUT_ERROR));
	}
	return need_erase_grids;
}

//设置语言
void InputLanguage()
{
	std::string language;
	do
	{
		message("1English 2中文");
		std::cin >> language;

		try
		{
			auto l = static_cast<Language>(std::stoul(language) - 1);
			if (l < Language::MAX)
			{
				I18n::Instance().SetLanguage(l);
				return;
			}
		}
		catch (...)
		{

		}
		message(I18n::Instance().Get(I18n::Key::INPUT_ERROR));
	} while (true);
}

