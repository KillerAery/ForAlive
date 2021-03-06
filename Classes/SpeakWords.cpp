#include "SpeakWords.h"

using namespace cocos2d;

void SpeakWords::pushAdditionWords(const string& words){

	for (auto otherwords : getChildren()) {
		auto pushUp = MoveBy::create(0.2f, cocos2d::Vec3(0, otherwords->getContentSize().height, 0));
		otherwords->runAction(pushUp);
	}

	auto addtionwords = Label::createWithSystemFont(words, "Arial", 25.0f);
	addtionwords->setPositionY(addtionwords->getContentSize().height*1.5);
	addtionwords->setOpacity(0);//透明度为0
	//渐入的动作
	auto fadein = FadeIn::create(0.3f);
	auto pushUp = MoveBy::create(0.2f, cocos2d::Vec3(0, addtionwords->getContentSize().height, 0));
	auto spawn1 = Spawn::create(fadein, pushUp,nullptr);
	//延迟一定秒数的动作
	auto delaytime = CCDelayTime::create(addtionwords->getString().size()*0.2f);
	//淡出的动作
	auto fadeout = FadeOut::create(1.0f);
	//死亡动作
	auto dieoutFunc = CallFunc::create([addtionwords]() {addtionwords->removeFromParent();});
	//4个动作做成一个队列动作
	auto sequence = Sequence::create(spawn1, delaytime, fadeout,dieoutFunc,nullptr);

	addtionwords->runAction(sequence);
	this->addChild(addtionwords);
}