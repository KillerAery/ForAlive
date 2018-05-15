#pragma once
#ifndef SpeakWords_h__
#define SpeakWords_h__

#include "cocos2d.h"

using cocos2d::Node;
using std::string;

class SpeakWords : public Node{
public:
	void pushAdditionWords(const string& words);			//说额外的话，原来的话语往上移动，新增话语
	CREATE_FUNC(SpeakWords);
};

#endif // SpeakWords_h__