#pragma once
#include<vector>
#include<set>
#include<map>
#include<ctime>
#include<algorithm>
using namespace std;

//==========================需要手动更改的配置===========================

static int POP_NUM = 30;	//种群大小
static int GEN = 10;	//迭代次数
const static int Pmut = 100;	//变异概率分母
const static int P = 4000;	//惩罚系数

static bool isMuted = false;

const static int Q1 = 11;	//杂交参数
const static int Q2 = 12;	//杂交参数

const static int MAX_DOC_NUM = 8;	//最多的医生数
const static int MAX_OPS_NUM = 24;	//最多的手术数量
const static int MAX_DAY_NUM = 5;	//最大天数
const static int MAX_PERIOD_PER_DAY = 2;	//一天分段数
const static int MAX_PERIOD_NUM = MAX_PERIOD_PER_DAY * MAX_DAY_NUM;	//总分段数量
const static int MAX_ROOM_NUM = 5;	//总手术室数
const static int MYINFINITY = 1000000;	//自己定义的无限大


static int dayliy_resource_num[MAX_DAY_NUM] = { 60, 60, 60, 60, 60 };	//每天的资源数
static int ops_resource_num[MAX_OPS_NUM] = { 2, 3, 4, 2, 4, 2, 2, 1, 4, 4, 1, 5, 2, 2, 2, 4, 4, 3, 3, 2, 2, 5, 2, 3 };	//每个手术需要的资源
static int ops_need_time[MAX_OPS_NUM] = { 3, 3, 5, 3, 4, 3, 3, 1, 4, 3, 2, 5, 3, 3, 2, 4, 4, 4, 4, 3, 3, 4, 3, 3 };	//每个手术需要的时间
static int DN[MAX_ROOM_NUM][MAX_DAY_NUM] = { 8, 6, 8, 6, 8, 8, 6, 8, 6, 8, 8, 6, 8, 6, 8, 8, 6, 8, 6, 8, 8, 6, 8, 6, 8 };	//DN
static int DM[MAX_ROOM_NUM][MAX_DAY_NUM] = { 12, 8, 12, 8, 12, 12, 8, 12, 8, 12, 12, 8, 12, 8, 12, 12, 8, 12, 8, 12, 12, 8, 12, 8, 12 };	//DM

//=======需要-1的数据========
static int DL[MAX_OPS_NUM] = { 3, 2, 2, 3, 5, 5, 5, 4, 4, 4, 4, 5, 4, 4, 3, 3, 3, 3, 5, 5, 4, 3, 2, 4 };	//每个手术的最晚完成时间
//===========================

map<int, int> dayliy_nurse_num;
map<int, int> dayliy_anesthetist_num;
map<int, int> nurse_always_num_by_ops;
map<int, int> nurse_temply_num_by_ops;
map<int, int> anesthetist_always_num_by_ops;
map<int, int> anesthetist_temply_num_by_ops;

static int room_rest_cost = 5;	//手术室空闲成本
static int room_over_cost = 6;	//手术室超时成本

static int RC[MAX_DOC_NUM][MAX_PERIOD_NUM] = { 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 };	//医生空闲时间
static int Qjs[MAX_OPS_NUM][MAX_ROOM_NUM] = { 1, 1, 0, 0, 1,
0, 1, 1, 1, 1,
0, 1, 0, 1, 1,
1, 0, 1, 1, 0,
1, 0, 1, 0, 0,
1, 1, 0, 0, 1,
0, 1, 1, 1, 1,
0, 1, 0, 1, 0,
0, 1, 1, 0, 0,
1, 0, 0, 1, 1,
0, 1, 1, 1, 0,
1, 0, 0, 1, 1,
0, 1, 0, 1, 1,
1, 0, 1, 0, 0,
1, 1, 0, 1, 1,
0, 0, 1, 1, 1,
0, 1, 0, 1, 1,
0, 1, 0, 1, 1,
1, 0, 1, 0, 1,
1, 1, 0, 0, 0,
1, 0, 1, 1, 0,
0, 1, 0, 0, 1,
0, 1, 1, 1, 1,
0, 1, 0, 0, 1
};	//手术与手术室的关系
vector<set<int> > doc_ops;
void initDoc_Ops(){
	doc_ops.clear();
	set<int> doc1;
	doc1.insert(1);
	doc1.insert(3);
	doc1.insert(5);
	doc1.insert(13);
	doc_ops.push_back(doc1);
	set<int> doc2;
	doc2.insert(0);
	doc2.insert(9);
	doc2.insert(15);
	doc2.insert(20);
	doc_ops.push_back(doc2);
	set<int> doc3;
	doc3.insert(21);
	doc3.insert(22);
	doc_ops.push_back(doc3);
	set<int> doc4;
	doc4.insert(23);
	doc_ops.push_back(doc4);
	set<int> doc5;
	doc5.insert(6);
	doc5.insert(12);
	doc5.insert(18);
	doc5.insert(19);
	doc_ops.push_back(doc5);
	set<int> doc6;
	doc6.insert(2);
	doc6.insert(4);
	doc6.insert(7);
	doc6.insert(8);
	doc_ops.push_back(doc6);
	set<int> doc7;
	doc7.insert(10);
	doc7.insert(16);
	doc_ops.push_back(doc7);
	set<int> doc8;
	doc8.insert(11);
	doc8.insert(14);
	doc8.insert(17);
	doc_ops.push_back(doc8);
}
//==========================需要手动更改的配置（完）=======================
//=============统计相关数据的变量======================
static int mut_1_counts = 0; //变异1发生的次数
static int mut_2_counts = 0; //变异2发生的次数
static int mut_3_counts = 0; //变异3发生的次数
//=============统计相关数据的变量（完）================
void initRecord(){
	mut_1_counts = 0;
	mut_2_counts = 0;
	mut_3_counts = 0;
}

