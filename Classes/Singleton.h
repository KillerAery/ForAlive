#pragma once
#ifndef _SINGLETON_H_
#define _SINGLETON_H_

#include <iostream>
#include "cocos2d.h"

//单例类模板

template<class T>
class Singleton{
private:
	static T * s_instance;
public:
	static T * getInstance();
	static bool deleteInstance();
	
};

template<class T>
T * Singleton<T>::getInstance() {
	if (!s_instance)
	{
		s_instance = new (std::nothrow)T();
		//Ref继承类 初始化
		if (s_instance&&s_instance->init()) {
			//Ref 引用计数+1
			s_instance->retain(); 
			//Ref 引用计数-1并开始放入自动释放池
			s_instance->autorelease(); 
		}
		else { CC_SAFE_DELETE(s_instance); }
	}

	return s_instance;
}

template<class T>
bool Singleton<T>::deleteInstance() {
	if (s_instance) {
		s_instance->autorelease();
		s_instance = nullptr;
		return true;
	}
	else return false;
}

template<class T>
T* Singleton<T>::s_instance = nullptr;



#endif // !_SINGLETON_H_
