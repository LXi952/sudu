/*************************************************************************
    > File Name: scene.h
    > Author: 
    > Mail: 
    > Created Time: Mon 03 Mar 2025 03:39:18 PM CST
 ************************************************************************/

#ifndef SCENE_H
#define SCENE_H

#include "../common/common.h"
#include "../block/block.h"
#include "../command/command.h"
#include "../displaysymbol/display_symbol.h"
#include "../i18n/i18n.h"
#include "../utility/utility.inl"
#include "../color/color.h"

class CScene {
public:
	CScene(int index = 3);
	virtual ~CScene();

	void generate();
	void show() const;

	bool setCurrValue(const int n_curr_value, int& n_last_value);
	bool setPointValue(const point_t&, const int);
	point_t getCurrPoint();

	void eraseRandomGrid(const int count);
	bool isComplete();

	void play();
	bool save(const char *filename);
	bool load(const char *filename);

private:
	void init();
	void setValue(const int);
	void setValue(const point_t &, const int);
	void printUnderLine(int line_no = -1) const;

private:
	//KeyMap m_key_map;
	KeyMap *m_key_map;
	int m_max_column;
	point_t m_curr_point;
	CBlock m_column_block[9];
	CBlock m_row_block[9];
	CBlock m_xy_block[3][3];
	point_value_t m_map[81];

	//保存前面的命令
	//实现撤销功能
	std::vector<CCommand> m_command;
};

#endif
