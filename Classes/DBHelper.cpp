#include "DBHelper.h"

using cocos2d::FileUtils;

DBHelper::DBHelper():m_SQL3(nullptr),m_stmt(nullptr){}

DBHelper::~DBHelper() {closeSQL(); }

bool DBHelper::init() {
	return true;
}

//打开SQL数据库
bool DBHelper::openSQL(const std::string& s) {
	//若存在SQL数据库 则关闭之
	if (m_SQL3)closeSQL();
	//打开sqlite数据库
	int ret = sqlite3_open(s.c_str(), &m_SQL3);
	//当sqllite数据库打开失败时
	if (ret != SQLITE_OK)
	{
		//获得sqltite数据库打开错误的信息
		const char* errmsg = sqlite3_errmsg(m_SQL3);
		//打印数据库打开失败的信息
		CCLOG("sqlite open error: %s", errmsg);
		//还没看完SQL文档，失败后不知如何处理
		m_SQL3 = nullptr;
		return false;
	}
	return true;
}
//关闭SQL数据库
void DBHelper::closeSQL() {
	if (m_stmt) {
		sqlite3_finalize(m_stmt);
	}
	if (m_SQL3) {
		sqlite3_close(m_SQL3);
		m_SQL3 = nullptr;
	}
}



//根据语法获取sqlite3_stmt数据
sqlite3_stmt* DBHelper::visitSTMTByString(const string& additionstring){
	if (m_stmt) {
		sqlite3_reset(m_stmt);
		sqlite3_clear_bindings(m_stmt);
	}
	const char *zTail;
	if (sqlite3_prepare_v2(m_SQL3,("SELECT * FROM " + additionstring ).c_str(), -1, &m_stmt, &zTail) == SQLITE_OK) {
		if (sqlite3_step(m_stmt) == SQLITE_ROW)return m_stmt;
	}
	return nullptr;
}

//根据ID获取sqlite3_stmt数据
sqlite3_stmt* DBHelper::getSTMTData(const string& table, int id){
	return visitSTMTByString(table + " WHERE id = " + cocos2d::StringUtils::toString(id));
}
//根据name获取sqlite3_stmt数据
sqlite3_stmt* DBHelper::getSTMTData(const string& table, const string& name) {
	return visitSTMTByString(table + " WHERE name = " + name);
}

//获取字符串数据
string DBHelper::getStringData(const string& table, int id, int field) {
	return string((char*)sqlite3_column_text(getSTMTData(table,id), field));
}
//获取字符串数据
string DBHelper::getStringData(const string& table, const string& name, int field) {
	return string((char*)sqlite3_column_text(getSTMTData(table, name), field));
}
//获取int数据
int DBHelper::getIntData(const string& table, int id, int field) {
	return sqlite3_column_int(getSTMTData(table, id), field);
}
//获取int数据
int DBHelper::getIntData(const string& table, const string& name, int field) {
	return sqlite3_column_int(getSTMTData(table, name), field);
}
//获取double数据
double DBHelper::getDoubleData(const string& table, int id, int field) {
	return sqlite3_column_double(getSTMTData(table, id), field);
}
//获取double数据
double DBHelper::getDoubleData(const string& table, const string& name, int field) {
	return sqlite3_column_double(getSTMTData(table, name), field);
}

//初始化准备遍历的Table语句
bool DBHelper::initTraversingTableData(const string& table) {
	if (m_stmt) {
		sqlite3_reset(m_stmt);
		//sqlite3_clear_bindings(m_stmt);
	}
	const char *zTail;
	if (sqlite3_prepare_v2(m_SQL3, ("SELECT * FROM " + table).c_str(), -1, &m_stmt, &zTail) == SQLITE_OK) {
		return true;
	}
	return false;
}
//遍历下一行数据
bool DBHelper::traverNextRowData() {
	if (sqlite3_step(m_stmt) == SQLITE_ROW) { return true; }
	return false;
}

//获取数组数据
ValueVector DBHelper::getTraversingVectorData(int field) {
	ValueVector vec;

	char text[100];
	//将SQL数据复制到text（保护SQL原生数据不被破坏）
	strcpy(text, (const char*)sqlite3_column_text(m_stmt, field));
	//将text逐个拆分，并把每个拆分的数据存入str以便转换int
	char str[25];
	for (int i = 0, begin = 0; text[i]; ++i)
		if (text[i] == '|') {
			text[i] = '\0';
			strcpy(str, text + begin);
			int num = atoi(str);
			vec.push_back(Value(num));
			begin = i + 1;
		}

	return vec;
}
