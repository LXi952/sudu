/*************************************************************************
    > File Name: common.h
    > Author: 
    > Mail: 
    > Created Time: Mon 03 Mar 2025 03:31:34 PM CST
 ************************************************************************/

#ifndef COMMON_H
#define COMMON_H

#include <cstring>
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <ctime>
#include <cmath>

#include <iostream>
#include <memory>
#include <filesystem>
#include <fstream>
#include <random>

#include <termio.h>
#include <memory.h>
#include <fcntl.h>

#include <algorithm>
#include <vector>
#include <unordered_map> 
#include <map>
#include <string>

static const unsigned int UNSELECTED = 0;

//难度
enum class Difficulty : int 
{
	EASY = 1,
	NORMAL,
	HARD
};

//状态
//INITED 初始的 不能修改
//ERASED 可以修改的
enum class State : int
{
	INITED = 0,
	ERASED
};

//按键
//ESC 退出	U  u返回上一步  ENTER 回车判断是否正确
//上下左右	wasd
class KeyMap
{
public:
	const char ESC = 0x1B;
	const char U = 0x75;
	char UP = 0x77;
	char LEFT = 0x61;
	char RIGHT = 0x64;
	char DOWN = 0x73;
	const char ENTER = 0x0D;
};

using point_t = struct point_t 
{
	int x;
	int y;
};

using point_value_t = struct point_value_t
{
	int value;
	State state;
};

class CPointSort
{
public:
	bool operator()(const point_t& a, const point_t& b) const
	{
		if ((a.x == b.x) && (a.y == b.y)) 
		{
			return false;
		} 
		else 
		{
			return true;
		}
	}
};

#endif
