/*************************************************************************
    > File Name: scene.cpp
    > Author: 
    > Mail: 
    > Created Time: Tue 04 Mar 2025 01:56:04 PM CST
 ************************************************************************/

#include "scene.h"

//构造函数
CScene::CScene(int index) 
	: m_max_column(pow(index, 2)),
	  m_curr_point({0, 0})
{
	init();
}

//析构函数
CScene::~CScene()
{
	if (m_key_map)
	{
		delete m_key_map;
	}
}

//封装打印表格
//显示数独内容
void CScene::show() const
{
	cls();
	printUnderLine();

	for (int row = 0; row < m_max_column; ++row)
	{
		CBlock block = m_row_block[row];
		block.print();
		printUnderLine(row);
	}
}

//输出一排线条
void CScene::printUnderLine(int line_no) const
{
	auto is_currline = (m_curr_point.y == line_no);
	for (int column = 0; column < 9; ++column)
	{
		//边上或者九宫格分界输出红色+
		if ((column % 3) == 0 || line_no == -1 || ((line_no + 1) % 3) == 0) 
		{
			std::cout << Color::Modifier(Color::BOLD, Color::BG_DEFAULT, Color::FG_RED) << CORNER << Color::Modifier();
		} 
		else
		{
			std::cout << CORNER;
		}
		
		//显示当前指针位置 ^表示
		auto third_symbol = (is_currline && m_curr_point.x == column) ? ARROW : LINE;
		if (line_no == -1 || ((line_no + 1) % 3) == 0)
		{
			std::cout << Color::Modifier(Color::BOLD, Color::BG_DEFAULT, Color::FG_RED) << LINE << third_symbol << LINE << Color::Modifier();
		}
		else
		{
			std::cout << LINE << third_symbol << LINE;
		}
	}
	std::cout << Color::Modifier(Color::BOLD, Color::BG_DEFAULT, Color::FG_RED) << CORNER << Color::Modifier() << std::endl;
}

//初始化
void CScene::init()
{
	memset(m_map, UNSELECTED, sizeof(m_map));
	//给映射分配空间
	m_key_map = new KeyMap();

	int col = 0;
	int row = 0;
	//列
	for (col = 0; col < m_max_column; ++col)
	{
		CBlock column_block;
		for (row = 0; row < m_max_column; ++row)
		{
			column_block.push_back(m_map + row * m_max_column + col);
		}
		m_column_block[col] = column_block;
	}
	//行
	for (row = 0; row < m_max_column; ++row)
	{
		CBlock row_block;
		for (col = 0; col < m_max_column; ++col)
		{
			row_block.push_back(m_map + row * m_max_column + col);
		}
		m_row_block[row] = row_block;
	}
	//九宫格
	for (row = 0; row < m_max_column; ++row)
	{
		for (col = 0; col < m_max_column; ++col)
		{
			m_xy_block[row / 3][col / 3].push_back(m_map + row * m_max_column + col);
		}
	}
	return;
}

//输入或修改
bool CScene::setCurrValue(const int n_curr_value, int& n_last_value)
{
	auto point = m_map[m_curr_point.x + m_curr_point.y * 9];
	if (point.state == State::ERASED)
	{
		n_last_value = point.value;
		setValue(n_curr_value);
		return true;
	}
	else
	{
		return false;
	}
}

void CScene::setValue(const point_t& p, const int value)
{
	m_map[p.x + p.y * 9].value = value;
}

void CScene::setValue(const int value)
{
	auto p = m_curr_point;
	this->setValue(p, value);
}

//删除指定数量的值
//随机删除
void CScene::eraseRandomGrid(const int count)
{
	point_value_t p = {UNSELECTED, State::ERASED};
	std::vector<int> v(81);
	for (int i = 0; i < 81; ++i)
	{
		v[i] = i;
	}
	for (int i = 0; i < count; ++i) 
	{
		int r = random(0, v.size() - 1);
		m_map[v[r]] = p;
		v.erase(v.begin() + r);
	}
}

//判断是否完成数独
bool CScene::isComplete()
{
	for (size_t i = 0; i < 81; ++i)
	{
		if (m_map[i].value == UNSELECTED)
		{
			return false;
		}
	}
	for (int row = 0; row < 9; ++row)
	{
		for (int col = 0; col < 9; ++col)
		{
			if (!m_row_block[row].isValid() || !m_column_block[col].isValid() || !m_xy_block[row / 3][col / 3].isValid())
			{
				return false;
			}
		}
	}
	return true;
}

