#pragma once
#ifndef SpeakWords_h__
#define SpeakWords_h__

#include "cocos2d.h"

using cocos2d::Node;
using std::string;

class SpeakWords : public Node{
public:
	void pushAdditionWords(const string& words);			//˵����Ļ���ԭ���Ļ��������ƶ�����������
	CREATE_FUNC(SpeakWords);
};

#endif // SpeakWords_h__