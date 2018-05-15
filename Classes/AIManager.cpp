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
	//根节点
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
	dialog.pushSentence(Sentence(30, Expression::normal, (string(u8"谢谢你,先生"))));
	DialogBoxManager::getInstance()->setDialog(dialog);
	MissionManager::getInstance()->runMission(1);
}

void rejectMission1() {
	auto dialog = Dialog();
	dialog.pushSentence(Sentence(30, Expression::normal, (string(u8"好吧...."))));
	DialogBoxManager::getInstance()->setDialog(dialog);
}

//第一次主动找玩家讲话
void initFirstTalk(AI_Talk* firstTalk, AI_RootNode* root) {
	auto requestDialog = Dialog();
	requestDialog.pushSentence(Sentence(30, Expression::normal, (string(u8"陌生人，\n给你一个生意，你做不做？"))));
	requestDialog.pushOption(Option(u8"生意？", []() {
		auto dialog = Dialog();
		dialog.pushSentence(Sentence(30, Expression::normal, (string(u8"我的孩子生病了，\n需要医疗包里的抗生素"))));
		dialog.pushSentence(Sentence(30, Expression::normal, (string(u8"就在附近的仓库就有一个医疗包。\n我和你一起去拿。"))));

		dialog.pushOption(Option(u8"你怎么不自己去？", []() {
			auto dialog = Dialog();
			dialog.pushSentence(Sentence(30, Expression::normal, (string(u8"仓库里有些危险，我担心我一个人解决不了。\n"))));
			dialog.pushSentence(Sentence(30, Expression::normal, (string(u8"如果你能帮我找到，\n我会给你5个罐头作为报酬。"))));
			dialog.pushOption(Option(u8"不了，我还是不去了", []() {rejectMission1(); }, ChoiceColor::red));
			dialog.pushOption(Option(u8"好的，没问题", []() {aceptMission1(); }, ChoiceColor::green));
			DialogBoxManager::getInstance()->setDialog(dialog);
		}));
		dialog.pushOption(Option(u8"你怎么知道附近仓库有医疗包", []() {
			auto dialog = Dialog();
			dialog.pushSentence(Sentence(30, Expression::normal, (string(u8"呃...."))));
			dialog.pushSentence(Sentence(30, Expression::normal, (string(u8"一般来说仓库也许都有医疗包常备吧？..."))));
			dialog.pushSentence(Sentence(30, Expression::normal, (string(u8"再说了，如果你能帮我找到，\n我会给你5个罐头作为报酬。"))));
			dialog.pushOption(Option(u8"不了，我还是不去了", []() {rejectMission1(); }, ChoiceColor::red));
			dialog.pushOption(Option(u8"好吧", []() {aceptMission1(); }, ChoiceColor::green));
			DialogBoxManager::getInstance()->setDialog(dialog);
		}));
		dialog.pushOption(Option(u8"我可没空闲管这种事", []() {rejectMission1(); }, ChoiceColor::red));
		dialog.pushOption(Option(u8"好的", []() {aceptMission1(); }, ChoiceColor::green));
		DialogBoxManager::getInstance()->setDialog(dialog);
	}));
	requestDialog.pushOption(Option(u8"我可没空闲管这种事", []() {rejectMission1(); }, ChoiceColor::red));
	firstTalk->setDialog(requestDialog);
	firstTalk->setTarget(AI_Player::create());
}

//跟随玩家模式
void initFollowMode(AI_Parallel* parallel, AI_RootNode* root) {
	//接受了任务才执行
	parallel->setCondition([](Biology*) {return MissionManager::getInstance()->getAllMissions()[1].getStatus() == MissionStatus::running; });

	auto s1 = AI_Seletor::create();
	parallel->addChild(s1);

	auto speakToDaughter = AI_Speak::create(u8"乖宝贝，你先待在这里等我。好吗？");
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
	//第一次主动找玩家说话
	auto firstTalk = AI_Talk::create();
	initFirstTalk(firstTalk, root);
	parallel->addChild(firstTalk);
	//跟随玩家前往仓库模式
	auto followPlayerMode = AI_Parallel::create();
	initFollowMode(followPlayerMode,root);

	seletor->addChild(keepFrom);
	seletor->addChild(followPlayerMode);
	seletor->addChild(hover);

	auto talk2 = AI_Talk::create(true);
	auto dialog2 = Dialog();
	dialog2.pushOption(Option(u8"我找到了", [root,talk2]() {
		auto dialog = Dialog();
		dialog.pushSentence(Sentence(30, Expression::normal, (string(u8"谢谢你,先生"))));
		dialog.pushSentence(Sentence(30, Expression::normal, (string(u8"这是给你的回报，请收下"))));
		dialog.pushOption(Option(u8"确认", [root,talk2](){
			Logger::log(u8"你失去了1个便捷医疗包");
			Logger::log(u8"你获得了5个黄豆罐头和2个鸡肉");
			auto player = GameManager::getInstance()->getPlayer();
			player->moveItem(player->findItem(104),1,root->getNPC());
			player->addItem(105,2);
			player->addItem(101,5);
			talk2->removeFromParent();
			auto dialog = Dialog();
			dialog.pushSentence(Sentence(30, Expression::normal, (string(u8"还有一件事，虽然很抱歉。"))));
			dialog.pushSentence(Sentence(30, Expression::normal, (string(u8"但是你还是去死吧。"))));
			DialogBoxManager::getInstance()->setDialog(dialog);	
			//关系变敌对
			root->getNPC()->getRelationship()->addIndividualRelationship(33, Relation(40, Attitude::against));
		},ChoiceColor::green));
		DialogBoxManager::getInstance()->setDialog(dialog);
	}, ChoiceColor::green, []() {return GameManager::getInstance()->getPlayer()->findItem(104)?true:false;}));
	dialog2.pushOption(Option(u8"离开"));
	talk2->setDialog(dialog2);
	talk2->setTarget(AI_Player::create());
	parallel->addChild(talk2);

	return root;
}

AI_RootNode* AIManager::createGetOutAI() {
	auto root = AI_RootNode::create();
	auto talk = AI_Talk::create(true);
	auto dialog = Dialog();
	dialog.pushSentence(Sentence(33,Expression::normal,string(u8"要离开这个小镇吗？")));
	dialog.pushOption(Option(u8"确认离开", [](){
		Logger::log(u8"你活了下来，离开了这个小镇");
		EndingManager::getInstance()->intoAliveEnding();
	}));
	dialog.pushOption(Option(u8"暂时不离开"));
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
	auto speak2 = AI_Speak::create(u8"好吧.....            ");
	selector->addChild(speak2);
	speak2->setFinishFunc([speak2](Biology* master) {
		speak2->removeFromParent();
	});
}