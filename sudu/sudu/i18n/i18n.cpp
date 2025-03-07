/*************************************************************************
    > File Name: i18n.cpp
    > Author: 
    > Mail: 
    > Created Time: Wed 05 Mar 2025 02:34:31 PM CST
 ************************************************************************/

#include "i18n.h"

//英语映射
I18n::Dict english = 
{
	{I18n::Key::ASK_KEY_MAP, "keymap mode: 1 WASD"},
	{I18n::Key::INPUT_ERROR, "input error!"},
	{I18n::Key::LOAD_PROGRESS_FAIL, "load program failed!"},
	{I18n::Key::ASK_QUIT, "quit game? [Y/N]"},
	{I18n::Key::ASK_SAVE, "do you want to save the game program? [Y/N]"},
	{I18n::Key::ASK_SAVE_PATH, "input path of the program file:"},
	{I18n::Key::FILE_EXIST_ERROR, "this file is already exist."},
	{I18n::Key::CONTINUE, "continue"},
	{I18n::Key::UNDO_ERROR, "no more action to undo."},
	{I18n::Key::CONGRATULATION, "congratulation! you win!"},
	{I18n::Key::NOT_COMPLETE, "sorry, not complete"},
	{I18n::Key::ASK_DIFFICULTY, "select difficulty: 1 easy 2 normal 3 hard"}
};

//中文映射
I18n::Dict chinses = 
{
	{I18n::Key::ASK_KEY_MAP, "设置按键模式： 1 WASD"},
	{I18n::Key::INPUT_ERROR, "输入错误！"},
	{I18n::Key::LOAD_PROGRESS_FAIL, "加载存档失败！"},
	{I18n::Key::ASK_QUIT, "退出游戏? [Y/N]"},
	{I18n::Key::ASK_SAVE, "保存进度? [Y/N]"},
	{I18n::Key::ASK_SAVE_PATH, "输入存档文件路径:"},
	{I18n::Key::FILE_EXIST_ERROR, "文件已存在"},
	{I18n::Key::CONTINUE, "继续"},
	{I18n::Key::UNDO_ERROR, "没有可以撤销的了"},
	{I18n::Key::CONGRATULATION, "恭喜！你赢了"},
	{I18n::Key::NOT_COMPLETE, "对不去，未完成"},
	{I18n::Key::ASK_DIFFICULTY, "设置难度: 1 简单 2 普通 3 困难"}
};

I18n::I18n() : m_dict(&english) {}

//单例模式
I18n& I18n::Instance()
{
	static I18n i18n;
	return i18n;
}

//设置语言
void I18n::SetLanguage(Language language)
{
	switch (language)
	{
		case Language::ENGLISH:
		{
			m_dict = &english;
			break;
		}
		case Language::CHINESE:
		{
			m_dict = &chinses;
			break;
		}
		case Language::MAX:
		default:
			assert(false);
	}
}

//通过关键字的到相应的提示信息
std::string I18n::Get(Key key) const
{
	assert(m_dict->count(key));
	return (*m_dict)[key];
}
