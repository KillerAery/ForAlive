#pragma once
#ifndef _PROTECTED_TRANSFER_H_
#define _PROTECTED_TRANSFER_H_

#include <iostream>

//保证堆指针内存的传递
template<class T>
class ProtectedTransfer{
	ProtectedTransfer():m_value(nullptr){}
	T* m_value;
public:
	ProtectedTransfer(T * value){
		m_value = value;
	}
	ProtectedTransfer(const ProtectedTransfer & value) {
		m_value = value.getValueAndClearProtectedTansfer();
	}

	ProtectedTransfer operator = (const ProtectedTransfer & value) {
		m_value = value.getValueAndClearProtectedTansfer();
	}
	~ProtectedTransfer(){
		if (m_value){
			delete m_value;
		}
	}
	T* getValueAndClearProtectedTansfer(){
		auto value = m_value;
		m_value = nullptr;
		return value;
	}

};


#endif