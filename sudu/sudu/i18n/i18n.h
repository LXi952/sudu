/*************************************************************************
    > File Name: i18n.h
    > Author: 
    > Mail: 
    > Created Time: Tue 04 Mar 2025 04:36:21 PM CST
 ************************************************************************/

#ifndef I18N_H
#define I18N_H

#include "../common/common.h"

//语言
enum class Language : uint32_t 
{
	ENGLISH,
	CHINESE,
	MAX
};

//映射
class I18n
{
public:
	//关键字
	enum class Key 
	{
		ASK_KEY_MAP,
		INPUT_ERROR,
		LOAD_PROGRESS_FAIL,
		ASK_QUIT,
		ASK_SAVE,
		ASK_SAVE_PATH,
		FILE_EXIST_ERROR,
		CONTINUE,
		UNDO_ERROR,
		CONGRATULATION,
		NOT_COMPLETE,
		ASK_DIFFICULTY
	};
	using Dict = std::map<Key, std::string>;

	static I18n& Instance();
	void SetLanguage(Language);
	std::string Get(Key) const;

private:
	I18n();

	Dict* m_dict;
};


#endif
