#pragma once
#ifndef _GAME_MANAGER_
#define _GAME_MANAGER_

#include "Singleton.h"
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "Player.h"

using cocos2d::Ref;
using cocos2d::Node;
using cocos2d::Point;
using cocos2d::Vec2;
using cocos2d::Size;
using std::string;

class GameLayer;

using BiologyMap = std::map<int,Biology*>;
using ContainerMap = std::map<int,Container*>;
using DropList = std::list<Drop*>;


//��Ϸ������
//�ṩȫ�ָ������ݵ��ò鿴
class GameManager:public Node, public Singleton<GameManager> {
	GameManager();
	~GameManager();
protected:
	CC_SYNTHESIZE(Player*,m_player,Player);
	CC_SYNTHESIZE_PASS_BY_REF(Vec2,m_playerPos,PlayerPos);

	CC_SYNTHESIZE(b2World*, m_b2world,b2World);

	CC_SYNTHESIZE_PASS_BY_REF(ContainerMap, m_containerMap,ContainerMap);
	CC_SYNTHESIZE_PASS_BY_REF(DropList, m_dropList, DropList);
	CC_SYNTHESIZE_PASS_BY_REF(BiologyMap, m_biologyMap, BiologyMap);	

	CC_SYNTHESIZE_PASS_BY_REF(Size,m_mapSize,MapSize);					//��ͼ�ߴ�
	CC_SYNTHESIZE_PASS_BY_REF(Size, m_tiles, Tiles);					//��ͼtile��
	CC_SYNTHESIZE_PASS_BY_REF(Size, m_tileSize, TileSize);				//��ͼtile�ĳߴ�
	bool barrierMark[50][100];

	CC_SYNTHESIZE(GameLayer*, r_gameLayer, GameLayer);
public:
	bool init();
	void initEventListener();
	//ע������
	void registerContainer(Container* c);
	//ע������ 
	void registerBiology(Biology* c);
	//ע�������
	void registerDrop(Drop* d);
	//�Ƴ�����
	void removeContainer(Ref* r);
	//�Ƴ����� 
	void removeBiology(Ref* r);
	//�Ƴ�������
	void removeDrop(Ref* r);
	void removePlayer(Ref* r);
	Biology* findBiology(int id);
	Container* findContainer(int id);
public:
	//�Ų���Ч
	void playFootEffect(const Vec2& pos);
	void playEffect(const string& str, const Vec2& pos);
	//����ϰ���
	void pushBarrierPoint(int x,int y) {
		barrierMark[x][y] = false;
	}
	//�������Ƭ��λ��
	Vec2 getTilepos(const Vec2& pos);

	friend Singleton<GameManager>;
};

#endif