#pragma once
#ifndef Dialog_h__
#define Dialog_h__

#include <functional>
#include "Biology.h"

using std::string;
using std::function;
using std::queue;

//一句话的表情
enum class Expression {normal , angry , happy };

//一句话：说话者+表情+内容
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

//选择文字的颜色
enum class ChoiceColor { white, green, red };

//一个选项，要满足condition，才允许点击，
//选项文字words 文字颜色color
//选完后执行choiceFunc
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

/*-----------------对话-----------------------------*/
//对话：N句话+1次选择(或者没有)
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