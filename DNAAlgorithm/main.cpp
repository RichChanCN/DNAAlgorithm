#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include "Ops.h"

using namespace std;

void randomArray(int a[], int n) //洗牌算法
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
	initRecord();
	clock_t start, finish;
	double totaltime;

	time_t cur_time = time(NULL);
	tm* loc_time = localtime(&cur_time);
	char detail_filename[100] = { 0 };
	char result_filename[100] = { 0 };
	sprintf(detail_filename, "%d年%02d月%02d日%02d时%02d分%02d秒Details.txt", loc_time->tm_year + 1900, loc_time->tm_mon + 1, loc_time->tm_mday, loc_time->tm_hour, loc_time->tm_min, loc_time->tm_sec);
	sprintf(result_filename, "%d年%02d月%02d日%02d时%02d分%02d秒Results.txt", loc_time->tm_year + 1900, loc_time->tm_mon + 1, loc_time->tm_mday, loc_time->tm_hour, loc_time->tm_min, loc_time->tm_sec);

	FILE* detail_file = fopen(detail_filename, "w");
	FILE* result_file = fopen(result_filename, "w");
	if (detail_file == NULL || result_file == NULL){
		cout << "创建文件失败！";
		return;
	}

	cout << "请输入种群数量：" << endl;
	while (cin >> POP_NUM){
		if (POP_NUM > 5){
			fprintf(detail_file, "种群数量:%d\n", POP_NUM);
			break;
		}
		else
			cout << "种群数量太小，重新输入：" << endl;
	}
	cout << "请输入迭代次数：" << endl;

	while (cin >> GEN){
		if (GEN > 1){
			fprintf(detail_file, "迭代次数:%d\n", GEN);
			break;
		}
		else
			cout << "迭代次数太少，重新输入：" << endl;
	}

	int *pop_random_array = new int[POP_NUM];
	for (int i = 0; i < POP_NUM; i++)
	{
		pop_random_array[i] = i;
	}

	initDoc_Ops();

	start = clock();//程序开始计时
	POP pop;

	for (int j = 0; j < POP_NUM; j++)
	{
		OpsGroup ops_group;
		for (int i = 0; i < MAX_OPS_NUM; ++i){
			int doc = MyTool::findDoctorByOps(i);
			int begin_time = MyTool::randomFindBeginTime(doc, DL[i]);
			int room_id = MyTool::randomFindRoomByOps(i);
			ops_group.m_ops_list.push_back(Ops(i, begin_time, room_id));
		}
		pop.m_list.push_back(ops_group);
	}
	MyTool::sel(pop);
	fprintf(detail_file, "原始种群:\n");
	pop.writeFile(detail_file);

	fprintf(result_file, "原始种群:\n");
	pop.writeFile(result_file);

	//cout << "原始种群适应度:" << endl;
	fprintf(result_file, "原始种群适应度:\n");
	for (int i = 0; i < pop.m_list.size(); i++)
	{
		fprintf(result_file, "%d ", MyTool::fitness(pop.m_list[i]));
		//cout << MyTool::fitness(pop.m_list[i]) << " ";
	}
	fprintf(result_file, "\n");
	//cout << endl;

	//cout << "\n每代种群适应度:" << endl;
	fprintf(result_file, "每代种群适应度:\n");
	fprintf(detail_file, "每代种群:\n");
	for (int i = 0; i < GEN; i++)
	{
		fprintf(result_file, "第%d代种群适应度:\t", i + 1);
		randomArray(pop_random_array, POP_NUM);
		for (int j = 0; j < POP_NUM; j += 2)
		{
			OpsGroup kid1 = MyTool::cross(pop.m_list[pop_random_array[j]], pop.m_list[pop_random_array[j + 1]], Q1, Q2);
			OpsGroup kid2 = MyTool::cross(pop.m_list[pop_random_array[j + 1]], pop.m_list[pop_random_array[j]], Q1, Q2);
			MyTool::mut(kid1, result_file);
			MyTool::mut(kid2, result_file);
			pop.m_list.push_back(kid1);
			pop.m_list.push_back(kid2);
		}

		fprintf(result_file, "\n");

		MyTool::sel(pop);
		fprintf(detail_file, "第%d代种群:\n", i + 1);
		pop.writeFile(detail_file);
		for (int i = 0; i < pop.m_list.size(); i++)
		{
			fprintf(result_file, "%d ", MyTool::fitness(pop.m_list[i]));
			//cout << MyTool::fitness(pop.m_list[i]) << " ";
		}
		fprintf(result_file, "\n");
		//cout << endl;
	}


	finish = clock();//程序结束运行时

	//cout << "最后一个种群:" << endl;
	fprintf(result_file, "\n最后一个种群:\n");
	pop.writeFile(result_file);
	//pop.toStr();

	totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
	cout << "\n此次迭代运行时间为(包括写文件的时间)" << totaltime << "秒！" << endl;
	cout << "\n请到文件中查看详细信息！" << endl;

	fprintf(result_file, "\n此次迭代发生的变异情况为:变异1:%d次，变异2:%d次，变异3:%d次\n", mut_1_counts, mut_2_counts, mut_3_counts);
	fprintf(result_file, "\n此次迭代运行时间为(包括写文件的时间):%0.3f\n", totaltime);

	delete[] pop_random_array;
	fclose(detail_file);
	fclose(result_file);
}

int main(){
	srand((unsigned)time(NULL));
	run();
	cout << "输入q继续..." << endl;
	char q;
	cin >> q;
	while (q == 'q'){
		run();
		cout << "输入q继续..." << endl;
		cin >> q;
	}
}