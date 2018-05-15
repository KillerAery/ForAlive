#include "SpeakWords.h"

using namespace cocos2d;

void SpeakWords::pushAdditionWords(const string& words){

	for (auto otherwords : getChildren()) {
		auto pushUp = MoveBy::create(0.2f, cocos2d::Vec3(0, otherwords->getContentSize().height, 0));
		otherwords->runAction(pushUp);
	}

	auto addtionwords = Label::createWithSystemFont(words, "Arial", 25.0f);
	addtionwords->setPositionY(addtionwords->getContentSize().height*1.5);
	addtionwords->setOpacity(0);//͸����Ϊ0
	//����Ķ���
	auto fadein = FadeIn::create(0.3f);
	auto pushUp = MoveBy::create(0.2f, cocos2d::Vec3(0, addtionwords->getContentSize().height, 0));
	auto spawn1 = Spawn::create(fadein, pushUp,nullptr);
	//�ӳ�һ�������Ķ���
	auto delaytime = CCDelayTime::create(addtionwords->getString().size()*0.2f);
	//�����Ķ���
	auto fadeout = FadeOut::create(1.0f);
	//��������
	auto dieoutFunc = CallFunc::create([addtionwords]() {addtionwords->removeFromParent();});
	//4����������һ�����ж���
	auto sequence = Sequence::create(spawn1, delaytime, fadeout,dieoutFunc,nullptr);

	addtionwords->runAction(sequence);
	this->addChild(addtionwords);
}