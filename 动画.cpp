#include <iostream>
#include <locale> // 宽字符本地化
#include"模拟器.h"
using namespace std;

// 在当前文件初始化宽字符支持
static auto init_locale = []() {
    setlocale(LC_ALL, ""); // 启用控制台宽字符显示★
    return 0;
    }(); // 全局匿名函数，程序启动时自动执行,无需手动调用

// 安全输出彩色文本的函数（自动恢复颜色）
void  DONGHUA::printColored(const string& text, const string& rarity) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);//获取控制台句柄
    CONSOLE_SCREEN_BUFFER_INFO csbi;//定义存储控制台状态的结构体，用于保存默认颜色
    GetConsoleScreenBufferInfo(hConsole, &csbi);//获取文本默认颜色
    WORD defaultColor = csbi.wAttributes; // 保存默认颜色

    // 设置颜色
    string r = rarity;
    //根据处理后的稀有度设置对应颜色
    if (r == "【★★★★★】") SetConsoleTextAttribute(hConsole, 14); 
    else if (r == "★★★★★") SetConsoleTextAttribute(hConsole, 14);
    else if (r == "★★★★") SetConsoleTextAttribute(hConsole, 13);
    else if (r == "★★★") SetConsoleTextAttribute(hConsole, 9);

    //输出卡牌文本
    cout << text;

    // 强制恢复默认颜色
    SetConsoleTextAttribute(hConsole, defaultColor);
}

// 加载条动画：
void  DONGHUA::drawLoadingBar(int maxQuality) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    WORD defaultColor = csbi.wAttributes;

    const int barLength = 20;//进度条总格子数
    const int sleepTime = 75; //每格绘制间隔 75ms，控制动画速度
    const int colorTriggerIdx = barLength - 5; // 第16格开始触发全条变色

    cout << "\r"; // 清空行
    for (int i = 0; i <= barLength; i++) { // i是当前加载进度（已填充的格子数）
        cout << "\r["; // 回到行首重新绘制

        // 判断是否触发全条变色：进度走到最后5格（i >= 16）
        bool isFullColor = (i >= colorTriggerIdx);

        for (int j = 0; j < barLength; j++) { // j是每个格子的位置
            // ========== 核心：最后5格时，整个加载条都变色 ==========
            if (isFullColor) { // 进度到最后5格，所有已填充格子都上色
                switch (maxQuality) {
                case 1: 
                    SetConsoleTextAttribute(hConsole, 14); 
                    break; 
                case 3: 
                    SetConsoleTextAttribute(hConsole, 13); 
                    break; 
                default: 
                    SetConsoleTextAttribute(hConsole, 9); 
                    break; 
                }
            }

            // 绘制进度：j < i 显示█（已填充），否则显示空格（未填充）
            cout << (j < i ? "█" : " ");

            // 恢复默认颜色，避免污染后续字符
            SetConsoleTextAttribute(hConsole, defaultColor);
        }

        cout << "]";
        cout.flush(); // 强制刷新，避免动画卡顿
        Sleep(sleepTime);
    }
    cout << endl; // 加载完成后换行
}

// 金卡星级动画：
void  DONGHUA::printNameStarAnimation() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    WORD defaultColor = csbi.wAttributes;

    SetConsoleTextAttribute(hConsole, 14); // 金色

    wchar_t stars[] = L"★★★★★"; // 用宽字符数组存储星星，避免问号产生
    const int starDelay = 300;

    // 逐个输出5个星星，每个都刷新
    for (int i = 0; i < 5; i++) {
        // 输出宽字符星星，同时避免乱码
        wcout << stars[i];
        wcout.flush(); // 强制刷新宽字符输出
        Sleep(starDelay);//输出每个星星之间时间间隔300毫秒
    }

    SetConsoleTextAttribute(hConsole, defaultColor); // 恢复默认颜色
}
//金卡闪烁动画
void  DONGHUA::blinkGoldCard(const string& serial, const string& name) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    WORD defaultColor = csbi.wAttributes;
    SetConsoleTextAttribute(hConsole, 14);

    // 金卡动画
    cout << serial + "、";
    cout.flush();
    printNameStarAnimation(); // 调用星级动画函数
    cout << " " << name;
    cout.flush();
    Sleep(200); // 闪烁前停顿200毫秒

    // 闪烁
    int blinkTimes = 3;// 闪烁3次
    int interval = 200;// 闪烁间隔200毫秒
    string fullText = serial + "、★★★★★ " + name;//用于获取文本长度
    for (int i = 0; i < blinkTimes; i++) {
        // 隐藏内容
        cout << string(fullText.size(), '\b');//输出n个退格符，即回到文本开头
        cout << string(fullText.size(), ' ');//输出n个空格，用于覆盖文本
        cout << string(fullText.size(), '\b');
        cout.flush();
        Sleep(interval);

        // 显示内容
        cout << fullText;
        cout.flush();
        Sleep(interval);
    }

    SetConsoleTextAttribute(hConsole, defaultColor);
}
