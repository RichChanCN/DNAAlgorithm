#pragma once
#include<vector>
#include<set>
#include<map>
#include<ctime>
#include<algorithm>
using namespace std;

//==========================��Ҫ�ֶ����ĵ�����===========================

static int POP_NUM = 30;	//��Ⱥ��С
static int GEN = 10;	//��������
const static int Pmut = 100;	//������ʷ�ĸ
const static int P = 400;	//�ͷ�ϵ��

static bool isMuted = false;

const static int MAX_DOC_NUM = 4;	//����ҽ����
const static int MAX_OPS_NUM = 5;	//������������
const static int MAX_DAY_NUM = 2;	//�������
const static int MAX_PERIOD_PER_DAY = 2;	//һ��ֶ���
const static int MAX_PERIOD_NUM = MAX_PERIOD_PER_DAY * MAX_DAY_NUM;	//�ֶܷ�����
const static int MAX_ROOM_NUM = 2;	//����������
const static int MYINFINITY = 1000000;	//�Լ���������޴�


static int dayliy_resource_num[MAX_DAY_NUM] = { 10, 10 };	//ÿ�����Դ��
static int ops_resource_num[MAX_OPS_NUM] = { 3, 4, 4, 1, 4 };	//ÿ��������Ҫ����Դ
static int ops_need_time[MAX_OPS_NUM] = { 4, 5, 3, 2, 4 };	//ÿ��������Ҫ��ʱ��
static int DN[MAX_ROOM_NUM][MAX_DAY_NUM] = { 6, 4, 4, 6 };	//DN
static int DM[MAX_ROOM_NUM][MAX_DAY_NUM] = { 8, 8, 8, 8 };	//DM

//=======��Ҫ-1������========
static int DL[MAX_OPS_NUM] = { 3, 3, 3, 3, 3 };	//ÿ���������������ʱ��
//===========================

map<int, int> dayliy_nurse_num;
map<int, int> dayliy_anesthetist_num;
map<int, int> nurse_always_num_by_ops;
map<int, int> nurse_temply_num_by_ops;
map<int, int> anesthetist_always_num_by_ops;
map<int, int> anesthetist_temply_num_by_ops;

static int room_rest_cost = 5;	//�����ҿ��гɱ�
static int room_over_cost = 6;	//�����ҳ�ʱ�ɱ�

static int RC[MAX_DOC_NUM][MAX_PERIOD_NUM] = { 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0 };	//ҽ������ʱ��
static int Qjs[MAX_OPS_NUM][MAX_ROOM_NUM] = { 1, 1, 1, 1, 1, 1, 0, 1, 1, 1 };	//�����������ҵĹ�ϵ
vector<set<int> > doc_ops;

//==========================��Ҫ�ֶ����ĵ����ã��꣩=======================
//=============ͳ��������ݵı���======================
static int mut_1_counts = 0; //����1�����Ĵ���
static int mut_2_counts = 0; //����2�����Ĵ���
static int mut_3_counts = 0; //����3�����Ĵ���
//=============ͳ��������ݵı������꣩================
void initRecord(){
	mut_1_counts = 0;
	mut_2_counts = 0;
	mut_3_counts = 0;
}

class Ops{//I�������Ԫ�ظ���
public:
	Ops(int ID, int bt, int room):id(ID),begin_time(bt),ops_room(room){

	}
	int id;
	int begin_time;

	int ops_room;

};

class Doctor{
public:
	Doctor(int id, set<int> op, set<int>time){
		doctor_id = id;
		can_op = op;
		has_time = time;
	}
	int doctor_id;
	set<int> can_op;
	set<int> has_time;

};

class OpsGroup{//һ��I
public:
	int getSize() const{
		return m_ops_list.size();
	}
	void toStr();
	void writeFile(FILE* f);
	vector<Ops> m_ops_list;
};

void OpsGroup::toStr(){
	for (int i = 0; i < m_ops_list.size(); i++)
	{
		cout << "(" << m_ops_list[i].id << "," << m_ops_list[i].begin_time << ")\t";
	}
	cout << endl;
	for (int i = 0; i < m_ops_list.size(); i++)
	{
		cout << "  " << m_ops_list[i].ops_room << "\t";
	}
	cout << endl;
}

void OpsGroup::writeFile(FILE* f){
	for (int i = 0; i < m_ops_list.size(); i++)
	{
		fprintf(f, "(%d,%d)\t", m_ops_list[i].id, m_ops_list[i].begin_time);
	}
	fprintf(f, "\n");
	for (int i = 0; i < m_ops_list.size(); i++)
	{
		fprintf(f, "  %d\t\t", m_ops_list[i].ops_room);
	}
	fprintf(f, "\n");
}

class POP{
public:
	vector<OpsGroup> m_list;
	void toStr();
	void writeFile(FILE* f);
};


