/* 2352475 计科 易阳 */
#pragma once

/* ------------------------------------------------------------------------------------------------------

     本文件功能：
	1、为了保证 hanoi_main.cpp/hanoi_menu.cpp/hanoi_multiple_solutions.cpp 能相互访问函数的函数声明
	2、一个以上的cpp中用到的宏定义（#define）或全局只读（const）变量，个数不限
	3、可以参考 cmd_console_tools.h 的写法（认真阅读并体会）
   ------------------------------------------------------------------------------------------------------ */

#define base_x 10
#define base_y 20

int menu            (void);
void input          (int* n, char* src, char* dst, int* sel, int* x, int* z);
void order          (char* p_src, char* p_dst);
void yanshi         (int delay);
void tip            (char src, char dst, int n,int sel);
void plate          (int sel);
void plate2         (int sel);
void box            (int x, int y, int n);
void p_cylinder     (void);
void p_plate        (int n, char src);
void move           (int n, char src, char dst);
void step           (int sel, int n, char src, char tmp, char dst);
void hanoi          (int n, char src, char tmp, char dst, int sel);
void game           (int n, char p_src, char p_dst, int sel);
void to_be_continued(void);