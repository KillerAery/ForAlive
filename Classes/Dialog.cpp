#include "Dialog.h"
#include "KaguyaHelper.h"

Option::Option(const string& words,string funcName, int color,string conditionName)
	:m_words(words), m_color((ChoiceColor)color)
	,m_choiceFunc([funcName](){
	KaguyaHelper::getInstance()->getState()[funcName].call<void>();
})
	, m_condition([conditionName]() {
		if(conditionName.empty())return true;
		return KaguyaHelper::getInstance()->getState()[conditionName].call<bool>();
		return true;
	})
	{}

Dialog::Dialog() :m_sentences{} {}

void Dialog::pushSentence(Sentence& sentence) {
	m_sentences.push(sentence);
}
void Dialog::pushOption(Option& option) {
	m_choice.pushOption(option);
}
bool Dialog::ifEmpty() {
	return m_sentences.empty();
}
const Sentence& Dialog::getFirstSentence(){
	return m_sentences.front();
}
const Choices& Dialog::getChoices(){
	return m_choice;
}
void Dialog::popFirstSentence() {
	m_sentences.pop();
}

void Dialog::cleanOptions() {
	m_choice.size = 0;
}