class MyTool
{
public:
	static int findDoctorByOps(int ops_id);	//ͨ�����������ID
	static int randomFindBeginTime(int doc, int deadline);	//ͨ��ҽ����DL����ҿ�ʼʱ��
	static int randomFindRoomByOps(int ops_id);	//ͨ�������������ҷ���
	static int fitness(const OpsGroup& opsg);	//��Ӧ�Ժ���
	static OpsGroup cross(const OpsGroup& lhs, const  OpsGroup& rhs, int q1, int q2);	//�ӽ�����
	static void mut(OpsGroup& opsg);	//����
	static void mut(OpsGroup& opsg,FILE* f);	//����
	static void sel(POP &pop);	//ѡ����
private:
	static int LR(const OpsGroup& opsg);
	static int LP(const OpsGroup& opsg);
	static bool LDL(const OpsGroup& opsg);
	static bool LDC(const OpsGroup& opsg);
	static int C(const OpsGroup& opsg);
	static int randomInVector(const vector<int>& vec);
	static bool comp(const OpsGroup& og1, const OpsGroup& og2);
};

void POP::toStr(){
	for (int i = 0; i < m_list.size(); i++)
	{
		cout<<"����" << i <<":"<<endl;
		m_list[i].toStr();
	}
	cout << endl;
}

void POP::writeFile(FILE* f){
	for (int i = 0; i < m_list.size(); i++)
	{
		fprintf(f, "����%d:(��Ӧ��:%d)\n",i+1,MyTool::fitness(m_list[i]));
		m_list[i].writeFile(f);
		fprintf(f, "\n");
	}
}

bool MyTool::comp(const OpsGroup& og1, const OpsGroup& og2){
	return MyTool::fitness(og1) < MyTool::fitness(og2);
}

int MyTool::randomInVector(const vector<int>& vec){
	return vec[rand()%vec.size()];
}

int MyTool::randomFindBeginTime(int doc, int ops_id){
	vector<int> temp;
	for (int i = 0; i < MAX_PERIOD_NUM && i <= DL[ops_id]; i++)
	{
		if (RC[doc][i] == 1)
			temp.push_back(i);
	}
	if (temp.size() < 1)
		return -1;

	return randomInVector(temp);
}

int MyTool::randomFindRoomByOps(int ops_id){
	vector<int> temp;
	for (int i = 0; i < MAX_ROOM_NUM; i++)
	{
		if (Qjs[ops_id][i] == 1)
			temp.push_back(i);
	}
	if (temp.size() < 1)
		return -1;

	return randomInVector(temp);
}

int MyTool::findDoctorByOps(int ops_id){
	int temp = -1;
	for (int i = 0; i < doc_ops.size(); i++)
	{
		if (doc_ops[i].find(ops_id) != doc_ops[i].end())
			temp = i;
	}

	return temp;
}

OpsGroup MyTool::cross(const OpsGroup& lhs, const  OpsGroup& rhs, int q1, int q2){
	set<int> ops_set;
	OpsGroup kid;
	for (int i = 0; i < q1; i++)
	{
		kid.m_ops_list.push_back(Ops(lhs.m_ops_list[i].id, lhs.m_ops_list[i].begin_time, -1));
		ops_set.insert(lhs.m_ops_list[i].id);
	}

	for (int i = 0; i < rhs.getSize(); i++)
	{
		if (ops_set.find(rhs.m_ops_list[i].id) == ops_set.end()){
			kid.m_ops_list.push_back(Ops(rhs.m_ops_list[i].id, rhs.m_ops_list[i].begin_time, -1));
		}
	}

	for (int i = 0; i < kid.getSize(); i++)
	{
		int lhs_index = 0;
		int rhs_index = 0;
		if (i < q2){
			while (lhs_index < lhs.getSize())
			{
				if (lhs.m_ops_list[lhs_index].id == kid.m_ops_list[i].id){
					kid.m_ops_list[i].ops_room = lhs.m_ops_list[lhs_index].ops_room;
					lhs_index++;
					break;
				}
				lhs_index++;
			}
		}
		else{
			while (rhs_index < rhs.getSize())
			{
				if (rhs.m_ops_list[rhs_index].id == kid.m_ops_list[i].id){
					kid.m_ops_list[i].ops_room = rhs.m_ops_list[rhs_index].ops_room;
					rhs_index++;
					break;
				}
				rhs_index++;
			}
		}
	}

	return kid;
}

int MyTool::LR(const OpsGroup& opsg){
	int LR[MAX_DAY_NUM];
	for (int i = 0; i < MAX_DAY_NUM; i++)
	{
		LR[i] = 0;
	}
	for (int i = 0; i < opsg.getSize(); i++)
	{
		LR[opsg.m_ops_list[i].begin_time / 2] += ops_resource_num[opsg.m_ops_list[i].id];
	}

	int result = 0;
	for (int i = 0; i < MAX_DAY_NUM; i++)
	{
		int temp = dayliy_resource_num[i] - LR[i];
		if (temp < 0){
			result += abs(temp);
		}
	}

	return result;
}

