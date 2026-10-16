#include <iostream>
#include <iomanip>
#include <conio.h>
#include <Windows.h>
#include "cmd_console_tools.h"
#include "90-01-b1-hanoi.h"
using namespace std;

/* ----------------------------------------------------------------------------------

     本文件功能：
	1、存放被 hanoi_main.cpp 中根据菜单返回值调用的各菜单项对应的执行函数

     本文件要求：
	1、不允许定义外部全局变量（const及#define不在限制范围内）
	2、允许定义静态全局变量（具体需要的数量不要超过文档显示，全局变量的使用准则是：少用、慎用、能不用尽量不用）
	3、静态局部变量的数量不限制，但使用准则也是：少用、慎用、能不用尽量不用
	4、按需加入系统头文件、自定义头文件、命名空间等

   ----------------------------------------------------------------------------------- */

static int num = 0;
static int top1 = 0, top2 = 0, top3 = 0;
static int a[10], b[10], c[10];
static int delay;

void input(int *n,char *src,char *dst,int *sel,int *x,int *z)
{
    cout << endl;
    cout << endl;
    cout << endl;
    while (1) {
        cout << "请输入汉诺塔的层数(1-10)" << endl;
        cin >> *n;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(2000, '\n');
        }
        else if (*n >= 1 && *n <= 10) {
            cin.clear();
            cin.ignore(2000, '\n');
            break;
        }
    }
    while (1) {
        cout << "请输入起始柱(A-C)" << endl;
        cin >> *src;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(2000, '\n');
            continue;
        }
        else if (*src == 'A' || *src == 'a') {
            *src = 'A';
            *x = 0;
        }
        else if (*src == 'B' || *src == 'b') {
            *src = 'B';
            *x = 1;
        }
        else if (*src == 'C' || *src == 'c') {
            *src = 'C';
            *x = 2;
        }
        else {
            cin.clear();
            cin.ignore(2000, '\n');
            continue;
        }
        cin.clear();
        cin.ignore(2000, '\n');
        break;
    }
    while (1) {
        cout << "请输入目标柱(A-C)" << endl;
        cin >> *dst;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(2000, '\n');
            continue;
        }
        else {
            if (*dst == 'A' || *dst == 'a') {
                *dst = 'A';
                *z = 0;
            }
            else if (*dst == 'B' || *dst == 'b') {
                *dst = 'B';
                *z = 1;
            }
            else if (*dst == 'C' || *dst == 'c') {
                *dst = 'C';
                *z = 2;
            }
            else {
                cin.clear();
                cin.ignore(2000, '\n');
                continue;
            }
            if (*dst != *src) {
                cin.clear();
                cin.ignore(2000, '\n');
                break;
            }
            else if (*dst == *src) {
                cout << "目标柱(" << *dst << ")不能与起始柱(" << *src << ")相同" << endl;
                cin.clear();
                cin.ignore(2000, '\n');
                continue;
            }
        }
    }
    if (*sel == 4 || *sel == 8) {
        while (1) {
            cout << "请输入移动速度(0-5: 0-按回车单步演示 1-延时最长 5-延时最短)" << endl;
            cin >> delay;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(2000, '\n');
            }
            else if (delay >= 0 && delay <= 5) {
                cin.clear();
                cin.ignore(2000, '\n');
                break;
            }
        }
        return;
    }
}

