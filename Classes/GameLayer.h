#pragma once
#ifndef _GAME_MAINLAYER_H_
#define _GAME_MAINLAYER_H_

#include "cocos2d.h"
#include "PhysicsWorld.h"
#include "Player.h"
#include "NPC.h"
#include "Drop.h"

using std::vector;
using cocos2d::Layer;
using cocos2d::TMXTiledMap;
using cocos2d::TMXLayer;
using cocos2d::TMXObjectGroup;

//��Ϸ����
class GameLayer : public Layer {
protected:
	CC_SYNTHESIZE(TMXTiledMap*, m_tmxmap, TMXMap);
	CC_SYNTHESIZE(PhysicsWorld*, m_physcisworld, PhysicsWorld);
	CC_SYNTHESIZE(TMXLayer*, m_wallcheckLayer, WallcheckLayer);
	CC_SYNTHESIZE(TMXLayer*, m_groundLayer, GroundLayer);
	CC_SYNTHESIZE_PASS_BY_REF(vector<TMXLayer*>, m_wallLayers, WallLayers);
public:
	GameLayer();
	~GameLayer();
	bool init(const std::string& tmxfilename);
	void initMap(const std::string& tmxfilename);//��ʼ����ͼ
	void initPhysicsWorld();//��ʼ����������
	void initEntities();//��ʼ��ʵ��
	void initContainers();//��ʼ������
	void initNPCs();//��ʼ��NPC
	void initPlayer();//��ʼ�����
	void recordBarrierVec();//��¼�ϰ���
	void recordMapSize();//��¼��ͼ��С
	static GameLayer* create(const std::string& tmxname);

	Vec2 getTilepos(const Vec2& pos);//�������Ƭ��λ��
	void LockView(float dt);//����ʵ���ӽ�//����������

	void hideWallLayer();//����ǽ���
	void showWallLayer();//��ʾǽ���
	void pauseGame(Ref* r);//��ͣ��Ϸ
	void resumeGame(Ref* r);//�ָ���Ϸ

	void addContainer(Ref* r);//�������
	void addContainer(Container* c);//�������
	void addEntity(Ref* r);//���ʵ��
	void addEntity(Entity* e);//���ʵ��
	void addPlayer(Ref* r);//������
	void addPlayer(Player* p);//������
	void addNPC(Ref* r);//���NPC
	void addNPC(NPC* n);//���NPC
	void addBiology(Biology* b);//�������
	void addDrop(Ref* r);//��ӵ�����
	void addDrop(Drop* d);//��ӵ�����
};

#endif // !_GAMESCENE_MAINLAYER_H_
