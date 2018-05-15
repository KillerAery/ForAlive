#ifndef _CACHEMANAGER_H_
#define _CACHEMANAGER_H_

#include "cocos2d.h"
#include "Singleton.h"

using cocos2d::Ref;

class CacheManager :public Ref, public Singleton<CacheManager> {
private:
	CacheManager();
	friend Singleton<CacheManager>;
public:
	bool init();


};

#endif // !_CACHEMANAGER_H_

