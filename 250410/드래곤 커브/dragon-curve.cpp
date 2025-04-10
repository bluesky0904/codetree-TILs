/*
좌표평면 : 좌상단(0, 0)
0차 드래곤 커브 = 길이가 1인 선분
1차 드래곤 커브 = 0차 드래곤 커브를 복제한 후 해당 드래곤 커브의 끝점을 기준으로 시계 방향 90도 회전
끝점은 해당 드래곤 커브에서 시작점으로부터 가장 멀리 떨어진 점(= 그려지며 도착한 마지막 지점)

n차 드래곤 커브 : n-1차 드래곤 커브의 끝점에 n-1차 드래곤 커브를 복제한 뒤 시계 방향으로 90도 회전시킨 뒤 연결한 도형

크기 100 x 100의 좌표평면 위에 n개의 드래곤 커브가 주어질 때 만들어지는 단위 정사각형의 개수
좌표평면의 x값과 y값의 범위는 0 <= x, y <= 100이고, 만들어지는 정사각형이란 정사각형의 네 꼭지점이 모두 드래곤 커브에 속하는 도형

좌표평면 범위 내에 있는 꼭짓점이 모두 드래곤 커브의 일부인 크기가 1인 정사각형의 개수 출력
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
using namespace std;

const int GRIDSIZE = 100;
const int MAXN = 20;

int n;
int grid[GRIDSIZE + 10][GRIDSIZE + 10];
vector<int> drag_d[MAXN + 10];
int drag_x[MAXN + 10];
int drag_y[MAXN + 10];

int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };

void print() {
	cout << "grid" << "\n";
    	for (int i = 0; i < GRIDSIZE; i++) {
        		for (int j = 0; j < GRIDSIZE; j++) {
                			cout << grid[i][j] << " ";
                            		}
                                    		cout << "\n";
                                            	}
                                                	cout << "\n";

                                                    	for (int i = 1; i <= n; i++) {
                                                        		cout << i << " : " << drag_x[i] << " " << drag_y[i] << "\n";
                                                                		cout << "drag_d : ";
                                                                        		for (int j = 0; j < (int)drag_d[i].size(); j++) {
                                                                                			cout << drag_d[i][j] << " ";
                                                                                            		}
                                                                                                    		cout << "\n";
                                                                                                            	}
                                                                                                                	cout << "\n";
                                                                                                                    }

                                                                                                                    void drawLine(int id) {
                                                                                                                    	vector<int> tmp;
                                                                                                                        	for (int i = 0; i < (int)drag_d[id].size(); i++) tmp.push_back(drag_d[id][i]);
                                                                                                                            	for (int i = (int)drag_d[id].size() - 1; i >= 0; i--) {
                                                                                                                                		int d = drag_d[id][i];
                                                                                                                                        		d = (d + 3) % 4;
                                                                                                                                                		tmp.push_back(d);
                                                                                                                                                        		drag_x[id] += dx[d];
                                                                                                                                                                		drag_y[id] += dy[d];

                                                                                                                                                                        		grid[drag_x[id]][drag_y[id]] = 1;
                                                                                                                                                                                	}

                                                                                                                                                                                    	drag_d[id].clear();
                                                                                                                                                                                        	for (int i = 0; i < (int)tmp.size(); i++) {
                                                                                                                                                                                            		drag_d[id].push_back(tmp[i]);
                                                                                                                                                                                                    	}
                                                                                                                                                                                                        }

                                                                                                                                                                                                        int getAns() {
                                                                                                                                                                                                        	int cnt = 0;
                                                                                                                                                                                                            	for (int i = 0; i < GRIDSIZE - 1; i++) {
                                                                                                                                                                                                                		for (int j = 0; j < GRIDSIZE - 1; j++) {
                                                                                                                                                                                                                        			int point = 0;
                                                                                                                                                                                                                                    			if (grid[i][j] == 1) point++;
                                                                                                                                                                                                                                                			if (grid[i + 1][j] == 1) point++;
                                                                                                                                                                                                                                                            			if (grid[i][j + 1] == 1) point++;
                                                                                                                                                                                                                                                                        			if (grid[i + 1][j + 1] == 1) point++;

                                                                                                                                                                                                                                                                                    			if (point == 4) cnt++;
                                                                                                                                                                                                                                                                                                		}
                                                                                                                                                                                                                                                                                                        	}

                                                                                                                                                                                                                                                                                                            	return cnt;
                                                                                                                                                                                                                                                                                                                }

                                                                                                                                                                                                                                                                                                                int main() {
                                                                                                                                                                                                                                                                                                                	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
                                                                                                                                                                                                                                                                                                                    	//freopen("sample_input.txt", "r", stdin);

                                                                                                                                                                                                                                                                                                                        	cin >> n;
                                                                                                                                                                                                                                                                                                                            	for (int i = 0; i < GRIDSIZE; i++) {
                                                                                                                                                                                                                                                                                                                                		for (int j = 0; j < GRIDSIZE; j++) {
                                                                                                                                                                                                                                                                                                                                        			grid[i][j] = 0;
                                                                                                                                                                                                                                                                                                                                                    		}
                                                                                                                                                                                                                                                                                                                                                            	}
                                                                                                                                                                                                                                                                                                                                                                	for (int i = 1; i <= n; i++) {
                                                                                                                                                                                                                                                                                                                                                                    		drag_d[i].clear();

                                                                                                                                                                                                                                                                                                                                                                            		int x, y, d, g; cin >> x >> y >> d >> g;
                                                                                                                                                                                                                                                                                                                                                                                    		grid[x][y] = 1;
                                                                                                                                                                                                                                                                                                                                                                                            		if (d == 0) d = 0;
                                                                                                                                                                                                                                                                                                                                                                                                    		else if (d == 1) d = 3;
                                                                                                                                                                                                                                                                                                                                                                                                            		else if (d == 2) d = 2;
                                                                                                                                                                                                                                                                                                                                                                                                                    		else if (d == 3) d = 1;
                                                                                                                                                                                                                                                                                                                                                                                                                            		drag_d[i].push_back(d);
                                                                                                                                                                                                                                                                                                                                                                                                                                    		x += dx[d]; y += dy[d];
                                                                                                                                                                                                                                                                                                                                                                                                                                            		grid[x][y] = 1;
                                                                                                                                                                                                                                                                                                                                                                                                                                                    		drag_x[i] = x;
                                                                                                                                                                                                                                                                                                                                                                                                                                                            		drag_y[i] = y;

                                                                                                                                                                                                                                                                                                                                                                                                                                                                    		while (g--) {
                                                                                                                                                                                                                                                                                                                                                                                                                                                                            			drawLine(i);
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        		}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                		//print();
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        	}

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            	cout << getAns() << "\n";
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                	return 0;
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    }