//保存
bool CScene::save(const char *filename) 
{
	auto filepath = std::filesystem::path(filename);
	if (std::filesystem::exists(filepath))
	{
		return false;
	}

	std::fstream fs;
	//已可读可写追加模式打开文件
	fs.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);
	//save m_map
	for (int i = 0; i < 81; ++i)
	{
		fs << m_map[i].value << ' ' << static_cast<int>(m_map[i].state) << std::endl;
	}
	//save m_curr_point
	fs << m_curr_point.x << ' ' << m_curr_point.y << std::endl;
	//save m_command
	fs << m_command.size() << std::endl;
	for (CCommand command : m_command)
	{
		point_t point = command.getPoint();
		fs << point.x << ' ' << point.y << ' '
		   << command.getPrevValue() << ' '
		   << command.getCurrValue() << std::endl;
	}
	fs.close();
	return true;
}

//加载
bool CScene::load(const char* filename)
{
	auto filepath = std::filesystem::path(filename);
	if (!std::filesystem::exists(filepath))
	{
		return false;
	}

	std::fstream fs;
	fs.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);
	//load m_map
	for (int i = 0; i < 81; ++i)
	{
		int tmp_state;
		fs >> m_map[i].value >> tmp_state;
		m_map[i].state = static_cast<State>(tmp_state); 
	}
	//load m_curr_point
	fs >> m_curr_point.x >> m_curr_point.y;
	//load m_command
	int command_size;
	fs >> command_size;
	for (int i = 0; i < command_size; ++i)
	{
		point_t point;
		int prev_value, curr_value;
		fs >> point.x >> point.y >> prev_value >> curr_value;
		m_command.emplace_back(this, point, prev_value, curr_value);
	}
	fs.close();
	return true;
}

//运行
//通过判断输入执行相应的操作
void CScene::play()
{
	//printf("play1\n");
	show();
	//printf("play2\n");

	char key = '\0';
	while (1)
	{
		//printf("play3\n");
	
		key = _getch();
		
		//printf("key = %c\n", key);
		//printf("play4\n");
		
		//输入数字
		if (key >= '0' && key <= '9')
		{
			CCommand o_command(this);
			//CCommand o_command();
			//设置数字
			if (!o_command.execute(key - '0'))
			{
				std::cout << "this number can't be modified." << std::endl; 
			}
			else
			{
				m_command.push_back(std::move(o_command));
				show();
				continue;
			}
		}
		//printf("play5\n");
		
		//退出
		//std::cout << m_key_map.ESC << std::endl;
		//if (key == m_key_map.ESC)
		if (key == m_key_map->ESC)
		{
			message(I18n::Instance().Get(I18n::Key::ASK_QUIT));
			std::string str_input;
			std::cin >> str_input;
			if (str_input[0] == 'y' || str_input[0] == 'Y')
			{
				message(I18n::Instance().Get(I18n::Key::ASK_SAVE));
				std::cin >> str_input;
				if (str_input[0] == 'y' || str_input[0] == 'Y')
				{
					do
					{
						message(I18n::Instance().Get(I18n::Key::ASK_SAVE_PATH));
						std::cin >> str_input;
						if (!save(str_input.c_str()))
						{
							message(I18n::Instance().Get(I18n::Key::FILE_EXIST_ERROR));
						}
						else 
						{
							break;
						}
					} while (true);
				} 
				exit(0);
			}
			else
			{
				message(I18n::Instance().Get(I18n::Key::CONTINUE));
			}
		}
		//撤销返回上一步
		//else if (key == m_key_map.U)
		else if (key == m_key_map->U)
		{
			if (m_command.empty())
			{
				message(I18n::Instance().Get(I18n::Key::UNDO_ERROR));
			}
			else
			{
				CCommand &o_command = m_command.back();
				m_command.pop_back();
				o_command.undo();
				show();
			}
		}
		//左移
		//else if (key == m_key_map.LEFT)
		else if (key == m_key_map->LEFT)
		{
			m_curr_point.x = (m_curr_point.x - 1) < 0 ? 0 : m_curr_point.x - 1;
			show();
		}
		//右移
		//else if (key == m_key_map.RIGHT)
		else if (key == m_key_map->RIGHT)
		{
			m_curr_point.x = (m_curr_point.x + 1) > 8 ? 8 : m_curr_point.x + 1;
			show();
		}
		//上
		//else if (key == m_key_map.UP)
		else if (key == m_key_map->UP)
		{
			m_curr_point.y = (m_curr_point.y - 1) < 0 ? 0 : m_curr_point.y - 1;
			show();
		}
		//下
		//else if (key == m_key_map.DOWN)
		else if (key == m_key_map->DOWN)
		{
			m_curr_point.y = (m_curr_point.y + 1) > 8 ? 8 : m_curr_point.y + 1;
			show();
		}
		//完成确认
		//else if (key == m_key_map.ENTER)
		else if (key == m_key_map->ENTER)
		{
			if (isComplete())
			{
				message(I18n::Instance().Get(I18n::Key::CONGRATULATION));
				getchar();
				exit(0);
			}
			else 
			{
				message(I18n::Instance().Get(I18n::Key::NOT_COMPLETE));
			}
		}
	}
}

