#pragma once
#ifndef Relation_h__
#define Relation_h__

//好感度
enum class Disposition{
	hate,dislike,normal,like,admire
};
//态度
enum class Attitude{
	against,guard,neutral,ally
};

//关系
//由好感度和态度决定
class Relation{
protected:
	int m_dispositionValue;		//好感值
	Disposition m_disposition;	//好感状态
	Attitude m_attitude;		//态度
	void judgeAttitude();//辅助方法：判断态度
public:
	Relation(int disposition = 100, Attitude attitude = Attitude::neutral);

	void addDisposition(int n);
	void reduceDisposition(int n);
	void setDisposition(int n);
	Disposition getDisposition();

	void setAttitue(Attitude attitude);
	Attitude getAttitude();
};

#endif // Relation_h__