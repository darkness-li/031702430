#include<iostream>
#include "stdafx.h"
#pragma warning(disable:4996)
using namespace std;
int s[10][10], s1[10][10];
int flag = 0, pan = 0;
int check1(int x, int y, int m, int num) {
	int x1 = x, y1 = y, m1 = m, num1 = num;
	int i;
	for (i = 1; i <= m1; i++) {
		if (s[x1][i] == num1) {
			return 0;
		}
	}
	for (i = 1; i <= m1; i++) {
		if (s[i][y1] == num1) {
			return 0;
		}
	}
	return 1;
}
int check2(int x, int y, int m, int num) {
	int x1 = x, y1 = y, m1 = m, num1 = num;
	int i, j, flag1, k;
	int row, col;
	k = (int)sqrt(m1);
	flag1 = check1(x1, y1, m1, num1);
	if (flag1 == 0)
		return 0;
	if (flag1 == 1) {
		row = ((x1 - 1) / k * k) + 1;
		col = ((y1 - 1) / k * k) + 1;
		for (i = row; i < row + k; i++) {
			for (j = col; j < col + k; j++) {
				if (s[i][j] == num1) {
					return 0;
				}
			}
		}
		return 1;
	}
}
int check3(int x, int y, int m, int num) {
	int x1 = x, y1 = y, m1 = m, num1 = num;
	int i, j, flag1;
	int row, col;
	flag1 = check1(x1, y1, m1, num1);
	if (flag1 == 0)
		return 0;
	if (flag1 == 1) {
		if (m1 == 6) {

			row = ((x1 - 1) / 2 * 2) + 1;
			col = ((y1 - 1) / 3 * 3) + 1;
			x1 = 2; y1 = 3;
		}
		if (m1 == 8) {

			row = ((x1 - 1) / 4 * 4) + 1;
			col = ((y1 - 1) / 2 * 2) + 1;
			x1 = 4; y1 = 2;
		}
		for (i = row; i < row + x1; i++) {
			for (j = col; j < col + y1; j++) {
				if (s[i][j] == num) {
					return 0;
				}
			}
		}
		return 1;
	}
}
int dfs(int n, int m) {
	int i;
	if (n > m*m) {
		pan = 1;
		return 0;
	}
	if (s[((n - 1) / m) + 1][((n - 1) % m) + 1] != 0) {
		dfs(n + 1, m);
	}
	if (s[((n - 1) / m) + 1][((n - 1) % m) + 1] == 0) {
		for (i = 1; i <= m; i++) {
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
				s[((n - 1) / m) + 1][((n - 1) % m) + 1] = i;
				dfs(n + 1, m);
				if (pan == 1)
					return 0;
				s[((n - 1) / m) + 1][((n - 1) % m) + 1] = 0;
			}
		}
	}
}
void sudok1(int m, int count) {
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
void sudok2(int m, int count) {
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
void sudok3(int m, int count) {
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