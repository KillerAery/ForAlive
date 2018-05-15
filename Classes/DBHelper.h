#ifndef _DBHELPER_H_
#define _DBHELPER_H_


#include "cocos2d.h"
#include "sqlite3/include/sqlite3.h"

using cocos2d::Ref;
using cocos2d::ValueMap;
using cocos2d::ValueVector;
using cocos2d::Value;
using std::string;


/******************�����汾ʵ�֣����Ľ�
��SQL����copy���ڴ棬��Ϸ���̶��ڴ����ݶ�д������Ϸ����ʱ���ڴ����ݸ���SQL
*******************/

class DBHelper:public Ref{
	sqlite3_stmt* visitSTMTByString(const string& additionstring);//�����﷨����sqlite3_stmt����
	sqlite3_stmt* getSTMTData(const string& table, int id);//����ID��ȡsqlite3_stmt����
	sqlite3_stmt* getSTMTData(const string& table, const string& name);//����name��ȡsqlite3_stmt����
protected:
	CC_SYNTHESIZE(sqlite3*, m_SQL3, SQL3);
	CC_SYNTHESIZE(sqlite3_stmt*, m_stmt, Stmt);
public:
	DBHelper();
	~DBHelper();
	bool init();
	bool openSQL(const string& SQL);//��һ��SQL���ݿ�
	void closeSQL();//�ر�SQL���ݿ�
	/*�������ݲ���*/
	string getStringData(const string& table, int id, int field);//��ȡ�ַ�������
	string getStringData(const string& table, const string& name, int field);//��ȡ�ַ�������
	int getIntData(const string& table, int id,int field);//��ȡint����
	int getIntData(const string& table, const string& name, int field);//��ȡint����
	double getDoubleData(const string& table, int id, int field);//��ȡdouble����
	double getDoubleData(const string& table, const string& name, int field);//��ȡdouble����
	/*��������*/
	bool initTraversingTableData(const string& table);//��ʼ��׼��������Table���
	bool traverNextRowData();//������һ������
	int getTraversingIntData(int field) { return sqlite3_column_int(m_stmt, field); }//��ȡint����
	double getTraversingDoubleData(int field) { return sqlite3_column_double(m_stmt, field); }//��ȡdouble����
	string getTraversingStringData(int field) { return string((char*)sqlite3_column_text(m_stmt, field)); }//��ȡ�ַ�������
	ValueVector getTraversingVectorData(int field);//��ȡ��������
};

#endif // !_DBHELPER_H_
