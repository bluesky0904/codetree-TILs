/*
배터리 양이 모두 소진되는 경우 더이상 움직일 수 없다
격자 : n x n
차가 지나갈 수 없는 벽의 위치
m명의 승객의 위치
주어진 배터리 용량으로 승객을 모두 태워줄 수 있는지를 알아보자

자율주행 전기차는 승객을 태우러 출발지에 이동할 때나 태우고 목적지로 이동할 때 항상 최단 거리로 이동
자율주행 전기차는 한 칸을 이동할 때 1만큼의 배터리를 소요
승객을 목적지로 무사히 태워주면 (그 승객을 태워서 이동하며 소요한 배터리 양의 두 배)만큼을 충전한 뒤 다시 이동
이동하는 도중에 배터리가 모두 소모되면 그 즉시 종료되며,
만일 승객을 목적지로 이동시킨 동시에 배터리가 모두 소모되는 경우에는 승객을 태우며 소모한 배터리의 두 배만큼 충전되어 다시 운행
마지막 승객을 태워주고 운행을 종료하는 순간에도 충전은 이뤄짐

승객이 여러명일 경우 현재 위치에서 최단 거리가 가장 짧은 승객을 먼저 태움
우선 순위 : 승객과의 거리 최소 > 승객 행 최소 > 승객 열 최소

모든 승객을 성공적으로 데려다 줄 수 있는지 알아내고, 데려다줄 수 있는 경우 최종적으로 남는 배터리의 양을 출력
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
using namespace std;

const int MAXN = 20;
const int MAXM = 400;
const int INF = 1e9;

int n, m, c;

int road[MAXN + 10][MAXN + 10];

int car_x, car_y, battery;
pair<int, int> start_pos[MAXM + 10];
pair<int, int> end_pos[MAXM + 10];
int arrived[MAXM + 10];

int dist[MAXN + 10][MAXN + 10];

int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };

void print() {
	cout << "car : " << car_x << " " << car_y << "\n";
		cout << "battery : " << battery << "\n";
			cout << "road" << "\n";
				for (int i = 0; i < n; i++) {
						for (int j = 0; j < n; j++) {
									cout << road[i][j] << " ";
											}
													cout << "\n";
														}
															cout << "\n";

																cout << "pos info" << "\n";
																	for (int i = 1; i <= m; i++) {
																			cout << i << " : " << start_pos[i].first << " " << start_pos[i].second << " >>> " << end_pos[i].first << " " << end_pos[i].second << "\n";
																				}
																					cout << "\n";

																						cout << "arrived" << "\n";
																							for (int i = 1; i <= m; i++) {
																									cout << i << " : " << arrived[i] << "\n";
																										}
																											cout << "\n";
																											}

																											bool isOver() {
																												for (int i = 1; i <= m; i++) {
																														if (arrived[i] == 0) return false;
																															}
																																return true;
																																}

																																bool inRange(int x, int y) {
																																	return (x >= 0 && x < n && y >= 0 && y < n);
																																	}

																																	void getDist(int x, int y) {
																																		for (int i = 0; i < n; i++) {
																																				for (int j = 0; j < n; j++) {
																																							dist[i][j] = -1;
																																									}
																																										}
																																											queue<pair<int, int>> q;

																																												q.push({ x, y });
																																													dist[x][y] = 0;
																																														while (!q.empty()) {
																																																int cx = q.front().first;
																																																		int cy = q.front().second;
																																																				q.pop();

																																																						for (int dir = 0; dir < 4; dir++) {
																																																									int nx = cx + dx[dir];
																																																												int ny = cy + dy[dir];

																																																															if (inRange(nx, ny) && dist[nx][ny] == -1 && road[nx][ny] == 0) {
																																																																			q.push({ nx, ny });
																																																																							dist[nx][ny] = dist[cx][cy] + 1;
																																																																										}
																																																																												}
																																																																													}
																																																																													}

																																																																													int main() {
																																																																														ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
																																																																															//freopen("sample_input.txt", "r", stdin);

																																																																																cin >> n >> m >> c;
																																																																																	for (int i = 0; i < n; i++) {
																																																																																			for (int j = 0; j < n; j++) {
																																																																																						cin >> road[i][j];
																																																																																								}
																																																																																									}

																																																																																										cin >> car_x >> car_y;
																																																																																											car_x--; car_y--;
																																																																																												battery = c;

																																																																																													for (int i = 1; i <= m; i++) {
																																																																																															int xs, ys, xe, ye; cin >> xs >> ys >> xe >> ye;
																																																																																																	xs--; ys--; xe--; ye--;
																																																																																																			start_pos[i] = { xs, ys };
																																																																																																					end_pos[i] = { xe, ye };
																																																																																																							arrived[i] = 0;
																																																																																																								}

																																																																																																									//print();

																																																																																																										while (1) {
																																																																																																												getDist(car_x, car_y);
																																																																																																														
																																																																																																																int min_dist = INF;
																																																																																																																		int min_x = INF;
																																																																																																																				int min_y = INF;
																																																																																																																						int target = 0;

																																																																																																																								for (int i = 1; i <= m; i++) {
																																																																																																																											if (arrived[i]) continue;
																																																																																																																														

																																																																																																																																	int cx = start_pos[i].first;
																																																																																																																																				int cy = start_pos[i].second;
																																																																																																																																							if (dist[cx][cy] == -1) continue;

																																																																																																																																										if (min_dist > dist[cx][cy] || (min_dist == dist[cx][cy] && min_x > cx) || (min_dist == dist[cx][cy] && min_x == cx && min_y > cy)) {
																																																																																																																																														min_dist = dist[cx][cy];
																																																																																																																																																		min_x = cx;
																																																																																																																																																						min_y = cy;
																																																																																																																																																										target = i;
																																																																																																																																																													}
																																																																																																																																																															}

																																																																																																																																																																	if (min_dist == INF) {
																																																																																																																																																																				battery = -1;
																																																																																																																																																																							break;
																																																																																																																																																																									}
																																																																																																																																																																											if (battery <= dist[min_x][min_y]) {
																																																																																																																																																																														battery = -1;
																																																																																																																																																																																	break;
																																																																																																																																																																																			}
																																																																																																																																																																																					car_x = min_x;
																																																																																																																																																																																							car_y = min_y;
																																																																																																																																																																																									battery -= dist[min_x][min_y];
																																																																																																																																																																																											//print();

																																																																																																																																																																																													getDist(car_x, car_y);


																																																																																																																																																																																															if (dist[end_pos[target].first][end_pos[target].second] == -1) {
																																																																																																																																																																																																		battery = -1;
																																																																																																																																																																																																					break;
																																																																																																																																																																																																							}
																																																																																																																																																																																																									if (battery < dist[end_pos[target].first][end_pos[target].second]) {
																																																																																																																																																																																																												battery = -1;
																																																																																																																																																																																																															break;
																																																																																																																																																																																																																	}
																																																																																																																																																																																																																			car_x = end_pos[target].first;
																																																																																																																																																																																																																					car_y = end_pos[target].second;
																																																																																																																																																																																																																							battery += dist[end_pos[target].first][end_pos[target].second];
																																																																																																																																																																																																																									arrived[target] = 1;
																																																																																																																																																																																																																											//print();

																																																																																																																																																																																																																													if (isOver()) break;
																																																																																																																																																																																																																														}
																																																																																																																																																																																																																															cout << battery << "\n";
																																																																																																																																																																																																																																return 0;
																																																																																																																																																																																																																																}