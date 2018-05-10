#include<iostream>
#include "Ops.h"
using namespace std;

void randomArray(int a[], int n) //ϴ���㷨
{
	int index, tmp, i;
	for (i = 0; i<n; i++)
	{
		index = rand() % (n - i) + i;
		if (index != i)
		{
			tmp = a[i];
			a[i] = a[index];
			a[index] = tmp;
		}

	}

}


void run(){
	system("cls");
	clock_t start, finish;
	double totaltime;

	cout << "��������Ⱥ������" << endl;
	while (cin >> POP_NUM){
		if (POP_NUM > 5)
			break;
		else
			cout << "��Ⱥ����̫С���������룺" << endl;
	}
	cout << "���������������" << endl;

	while (cin >> GEN){
		if (GEN > 1)
			break;
		else
			cout << "��������̫�٣��������룺" << endl;
	}

	int *pop_random_array = new int[POP_NUM];
	for (int i = 0; i < POP_NUM; i++)
	{
		pop_random_array[i] = i;
	}

	doc_ops.clear();
	set<int> doc1;
	doc1.insert(1);
	doc_ops.push_back(doc1);
	set<int> doc2;
	doc2.insert(4);
	doc_ops.push_back(doc2);
	set<int> doc3;
	doc3.insert(2);
	doc_ops.push_back(doc3);
	set<int> doc4;
	doc4.insert(0);
	doc4.insert(3);
	doc_ops.push_back(doc4);

	start = clock();//����ʼ��ʱ
	POP pop;

	for (int j = 0; j < POP_NUM; j++)
	{
		OpsGroup ops_group;
		for (int i = 0; i < 5; ++i){
			int doc = MyTool::findDoctorByOps(i);
			int begin_time = MyTool::randomFindBeginTime(doc, DL[i]);
			int room_id = MyTool::randomFindRoomByOps(i);
			ops_group.m_ops_list.push_back(Ops(i, begin_time, room_id));
		}
		pop.m_list.push_back(ops_group);
	}
	MyTool::sel(pop);
	cout << "ԭʼ��Ⱥ��Ӧ��:" << endl;
	for (int i = 0; i < pop.m_list.size(); i++)
	{
		cout << MyTool::fitness(pop.m_list[i]) << " ";
	}
	cout << endl;

	cout << "ÿ����Ⱥ��Ӧ��:" << endl;
	for (int i = 0; i < GEN; i++)
	{
		randomArray(pop_random_array, POP_NUM);
		for (int j = 0; j < POP_NUM; j += 2)
		{
			OpsGroup kid1 = MyTool::cross(pop.m_list[pop_random_array[j]], pop.m_list[pop_random_array[j + 1]], 2, 3);
			OpsGroup kid2 = MyTool::cross(pop.m_list[pop_random_array[j + 1]], pop.m_list[pop_random_array[j]], 2, 3);
			MyTool::mut(kid1);
			MyTool::mut(kid2);
			pop.m_list.push_back(kid1);
			pop.m_list.push_back(kid2);
		}

		MyTool::sel(pop);
		for (int i = 0; i < pop.m_list.size(); i++)
		{
			cout << MyTool::fitness(pop.m_list[i]) << " ";
		}
		cout << endl;
	}


	finish = clock();//�����������ʱ

	cout << "���һ����Ⱥ:" << endl;
	pop.toStr();

	totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
	cout << "\n�˴ε�������ʱ��Ϊ" << totaltime << "�룡" << endl;

	delete[] pop_random_array;
}

int main(){
	srand((unsigned)time(NULL));
	run();
	cout << "����q����..." << endl;
	char q;
	cin >> q;
	while (q == 'q'){
		run();
		cout << "����q����..." << endl;
		cin >> q;
	}
}