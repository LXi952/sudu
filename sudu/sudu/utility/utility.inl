#ifndef _UTILITY_INL_
#define _UTILITY_INL_

#include "../common/common.h"

//获得随机数
inline unsigned int random(int begin, int end)
{
	std::random_device rd;
	std::mt19937 g(rd());
	return std::uniform_int_distribution<unsigned int>(begin, end)(g);
}

//获得数独数字数组
inline std::vector<int> get_unit()
{
	return std::vector<int> {1, 2, 3, 4, 5, 6, 7, 8, 9};
}

//对数组洗牌
//让数组随机
inline std::vector<int> shuffle_unit()
{
	std::vector<int> unit = get_unit();
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(unit.begin(), unit.end(), g);
	return unit;
}

//输出信息
//根据标志决定是否换行
inline void message(const char* msg = "", bool lf = true)
{
	std::cout << msg;
	if (lf) 
	{
		std::cout << std::endl;
	}
}

//输出字符串内容
inline void message(const std::string& msg, bool lf = true)
{
	message(msg.c_str(), lf);
}

inline char getch(void)
{
	//printf("getch\n");
	struct termios tmtemp, tm;
	int c;
	int fd = 0;
	//获取终端属性设置并保存到tm中
	//串口
	if (tcgetattr(fd, &tm) != 0)
	{
		return -1;
	}
	tmtemp = tm;
	//将串口设置为RAW模式
	cfmakeraw(&tmtemp);
	//设置终端属性
	if (tcsetattr(fd, TCSANOW, &tmtemp) != 0)
	{
		return -1;
	}
	//printf("getch1\n");
	//getchar();
	//刷新缓冲
	fflush(stdin);
	c = getchar();
	//printf("getch2\n");
	if (c == 27) 
	{
		int back_flags = fcntl(fd, F_GETFL);
		fcntl(fd, F_SETFL, back_flags | O_NONBLOCK);
		c = getchar();
		if (c == EOF) 
		{
			c = 27;
		}
		else 
		{
			while ((c = getchar()) != EOF)
			{

			}
		}
		fcntl(fd, F_SETFL, back_flags);
	}
	//恢复终端设置
	if (tcsetattr(fd, TCSANOW, &tm) != 0) 
	{
		return 0;
	}
	//printf("getch3\n");
	return static_cast<char>(c);
}

inline char _getch()
{
	return getch();
}

inline void cls(void) 
{
	system("clear");
}

#endif
