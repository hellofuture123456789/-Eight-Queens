#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<limits.h>


void Mycopy(int minpath[100][100], int visited[100][100],int m,int n) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			minpath[i][j] = visited[i][j];
		}
	}
}

void dfs(int x, int y, int step,int migong[100][100],int visited[100][100],int m,int n,int *min,int minpath[100][100],int* isok) {
	//最短路径更新
	if (x == m-1 && y == n-1) {
		if (step < *min) {
			*min = step;
			Mycopy(minpath, visited, m, n);
			*isok = 1;
			return;
		}
	}
	//向右，下，左，上
	int dx[4] = { 1,0,-1,0 };
	int dy[4] = { 0,1,0,-1 };
	for (int i = 0; i < 4; i++) {
		int xnext = x + dx[i];
		int ynext = y + dy[i];
		if (xnext >= 0 && xnext < m && ynext >= 0 && ynext < n) {
			if (migong[xnext][ynext] == 0 && visited[xnext][ynext] == 0) {
				visited[xnext][ynext] = 1;
				dfs(xnext, ynext, step + 1, migong, visited, m, n, min,minpath,isok);
				visited[xnext][ynext] = 0;
			}
		}
	}

}

void printAns(int minpath[100][100], int m, int n, int migong[100][100], FILE *outputFile) {
    fprintf(outputFile, "\n\n\n");
    fprintf(outputFile, "最短路如下（q是墙）（0是空地）（*是路）\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (minpath[i][j] == 1) {
                fprintf(outputFile, "* ");
            }
            else if (migong[i][j] == 1) {
                fprintf(outputFile, "q ");
            }
            else {
                fprintf(outputFile, "0 ");
            }
        }
        fprintf(outputFile, "\n");
    }
}
 
int main() {
    FILE *file = fopen("migong.txt", "r");
    if (file == NULL) {
        printf("无法打开文件migong.txt\n");
        return 1;
    }
 
    int migong[100][100];
    int visited[100][100] = {0};
    int m, n;
 

    if (fscanf(file, "%d", &m) != 1) {
        printf("读取迷宫行数失败\n");
        fclose(file);
        return 1;
    }
 
    if (fscanf(file, "%d", &n) != 1) {
        printf("读取迷宫列数失败\n");
        fclose(file);
        return 1;
    }
 
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (fscanf(file, "%d", &migong[i][j]) != 1) {
                printf("读取迷宫结构失败\n");
                fclose(file);
                return 1;
            }
        }
    }
 
    fclose(file);
 
    int step = 0; 
    int min = INT_MAX;
    int minpath[100][100] = {0};
    int isok = 0;
    visited[0][0] = 1;
 
    dfs(0, 0, step, migong, visited, m, n, &min, minpath, &isok);

    FILE *outputFile = fopen("AnsMigong.txt", "w");
    if (outputFile == NULL) {
        printf("无法打开文件AnsMigong.txt\n");
        return 1;
    }
 
    if (isok) {
        printAns(minpath, m, n, migong, outputFile);
    } else {
        fprintf(outputFile, "没有找到路\n");
    }

    fclose(outputFile);
 
    return 0;
}
/*
int main() {
	int migong[100][100];
	int visited[100][100] = {0};
	int m, n;
	printf("请输入迷宫的大小\n");
	printf("行：");
	scanf("%d", &m);
	printf("列：");
	scanf("%d", &n);
	printf("请从左往右，从上往下输入迷宫的结构。\n“0”表示无障碍物，“1”表示有障碍物\n");
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &migong[i][j]);
		}
	}
	int step = 0;
	int min = INT_MAX;
	int minpath[100][100] = { 0 };
	int isok = 0;
	visited[0][0] = 1;
	dfs(0, 0, step, migong, visited, m, n, &min, minpath,&isok);
	if (isok)
		printAns(minpath, m, n, migong);
	else
	{
		printf("没有找到路");
	}
	return 0;
}
*/
/*
4行4列
0 1 1 1
0 1 1 1
0 1 1 1
0 0 0 0 
*/
/*
9行16列
0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
1 1 1 1 1 1 1 1 0 1 1 1 1 1 0 1
1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 1 1 0 1 0 1 0 1 1 1 1 1
1 1 1 1 1 1 0 0 0 1 1 1 1 1 1 1
0 0 0 0 1 1 0 0 1 0 0 0 0 0 0 0
1 1 1 0 1 1 1 0 0 0 1 1 1 1 1 1
1 1 1 0 0 0 0 0 1 0 0 0 0 0 0 0 
*/