void order(char* p_src, char* p_dst)
{
    int i, j, k;
    char str[80];
    for (i = 0; i < 80; i++) {
        str[i] = 0;
    }
    cct_gotoxy(base_x, base_y + 23);
    cout << "请输入移动的柱号（命令形式：AC=A顶端的盘子移动到C，Q=退出）：";
    for (k = 0; k < 40; k++) {
        cout << " ";
    }
    cct_gotoxy(base_x + 61, base_y + 23);
    while (1) {
        cin >> str;
        *p_src = str[0];
        *p_dst = str[1];
        if (*p_src == 'Q' || *p_src == 'q') {
            *p_src = '0';
            cct_gotoxy(base_x, base_y + 24);
            cout << "游戏中止！" << endl;
            return;
        }
        if (cin.fail()) {
            cin.clear();
            cin.ignore(2000, '\n');
        }
        else if (str[2] != 0) {
            cin.clear();
            cin.ignore(2000, '\n');
            cct_gotoxy(base_x + 61, base_y + 23);
            for (k = 0; k < 40; k++) {
                cout << " ";
            }
            cct_gotoxy(base_x + 61, base_y + 23);
            continue;
        }
        else if ((*p_src == 'A' || *p_src == 'B' || *p_src == 'C' ||
            *p_dst == 'A' || *p_dst == 'B' || *p_dst == 'C' ||
            *p_src == 'a' || *p_src == 'b' || *p_src == 'c' ||
            *p_dst == 'a' || *p_dst == 'b' || *p_dst == 'c')&&(*p_src!=*p_dst))
        {
            if (*p_src == 'A' || *p_src == 'a') {
                *p_src = 'A';
                i = a[top1 - 1];
            }
            else if (*p_src == 'B' || *p_src == 'b') {
                *p_src = 'B';
                i = b[top2 - 1];
            }
            else {
                *p_src = 'C';
                i = c[top3 - 1];
            }
            if (*p_dst == 'A' || *p_dst == 'a') {
                *p_dst = 'A';
                j = a[top1 - 1];
            }
            else if (*p_dst == 'B' || *p_dst == 'b') {
                *p_dst = 'B';
                j = b[top2 - 1];
            }
            else {
                *p_dst = 'C';
                j = c[top3 - 1];
            }
            if (i > j && j != 0) {
                cct_gotoxy(base_x, base_y + 24);
                cout << "大盘压小盘，非法移动！" << endl;
                Sleep(1000);
                cct_gotoxy(base_x, base_y + 24);
                for (k = 0; k < 40; k++) {
                    cout << " ";
                }
                cct_gotoxy(base_x + 61, base_y + 23);
                for (k = 0; k < 40; k++) {
                    cout << " ";
                }
                cct_gotoxy(base_x + 61, base_y + 23);
                continue;
            }
            else if (i == 0) {
                cct_gotoxy(base_x, base_y + 24);
                cout << "源柱为空！" << endl;
                Sleep(1000);
                cct_gotoxy(base_x, base_y + 24);
                for (k = 0; k < 40; k++) {
                    cout << " ";
                }
                cct_gotoxy(base_x + 61, base_y + 23);
                for (k = 0; k < 40; k++) {
                    cout << " ";
                }
                cct_gotoxy(base_x + 61, base_y + 23);
                continue;
            }
            else {
                break;
            }
        }
        else {
            cin.clear();
            cin.ignore(2000, '\n');
            cct_gotoxy(base_x + 61, base_y + 23);
            for (k = 0; k < 40; k++) {
                cout << " ";
            }
            cct_gotoxy(base_x + 61, base_y + 23);
            continue;
        }
    }
}

void tip(char src, char dst,int n,int sel)
{
    if (sel == 4 || sel == 8) {
        cout << "从 " << src << " 移动到 " << dst << "，共" << n << "层，延时设置为 " << delay << endl;
    }
    else if (sel == 6 || sel == 7|| sel == 9) {
        cout << "从 " << src << " 移动到 " << dst << "，共" << n << "层" << endl;
    }
}

void yanshi(int delay)
{
    if (delay == 1) {
        Sleep(1000);
    }
    else if (delay == 2) {
        Sleep(500);
    }
    else if (delay == 3) {
        Sleep(250);
    }
    else if (delay == 4) {
        Sleep(125);
    }
    else if (delay == 5) {
        Sleep(50);
    }
    else {

        while (1) {
            if (getchar() == '\n') {
                break;
            }
            else {
                continue;
            }
        }

    }
}

