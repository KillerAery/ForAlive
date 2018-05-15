#pragma once
#ifndef _BIOLOGY_H_
#define _BIOLOGY_H_

#include <vector>
#include "Container.h"
#include "Drop.h"
#include "BloodBar.h"
#include "Perceptionable.h"
#include "BiologyRelationship.h"
#include "SpeakWords.h"
#include "findWayCaculator.h"

class Item;
using std::vector;
using cocos2d::NotificationCenter;

//暂时设计， 生物类型声明
enum class BiologyTpye{player = 0,zombie = 1,human = 2};
//装备类型声明
enum GearTpye
{HeadGear=0,BodyGear=1,LegGear=2,FeetGear=3,HandGear=4,LeftHandGear=5,RightHandGear=6};

/*生物是纯虚类 然而没有什么函数值得纯虚化*/
class Biology :public Container{
protected:
	CC_SYNTHESIZE_PASS_BY_REF(Vec2, m_velocity, Veclocity);
	CC_PROPERTY(double, m_health, Health);
	CC_SYNTHESIZE(double, m_maxhealth, MaxHealth);
	CC_SYNTHESIZE(double, m_hungry, Hungry);
	CC_SYNTHESIZE(double, m_attack, Attack);
	CC_SYNTHESIZE(double, m_speed, Speed);
	CC_SYNTHESIZE(BiologyTpye, m_biologytpye, BiologyTpye);
	CC_SYNTHESIZE(bool, m_ifcooltime, IfCoolTime);
	CC_SYNTHESIZE_PASS_BY_REF(Vec2,m_direction,Direction);
	CC_SYNTHESIZE(bool, m_ifRequireToTalk,IfRequireToTalk);
	FindWayCaculator m_wayCaculator;
/*-------------------基础生物属性初始化部分----------------------------*/
public:
	//初始化部分
	Biology();
	virtual ~Biology() = 0;
	virtual bool init(ValueMap& obj_valuemap)override;
	virtual bool initPhysics(ValueMap& obj_valuemap)override;
	virtual void update(float dt)override;

	//结束部分
	void die();								//死亡——预移除
	virtual void removeFromScene()override;	//从场景中移除
public:
	void makeFootEffect(float dt);	//脚步声音
	FindWayCaculator& getWayCaculator() { return m_wayCaculator; }
	void attack(const Vec2&dir);
	void attack();
/*-----------------------------装备模块-----------------------*/
protected:
	CC_SYNTHESIZE_PASS_BY_REF(vector<Item*>, m_gearvec, GearVec);
	CC_PROPERTY(int, m_inhandindex, InHandIndex);
	bool wearGear(int id,int sum, GearTpye gtpye);
	bool wearGear(ProtectedTransfer<Item> i, GearTpye gtpye);
	bool removeGear(GearTpye tpye);
	bool removeGear(GearTpye tpye,int num);
	ProtectedTransfer<Item> moveGear(GearTpye tpye);
	void checkTexture();
/*---------------------------物品使用模块-------------------*/
	//使用者对使用者使用
	bool itemUseable(Item* i, int usesum);
	void useItem(Item* i, int usesum);
	//使用者对生物使用
	bool itemUseable(Item* i, Biology* biology, int usesum);
	void useItem(Item* i, Biology* biology, int usesum);
	//使用者对物体使用
	bool itemUseable(Item* i, Entity* entity, int usesum);
	void useItem(Item* i, Entity* entity, int usesum);
	//使用者对一个方向使用
	bool itemUseable(Item* i, const Vec2& direction, int usesum);
	void useItem(Item* i, const Vec2& direction, int usesum);
	//使用者对一个物品使用
	bool itemUseable(Item* i, Item* preusedItem, int usesum);
	void useItem(Item* i, Item* preusedItem, int usesum);

	//查找函数
	Item* findGearItem(int id);
	Item* findGearItem(Item* item);

	//扔出使用者的容器（死亡的骨灰盒）
	void throwContainer();
	//捡起最近的掉落物
	void pickupNearestDrop();
	//生成掉落物
	void throwGearDrop(GearTpye gtpye,int sum);
/*-----------------------------血条模块-----------------------*/
	CC_SYNTHESIZE(BloodBar*, m_bloodbar, BloodBar);
public:
	void initBloodBar();
/*---------------------------关系态度网-------------------*/
	CC_SYNTHESIZE_PASS_BY_REF(Relationship, m_relationship, Relationship);
/*--------------------------AI所需的感知模块-------------------*/
	CC_PROPERTY(Perceptionable*, m_perception, Perception);
/*--------------------------说话模块-------------------*/
	CC_SYNTHESIZE(SpeakWords*,m_speakWords,SpeakWords);
	void speakAdditionWords(const string& words);			//说额外的话，原来的话语往上移动，新增话语
	void speakWords(const string& words);					//直接说话，覆盖原来的话语
};

#endif // !_BIOLOGY_H_

