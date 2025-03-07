/*************************************************************************
    > File Name: main.cpp
    > Author: 
    > Mail: 
    > Created Time: Sun 02 Mar 2025 07:48:51 PM CST
 ************************************************************************/

#include "./common/common.h"
#include "./scene/scene.h"
#include "./i18n/i18n.h"
#include "./utility/utility.inl"
#include "./input/input.h"

int main(int argc, char* argv[]) {
	CScene scene;

	//直接运行开始新游戏	./sudu
	if (argc == 1) 
	{
		InputLanguage();
		int erase_grids_number = inputDifficulty();
		scene.generate();
		scene.eraseRandomGrid(erase_grids_number);
	}
	//加载游戏	./sudu	-l path
	else if (argc == 3 && !strcmp(argv[1], "-l"))
	{
		//load saved game progress
		if (!scene.load(argv[2]))
		{
			message(I18n::Instance().Get(I18n::Key::LOAD_PROGRESS_FAIL));
			return 0;
		}
		InputLanguage();
	} 
	else 
	{
		return 0;
	}
	scene.play();
	return 0;
}
