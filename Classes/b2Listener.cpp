#include "b2Listener.h"
//处理生物碰撞事件
#include "Biology.h"
#include "Bullet.h"

#include "BattleTimer.h"

//开始接触  
void b2Listener::BeginContact(b2Contact *contact) {
	//判断身体是否子弹
	//若不存活
	b2Body* body[2] = { contact->GetFixtureA()->GetBody(),contact->GetFixtureB()->GetBody() };
	for (int i = 0; i < 2; ++i) {
		if (!body[i]->GetUserData())continue;
		auto entity = static_cast<Entity*>(body[i]->GetUserData());
		if (entity->getEntityTpye() != EntityTpye::bullet)continue;

		entity->setIfPredelete(true);
		auto bullet = static_cast<Bullet*>(entity);
		auto damage = bullet->getDamage();
				
		if (body[!i]->GetUserData()){
			auto anotherEntity = static_cast<Entity*>(body[!i]->GetUserData());
				if (anotherEntity->getEntityTpye() == EntityTpye::biology) {
				auto anotherBiology = static_cast<Biology*>(anotherEntity);
				//被打中的人 减少生命
				anotherBiology->setHealth(anotherBiology->getHealth() - damage);
				//被打中的人 态度变为敌对
				anotherBiology->getRelationship()->addIndividualRelationship(bullet->getUser()->getID(),Relation(100,Attitude::against));
				//如果开枪的人是玩家，则进入战斗时刻
				if(bullet->getUser()==GameManager::getInstance()->getPlayer()){ BattleTimer::getInstance()->intoBattle(); }
			}
		}
	}

}

//结束接触  
void b2Listener::EndContact(b2Contact *contact) {

}

//求解之前的  

void  b2Listener::PreSolve(b2Contact *contact, const b2Manifold *oldManifold) {
}

//求解之后的  

void b2Listener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {


}



