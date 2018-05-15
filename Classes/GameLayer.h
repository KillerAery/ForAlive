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

//游戏主层
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
	void initMap(const std::string& tmxfilename);//初始化地图
	void initPhysicsWorld();//初始化物理世界
	void initEntities();//初始化实体
	void initContainers();//初始化容器
	void initNPCs();//初始化NPC
	void initPlayer();//初始化玩家
	void recordBarrierVec();//记录障碍组
	void recordMapSize();//记录地图大小
	static GameLayer* create(const std::string& tmxname);

	Vec2 getTilepos(const Vec2& pos);//获得在瓦片的位置
	void LockView(float dt);//锁定实体视角//处理房屋遮掩

	void hideWallLayer();//隐藏墙体层
	void showWallLayer();//显示墙体层
	void pauseGame(Ref* r);//暂停游戏
	void resumeGame(Ref* r);//恢复游戏

	void addContainer(Ref* r);//添加容器
	void addContainer(Container* c);//添加容器
	void addEntity(Ref* r);//添加实体
	void addEntity(Entity* e);//添加实体
	void addPlayer(Ref* r);//添加玩家
	void addPlayer(Player* p);//添加玩家
	void addNPC(Ref* r);//添加NPC
	void addNPC(NPC* n);//添加NPC
	void addBiology(Biology* b);//添加生物
	void addDrop(Ref* r);//添加掉落物
	void addDrop(Drop* d);//添加掉落物
};

#endif // !_GAMESCENE_MAINLAYER_H_
