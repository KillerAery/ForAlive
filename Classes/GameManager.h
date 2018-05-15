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


//游戏管理者
//提供全局各种数据调用查看
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

	CC_SYNTHESIZE_PASS_BY_REF(Size,m_mapSize,MapSize);					//地图尺寸
	CC_SYNTHESIZE_PASS_BY_REF(Size, m_tiles, Tiles);					//地图tile数
	CC_SYNTHESIZE_PASS_BY_REF(Size, m_tileSize, TileSize);				//地图tile的尺寸
	bool barrierMark[50][100];

	CC_SYNTHESIZE(GameLayer*, r_gameLayer, GameLayer);
public:
	bool init();
	void initEventListener();
	//注册容器
	void registerContainer(Container* c);
	//注册生物 
	void registerBiology(Biology* c);
	//注册掉落物
	void registerDrop(Drop* d);
	//移除容器
	void removeContainer(Ref* r);
	//移除生物 
	void removeBiology(Ref* r);
	//移除掉落物
	void removeDrop(Ref* r);
	void removePlayer(Ref* r);
	Biology* findBiology(int id);
	Container* findContainer(int id);
public:
	//脚步音效
	void playFootEffect(const Vec2& pos);
	void playEffect(const string& str, const Vec2& pos);
	//添加障碍点
	void pushBarrierPoint(int x,int y) {
		barrierMark[x][y] = false;
	}
	//获得在瓦片的位置
	Vec2 getTilepos(const Vec2& pos);

	friend Singleton<GameManager>;
};

#endif