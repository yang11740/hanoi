/* 2352475 计科 易阳 */
#include <iostream>
#include <iomanip>
#include "../include/cmd_console_tools.h"
#include "90-01-b1-hanoi.h"
using namespace std;
/* ----------------------------------------------------------------------------------

     本文件功能：
	1、放main函数
	2、初始化屏幕
	3、调用菜单函数（hanoi_menu.cpp中）并返回选项
	4、根据选项调用菜单各项对应的执行函数（hanoi_multiple_solutions.cpp中）

     本文件要求：
	1、不允许定义全局变量（含外部全局和静态全局，const及#define不在限制范围内）
	2、静态局部变量的数量不限制，但使用准则也是：少用、慎用、能不用尽量不用
	3、按需加入系统头文件、自定义头文件、命名空间等

   ----------------------------------------------------------------------------------- */


int main()
{
	int sel, n, x, y, z;
	char src, tmp, dst;
	char p_src='0', p_dst='0';

	/* demo中首先执行此句，将cmd窗口设置为40行x120列（缓冲区宽度120列，行数9000行，即cmd窗口右侧带有垂直滚动杆）*/
	cct_setconsoleborder(120, 40, 120, 9000);
	while (1) {
		sel = menu();
		if (sel == 1 || sel == 2 || sel == 3 || sel == 4) {
			input(&n, &src, &dst, &sel, &x, &z);
			tmp = 'A' + 'B' + 'C' - src - dst;
			y = 0 + 1 + 2 - x - z;
			box(x, y, n);
			if (sel == 4) {
				cct_cls();
				tip(src, dst, n, sel);
				plate(sel);
				plate2(sel);
				cct_gotoxy(base_x, base_y + 6);
				hanoi(n, src, tmp, dst, sel);
			}
			else {
				hanoi(n, src, tmp, dst, sel);
			}
			to_be_continued();
		}
		else if (sel == 5) {
			cct_cls();
			p_cylinder();
			to_be_continued();
		}
		else if (sel == 6 || sel == 7 || sel == 8 || sel == 9) {
			input(&n, &src, &dst, &sel, &x, &z);
			tmp = 'A' + 'B' + 'C' - src - dst;
			y = 0 + 1 + 2 - x - z;
			box(x, y, n);
			cct_cls();
			tip(src, dst, n, sel);
			p_cylinder();
			p_plate(n, src);
			if (sel == 7) {
				box((int)(src - 'A'), (int)(dst - 'A'), 1);
				move(1, src, dst);
			}
			else if (sel == 8) {
				plate(sel);
				plate2(sel);
				cct_gotoxy(base_x, base_y + 6 + 3 * (sel - 4));
				hanoi(n, src, tmp, dst, sel);
			}
			else if (sel == 9) {
				plate(sel);
				plate2(sel);
				cct_gotoxy(base_x, base_y + 8 + 3 * (sel - 4));
				game(n, p_src, p_dst, sel);
			}
			to_be_continued();
		}
		else {
			return 0;
		}
	}
}
