#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include<cmath>
#pragma warning(disable:4996)
#include"stdafx.h"
using namespace std;
int s[10][10], s1[10][10];//����s[10][10]���ڱ����input.txt�ж����������Ϣ��s1[10][10]Ϊ���ݵ�������Ϣ
int flag = 0, pan = 0;//�����������־���õ�ѭ����������������ĳ���ʹ��
int check1(int x, int y, int m, int num) {  //check1()�������ڼ���������Ϊ3��5��7��������ֵĺϷ���
	int x1 = x, y1 = y, m1 = m, num1 = num;
	int i;
	for (i = 1; i <= m1; i++) {
		if (s[x1][i] == num1) {   //�����������д���Ҫ���������num���������룬����0
			return 0;
		}
	}
	for (i = 1; i <= m1; i++) {
		if (s[i][y1] == num1) {   //�����������д���Ҫ���������num���������룬����0
			return 0;
		}
	}
	return 1;
}
int check2(int x, int y, int m, int num) { //check2()�������ڼ���������Ϊ4��9��������ֵĺϷ���
	int x1 = x, y1 = y, m1 = m, num1 = num;
	int i, j, flag1, k;
	int row, col;
	k = (int)sqrt(m1);
	flag1 = check1(x1, y1, m1, num1);
	if (flag1 == 0)    //����check1�����ȼ�����еĺϷ��ԣ����Ϸ���ֱ�ӷ���0
		return 0;
	if (flag1 == 1) {
		row = ((x1 - 1) / k * k) + 1;
		col = ((y1 - 1) / k * k) + 1;
		for (i = row; i < row + k; i++) {
			for (j = col; j < col + k; j++) {   //���Ҫ�����λ�����ڵ�С����ĺϷ���
				if (s[i][j] == num1) {
					return 0;
				}
			}
		}
	}
	return 1;
}
int check3(int x, int y, int m, int num) {  //check3()�������ڼ���������Ϊ6��8��������ֵĺϷ���
	int x1 = x, y1 = y, m1 = m, num1 = num;
	int i, j, flag1;
	int row, col;
	flag1 = check1(x1, y1, m1, num1);
	if (flag1 == 0)  //����check1�����ȼ�����еĺϷ��ԣ����Ϸ���ֱ�ӷ���0
		return 0;
	if (flag1 == 1) {
		if (m1 == 6) {

			row = ((x1 - 1) / 2 * 2) + 1;
			col = ((y1 - 1) / 3 * 3) + 1;  //����һ�����ڼ���С���������ϵ�λ������Ĺ�ʽ
			x1 = 2; y1 = 3;
		}
		if (m1 == 8) {

			row = ((x1 - 1) / 4 * 4) + 1;
			col = ((y1 - 1) / 2 * 2) + 1;
			x1 = 4; y1 = 2;
		}
		for (i = row; i < row + x1; i++) {
			for (j = col; j < col + y1; j++) {  //���Ҫ�����λ�����ڵ�С����ĺϷ���
				if (s[i][j] == num) {
					return 0;
				}
			}
		}
	}
	return 1;
}
int dfs(int n, int m) {  /*���������������������������ÿ��λ��Ϊ0�ĸ񣬴�1-m��mΪ��������m�������ȼ���ĸ����������������������������룬������������
	                   ��ÿ����λ���ɹ�����һ���˵�����ǽ����������������Ƿ��أ������m������û��һ������Ҫ������ݣ����������������0��*/
	int i;
	if (n > m*m) {   
		pan = 1;   
		return 0;
	}
	if (s[((n - 1) / m) + 1][((n - 1) % m) + 1] != 0) {   //�����������ÿ��λ�ô�1-n*n��ţ���(n - 1) / m) + 1���ڼ���λ�õ������꣬((n - 1) % m) + 1���ڼ���λ�õ�������
		dfs(n + 1, m);
	}
	if (s[((n - 1) / m) + 1][((n - 1) % m) + 1] == 0) {
		for (i = 1; i <= m; i++) {   //���1-m��m�������ļ�����������
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
				s[((n - 1) / m) + 1][((n - 1) % m) + 1] = i;  //flag=1˵����λ��������i�������룬����������һ������
				dfs(n + 1, m);
				if (pan == 1)
					return 0;
				s[((n - 1) / m) + 1][((n - 1) % m) + 1] = 0;//˵����������ֲ�����Ҫ����0
			}
		}
	}
	return 0;
}
void sudok1(int m, int count) {  //sudok1�����Ȱѽ���Ϊ3��5��7�������н�����������Ϣ����Ψһȷ������������
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
void sudok2(int m, int count) {  //sudok2�����Ȱѽ���Ϊ4��9�������н������С��С�С������Ϣ����Ψһȷ������������
	int i, j, k, k1, k2, k3, m2;
	int row;//��
	int col;//��
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
void sudok3(int m, int count) {  //sudok3�����Ȱѽ���Ϊ6��8�������н������С��С�С������Ϣ����Ψһȷ������������
	int i, j, x1, y1, k1, k2, k3;
	int row;//��
	int col;//��
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
	int n, m,k;//m�ǹ���׼���n��������Ŀ
	int i, j, count;
	FILE *fp1;
	FILE *fp2;
	m = atoi(argv[2]);//��ȡ��������������Ĳ���
	n = atoi(argv[4]);
	fp1 = fopen("input.txt", "r");
	if (fp1 == NULL)
		return -1;
	fp2 = fopen("output.txt", "r");
	if (fp2 == NULL)
		return -1;
	fclose(fp2);
	while (n--) {
		i = 0, j = 0, count = 0, flag = 0;//��ʼ��ѭ������
		s[10][10] = { 0 };
		s1[10][10] = { 0 };
		for (i = 1; i < m + 1; i++) {
			for (j = 1; j < m + 1; j++) {
				fscanf(fp1, "%d", &s[i][j]);//��input.txt�ж�����������Ϣ
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
		if (flag == 1) {  //flag==1˵�����������ܽ������С��С�С������Ϣ������룬Ҫִ��dfs����
			k=dfs(1, m);
		}
		pan = 0; flag = 0;//������ÿ��������Կ��Ʊ������¸���ֵ
		fp2 = fopen("output.txt", "a");
		if (fp2 == NULL)
			return -1;
		for (i = 1; i < m + 1; i++) {
			for (j = 1; j < m + 1; j++) {
				fprintf(fp2, "%d", s[i][j]);//������õ�����д��output.txt
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