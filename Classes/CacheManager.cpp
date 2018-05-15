#pragma once
#include "CacheManager.h"

#include "ItemDataBase.h"
#include "BackPackUITemplate.h"

CacheManager::CacheManager(){}

bool CacheManager::init(){
	Singleton<ItemDataBase>::getInstance();
	Singleton<BackPackUITemplate>::getInstance();

	return true;
}