int MyTool::LP(const OpsGroup& opsg){
	int LP[MAX_ROOM_NUM][MAX_DAY_NUM];

	memset(LP, 0, MAX_ROOM_NUM*MAX_DAY_NUM * 4);//����

	for (int i = 0; i < opsg.getSize(); i++)
	{
		LP[opsg.m_ops_list[i].ops_room][opsg.m_ops_list[i].begin_time/2] += ops_need_time[opsg.m_ops_list[i].id];
	}

	int result = 0;
	for (int i = 0; i < MAX_ROOM_NUM; i++)
	{
		for (int j = 0; j < MAX_DAY_NUM; j++)
		{
			int temp = DM[i][j] - LP[i][j];
			if (temp < 0){
				result += abs(temp);
			}
		}
	}

	return result;
}

bool MyTool::LDL(const OpsGroup& opsg){
	for (int i = 0; i < opsg.getSize(); i++)
	{
		if (opsg.m_ops_list[i].begin_time > DL[opsg.m_ops_list[i].id])
			return false;
	}
	
	return true;
}

bool MyTool::LDC(const OpsGroup& opsg){
	for (int i = 0; i < opsg.getSize(); i++)
	{
		int doc = MyTool::findDoctorByOps(opsg.m_ops_list[i].id);
		if (RC[doc][opsg.m_ops_list[i].begin_time] == 0)
			return false;
	}

	return true;
}


int MyTool::C(const OpsGroup& opsg){
	int LSD[MAX_ROOM_NUM][MAX_DAY_NUM];

	memset(LSD, 0, MAX_ROOM_NUM*MAX_DAY_NUM * 4);//����

	for (int i = 0; i < opsg.getSize(); i++)
	{
		LSD[opsg.m_ops_list[i].ops_room][opsg.m_ops_list[i].begin_time / 2] += ops_need_time[opsg.m_ops_list[i].id];
	}

	int Lrest = 0;
	int Lover = 0;
	for (int i = 0; i < MAX_ROOM_NUM; i++)
	{
		for (int j = 0; j < MAX_DAY_NUM; j++)
		{
			int temp = DN[i][j] - LSD[i][j];
			if (temp < 0){
				Lover += abs(temp);
			}
			else{
				Lrest += temp;
			}
		}
	}

	return room_over_cost*Lover + room_rest_cost*Lrest;
}

int MyTool::fitness(const OpsGroup& opsg){
	int lr_result = MyTool::LR(opsg);
	int lp_result = MyTool::LP(opsg);
	int ldc_result = MyTool::LDC(opsg) ? 0 : MYINFINITY;
	int ldl_result = MyTool::LDL(opsg) ? 0 : MYINFINITY;

	if (lr_result > 0 || lp_result > 0 || ldc_result > 0 || ldl_result > 0)
		return P + lr_result + lp_result + ldc_result + ldl_result;
	else
		return C(opsg);
}

void MyTool::mut(OpsGroup& opsg){
	if (rand() % Pmut == Pmut-1){
		int index = rand() % (opsg.getSize() - 1);
		int temp = opsg.m_ops_list[index].id;
		opsg.m_ops_list[index].id = opsg.m_ops_list[index + 1].id;
		opsg.m_ops_list[index + 1].id = temp;
		mut_1_counts++;
		isMuted = true;
	}
	if (rand() % Pmut == Pmut - 1){
		int index = rand() % (opsg.getSize() - 1);
		int doc = findDoctorByOps(opsg.m_ops_list[index].id);
		opsg.m_ops_list[index].begin_time = randomFindBeginTime(doc, DL[opsg.m_ops_list[index].id]);
		mut_2_counts++;
		isMuted = true;
	}
	if (rand() % Pmut == Pmut - 1){
		int index = rand() % (opsg.getSize());
		opsg.m_ops_list[index].ops_room = randomFindRoomByOps(opsg.m_ops_list[index].id);
		mut_3_counts++;
		isMuted = true;
	}
}

void MyTool::mut(OpsGroup& opsg, FILE* f){
	if (rand() % Pmut == Pmut - 1){
		int index = rand() % (opsg.getSize() - 1);
		int temp = opsg.m_ops_list[index].id;
		opsg.m_ops_list[index].id = opsg.m_ops_list[index + 1].id;
		opsg.m_ops_list[index + 1].id = temp;
		mut_1_counts++;
		fprintf(f, "�Ӵ���������1\t");
		isMuted = true;
	}
	if (rand() % Pmut == Pmut - 1){
		int index = rand() % (opsg.getSize() - 1);
		int doc = findDoctorByOps(opsg.m_ops_list[index].id);
		opsg.m_ops_list[index].begin_time = randomFindBeginTime(doc, DL[opsg.m_ops_list[index].id]);
		mut_2_counts++;
		fprintf(f, "�Ӵ���������2\t");
		isMuted = true;
	}
	if (rand() % Pmut == Pmut - 1){
		int index = rand() % (opsg.getSize());
		opsg.m_ops_list[index].ops_room = randomFindRoomByOps(opsg.m_ops_list[index].id);
		mut_3_counts++;
		fprintf(f, "�Ӵ���������3\t");
		isMuted = true;
	}
}

void MyTool::sel(POP& pop){
	sort(pop.m_list.begin(), pop.m_list.end(), MyTool::comp);
	while (pop.m_list.size() > POP_NUM){
		pop.m_list.pop_back();
	}
}