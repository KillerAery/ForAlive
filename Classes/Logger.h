#pragma once
#ifndef Logger_h__
#define Logger_h__

#include "cocos2d.h"

using cocos2d::Label;
using std::string;
using cocos2d::StringUtils::format;

class Logger : public cocos2d::Node{
	static Logger* s_logger;
	CREATE_FUNC(Logger);
public:
	static void log(const string & str);
	static void clean();
};


#endif // Logger_h__