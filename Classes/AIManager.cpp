#include "AIManager.h"
#include "DialogBoxManager.h"
#include "MissionManager.h"
#include "EndingManager.h"
#include "Logger.h"

AIManager::AIManager(){}


bool AIManager::init() { 
	return true; 
}


void AIManager::bindAIonNPC(AI_RootNode* root, NPC* npc) {
	CCASSERT(root&&npc, "AIManager receive a nullptr rootnode or npc!!!");
	npc->addChild(root);
	root->run(npc);
}

void AIManager::bindAIonNPC(AI_RootNode* root, int id) {
	auto npc = static_cast<NPC*>(GameManager::getInstance()->findBiology(id));
	CCASSERT(npc, "AIManager receive a unexist biology ID");
	bindAIonNPC(root, npc);
}

AI_RootNode* AIManager::createZombieAI() {
	//���ڵ�
	auto root = AI_RootNode::create();

	auto seletor = AI_Seletor::create();

	root->addChild(seletor);

	auto p1 = AI_Parallel::create();
	p1->setCondition([](NPC* master) {return !master->getPerception()->getNearest(Attitude::against);});
	auto emmmm = AI_Speak::create("em....");
	auto hover = AI_Hover::create();
	p1->addChild(emmmm);
	p1->addChild(hover);


	auto p2 = AI_Parallel::create();
	auto raaaa = AI_Speak::create("raaaaa!");
	auto catchTo = AI_CatchTo::create();
	catchTo->setTarget(AI_Nearest::create(Attitude::against));
	auto attack = AI_Attack::create();
	p2->addChild(raaaa);
	p2->addChild(catchTo);
	p2->addChild(attack);


	seletor->addChild(p1);
	seletor->addChild(p2);

	return root;
}

void aceptMission1() {
	auto dialog = Dialog();
	dialog.pushSentence(Sentence(30, Expression::normal, (string(u8"лл��,����"))));
	DialogBoxManager::getInstance()->setDialog(dialog);
	MissionManager::getInstance()->runMission(1);
}

void rejectMission1() {
	auto dialog = Dialog();
	dialog.pushSentence(Sentence(30, Expression::normal, (string(u8"�ð�...."))));
	DialogBoxManager::getInstance()->setDialog(dialog);
}

//��һ����������ҽ���
void initFirstTalk(AI_Talk* firstTalk, AI_RootNode* root) {
	auto requestDialog = Dialog();
	requestDialog.pushSentence(Sentence(30, Expression::normal, (string(u8"İ���ˣ�\n����һ�����⣬����������"))));
	requestDialog.pushOption(Option(u8"���⣿", []() {
		auto dialog = Dialog();
		dialog.pushSentence(Sentence(30, Expression::normal, (string(u8"�ҵĺ��������ˣ�\n��Ҫҽ�ư���Ŀ�����"))));
		dialog.pushSentence(Sentence(30, Expression::normal, (string(u8"���ڸ����Ĳֿ����һ��ҽ�ư���\n�Һ���һ��ȥ�á�"))));

		dialog.pushOption(Option(u8"����ô���Լ�ȥ��", []() {
			auto dialog = Dialog();
			dialog.pushSentence(Sentence(30, Expression::normal, (string(u8"�ֿ�����ЩΣ�գ��ҵ�����һ���˽�����ˡ�\n"))));
			dialog.pushSentence(Sentence(30, Expression::normal, (string(u8"������ܰ����ҵ���\n�һ����5����ͷ��Ϊ���ꡣ"))));
			dialog.pushOption(Option(u8"���ˣ��һ��ǲ�ȥ��", []() {rejectMission1(); }, ChoiceColor::red));
			dialog.pushOption(Option(u8"�õģ�û����", []() {aceptMission1(); }, ChoiceColor::green));
			DialogBoxManager::getInstance()->setDialog(dialog);
		}));
		dialog.pushOption(Option(u8"����ô֪�������ֿ���ҽ�ư�", []() {
			auto dialog = Dialog();
			dialog.pushSentence(Sentence(30, Expression::normal, (string(u8"��...."))));
			dialog.pushSentence(Sentence(30, Expression::normal, (string(u8"һ����˵�ֿ�Ҳ����ҽ�ư������ɣ�..."))));
			dialog.pushSentence(Sentence(30, Expression::normal, (string(u8"��˵�ˣ�������ܰ����ҵ���\n�һ����5����ͷ��Ϊ���ꡣ"))));
			dialog.pushOption(Option(u8"���ˣ��һ��ǲ�ȥ��", []() {rejectMission1(); }, ChoiceColor::red));
			dialog.pushOption(Option(u8"�ð�", []() {aceptMission1(); }, ChoiceColor::green));
			DialogBoxManager::getInstance()->setDialog(dialog);
		}));
		dialog.pushOption(Option(u8"�ҿ�û���й�������", []() {rejectMission1(); }, ChoiceColor::red));
		dialog.pushOption(Option(u8"�õ�", []() {aceptMission1(); }, ChoiceColor::green));
		DialogBoxManager::getInstance()->setDialog(dialog);
	}));
	requestDialog.pushOption(Option(u8"�ҿ�û���й�������", []() {rejectMission1(); }, ChoiceColor::red));
	firstTalk->setDialog(requestDialog);
	firstTalk->setTarget(AI_Player::create());
}

