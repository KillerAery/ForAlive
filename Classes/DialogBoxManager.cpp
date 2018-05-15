#include "DialogBoxManager.h"
#include "GameManager.h"


USING_NS_CC;


DialogBoxManager::DialogBoxManager() :m_dialogBoxView{ nullptr, nullptr }, m_choicesView(nullptr){}

DialogBoxManager::~DialogBoxManager(){ 
	NotificationCenter::getInstance()->removeObserver(this, "DialogBox_Done");
}

bool DialogBoxManager::init() {
	//对话框完成一句话
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(DialogBoxManager::doneTalk), "DialogBox_Done", nullptr); 
	return true;
}

bool DialogBoxManager::requestTalk(Dialog& dialog){
	pauseGame();//暂停游戏
	
	m_dialog = dialog;

	doneTalk(nullptr);

	return true;
}

void DialogBoxManager::requestChoices(const Choices& choices) {
	if (!m_choicesView) {
		m_choicesView = ChoicesView::create();
		Director::getInstance()->getRunningScene()->addChild(m_choicesView);
	}
	m_choicesView->putChoices(choices);
	m_choicesView->showChoices();
}


void DialogBoxManager::doneTalk(Ref* r){
	//如果说完话了
	if (m_dialog.ifEmpty()){
		//如果没有选择
		if (!m_dialog.getChoices().size) {
			//结束对话，返回
			this->finishTalk(); return;
		}
		//开启选择
		this->requestChoices(m_dialog.getChoices());
		m_dialog.cleanOptions();
		return;
	}

	const Sentence & st = m_dialog.getFirstSentence();
	bool ifplayer = (st.id == GameManager::getInstance()->getPlayer()->getID());
	

	Biology* biology = GameManager::getInstance()->findBiology(st.id);
	auto name = biology->getName();
	auto photo = cocos2d::StringUtils::format("TouXiang/%d.png",st.id);

	if (!m_dialogBoxView[ifplayer]) {
		m_dialogBoxView[ifplayer] = DialogBoxView::create(photo , name , st.words, ifplayer);
		Director::getInstance()->getRunningScene()->addChild(m_dialogBoxView[ifplayer]);
	}
	else {
		m_dialogBoxView[ifplayer]->pushWords(st.words);
		m_dialogBoxView[ifplayer]->changeName(name);
	}

	m_dialog.popFirstSentence();
}

void DialogBoxManager::finishTalk() {

	for (int i = 0; i <= 1; i++)
		if (m_dialogBoxView[i]) {
			m_dialogBoxView[i]->removeFromParent();
			m_dialogBoxView[i] = nullptr;
		}

	if (m_choicesView)m_choicesView->removeFromParent();
	m_choicesView = nullptr;

	resumeGame();
}

void DialogBoxManager::pauseGame(){
	NotificationCenter::getInstance()->postNotification("PAUSEGAME",this);
	NotificationCenter::getInstance()->postNotification("MOUSE_SHIELD", this);
}

void DialogBoxManager::resumeGame() {
	NotificationCenter::getInstance()->postNotification("RESUMEGAME", this);
	NotificationCenter::getInstance()->postNotification("MOUSE_UNSHIELD", this);
}