void plate(int sel)
{
    int i;
    if (sel == 4||sel==8||sel==9) {
        if (num == 1) {
            cct_gotoxy(base_x, base_y + 6 + 3 * (sel - 4));
            cout << setiosflags(ios::left) << setw(20) << "初始:";
            cout << resetiosflags(ios::left);
        }
        else {
            cct_gotoxy(base_x + 20, base_y + 6 + 3 * (sel - 4));
        }
    }
    cout << " A:";
    for (i = 0; i < 10; i++) {
        if (a[i] != 0) {
            cout << setw(2) << a[i];
        }
        else {
            cout << "  ";
        }
    }
    cout << " B:";
    for (i = 0; i < 10; i++) {
        if (b[i] != 0) {
            cout << setw(2) << b[i];
        }
        else {
            cout << "  ";
        }
    }
    cout << " C:";
    for (i = 0; i < 10; i++) {
        if (c[i] != 0) {
            cout << setw(2) << c[i];
        }
        else {
            cout << "  ";
        }
    }
    cout << endl;
    if (sel == 4) {
        yanshi(delay);
    }
}

void plate2(int sel)
{
    int i;
    if (num == 1) {
        cct_gotoxy(base_x, base_y + 1+3*(sel-4));
        for (i = 0; i < 23; i++) {
            cout << "=";
        }
        cout << endl;
        cct_gotoxy(base_x, base_y + 2 + 3 * (sel - 4));
        cout << " A         B        C" << endl;
    }
    cct_gotoxy(base_x, base_y + 3 * (sel - 4));
    for (i = 0; i < 10; i++) {
        if (a[i] != 0) {
            cout << setw(2) << a[i];
            cct_gotoxy(base_x, base_y - 1 - i + 3 * (sel - 4));
        }
        else {
            cout << "  ";
            cct_gotoxy(base_x, base_y - 1 - i + 3 * (sel - 4));
        }
    }
    cct_gotoxy(base_x+10, base_y + 3 * (sel - 4));
    for (i = 0; i < 10; i++) {
        if (b[i] != 0) {
            cout << setw(2) << b[i];
            cct_gotoxy(base_x+10, base_y - 1 - i + 3 * (sel - 4));
        }
        else {
            cout << "  ";
            cct_gotoxy(base_x+10, base_y - 1 - i + 3 * (sel - 4));
        }
    }
    cct_gotoxy(base_x+20, base_y + 3 * (sel - 4));
    for (i = 0; i < 10; i++) {
        if (c[i] != 0) {
            cout << setw(2) << c[i];
            cct_gotoxy(base_x + 20, base_y - 1 - i + 3 * (sel - 4));
        }
        else {
            cout << "  ";
            cct_gotoxy(base_x + 20, base_y - 1 - i + 3 * (sel - 4));
        }
    }
    if ((sel == 4||num==1)&&(sel!=9)) {
        yanshi(delay);
    }
}

void box(int x, int y, int n)
{
    int i, t;
    int duiying[3] = { 0,1,2 };
    if (num == 0) {
        for (i = n; i > 0; --i) {
            if (duiying[x] == 0) {
                a[top1] = i;
                ++top1;
            }
            else if (duiying[x] == 1) {
                b[top2] = i;
                ++top2;
            }
            else {
                c[top3] = i;
                ++top3;
            }
        }
        num++;
        return;
    }
    else {
        if (duiying[x] == 0 && duiying[y] == 1) {
            t = a[--top1];
            a[top1] = 0;
            b[top2] = t;
            ++top2;
        }
        else if (duiying[x] == 0 && duiying[y] == 2) {
            t = a[--top1];
            a[top1] = 0;
            c[top3] = t;
            ++top3;
        }
        else if (duiying[x] == 1 && duiying[y] == 0) {
            t = b[--top2];
            b[top2] = 0;
            a[top1] = t;
            ++top1;
        }
        else if (duiying[x] == 1 && duiying[y] == 2) {
            t = b[--top2];
            b[top2] = 0;
            c[top3] = t;
            ++top3;
        }
        else if (duiying[x] == 2 && duiying[y] == 0) {
            t = c[--top3];
            c[top3] = 0;
            a[top1] = t;
            ++top1;
        }
        else {
            t = c[--top3];
            c[top3] = 0;
            b[top2] = t;
            ++top2;
        }
        num++;
        return;
    }
}

