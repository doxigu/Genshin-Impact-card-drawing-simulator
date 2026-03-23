#include<iostream>
#include"模拟器.h"
using namespace std;

void KACHI::addjilu(const KA& card)// 记录抽到的卡牌
{
    if (jilu.count(card.name)) //按名称判断obtained中是否已有该卡牌
    {
        jilu[card.name].second++; // 已有该卡，数量+1
    }
    else 
    {
        jilu[card.name] = { card.xi, 1 }; // 新卡，初始化其数量为1
    }
}

void KACHI::showjilu()// 查看已获得卡牌
{
    // 获取控制台句柄+保存默认颜色（避免全局变色）
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    WORD defaultColor = csbi.wAttributes;

    cout << "\n===== 已获得卡牌 =====\n";

    if (jilu.empty()) 
    {
        cout << "  暂无已获得卡牌\n";
    }
    else 
    {
        for (auto& p : jilu) 
        {
            string rarity = p.second.first;

            // 颜色配置：金卡金色、紫卡紫色、蓝卡蓝色
            if (rarity == "【★★★★★】") SetConsoleTextAttribute(hConsole, 14);  // 金色
            else if (rarity == "★★★★★") SetConsoleTextAttribute(hConsole, 14); // 金色
            else if (rarity == "★★★★") SetConsoleTextAttribute(hConsole, 13);  // 紫色
            else if (rarity == "★★★") SetConsoleTextAttribute(hConsole, 9);   // 蓝色

            // 立即恢复默认颜色
            SetConsoleTextAttribute(hConsole, defaultColor);
        }
    }

    cout << "\n【★★★★★ up金卡】：\n";
    bool has_gold = false;
    for (auto& p : jilu) 
    {
        string rarity = p.second.first;

        if (rarity == "【★★★★★】") 
        {
            SetConsoleTextAttribute(hConsole, 14); // 金色
            cout << "  " << p.first << " ×" << p.second.second << "\n";
            SetConsoleTextAttribute(hConsole, defaultColor);
            has_gold = true;
        }
    }
    if (!has_gold) cout << "  暂无\n";

    cout << "\n【★★★★★ 常驻金卡】：\n";
    bool has_wj = false;
    for (auto& p : jilu) 
    {
        string rarity = p.second.first;

        if (rarity == "★★★★★") 
        {
            SetConsoleTextAttribute(hConsole, 14); // 金色
            cout << "  " << p.first << " ×" << p.second.second << "\n";
            SetConsoleTextAttribute(hConsole, defaultColor);
            has_wj = true;
        }
    }
    if (!has_wj) cout << "  暂无\n";

    cout << "\n【★★★★ 紫卡】：\n";
    bool has_purple = false;
    for (auto& p : jilu) 
    {
        string rarity = p.second.first;

        if (rarity == "★★★★") 
        {
            SetConsoleTextAttribute(hConsole, 13); // 紫色
            cout << "  " << p.first << " ×" << p.second.second << "\n";
            SetConsoleTextAttribute(hConsole, defaultColor);
            has_purple = true;
        }
    }
    if (!has_purple) cout << "  暂无\n";

    cout << "\n【★★★ 蓝卡】：\n";
    bool has_blue = false;
    for (auto& p : jilu) 
    {
        string rarity = p.second.first;
        
        if (rarity == "★★★") {
            SetConsoleTextAttribute(hConsole, 9); // 蓝色
            cout << "  " << p.first << " ×" << p.second.second << "\n";
            SetConsoleTextAttribute(hConsole, defaultColor);
            has_blue = true;
        }
    }
    if (!has_blue) cout << "  暂无\n";

    cout << "======================\n";
}

//查看当前卡池信息
void KACHI::view(const vector<KA>& card, int a)
{
    cout << "当前卡池中的up金卡为：" << endl;
    if (a % 2 == 0) 
        cout << J[0].xi << J[0].name << endl;
    else 
        cout << J[1].xi << J[1].name << endl;

    cout << "当前卡池中的常驻金卡为：" << endl;
    for (const auto& ka : WJ) cout << ka.xi << " " << ka.name << endl;
        
    cout << "当前卡池中的紫卡为：" << endl;
    for (const auto& ka : Z) cout << ka.xi << " " << ka.name << endl;

    cout << "当前卡池中的蓝卡为：" << endl;
    for (const auto& ka : L) cout << ka.xi << " " << ka.name << endl;
}