#ifndef _DBHELPER_H_
#define _DBHELPER_H_


#include "cocos2d.h"
#include "sqlite3/include/sqlite3.h"

using cocos2d::Ref;
using cocos2d::ValueMap;
using cocos2d::ValueVector;
using cocos2d::Value;
using std::string;


/******************初级版本实现，待改进
把SQL数据copy到内存，游戏过程对内存数据读写，在游戏结束时将内存数据覆盖SQL
*******************/

class DBHelper:public Ref{
	sqlite3_stmt* visitSTMTByString(const string& additionstring);//根据语法访问sqlite3_stmt数据
	sqlite3_stmt* getSTMTData(const string& table, int id);//根据ID获取sqlite3_stmt数据
	sqlite3_stmt* getSTMTData(const string& table, const string& name);//根据name获取sqlite3_stmt数据
protected:
	CC_SYNTHESIZE(sqlite3*, m_SQL3, SQL3);
	CC_SYNTHESIZE(sqlite3_stmt*, m_stmt, Stmt);
public:
	DBHelper();
	~DBHelper();
	bool init();
	bool openSQL(const string& SQL);//打开一个SQL数据库
	void closeSQL();//关闭SQL数据库
	/*单个数据操作*/
	string getStringData(const string& table, int id, int field);//获取字符串数据
	string getStringData(const string& table, const string& name, int field);//获取字符串数据
	int getIntData(const string& table, int id,int field);//获取int数据
	int getIntData(const string& table, const string& name, int field);//获取int数据
	double getDoubleData(const string& table, int id, int field);//获取double数据
	double getDoubleData(const string& table, const string& name, int field);//获取double数据
	/*遍历操作*/
	bool initTraversingTableData(const string& table);//初始化准备遍历的Table语句
	bool traverNextRowData();//遍历下一行数据
	int getTraversingIntData(int field) { return sqlite3_column_int(m_stmt, field); }//获取int数据
	double getTraversingDoubleData(int field) { return sqlite3_column_double(m_stmt, field); }//获取double数据
	string getTraversingStringData(int field) { return string((char*)sqlite3_column_text(m_stmt, field)); }//获取字符串数据
	ValueVector getTraversingVectorData(int field);//获取数组数据
};

#endif // !_DBHELPER_H_