void p_cylinder()
{
    int i, j;
    if (1) {
        cct_showch(base_x, base_y, ' ', COLOR_HYELLOW, COLOR_HYELLOW, 23);
        cct_showch(base_x + 40, base_y, ' ', COLOR_HYELLOW, COLOR_HYELLOW, 23);
        cct_showch(base_x + 80, base_y, ' ', COLOR_HYELLOW, COLOR_HYELLOW, 23);
        for (i = 1; i < 12; i++) {
            for (j = 0; j < 3; j++) {
                cct_showch(base_x + 11 + 40 * j, base_y - i, ' ', COLOR_HYELLOW, COLOR_HYELLOW, 1);
                Sleep(50);
            }
        }
    }
    cct_setcolor();
    cct_gotoxy(base_x, base_y + 5);
}

void p_plate(int n,char src)
{
    if (1) {
        int i;
        for (i = 0; i < n; i++) {
            cct_showch(base_x + 11 - n + i + 40*(int)(src-'A'), base_y - i - 1, ' ', n-i, n-i, 2 * (n - i) + 1);
            Sleep(100);
        }
    }
    cct_setcolor();
    cct_gotoxy(base_x, base_y + 5);
}

void move(int n, char src, char dst)
{
    int j;
    int n1, n2;
    if ((int)(src - 'A') == 0) {
        n1 = top1+1;
    }
    else if ((int)(src - 'A') == 1) {
        n1 = top2+1;
    }
    else {
        n1 = top3+1;
    }
    if ((int)(dst - 'A') == 0) {
        n2 = top1-1;
    }
    else if ((int)(dst - 'A') == 1) {
        n2 = top2-1;
    }
    else {
        n2 = top3-1;
    }
    if (1) {
        for (j = n1; j < 13; j++) {
            cct_showstr(base_x + 11 - n + 40 * (int)(src - 'A'), base_y - j, " ", n, n, 2 * n + 1);
            Sleep(100);
            if (j < 13) {
                if (j < 12) {
                    cct_showch(base_x + 11 - n + 40 * (int)(src - 'A'), base_y - j, ' ', COLOR_BLACK, COLOR_WHITE, n);
                    cct_showch(base_x + 11 + 40 * (int)(src - 'A'), base_y - j, ' ', COLOR_HYELLOW, COLOR_HYELLOW, 1);
                    cct_showch(base_x + 11 + 1 + 40 * (int)(src - 'A'), base_y - j, ' ', COLOR_BLACK, COLOR_WHITE, n);
                }
                else {
                    cct_showch(base_x + 11 - n + 40 * (int)(src - 'A'), base_y - j, ' ', COLOR_BLACK, COLOR_WHITE, 2 * n + 1);
                }
            }
        }
        if (src < dst) {
            for (j = 0; j < 40 * (int)(dst - src); j++) {
                cct_showstr(base_x + 11 - n + j + 40 * (int)(src - 'A'), base_y - 13, " ", n, n, 2 * n + 1);
                Sleep(100);
                if (j < 40 * (int)(dst - src)) {
                    cct_showch(base_x + 11 - n + j + 40 * (int)(src - 'A'), base_y - 13, ' ', COLOR_BLACK, COLOR_WHITE, 2 * n + 1);
                }
            }
        }
        else {
            for (j = 0; j > 40 * (int)(dst - src) - 1; --j) {
                cct_showstr(base_x + 11 - n + j + 40 * (int)(src - 'A'), base_y - 13, " ", n, n, 2 * n + 1);
                Sleep(100);
                if (j > 40 * (int)(dst - src) - 1) {
                    cct_showch(base_x + 11 - n + j + 40 * (int)(src - 'A'), base_y - 13, ' ', COLOR_BLACK, COLOR_WHITE, 2 * n + 1);
                }
            }
        }
        for (j = 12; j > n2; --j) {
            cct_showstr(base_x + 11 - n + 40 * (int)(src - 'A') + 40 * (int)(dst - src), base_y - j, " ", n, n, 2 * n + 1);
            Sleep(100);
            if (j > n2 + 1) {
                if (j < 12) {
                    cct_showch(base_x + 11 - n + 40 * (int)(src - 'A') + 40 * (int)(dst - src), base_y - j, ' ', COLOR_BLACK, COLOR_WHITE, n);
                    cct_showch(base_x + 11 - n + 40 * (int)(src - 'A') + 40 * (int)(dst - src) + n, base_y - j, ' ', COLOR_HYELLOW, COLOR_HYELLOW, 1);
                    cct_showch(base_x + 11 - n + 40 * (int)(src - 'A') + 40 * (int)(dst - src) + n + 1, base_y - j, ' ', COLOR_BLACK, COLOR_WHITE, n);
                }
                else {
                    cct_showch(base_x + 11 - n + 40 * (int)(src - 'A') + 40 * (int)(dst - src), base_y - j, ' ', COLOR_BLACK, COLOR_WHITE, 2 * n + 1);
                }
            }
        }
    }
    cct_setcolor();
    cct_gotoxy(base_x, base_y + 5);
    yanshi(delay);
}

