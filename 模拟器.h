#include<iostream>
#include<string>
#include <vector> // 用于引入vector头文件：能自动管理内存，无需关心数组大小的容器
#include <map>  // 用于存储已获得卡牌（名称→<稀有度, 数量>）
#include <windows.h> // 控制台颜色控制需要
using namespace std;

struct KA // 卡：包括四、五星角色与三星武器
{
    string xi;//稀有度
    string name;
};

class DONGHUA //动画类
{
public:
    // 安全输出彩色文本的函数（自动恢复颜色）
    void printColored(const string& text, const string& rarity);

    //进度条动画
    void drawLoadingBar(int maxQuality);

    // 金卡星级动画：
    void printNameStarAnimation();

    //金卡闪烁动画
    void blinkGoldCard(const string& serial, const string& name);
};


class YUANSHI
{
public:
    int num = 16000;
    void buchong() { num += 16000; }
    void reset() { num = 16000; }
};

class KACHI //卡池
{
private:
    vector<KA> J; // 金卡
    vector<KA> WJ; // 歪了的金卡
    vector<KA> Z; // 紫卡
    vector<KA> L; // 蓝卡

    map<string, pair<string, int>> jilu;   
    DONGHUA d;
public:
    KACHI(const vector<KA>& j, const vector<KA>& wj, const vector<KA>& z, const vector<KA>& l) : J(j), WJ(wj), Z(z), L(l) {}
    void choukaxitong(int a);
    void show(const vector<KA>& card, int n);
    void show(const vector<KA>& card, int n, int s);
    void view(const vector<KA>& card, int a);//查看卡池信息
    void resetDraw(); // 重置保底计数
    void addjilu(const KA& card); // 记录抽到的卡牌
    void showjilu();// 查看已获得卡牌
};