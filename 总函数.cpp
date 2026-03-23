#include<iostream>
#include <ctime>// 有关生成随机数的头文件
#include"模拟器.h"
using namespace std;

//外部变量声明
extern vector<KA> j;
extern vector<KA> wj;
extern vector<KA> z;
extern vector<KA> l;
static int c ;//用于切换角色卡池

int main()
{
	srand((unsigned)time(NULL)); // 根据系统时间初始化随机数种子
	KACHI yuan(j, wj, z, l);
	YUANSHI shi;
    void menu(KACHI yuan,YUANSHI a);
	int a = 1;
	menu(yuan,shi);

	while (a != 0)    
	{
		cin >> a;
		switch (a)
		{
		case 1://单抽
			system("cls");//清屏操作
			if (shi.num >= 160)
			{
				shi.num -= 160;
				menu(yuan, shi);
				yuan.choukaxitong(a);
			}
			else
			{
				menu(yuan, shi);
				cout << "原石不足" << endl;
			}
			break;
		case 2://十连抽
			system("cls");
			if (shi.num >= 1600)
			{
				shi.num -= 1600;
				menu(yuan, shi);
				yuan.choukaxitong(a);
			}
			else
			{
				menu(yuan, shi);
				cout << "原石不足" << endl;
			}
			break;
		case 3://切换角色卡池
			c++;
			yuan.choukaxitong(a);
			system("cls");
			menu(yuan,shi);
			cout << "切换完毕" << endl;
			break;
		case 4://查看卡池信息
			system("cls");
			menu(yuan,shi);
			yuan.view((j,wj,z,l), c);
			break;
		case 5://查看抽卡规则
			system("cls");
			menu(yuan, shi);
			cout << endl;
			cout << "                           160原石抽一次                              " << endl;
			cout << endl;
			cout << "                          九十抽内必出金卡                            " << endl;
			cout << endl;
			cout << "                      十抽内必出紫或紫以上品质                        " << endl;
			cout << endl;
			cout << "                抽出金卡时有50%概率得到指定的当期up角色               " << endl; 
			cout << endl;
			cout << "  若本次抽出金卡时未能得到指定的当期up角色，则下次出金必定锁定up角色  " << endl;
			break;
		case 6://查看已获得角色
			system("cls");
			menu(yuan,shi);
			yuan.showjilu(); 
			break;
		case 7://补充原石
			system("cls");
			shi.buchong();
			menu(yuan,shi);
			cout << "您的原石已增加了16000个" << endl;
			break;
		case 8://重置抽卡
			c = 0;
			system("cls");
			yuan.resetDraw();
			shi.reset();
			menu(yuan, shi);
			cout << "抽卡模拟器已重置\n";
			break;
		case 0://退出抽卡模拟器
			system("cls");
			cout << "已退出抽卡模拟器" << endl;
			return 0;
		default: // 输入无效时提示
			system("cls");
			menu(yuan, shi);
			cout << "输入无效！请输入0-8之间的数字\n";
			break;
		}
	}
}

void menu(KACHI yuan, YUANSHI a)
{
	cout << "欢迎使用原神抽卡模拟器" << endl;
	if(c % 2 ==0)cout << "当前up卡池中五星角色为：" <<j[0].name<< endl;
	else if (c % 2 == 1)cout << "当前up卡池中五星角色为：" << j[1].name << endl;
	cout << "当前剩余原石为：" <<a.num<< endl;
	cout << "==============================" << endl;
	cout << "1、单抽（消耗160原石）" << endl;
	cout << "2、十连抽（消耗1600原石）" << endl;
	cout << "3、切换角色卡池" << endl;
	cout << "4、查看卡池信息" << endl;
	cout << "5、查看抽卡规则" << endl;
	cout << "6、查看已获得角色" << endl;
	cout << "7、补充原石" << endl;
	cout << "8、重置抽卡" << endl;
	cout << "0、退出抽卡模拟器" << endl;
	cout << "==============================" << endl;
}