void step(int sel, int n, char src, char tmp, char dst)
{
    if (sel == 1) {
        cout << setw(2) << n << "# " << src << "-->" << dst << endl;
    }
    else if (sel == 2) {
        cout << "第" << setw(4) << num << "步(" << n << "#: " << src << "-->" << dst << ") "<<endl;
        num++;
    }
    else if (sel == 3) {
        cout << "第" << setw(4) << num << "步(" << n << "#: " << src << "-->" << dst << ") ";
        box((int)(src - 'A'), (int)(dst - 'A'), n);
        plate(sel);
    }
    else if (sel == 4) {
        cout << "第" << setw(4) << num << "步(" << n << "#: " << src << "-->" << dst << ") ";
        box((int)(src - 'A'), (int)(dst - 'A'), n);
        plate(sel);
        plate2(sel);
        cct_gotoxy(base_x, base_y+6);
    }
    else {
        cct_gotoxy(base_x, base_y + 6 + 3 * (sel - 4));
        cout << "第" << setw(4) << num << "步(" << n << "#: " << src << "-->" << dst << ") ";
        box((int)(src - 'A'), (int)(dst - 'A'), n);
        plate(sel);
        plate2(sel);
        move(n, src, dst);
    }
}

void hanoi(int n, char src, char tmp, char dst,int sel)
{
    if (n == 1) {
        step(sel, n, src, tmp, dst);
    }
    else {
        hanoi(n - 1, src, dst, tmp,sel);
        step(sel, n, src, tmp, dst);
        hanoi(n - 1, tmp, src, dst,sel);
    }
}

void game(int n,char p_src,char p_dst,int sel)
{
    int answer[10]={0}, x[10];
    int i, N, line;
    for (i = 0; i < n; i++) {
        answer[i] = n - i;
    }
    while (1) {
        order(&p_src, &p_dst);
        if (p_src - 'A' == 0) {
            N = a[top1 - 1];
        }
        else if (p_src - 'A' == 1) {
            N = b[top2 - 1];
        }
        else if (p_src == '0') {
            return;
        }
        else {
            N = c[top3 - 1];
        }
        cct_gotoxy(base_x, base_y + 6 + 3 * (sel - 4 ));
        cout << "第" << setw(4) << num << "步(" << n << "#: " << p_src << "-->" << p_dst << ") ";
        box((int)(p_src - 'A'), (int)(p_dst - 'A'), n);
        plate(sel);
        plate2(sel);
        move(N, p_src, p_dst);
        if (p_dst - 'A' == 0) {
            for (i = 0; i < 10; i++) {
                x[i] = a[i];
            }
        }
        else if (p_dst - 'A' == 1) {
            for (i = 0; i < 10; i++) {
                x[i] = b[i];
            }
        }
        else {
            for (i = 0; i < 10; i++) {
                x[i] = c[i];
            }
        }
        for (i = 0,line=0; i < 10; i++) {
            if (x[i] == answer[i]) {
                continue;
            }
            else {
                line++;
                break;
            }
        }
        if (line==0) {
            cct_gotoxy(base_x, base_y + 24);
            cout << "游戏结束！" << endl;
            break;
        }
        else {
            continue;
        }
    }
}

void to_be_continued()
{
    int i;
    cct_setcolor();
    cct_gotoxy(0, base_y + 25);
    cout << "按回车键继续...";
    while (_getch() != '\r')
        ;

    cct_cls();
    num = 0;
    top1 = 0, top2 = 0, top3 = 0;
    for (i = 0; i < 10; i++) {
        a[i] = 0;
        b[i] = 0;
        c[i] = 0;
    }
    delay = 0;
    return;
}
