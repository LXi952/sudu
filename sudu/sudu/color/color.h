/*************************************************************************
    > File Name: color.h
    > Author: 
    > Mail: 
    > Created Time: Mon 03 Mar 2025 04:30:32 PM CST
 ************************************************************************/

#ifndef COLOR_H
#define COLOR_H

#include <iostream>

namespace Color 
{
	enum Code
	{
		BOLD = 1,
		RESET = 0,

		BG_BLACK = 40,
		BG_RED = 41,
		BG_GREEN = 42,
		BG_YELLOW = 43,
		BG_BLUE = 44,
		BG_MAGENTA = 45,
		BG_CYAN = 46,
		BG_LIGHT_GRAY = 47,
		BG_DEFAULT = 49,

		FG_BLACK = 30,
		FG_RED = 31,
		FG_GREEN = 32,
		FG_YELLOW = 33,
		FG_BLUE = 34,
		FG_MAGENTA = 35,
		FG_CYAN = 36,
		FG_LIGHT_GRAY = 37,
		FG_DEFAULT = 38,
		FG_DARK_GRAY = 39,
		FG_LIGHT_RED = 90,
		FG_LIGHT_GREEN = 91,
		FG_LIGHT_YELLOW = 92,
		FG_LIGHT_BLUE = 93,
		FG_LIGHT_MAGENTA = 94,
		FG_LIGHT_CYAN = 95,
		FG_WHITE = 96
	};

	class Modifier
	{
		Code md, bg, fg;

	public:
		Modifier() : md(Color::RESET), bg(Color::BG_DEFAULT), fg(Color::FG_DEFAULT) {}
		Modifier(Code Mode, Code background, Code frontground) : md(Mode), bg(background), fg(frontground) {}
		friend std::ostream & operator <<(std::ostream& os, const Modifier& mod) 
		{
			return os << "\033[" << mod.md << ";" << mod.bg << ";" << mod.fg << "m";
		}
	};
}

#endif
