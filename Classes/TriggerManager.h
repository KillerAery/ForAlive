#ifndef TriggerManager_h__
#define TriggerManager_h__


#include "cocos2d.h"
#include "Singleton.h"

using TriggerMap = std::multimap<int,int>;

enum class BiologyTpye;

//����������  Ŀǰ�������񴥷�����
class TriggerManager : public cocos2d::Ref, public Singleton<TriggerManager>{
	CC_SYNTHESIZE_PASS_BY_REF(TriggerMap,m_killTriggers,KillTriggers);
	CC_SYNTHESIZE_PASS_BY_REF(TriggerMap,m_getTriggers, GetTriggers);
	CC_SYNTHESIZE_PASS_BY_REF(TriggerMap,m_talkTriggers,TalkTriggers);
public:
	bool init();
	void registerKillTrigger(BiologyTpye requireTpye,int MissionID);//ע���ɱ����
	void registerGetTrigger(int requireID,int MissionID);//ע����Ʒ��ȡ����
	void registerTalkTrigger(int requireID,int MissionID);//ע��˵������

	void unregisterKillTrigger(BiologyTpye requireTpye, int MissionID);//ע����ɱ����
	void unregisterGetTrigger(int requireID, int MissionID);//ע����Ʒ��ȡ����
	void unregisterTalkTrigger(int requireID, int MissionID);//ע��˵������

	void checkKillTrigger(BiologyTpye tpye);//����ɱ����
	void checkGetTrigger(int id,int num);//�����Ʒ��ȡ����
	void checkTalkTrigger(int id);//���˵������
};

#endif // TriggerManager_h__