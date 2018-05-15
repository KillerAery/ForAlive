#include "DBHelper.h"

using cocos2d::FileUtils;

DBHelper::DBHelper():m_SQL3(nullptr),m_stmt(nullptr){}

DBHelper::~DBHelper() {closeSQL(); }

bool DBHelper::init() {
	return true;
}

//��SQL���ݿ�
bool DBHelper::openSQL(const std::string& s) {
	//������SQL���ݿ� ��ر�֮
	if (m_SQL3)closeSQL();
	//��sqlite���ݿ�
	int ret = sqlite3_open(s.c_str(), &m_SQL3);
	//��sqllite���ݿ��ʧ��ʱ
	if (ret != SQLITE_OK)
	{
		//���sqltite���ݿ�򿪴������Ϣ
		const char* errmsg = sqlite3_errmsg(m_SQL3);
		//��ӡ���ݿ��ʧ�ܵ���Ϣ
		CCLOG("sqlite open error: %s", errmsg);
		//��û����SQL�ĵ���ʧ�ܺ�֪��δ���
		m_SQL3 = nullptr;
		return false;
	}
	return true;
}
//�ر�SQL���ݿ�
void DBHelper::closeSQL() {
	if (m_stmt) {
		sqlite3_finalize(m_stmt);
	}
	if (m_SQL3) {
		sqlite3_close(m_SQL3);
		m_SQL3 = nullptr;
	}
}



//�����﷨��ȡsqlite3_stmt����
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

//����ID��ȡsqlite3_stmt����
sqlite3_stmt* DBHelper::getSTMTData(const string& table, int id){
	return visitSTMTByString(table + " WHERE id = " + cocos2d::StringUtils::toString(id));
}
//����name��ȡsqlite3_stmt����
sqlite3_stmt* DBHelper::getSTMTData(const string& table, const string& name) {
	return visitSTMTByString(table + " WHERE name = " + name);
}

//��ȡ�ַ�������
string DBHelper::getStringData(const string& table, int id, int field) {
	return string((char*)sqlite3_column_text(getSTMTData(table,id), field));
}
//��ȡ�ַ�������
string DBHelper::getStringData(const string& table, const string& name, int field) {
	return string((char*)sqlite3_column_text(getSTMTData(table, name), field));
}
//��ȡint����
int DBHelper::getIntData(const string& table, int id, int field) {
	return sqlite3_column_int(getSTMTData(table, id), field);
}
//��ȡint����
int DBHelper::getIntData(const string& table, const string& name, int field) {
	return sqlite3_column_int(getSTMTData(table, name), field);
}
//��ȡdouble����
double DBHelper::getDoubleData(const string& table, int id, int field) {
	return sqlite3_column_double(getSTMTData(table, id), field);
}
//��ȡdouble����
double DBHelper::getDoubleData(const string& table, const string& name, int field) {
	return sqlite3_column_double(getSTMTData(table, name), field);
}

//��ʼ��׼��������Table���
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
//������һ������
bool DBHelper::traverNextRowData() {
	if (sqlite3_step(m_stmt) == SQLITE_ROW) { return true; }
	return false;
}

//��ȡ��������
ValueVector DBHelper::getTraversingVectorData(int field) {
	ValueVector vec;

	char text[100];
	//��SQL���ݸ��Ƶ�text������SQLԭ�����ݲ����ƻ���
	strcpy(text, (const char*)sqlite3_column_text(m_stmt, field));
	//��text�����֣�����ÿ����ֵ����ݴ���str�Ա�ת��int
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
