#include <iostream>
#include <cmath>
#include"模拟器.h"
using namespace std;

void KACHI::show(const vector<KA>& card,int n)
{
   int length = card.size();// 结构体数组的长度
   int a = rand() % length;// 生成随机数后取模
   string rarity = card[a].xi;
   string name = card[a].name;

   if (rarity == "★★★★★") 
   {
       HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
       CONSOLE_SCREEN_BUFFER_INFO csbi;
       GetConsoleScreenBufferInfo(hConsole, &csbi);
       WORD defaultColor = csbi.wAttributes;

       // 调用动画
       d.blinkGoldCard(to_string(n), name);

       // 换行+恢复默认颜色
       cout << "\n";
       SetConsoleTextAttribute(hConsole, defaultColor);
   }
   else 
   {
       string outputText = to_string(n) + "、" + rarity + " " + name + "\n";
       d.printColored(outputText, rarity);
   }
  
   this->addjilu(card[a]); //记录这张抽到的卡
}

void KACHI::show(const vector<KA>& card, int n,int c)//重载：用于切换金卡卡池
{
    int a = (c % 2 == 0) ? 0 : 1;
    string rarity = card[a].xi;
    string name = card[a].name;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    WORD defaultColor = csbi.wAttributes;

    d.blinkGoldCard(to_string(n), name);
    cout << "\n";
    SetConsoleTextAttribute(hConsole, defaultColor);
    
    this->addjilu(card[a]);
}

static int n = 1;//不出金的抽数
static int k = 1;//不出金或紫的抽数
static int w = 0;//歪卡次数
static int c ;//用于切换角色卡池

void KACHI::choukaxitong(int a) //抽卡系统
{
    if (a == 3)
    {
        c++;
        return;
    }
    // a==1单抽，a==2十连
    int s = (a == 1) ? 1 : 10;
    int chouka(int n, int k, int w);

    int actualMaxQuality = 4;//用于加载条颜色

    vector<int> drawResults;//用于保存数字结果
    
    // 这几个变量用于静默抽卡：先算结果再显示，避免动画效果卡顿
    int temp_n = n, temp_k = k, temp_w = w;
    int temp_count = 0;

    while (temp_count < s)
    {
        int res = chouka(temp_n, temp_k, temp_w);
        drawResults.push_back(res);// 保存数字结果到动态数组，让下面的while也能用

        // 这里仅用于计算，不影响全局
        if (res == 1) { temp_n = 1; temp_k = 1; temp_w = 0; }
        else if (res == 2) { temp_n = 1; temp_k = 1; temp_w++; }
        else if (res == 3) { temp_n++; temp_k = 1; }
        else { temp_n++; temp_k++; }
        temp_count++;

        // 更新实际最高品质（加载条颜色用）
        if (res <= 2 && res > 0) actualMaxQuality = 1;
        else if (res == 3 && actualMaxQuality > 3) actualMaxQuality = 3;
    }
    // 画加载条
    d.drawLoadingBar(actualMaxQuality);

    int count = 0;
    while (count < s)
    {
        int drawResult = drawResults[count];
        if (drawResult == 1) 
        {
            show(J, n, c);           
            n = 1;    
            k = 1;
            w = 0;            
        }
        else if (drawResult == 2) 
        {           
            show(WJ, n);            
            n = 1;
            k = 1;
            w++;
        }
        else if (drawResult == 3) 
        {
            show(Z, n);
            k = 1;
            n++;
        }
        else 
        {
            show(L, n);
            n++;
            k++;
        }     
        count++;

        // 十连时每次抽卡延迟150毫秒 
        if (s == 10) {
            Sleep(150); // Windows系统延迟函数
        }
    }
}
    
double jgailv(int n) // 计算第 n 抽的出金概率
{
    const double chugailv = 0.0006;    // 第一抽的初概率：0.06%；90抽为保底，概率为100%
    const double growthrate = 1.0788;    // 指数增长率
    if (n == 90) return 1.0;
    return chugailv * pow(growthrate, n - 1);
}
double zgailv(int k)// 10连保底出金或紫机制：计算第 k 抽的出紫概率
{
    //第一抽的初概率：1%；连续9抽不出金或紫，则第10抽在不出金时，出紫概率为100% 
    const double chugailv = 0.01;       //出紫初概率：1 %
    const double growthrate = 1.668;    // 指数增长率
    if (k == 10) return 1.0;
    return chugailv * pow(growthrate, k - 1);
}

int chouka(int n,int k,int w) // 模拟一次抽卡
{
    double roll = (double)rand() / RAND_MAX;// 生成零到一之间的随机数
    /*RAND_MAX的定义：表示 rand() 能返回的最大值。
    此处用途：被随机数除后，确定随机数在零到一区间内的位置。*/

    if (roll < jgailv(n))
    {
        return (w == 1) ? 1 : rand() % 2 + 1;
        //若已歪了一次，则返回1；若未歪过，则1或2随机返回
    }
    else
    {
        if (roll < zgailv(k))
        {
            return 3;//出紫
        }
        else return 4;//出蓝
    }
}

void KACHI::resetDraw() // 重置抽卡
{
    n = 1; // 不出金次数重置
    k = 1; // 不出金紫次数重置
    w = 0; // 歪卡次数重置
    c = 0; // 卡池切换标记重置 
    jilu.clear(); // 清空已获得卡牌
    cout << "抽卡数据已重置！\n";
}

