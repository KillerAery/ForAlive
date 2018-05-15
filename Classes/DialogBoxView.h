#pragma once
#ifndef DialogBoxView_h__
#define DialogBoxView_h__

#include "cocos2d.h"
#include "DialogBoxUITemlate.h"

using std::string;
using cocos2d::ui::Text;
using cocos2d::Sprite;

class DialogBoxView : public Layout{
protected:
	CC_SYNTHESIZE(Layout*, m_dialogBoxLayout, DialogBoxLayout);	//对话框层
	CC_SYNTHESIZE(Layout*, m_photoLayout, PhotoLayout);			//头像layout（提供位置）
	CC_SYNTHESIZE(Sprite*, m_photo, Photo);						//头像
	CC_SYNTHESIZE(Text*, m_nameText,NameText);					//对话框名字
	CC_SYNTHESIZE(Text*, m_wordsText,WordsText);				//对话框文字

	CC_SYNTHESIZE(int, m_index, Index);							//对话框文字i指标
	CC_SYNTHESIZE_PASS_BY_REF(string, m_text, Text);			//对话框文字字符串

	CC_SYNTHESIZE(bool, m_ifShowAll, IfShowAll);				//是否显示完所有字符
	CC_SYNTHESIZE(bool, m_ifDone, IfDone);						//是否结束

public:
	DialogBoxView();
	static DialogBoxView* create(const string& photoFilePath,const string& name,const string& words,bool ifIsMyDialog);
	bool init(const string& photoFilePath, const string& name, const string& words, bool ifIsMyDialog);
	void initName(const string& name);
	void initPhoto(const string& photoFilePath);
	void initWords(const string& words);

	void initTouchListener();						//点击对话框，可快速跳过对话动画效果
	
	void changePhoto(const string& photoFilePath);	//改变头像（一般用作表情变化）
	void changeName(const string& name);			//改变名字
	void pushWords(const string& words);			//继续显示新的对话内容
	void makeWordsEffects(const string& words);		//对话动画特效
	void finishWordsEffect();						//结束动画特效
};




#endif // DialogBoxView_h__