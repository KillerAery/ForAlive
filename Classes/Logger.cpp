#include "Logger.h"

using namespace cocos2d;

Logger* Logger::s_logger = nullptr;

void Logger::clean(){
	if (s_logger)s_logger = nullptr;
}

void Logger::log(const string & str) {
	if (!s_logger){ 
	s_logger = Logger::create();
	s_logger->setPosition(400,100);
	Director::getInstance()->getRunningScene()->addChild(s_logger);
	}

	for (auto otherwords : s_logger->getChildren()){
		auto pushUp = MoveBy::create(0.2f, cocos2d::Vec3(0, otherwords->getContentSize().height, 0));
		otherwords->runAction(pushUp);
	}

	auto addtionwords = Label::createWithSystemFont(str, "Arial", 25.0f);
	addtionwords->setPositionY(addtionwords->getContentSize().height / 2);
	addtionwords->setOpacity(0);//͸����Ϊ0
								//����Ķ���
	auto fadein = FadeIn::create(0.3f);
	auto pushUp = MoveBy::create(0.2f, cocos2d::Vec3(0, addtionwords->getContentSize().height, 0));
	auto spawn1 = Spawn::create(fadein, pushUp, nullptr);
	//�ӳ�һ�������Ķ���
	auto delaytime = CCDelayTime::create(addtionwords->getString().size()*0.2f);
	//�����Ķ���
	auto fadeout = FadeOut::create(1.0f);
	//��������
	auto dieoutFunc = CallFunc::create([addtionwords]() {addtionwords->removeFromParent(); });
	//4����������һ�����ж���
	auto sequence = Sequence::create(spawn1, delaytime, fadeout, dieoutFunc, nullptr);

	addtionwords->runAction(sequence);
	s_logger->addChild(addtionwords);
}