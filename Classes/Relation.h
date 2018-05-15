#pragma once
#ifndef Relation_h__
#define Relation_h__

//�øж�
enum class Disposition{
	hate,dislike,normal,like,admire
};
//̬��
enum class Attitude{
	against,guard,neutral,ally
};

//��ϵ
//�ɺøжȺ�̬�Ⱦ���
class Relation{
protected:
	int m_dispositionValue;		//�ø�ֵ
	Disposition m_disposition;	//�ø�״̬
	Attitude m_attitude;		//̬��
	void judgeAttitude();//�����������ж�̬��
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