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

//��ʱ��ƣ� ������������
enum class BiologyTpye{player = 0,zombie = 1,human = 2};
//װ����������
enum GearTpye
{HeadGear=0,BodyGear=1,LegGear=2,FeetGear=3,HandGear=4,LeftHandGear=5,RightHandGear=6};

/*�����Ǵ����� Ȼ��û��ʲô����ֵ�ô��黯*/
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
/*-------------------�����������Գ�ʼ������----------------------------*/
public:
	//��ʼ������
	Biology();
	virtual ~Biology() = 0;
	virtual bool init(ValueMap& obj_valuemap)override;
	virtual bool initPhysics(ValueMap& obj_valuemap)override;
	virtual void update(float dt)override;

	//��������
	void die();								//��������Ԥ�Ƴ�
	virtual void removeFromScene()override;	//�ӳ������Ƴ�
public:
	void makeFootEffect(float dt);	//�Ų�����
	FindWayCaculator& getWayCaculator() { return m_wayCaculator; }
	void attack(const Vec2&dir);
	void attack();
/*-----------------------------װ��ģ��-----------------------*/
protected:
	CC_SYNTHESIZE_PASS_BY_REF(vector<Item*>, m_gearvec, GearVec);
	CC_PROPERTY(int, m_inhandindex, InHandIndex);
	bool wearGear(int id,int sum, GearTpye gtpye);
	bool wearGear(ProtectedTransfer<Item> i, GearTpye gtpye);
	bool removeGear(GearTpye tpye);
	bool removeGear(GearTpye tpye,int num);
	ProtectedTransfer<Item> moveGear(GearTpye tpye);
	void checkTexture();
/*---------------------------��Ʒʹ��ģ��-------------------*/
	//ʹ���߶�ʹ����ʹ��
	bool itemUseable(Item* i, int usesum);
	void useItem(Item* i, int usesum);
	//ʹ���߶�����ʹ��
	bool itemUseable(Item* i, Biology* biology, int usesum);
	void useItem(Item* i, Biology* biology, int usesum);
	//ʹ���߶�����ʹ��
	bool itemUseable(Item* i, Entity* entity, int usesum);
	void useItem(Item* i, Entity* entity, int usesum);
	//ʹ���߶�һ������ʹ��
	bool itemUseable(Item* i, const Vec2& direction, int usesum);
	void useItem(Item* i, const Vec2& direction, int usesum);
	//ʹ���߶�һ����Ʒʹ��
	bool itemUseable(Item* i, Item* preusedItem, int usesum);
	void useItem(Item* i, Item* preusedItem, int usesum);

	//���Һ���
	Item* findGearItem(int id);
	Item* findGearItem(Item* item);

	//�ӳ�ʹ���ߵ������������ĹǻҺУ�
	void throwContainer();
	//��������ĵ�����
	void pickupNearestDrop();
	//���ɵ�����
	void throwGearDrop(GearTpye gtpye,int sum);
/*-----------------------------Ѫ��ģ��-----------------------*/
	CC_SYNTHESIZE(BloodBar*, m_bloodbar, BloodBar);
public:
	void initBloodBar();
/*---------------------------��ϵ̬����-------------------*/
	CC_SYNTHESIZE_PASS_BY_REF(Relationship, m_relationship, Relationship);
/*--------------------------AI����ĸ�֪ģ��-------------------*/
	CC_PROPERTY(Perceptionable*, m_perception, Perception);
/*--------------------------˵��ģ��-------------------*/
	CC_SYNTHESIZE(SpeakWords*,m_speakWords,SpeakWords);
	void speakAdditionWords(const string& words);			//˵����Ļ���ԭ���Ļ��������ƶ�����������
	void speakWords(const string& words);					//ֱ��˵��������ԭ���Ļ���
};

#endif // !_BIOLOGY_H_

