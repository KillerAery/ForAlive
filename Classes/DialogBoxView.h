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
	CC_SYNTHESIZE(Layout*, m_dialogBoxLayout, DialogBoxLayout);	//�Ի����
	CC_SYNTHESIZE(Layout*, m_photoLayout, PhotoLayout);			//ͷ��layout���ṩλ�ã�
	CC_SYNTHESIZE(Sprite*, m_photo, Photo);						//ͷ��
	CC_SYNTHESIZE(Text*, m_nameText,NameText);					//�Ի�������
	CC_SYNTHESIZE(Text*, m_wordsText,WordsText);				//�Ի�������

	CC_SYNTHESIZE(int, m_index, Index);							//�Ի�������iָ��
	CC_SYNTHESIZE_PASS_BY_REF(string, m_text, Text);			//�Ի��������ַ���

	CC_SYNTHESIZE(bool, m_ifShowAll, IfShowAll);				//�Ƿ���ʾ�������ַ�
	CC_SYNTHESIZE(bool, m_ifDone, IfDone);						//�Ƿ����

public:
	DialogBoxView();
	static DialogBoxView* create(const string& photoFilePath,const string& name,const string& words,bool ifIsMyDialog);
	bool init(const string& photoFilePath, const string& name, const string& words, bool ifIsMyDialog);
	void initName(const string& name);
	void initPhoto(const string& photoFilePath);
	void initWords(const string& words);

	void initTouchListener();						//����Ի��򣬿ɿ��������Ի�����Ч��
	
	void changePhoto(const string& photoFilePath);	//�ı�ͷ��һ����������仯��
	void changeName(const string& name);			//�ı�����
	void pushWords(const string& words);			//������ʾ�µĶԻ�����
	void makeWordsEffects(const string& words);		//�Ի�������Ч
	void finishWordsEffect();						//����������Ч
};




#endif // DialogBoxView_h__