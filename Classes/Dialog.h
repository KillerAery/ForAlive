#pragma once
#ifndef Dialog_h__
#define Dialog_h__

#include <functional>
#include "Biology.h"

using std::string;
using std::function;
using std::queue;

//һ�仰�ı���
enum class Expression {normal , angry , happy };

//һ�仰��˵����+����+����
struct Sentence{
	int id;
	Expression expression;
	string words;
public:
	Sentence(int _id, int _expression, string& _words) {
		id = _id;
		expression = Expression(_expression);
		words = _words;
	}
	Sentence(int _id, Expression _expression,string& _words){
		id = _id;
		expression = _expression;
		words = _words;
	}
};

//ѡ�����ֵ���ɫ
enum class ChoiceColor { white, green, red };

//һ��ѡ�Ҫ����condition������������
//ѡ������words ������ɫcolor
//ѡ���ִ��choiceFunc
struct Option
{
	function<bool()> m_condition;
	string m_words;
	ChoiceColor m_color;
	function<void()> m_choiceFunc;
	Option(const string& words = "ERROR", function<void()> func = [](){}, ChoiceColor color = ChoiceColor::white, function<bool()> condition = []() {return true; })
		:m_condition(condition), m_words(words), m_color(color), m_choiceFunc(func) {}

	Option(const string& words,string funcName, int color,string conditionName = string());
};

struct Choices{
	Option option[4];
	int size;
	void pushOption(Option& _option) {
		option[size] = _option;
		size++;
	}
	Choices() :size(0){}
};

/*-----------------�Ի�-----------------------------*/
//�Ի���N�仰+1��ѡ��(����û��)
class Dialog{
protected:
	queue<Sentence> m_sentences;
	Choices m_choice;
public:
	Dialog();
	void pushSentence(Sentence& sentence);
	void pushOption(Option& option);
	bool ifEmpty();
	const Sentence& getFirstSentence();
	const Choices& getChoices();
	void popFirstSentence();
	void cleanOptions();

};


#endif // Dialog_h__