//�������ģʽ
void initFollowMode(AI_Parallel* parallel, AI_RootNode* root) {
	//�����������ִ��
	parallel->setCondition([](Biology*) {return MissionManager::getInstance()->getAllMissions()[1].getStatus() == MissionStatus::running; });

	auto s1 = AI_Seletor::create();
	parallel->addChild(s1);

	auto speakToDaughter = AI_Speak::create(u8"�Ա��������ȴ���������ҡ�����");
	speakToDaughter->setFinishFunc([speakToDaughter](Biology* biology){
		speakToDaughter->removeFromParent();
	});

	s1->addChild(speakToDaughter);

	auto follow = AI_KeepFrom::create();
	follow->setKeepDistance(100);
	follow->setTarget(AI_Player::create());
	s1->addChild(follow);

}

AI_RootNode* AIManager::createHummanAI(){
	auto root = AI_RootNode::create();

	auto seletor = AI_Seletor::create();

	auto parallel = AI_Parallel::create();

	auto hover = AI_Hover::create();
	auto attack = AI_Attack::create();
	auto keepFrom = AI_KeepFrom::create();
	keepFrom->setKeepDistance(50);
	keepFrom->setTarget(AI_Nearest::create(Attitude::against));

	root->addChild(parallel);
	parallel->addChild(attack);
	parallel->addChild(seletor);
	//��һ�����������˵��
	auto firstTalk = AI_Talk::create();
	initFirstTalk(firstTalk, root);
	parallel->addChild(firstTalk);
	//�������ǰ���ֿ�ģʽ
	auto followPlayerMode = AI_Parallel::create();
	initFollowMode(followPlayerMode,root);

	seletor->addChild(keepFrom);
	seletor->addChild(followPlayerMode);
	seletor->addChild(hover);

	auto talk2 = AI_Talk::create(true);
	auto dialog2 = Dialog();
	dialog2.pushOption(Option(u8"���ҵ���", [root,talk2]() {
		auto dialog = Dialog();
		dialog.pushSentence(Sentence(30, Expression::normal, (string(u8"лл��,����"))));
		dialog.pushSentence(Sentence(30, Expression::normal, (string(u8"���Ǹ���Ļر���������"))));
		dialog.pushOption(Option(u8"ȷ��", [root,talk2](){
			Logger::log(u8"��ʧȥ��1�����ҽ�ư�");
			Logger::log(u8"������5���ƶ���ͷ��2������");
			auto player = GameManager::getInstance()->getPlayer();
			player->moveItem(player->findItem(104),1,root->getNPC());
			player->addItem(105,2);
			player->addItem(101,5);
			talk2->removeFromParent();
			auto dialog = Dialog();
			dialog.pushSentence(Sentence(30, Expression::normal, (string(u8"����һ���£���Ȼ�ܱ�Ǹ��"))));
			dialog.pushSentence(Sentence(30, Expression::normal, (string(u8"�����㻹��ȥ���ɡ�"))));
			DialogBoxManager::getInstance()->setDialog(dialog);	
			//��ϵ��ж�
			root->getNPC()->getRelationship()->addIndividualRelationship(33, Relation(40, Attitude::against));
		},ChoiceColor::green));
		DialogBoxManager::getInstance()->setDialog(dialog);
	}, ChoiceColor::green, []() {return GameManager::getInstance()->getPlayer()->findItem(104)?true:false;}));
	dialog2.pushOption(Option(u8"�뿪"));
	talk2->setDialog(dialog2);
	talk2->setTarget(AI_Player::create());
	parallel->addChild(talk2);

	return root;
}

AI_RootNode* AIManager::createGetOutAI() {
	auto root = AI_RootNode::create();
	auto talk = AI_Talk::create(true);
	auto dialog = Dialog();
	dialog.pushSentence(Sentence(33,Expression::normal,string(u8"Ҫ�뿪���С����")));
	dialog.pushOption(Option(u8"ȷ���뿪", [](){
		Logger::log(u8"������������뿪�����С��");
		EndingManager::getInstance()->intoAliveEnding();
	}));
	dialog.pushOption(Option(u8"��ʱ���뿪"));
	talk->setDialog(dialog);
	talk->setTarget(AI_Player::create());
	root->addChild(talk);
	return root;
}

void AIManager::addDaugtherAIwhenAcceptMission1(AI_RootNode* root) {
	auto p0 = static_cast<AI_Parallel*>(root->getChildren().at(0)->getChildren().at(1));
	p0->setCondition([](Biology* master){return MissionManager::getInstance()->getAllMissions()[1].getStatus() == MissionStatus::running; });
	auto selector = AI_Seletor::create();
	p0->addChild(selector);
	auto speak1 = AI_Speak::create("               ");
	speak1->setFinishFunc([speak1,root](Biology* master) {
		auto followMode = root->getChildren().at(0)->getChildren().at(2)->getChildren().at(1);
		followMode->removeFromParent();
		speak1->removeFromParent();
	});
	selector->addChild(speak1);
	auto speak2 = AI_Speak::create(u8"�ð�.....            ");
	selector->addChild(speak2);
	speak2->setFinishFunc([speak2](Biology* master) {
		speak2->removeFromParent();
	});
}