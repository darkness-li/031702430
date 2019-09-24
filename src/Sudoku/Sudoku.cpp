#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include<cmath>
#pragma warning(disable:4996)
#include"stdafx.h"
using namespace std;
int s[10][10], s1[10][10];//数组s[10][10]用于保存从input.txt中读入的数独信息，s1[10][10]为备份的数独信息
int flag = 0, pan = 0;//定义两个起标志作用的循环变量，用于下面的程序使用
int check1(int x, int y, int m, int num) {  //check1()函数用于检查填入阶数为3、5、7宫格的数字的合法性
	int x1 = x, y1 = y, m1 = m, num1 = num;
	int i;
	for (i = 1; i <= m1; i++) {
		if (s[x1][i] == num1) {   //如果宫格的列中存在要填入的数字num，则不能填入，返回0
			return 0;
		}
	}
	for (i = 1; i <= m1; i++) {
		if (s[i][y1] == num1) {   //如果宫格的行中存在要填入的数字num，则不能填入，返回0
			return 0;
		}
	}
	return 1;
}
int check2(int x, int y, int m, int num) { //check2()函数用于检查填入阶数为4、9宫格的数字的合法性
	int x1 = x, y1 = y, m1 = m, num1 = num;
	int i, j, flag1, k;
	int row, col;
	k = (int)sqrt(m1);
	flag1 = check1(x1, y1, m1, num1);
	if (flag1 == 0)    //调用check1函数先检查行列的合法性，不合法则直接返回0
		return 0;
	if (flag1 == 1) {
		row = ((x1 - 1) / k * k) + 1;
		col = ((y1 - 1) / k * k) + 1;
		for (i = row; i < row + k; i++) {
			for (j = col; j < col + k; j++) {   //检查要填入的位置所在的小宫格的合法性
				if (s[i][j] == num1) {
					return 0;
				}
			}
		}
	}
	return 1;
}
int check3(int x, int y, int m, int num) {  //check3()函数用于检查填入阶数为6、8宫格的数字的合法性
	int x1 = x, y1 = y, m1 = m, num1 = num;
	int i, j, flag1;
	int row, col;
	flag1 = check1(x1, y1, m1, num1);
	if (flag1 == 0)  //调用check1函数先检查行列的合法性，不合法则直接返回0
		return 0;
	if (flag1 == 1) {
		if (m1 == 6) {

			row = ((x1 - 1) / 2 * 2) + 1;
			col = ((y1 - 1) / 3 * 3) + 1;  //这是一个用于计算小宫格最左上的位置坐标的公式
			x1 = 2; y1 = 3;
		}
		if (m1 == 8) {

			row = ((x1 - 1) / 4 * 4) + 1;
			col = ((y1 - 1) / 2 * 2) + 1;
			x1 = 4; y1 = 2;
		}
		for (i = row; i < row + x1; i++) {
			for (j = col; j < col + y1; j++) {  //检查要填入的位置所在的小宫格的合法性
				if (s[i][j] == num) {
					return 0;
				}
			}
		}
	}
	return 1;
}
int dfs(int n, int m) {  /*深度优先搜索函数，对于数独中每个位置为0的格，从1-m（m为阶数）这m个数中先检查哪个数能填入数独，若能填入则填入，当把整个数独
	                   的每个空位都成功填入一遍后，说明我们解出了这个数独，于是返回；如果这m个数中没有一个满足要求，则回溯，并将填入的数字置0。*/
	int i;
	if (n > m*m) {   
		pan = 1;   
		return 0;
	}
	if (s[((n - 1) / m) + 1][((n - 1) % m) + 1] != 0) {   //这里把数独的每个位置从1-n*n编号，（(n - 1) / m) + 1用于计算位置的行坐标，((n - 1) % m) + 1用于计算位置的列坐标
		dfs(n + 1, m);
	}
	if (s[((n - 1) / m) + 1][((n - 1) % m) + 1] == 0) {
		for (i = 1; i <= m; i++) {   //检查1-m这m个数中哪几个数能填入
			int flag = 0;
			if (m == 3 || m == 5 || m == 7) {
				flag = check1(((n - 1) / m) + 1, ((n - 1) % m) + 1, m, i);
			}
			if (m == 4 || m == 9) {
				flag = check2(((n - 1) / m) + 1, ((n - 1) % m) + 1, m, i);
			}
			if (m == 6 || m == 8) {
				flag = check3(((n - 1) / m) + 1, ((n - 1) % m) + 1, m, i);
			}
			if (flag == 1) {
				s[((n - 1) / m) + 1][((n - 1) % m) + 1] = i;  //flag=1说明该位置能填入i，则填入，继续搜索下一个格子
				dfs(n + 1, m);
				if (pan == 1)
					return 0;
				s[((n - 1) / m) + 1][((n - 1) % m) + 1] = 0;//说明填入的数字不满足要求，置0
			}
		}
	}
	return 0;
}
void sudok1(int m, int count) {  //sudok1函数先把阶数为3、5、7的数独中仅根据行列信息就能唯一确定的数字填入
	int i, j, k1, k2, k3;
	int m1 = m;
	int count1 = count;
	int m2 = m1 + 1;
	int count2;
	while (count1) {
		count2 = count1;
		for (i = 1; i < m1 + 1; i++) {
			for (j = 1; j < m1 + 1; j++) {
				if (s[i][j] == 0) {
					int count2 = m1;
					int a[10] = { 0 };
					for (k1 = 1; k1 < m1 + 1; k1++) {
						if (s[i][k1] != 0) {
							if (a[s[i][k1]] == 0) {
								a[s[i][k1]] = 1;
								count2--;
							}
						}
					}
					for (k2 = 1; k2 < m1 + 1; k2++) {
						if (s[k2][j] != 0) {
							if (a[s[k2][j]] == 0) {
								a[s[k2][j]] = 1;
								count2--;
							}
						}
					}
					if (count2 == 1) {
						count1--;
						for (k3 = 1; k3 < m1 + 1; k3++) {
							if (a[k3] == 0) {
								s1[i][j] = k3;
								s[i][j] = k3;
								break;
							}
						}
					}
				}
			}
		}
		if (count2 == count1) {
			flag = 1;
			break;
		}
	}
}
void sudok2(int m, int count) {  //sudok2函数先把阶数为4、9的数独中仅根据行、列、小宫的信息就能唯一确定的数字填入
	int i, j, k, k1, k2, k3, m2;
	int row;//行
	int col;//列
	int m1 = m;
	int count1 = count;
	k = (int)sqrt(m1);
	m2 = m1 + 1;
	int count3;
	while (count1) {
		count3 = count1;
		for (i = 1; i < m1 + 1; i++) {
			for (j = 1; j < m1 + 1; j++) {
				if (s[i][j] == 0) {
					int count2 = m1;
					int a[10] = { 0 };
					for (k1 = 1; k1 < m1 + 1; k1++) {
						if (s[i][k1] != 0) {
							if (a[s[i][k1]] == 0) {
								a[s[i][k1]] = 1;
								count2--;
							}
						}
					}
					for (k2 = 1; k2 < m1 + 1; k2++) {
						if (s[k2][j] != 0) {
							if (a[s[k2][j]] == 0) {
								a[s[k2][j]] = 1;
								count2--;
							}
						}
					}
					row = ((i - 1) / k * k) + 1;
					col = ((j - 1) / k * k) + 1;
					for (k1 = row; k1 < row + k; k1++) {
						for (k2 = col; k2 < col + k; k2++) {
							if (s[k1][k2] != 0) {
								if (a[s[k1][k2]] == 0) {
									a[s[k1][k2]] = 1;
									count2--;
								}
							}
						}
					}
					if (count2 == 1) {
						count1--;
						for (k3 = 1; k3 < m1 + 1; k3++) {
							if (a[k3] == 0) {
								s1[i][j] = k3;
								s[i][j] = k3;
								break;
							}
						}
					}
				}
			}
		}
		if (count3 == count1) {
			flag = 1;
			break;
		}
	}
}
void sudok3(int m, int count) {  //sudok3函数先把阶数为6、8的数独中仅根据行、列、小宫的信息就能唯一确定的数字填入
	int i, j, x1, y1, k1, k2, k3;
	int row;//行
	int col;//列
	int m1 = m;
	int count1 = count;
	int m2 = m1 + 1;
	int c;
	int count3;
	while (count1) {
		count3 = count1;
		for (i = 1; i < m1 + 1; i++) {
			for (j = 1; j < m1 + 1; j++) {
				if (s[i][j] == 0) {
					int count2 = m1;
					int a[10] = { 0 };
					for (k1 = 1; k1 < m1 + 1; k1++) {
						if (s[i][k1] != 0) {
							c = s[i][k1];
							if (a[c] == 0) {
								a[c] = 1;
								count2--;
							}
						}
					}
					for (k2 = 1; k2 < m1 + 1; k2++) {
						if (s[k2][j] != 0) {
							if (a[s[k2][j]] == 0) {
								a[s[k2][j]] = 1;
								count2--;
							}
						}
					}
					if (m1 == 6) {
						x1 = 2; y1 = 3;
						row = ((i - 1) / x1 * x1) + 1;
						col = ((j - 1) / y1 * y1) + 1;
					}
					if (m1 == 8) {
						x1 = 4; y1 = 2;
						row = ((i - 1) / x1 * x1) + 1;
						col = ((j - 1) / y1 * y1) + 1;
					}
					for (k1 = row; k1 < row + x1; k1++) {
						for (k2 = col; k2 < col + y1; k2++) {
							if (s[k1][k2] != 0) {
								if (a[s[k1][k2]] == 0) {
									a[s[k1][k2]] = 1;
									count2--;
								}
							}
						}
					}
					if (count2 == 1) {
						count1--;
						for (k3 = 1; k3 < m1 + 1; k3++) {
							if (a[k3] == 0) {
								s1[i][j] = k3;
								s[i][j] = k3;
								break;
							}
						}
					}
				}
			}
		}
		if (count3 == count1) {
			flag = 1;
			break;
		}
	}
}
int main(int argc, char *argv[]) {
	int n, m,k;//m是宫格阶级，n是盘面数目
	int i, j, count;
	FILE *fp1;
	FILE *fp2;
	m = atoi(argv[2]);//获取从命令行中输入的参数
	n = atoi(argv[4]);
	fp1 = fopen("input.txt", "r");
	if (fp1 == NULL)
		return -1;
	fp2 = fopen("output.txt", "r");
	if (fp2 == NULL)
		return -1;
	fclose(fp2);
	while (n--) {
		i = 0, j = 0, count = 0, flag = 0;//初始化循环变量
		s[10][10] = { 0 };
		s1[10][10] = { 0 };
		for (i = 1; i < m + 1; i++) {
			for (j = 1; j < m + 1; j++) {
				fscanf(fp1, "%d", &s[i][j]);//从input.txt中读入数独的信息
				s1[i][j] = s[i][j];
				if (s1[i][j] == 0)
					count++;
			}
		}
		if (m == 3 || m == 5 || m == 7)
			sudok1(m, count);
		if (m == 4 || m == 9)
			sudok2(m, count);
		if (m == 6 || m == 8)
			sudok3(m, count);
		if (flag == 1) {  //flag==1说明该数独不能仅根据行、列、小宫的信息完成填入，要执行dfs函数
			k=dfs(1, m);
		}
		pan = 0; flag = 0;//处理完每个数独后对控制变量重新赋初值
		fp2 = fopen("output.txt", "a");
		if (fp2 == NULL)
			return -1;
		for (i = 1; i < m + 1; i++) {
			for (j = 1; j < m + 1; j++) {
				fprintf(fp2, "%d", s[i][j]);//将处理好的数独写入output.txt
				if (j != m)
					fprintf(fp2, " ");
			}
			fprintf(fp2, "\n");
		}
		fprintf(fp2, "\n");
		fclose(fp2);

	}
	fclose(fp1);
	return 0;
}