//生成数独表
//先把左上到右下的3个九宫格随机赋予数字
//这三个九宫格不会相互影响 直接随机填入1-9就行
//剩下的空格依次填入
//出现冲突时返回上一步
void CScene::generate()
{
	std::vector<std::vector<int>> matrix;
	for (int i = 0; i < 9; ++i)
	{
		matrix.push_back(std::vector<int>(9, 0));
	}	

	//初始化 左上到右下的三个九宫格
	for (int num = 0; num < 3; ++num)
	{
		std::vector<int> unit = shuffle_unit();
		int start_index = num * 3;
		for (int i = start_index; i < start_index + 3; ++i)
		{
			for (int j = start_index; j < start_index + 3; ++j)
			{
				matrix[i][j] = unit.back();
				unit.pop_back();
			}
		}
	}

	//统计空格数量
	std::vector<std::tuple<int, int>> box_list;
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; ++j) 
		{
			if (matrix[i][j] == 0)
			{
				box_list.push_back(std::make_tuple(i, j));
			}
		}
	}

	//逐个填充空格
	std::map<std::string, std::vector<int>> available_num;
	int full_num = 0;
	int empty_num = box_list.size();
	while (full_num < empty_num)
	{
		std::tuple<int, int> position = box_list[full_num];
		int row = std::get<0>(position);
		int col = std::get<1>(position);
		std::vector<int> able_unit;
		std::string key = std::to_string(row) + "x" + std::to_string(col);
		//删除当前位置不能填入的数字
		if (available_num.find(key) == available_num.end())
		{
			//九宫格
			std::vector<int> able_unit = get_unit();
			for (int i = row / 3 * 3; i < row / 3 * 3 + 3; ++i)
			{
				for (int j = col / 3 * 3; j < col / 3 * 3 + 3; ++j)
				{
					//vector删除操作
					//先通过remove将指定数字移到末尾
					//remove返回不包含指定数字的末尾迭代器
					//再通过erase删除后面包含指定数字的空间
					able_unit.erase(std::remove(able_unit.begin(), able_unit.end(), matrix[i][j]), able_unit.end());
				}
			}
			//行
			for (int j = 0; j < 9; ++j) {
				able_unit.erase(std::remove(able_unit.begin(), able_unit.end(), matrix[row][j]), able_unit.end());
			}
			//列
			for (int i = 0; i < 9; ++i) {
				able_unit.erase(std::remove(able_unit.begin(), able_unit.end(), matrix[i][col]), able_unit.end());
			}
			available_num[key] = able_unit;
		}
		else
		{
			able_unit = available_num[key];
		}

		//返回上一步
		if (available_num[key].size() <= 0) 
		{
			full_num -= 1;
			if (available_num.find(key) != available_num.end())
			{
				available_num.erase(key);
			}
			matrix[row][col] = 0;
			continue;
		} 
		else 
		{
			matrix[row][col] = available_num[key].back();
			available_num[key].pop_back();
			full_num += 1;
		}
	}

	//填入场景
	for (int row = 0; row < 9; ++row)
	{
		for (int col = 0; col < 9; ++col)
		{
			point_t point = {row, col};
			setValue(point, matrix[row][col]);
		}
	}
	assert(isComplete());
	return;
}

bool CScene::setPointValue(const point_t& st_point, const int value)
{
	auto point = m_map[st_point.x + st_point.y * 9];
	if (State::ERASED == point.state)
	{
		m_curr_point = st_point;
		setValue(value);
		return true;
	}
	else {
		return false;
	}
}

point_t CScene::getCurrPoint()
{
	return m_curr_point;
}
