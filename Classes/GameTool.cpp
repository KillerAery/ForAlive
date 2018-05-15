#include "GameTool.h"
#include "AudioEngine.h"

using namespace cocos2d;
using namespace experimental;

GameTool::GameTool():m_EnviromentBGMID(0){}

bool GameTool::init() {
	if (!Node::init())return false;
	Node::onEnter();
	Node::onEnterTransitionDidFinish();
	return true;
}

void GameTool::fadePlayBGM(const string& str, float fadeTime) {
	playBGM(str);
	//一开始声音为0
	AudioEngine::setVolume(m_BGMlist.front(), 0.0f);
	//渐渐大声
	this->schedule([this, fadeTime](float dt) {
		for (auto ID : m_BGMlist)AudioEngine::setVolume(ID, AudioEngine::getVolume(ID) + 1.0f/60/fadeTime);
		if (AudioEngine::getVolume(m_BGMlist.front()) >= 1.0f)
			this->unschedule("fadePlay");
		}, "fadePlay");
}


void GameTool::setIfBGM(bool ret){
	UserDefault::getInstance()->setBoolForKey("IfBGM", ret);
	if (!ret) { for (auto BGMID : m_BGMlist)AudioEngine::pause(BGMID); }
	else { for (auto BGMID : m_BGMlist)AudioEngine::resume(BGMID); }
}


bool GameTool::getIfBGM(){
	return 	UserDefault::getInstance()->getBoolForKey("IfBGM");
}


void GameTool::setIfEffect(bool ret){
	UserDefault::getInstance()->setBoolForKey("IfEffect", ret);
}


bool GameTool::getIfEffect(){
	return 	UserDefault::getInstance()->getBoolForKey("IfEffect");
}


void GameTool::playBGM(const string& str){
	if(getIfBGM())m_BGMlist.push_back(AudioEngine::play2d(FileUtils::getInstance()->fullPathForFilename(str), true));
}


void GameTool::fadePlayBGMandCloseOtherBGM(const string& str,float fadeTime) {
	if (!getIfBGM())return;
	//如果有正在播放的BGM，渐渐关闭之
	if (!m_BGMlist.empty()) 
	{	//渐渐小声
		this->schedule([this, str, fadeTime](float dt) {
			for (auto ID : m_BGMlist)AudioEngine::setVolume(ID, AudioEngine::getVolume(ID) - 1.0f / 60/ fadeTime);
			if (AudioEngine::getVolume(m_BGMlist.front()) <= 0.0f) {
				clearBGM();
				GameTool::fadePlayBGM(str, fadeTime);
				this->unschedule("fadeClose");
			}}, "fadeClose");
	}
	else
	{
		fadePlayBGM(str, fadeTime);
	}
}

void GameTool::playEffect(const string& str,float voice){
	if (getIfEffect())AudioEngine::play2d(FileUtils::getInstance()->fullPathForFilename(str),false,voice);
}


void GameTool::clearBGM() {
	AudioEngine::stopAll();
	m_BGMlist.clear();
}

void GameTool::playEnviromentBGM(const string& str) {
	m_EnviromentBGMID = AudioEngine::play2d(FileUtils::getInstance()->fullPathForFilename(str),true);
}
void GameTool::stopEnviromentBGM() {
	AudioEngine::stop(m_EnviromentBGMID);
}