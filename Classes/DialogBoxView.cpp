#include "DialogBoxView.h"

using namespace cocos2d;

DialogBoxView::DialogBoxView():m_dialogBoxLayout(nullptr),m_wordsText(nullptr),m_photo(nullptr),m_ifDone(true),m_ifShowAll(true),m_index(0),m_text(string()),m_photoLayout(nullptr),m_nameText(nullptr){}

DialogBoxView* DialogBoxView::create(const string& photoFilePath, const string& name, const string& words, bool ifIsMyDialog) {
	auto dialogboxView = new (std::nothrow)DialogBoxView();
	if (dialogboxView &&dialogboxView->init(photoFilePath, name, words, ifIsMyDialog)) { dialogboxView->autorelease(); }
	else CC_SAFE_DELETE(dialogboxView);
	return dialogboxView;
}
bool DialogBoxView::init(const string& photoFilePath, const string& name, const string& words, bool ifIsMyDialog) {
	if (!Layout::init())return false;

	//�����Ƿ��Լ��ĶԻ��� ��ѡ��Ի���ģ��
	if(ifIsMyDialog)m_dialogBoxLayout = DialogBoxUITemlate::getInstance()->getBasicMyDialogUI();
	else m_dialogBoxLayout = DialogBoxUITemlate::getInstance()->getBasicOtherDialogUI();

	this->addChild(m_dialogBoxLayout);

	initName(name);
	initPhoto(photoFilePath);
	initWords(words);
	initTouchListener();

	return true;
}
void DialogBoxView::initName(const string& name) {
	m_nameText = static_cast<Text*>(m_dialogBoxLayout->getChildByName("Name"));
	m_nameText->setText(name+":");
}
void DialogBoxView::initPhoto(const string& photoFilePath) {
	m_photoLayout = static_cast<Layout*>(m_dialogBoxLayout->getChildByName("PhotoLayout"));
	m_photo = Sprite::create(photoFilePath);
	m_photoLayout->addChild(m_photo);
}
void DialogBoxView::initWords(const string& words) {
	m_wordsText = static_cast<Text*>(m_dialogBoxLayout->getChildByName("Words"));

	makeWordsEffects(words);
}

//����Ի��򣬿ɿ��������Ի�����Ч��
void DialogBoxView::initTouchListener(){
	auto listener = EventListenerTouchOneByOne::create();
	//�Ƿ���û�¼������¼�
	listener->setSwallowTouches(true);
	//ItemPage������ʼ�¼�
	listener->onTouchBegan = [](Touch* touch, Event* event){
		auto dialogBoxNode = static_cast<Layout*>(event->getCurrentTarget());
		//���Ŀ�����Χ
		auto rect = Rect(0,0, dialogBoxNode->getContentSize().width, dialogBoxNode->getContentSize().height);
		//��ȡ������
		auto touchpoint = dialogBoxNode->convertToNodeSpace(touch->getLocation());
		//������Ŀ�����Χ�ڣ�����Ӧ
		if (!rect.containsPoint(touchpoint))return false;
		return true;
	};
	//ItemPage�����ɿ��¼�
	listener->onTouchEnded = [this](Touch* touch, Event* event){
		if (!m_ifShowAll) {
			this->finishWordsEffect();
		}
		else if(!m_ifDone){
			m_ifDone = true;
			NotificationCenter::getInstance()->postNotification("DialogBox_Done",this);
		}
	};
	//�󶨴��������NODE��
	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,m_dialogBoxLayout);
}

//�ı�ͷ��һ����������仯��
void DialogBoxView::changePhoto(const string& photoFilePath) {
	m_photo->setTexture(photoFilePath);
}
//�ı�����
void DialogBoxView::changeName(const string& name) {
	m_nameText->setText(name+":");
}

//������ʾ�µ�˵������
void DialogBoxView::pushWords(const string& words){
	makeWordsEffects(words);
}

//�Ի�������Ч
void DialogBoxView::makeWordsEffects(const string& words){
	if (!m_wordsText)return;
	if (!m_ifShowAll)finishWordsEffect();

	m_ifDone = false;
	m_ifShowAll = false;
	m_text = words;
	this->schedule([this](float dt){
		m_index += 1;
		m_wordsText->setText(string(m_text.begin(), m_text.begin() + m_index));
		if (m_index >= m_text.size())  this->finishWordsEffect(); 
	},0.05f,"DialogBoxView_Effect");
}

//����������Ч
void DialogBoxView::finishWordsEffect(){
	m_wordsText->setText(m_text);

	m_index = 0;
	m_ifShowAll = true;
	this->unschedule("DialogBoxView_Effect");
}