class Ops{//I里面的三元素个体
public:
	Ops(int ID, int bt, int room) :id(ID), begin_time(bt), ops_room(room){

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

class OpsGroup{//一个I
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
	static int findDoctorByOps(int ops_id);	//通过手术编号找ID
	static int randomFindBeginTime(int doc, int deadline);	//通过医生和DL随机找开始时间
	static int randomFindRoomByOps(int ops_id);	//通过手术编号随机找房间
	static int fitness(const OpsGroup& opsg);	//适应性函数
	static OpsGroup cross(const OpsGroup& lhs, const  OpsGroup& rhs, int q1, int q2);	//杂交函数
	static void mut(OpsGroup& opsg);	//变异
	static void mut(OpsGroup& opsg, FILE* f);	//变异
	static void sel(POP &pop);	//选择函数
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
		cout << "个体" << i << ":" << endl;
		m_list[i].toStr();
	}
	cout << endl;
}

void POP::writeFile(FILE* f){
	for (int i = 0; i < m_list.size(); i++)
	{
		fprintf(f, "个体%d:(适应度:%d)\n", i + 1, MyTool::fitness(m_list[i]));
		m_list[i].writeFile(f);
		fprintf(f, "\n");
	}
}

bool MyTool::comp(const OpsGroup& og1, const OpsGroup& og2){
	return MyTool::fitness(og1) < MyTool::fitness(og2);
}

int MyTool::randomInVector(const vector<int>& vec){
	return vec[rand() % vec.size()];
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

	memset(LP, 0, MAX_ROOM_NUM*MAX_DAY_NUM * 4);//清零

	for (int i = 0; i < opsg.getSize(); i++)
	{
		LP[opsg.m_ops_list[i].ops_room][opsg.m_ops_list[i].begin_time / 2] += ops_need_time[opsg.m_ops_list[i].id];
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

	memset(LSD, 0, MAX_ROOM_NUM*MAX_DAY_NUM * 4);//清零

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
	if (rand() % Pmut == Pmut - 1){
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
		fprintf(f, "子代发生变异1\t");
		isMuted = true;
	}
	if (rand() % Pmut == Pmut - 1){
		int index = rand() % (opsg.getSize() - 1);
		int doc = findDoctorByOps(opsg.m_ops_list[index].id);
		opsg.m_ops_list[index].begin_time = randomFindBeginTime(doc, DL[opsg.m_ops_list[index].id]);
		mut_2_counts++;
		fprintf(f, "子代发生变异2\t");
		isMuted = true;
	}
	if (rand() % Pmut == Pmut - 1){
		int index = rand() % (opsg.getSize());
		opsg.m_ops_list[index].ops_room = randomFindRoomByOps(opsg.m_ops_list[index].id);
		mut_3_counts++;
		fprintf(f, "子代发生变异3\t");
		isMuted = true;
	}
}

void MyTool::sel(POP& pop){
	sort(pop.m_list.begin(), pop.m_list.end(), MyTool::comp);
	while (pop.m_list.size() > POP_NUM){
		pop.m_list.pop_back();
	}
}