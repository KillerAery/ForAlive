#include "b2Listener.h"
//����������ײ�¼�
#include "Biology.h"
#include "Bullet.h"

#include "BattleTimer.h"

//��ʼ�Ӵ�  
void b2Listener::BeginContact(b2Contact *contact) {
	//�ж������Ƿ��ӵ�
	//�������
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
				//�����е��� ��������
				anotherBiology->setHealth(anotherBiology->getHealth() - damage);
				//�����е��� ̬�ȱ�Ϊ�ж�
				anotherBiology->getRelationship()->addIndividualRelationship(bullet->getUser()->getID(),Relation(100,Attitude::against));
				//�����ǹ��������ң������ս��ʱ��
				if(bullet->getUser()==GameManager::getInstance()->getPlayer()){ BattleTimer::getInstance()->intoBattle(); }
			}
		}
	}

}

//�����Ӵ�  
void b2Listener::EndContact(b2Contact *contact) {

}

//���֮ǰ��  

void  b2Listener::PreSolve(b2Contact *contact, const b2Manifold *oldManifold) {
}

//���֮���  

void b2Listener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {


}



