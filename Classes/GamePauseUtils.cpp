#include "GamePauseUtils.h"  

USING_NS_CC;

GamePauseUtils::GamePauseUtils(){}

bool GamePauseUtils::init() { return true; }

void GamePauseUtils::operateAllSchedulerAndActions(Node* node, PauseTpye type, int ignoreTag) {
	if (node->isRunning()) {
		switch (type){
		case PauseTpye::PAUSE:
			node->pause();
			break;
		case PauseTpye::RESUME:
			node->resume();
			break;
		}

		Vector<Node*> array = node->getChildren();

		if (array.size() > 0) {
			for (Vector<Node*>::iterator iter = array.begin(); iter != array.end();) {
				Node* child = *iter;

				if (child->getTag() == ignoreTag) {
					iter++;
				}
				else {
					iter++;
					this->operateAllSchedulerAndActions(child, type, ignoreTag);
				}
			}
		}
	}
}