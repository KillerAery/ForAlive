#include "KaguyaHelper.h"

using namespace cocos2d;

bool KaguyaHelper::init() {

	registerDialogBoxLib(m_state);
	registerMissionLib(m_state);
	registerCocos2dxLib(m_state);
	registerAIBaseLib(m_state);
	registerAIBehavioerLib(m_state);



	loadLuaScrip("AI/test.lua");
	return true;
}

void KaguyaHelper::loadLuaScrip(const std::string& luafile) {
	auto str = cocos2d::FileUtils::getInstance()->fullPathForFilename(luafile);
	auto ret = m_state.dofile(str);
	if (ret)CCLOG("Kaguya OK!");

	m_state["CCLOG"] = kaguya::function([](int a) {CCLOG("--------------------------%d", a); });

	//kaguya::LuaFunction f1 = m_state.loadfile(str);
	//f1();
}

//注册cocos2dx库的部分类的部分接口
void KaguyaHelper::registerCocos2dxLib(kaguya::State & state) {
	state["Node"].setClass(kaguya::UserdataMetatable<Node>()
		.addStaticFunction("create", &Node::create)
		.addOverloadedFunctions("addChild"
			, static_cast<void(Node::*)(Node*)>(&Node::addChild)
			, static_cast<void(Node::*)(Node*, int)>(&Node::addChild)
			, static_cast<void(Node::*)(Node*, int, int)>(&Node::addChild)
			, static_cast<void(Node::*)(Node*, int, const std::string&)>(&Node::addChild))
		.addFunction("removeChild", &Node::removeChild)
		.addOverloadedFunctions("setPosition"
			, static_cast<void(Node::*)(const Vec2&)>(&Node::setPosition)
			, static_cast<void(Node::*)(float, float)>(&Node::setPosition))

		.addFunction("setColor", &Node::setColor)
		.addFunction("setOpacity", &Node::setOpacity)
		.addFunction("schedule", static_cast<void(Node::*)(const std::function<void(float)>&, float, const std::string &)>(&Node::schedule))
	);
}
//注册AI的基础节点类的部分接口
void KaguyaHelper::registerAIBaseLib(kaguya::State & state) {
	state["BaseNode"].setClass(kaguya::UserdataMetatable<AI_BaseNode, Node>()

	);
	state["BehaviorNode"].setClass(kaguya::UserdataMetatable<AI_BehaviorNode, AI_BaseNode>()
	);

	state["RootNode"].setClass(kaguya::UserdataMetatable<AI_RootNode, AI_BaseNode>()
		.addStaticFunction("create", &AI_RootNode::create)
		.addFunction("run", &AI_RootNode::run)
	);
	state["Parallel"].setClass(kaguya::UserdataMetatable<AI_Parallel, AI_BaseNode>()
		.addStaticFunction("create", &AI_Parallel::create)
	);
	state["Seletor"].setClass(kaguya::UserdataMetatable<AI_Seletor, AI_BaseNode>()
		.addStaticFunction("create", &AI_Seletor::create)
	);
	state["AIManager"].setClass(kaguya::UserdataMetatable<AIManager>()
		.addStaticFunction("getInstance", &AIManager::getInstance)
		.addFunction("bindAIonNPC", static_cast<void(AIManager::*)(AI_RootNode*, int)>(&AIManager::bindAIonNPC))
		.addFunction("createHumanAI", &AIManager::createHummanAI)
		.addFunction("createGetOutAI",&AIManager::createGetOutAI)
		.addFunction("addDaugtherAIwhenAcceptMission1",&AIManager::addDaugtherAIwhenAcceptMission1)
	);



}

//注册AI的行为节点类的部分接口
void KaguyaHelper::registerAIBehavioerLib(kaguya::State & state) {

	state["Attack"].setClass(kaguya::UserdataMetatable<AI_Attack, AI_BehaviorNode>()
		.addStaticFunction("create", &AI_Attack::create)
	);

	state["Hover"].setClass(kaguya::UserdataMetatable<AI_Hover, AI_BehaviorNode>()
		.addStaticFunction("create", &AI_Hover::create)
	);
	state["KeepFrom"].setClass(kaguya::UserdataMetatable<AI_KeepFrom, AI_BehaviorNode>()
		.addStaticFunction("create", &AI_KeepFrom::create)
		.addFunction("setTarget", &AI_KeepFrom::setTarget)
		.addFunction("setKeepDistance",&AI_KeepFrom::setKeepDistance)
	);
	state["EscapeFrom"].setClass(kaguya::UserdataMetatable<AI_EscapeFrom, AI_BehaviorNode>()
		.addStaticFunction("create", &AI_EscapeFrom::create)
		.addFunction("setTarget", &AI_EscapeFrom::setTarget)
	);
	state["Talk"].setClass(kaguya::UserdataMetatable<AI_Talk, AI_BehaviorNode>()
		.addStaticFunction("create", &AI_Talk::create)
		.addFunction("setTarget", &AI_Talk::setTarget)
		.addFunction("setDialog", &AI_Talk::setDialog)
	);

	state["Speak"].setClass(kaguya::UserdataMetatable<AI_Speak, AI_BehaviorNode>()
		.addStaticFunction("create", &AI_Speak::create)
	);

	state["Target"].setClass(kaguya::UserdataMetatable<AI_Target>()
		.addStaticFunction("create", static_cast<AI_Target::Target (*)(int)>(&AI_Target::create))
		.addFunction("setTargetID", &AI_Nearest::setTargetID)
	);

	state["Nearest"].setClass(kaguya::UserdataMetatable<AI_Nearest, AI_Target>()
		.addStaticFunction("create", static_cast<AI_Nearest::Target(*)(int)>(&AI_Nearest::create))
		.addFunction("setTargetAttitude", &AI_Nearest::setTargetAttitude)
	);


}

//注册对话框的部分接口
void KaguyaHelper::registerDialogBoxLib(kaguya::State & state) {
	state["Dialog"].setClass(kaguya::UserdataMetatable<Dialog>()
		.setConstructors<Dialog()>()
		.addFunction("pushSentence", &Dialog::pushSentence)
		.addFunction("pushOption", &Dialog::pushOption)
	);
	state["Sentence"].setClass(kaguya::UserdataMetatable<Sentence>()
		.setConstructors<Sentence(int, int, const string&)>()
	);
	state["Option"].setClass(kaguya::UserdataMetatable<Option>()
		.setConstructors<Option(const string&, string, int, string)>()
	);

	state["DialogBoxManager"].setClass(kaguya::UserdataMetatable<DialogBoxManager>()
		.addStaticFunction("getInstance", &DialogBoxManager::getInstance)
		.addFunction("setDialog", &DialogBoxManager::setDialog)
	);

}
//注册任务的部分接口
void KaguyaHelper::registerMissionLib(kaguya::State & state) {
	state["MissionManager"].setClass(kaguya::UserdataMetatable<MissionManager>()
		.addStaticFunction("getInstance", &MissionManager::getInstance)
		.addFunction("runMission", &MissionManager::runMission)
	);
}