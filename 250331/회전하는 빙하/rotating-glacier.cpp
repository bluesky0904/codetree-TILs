/*
얼음판 : 2^N x 2^N
A[r][c]는 (r, c)에 있는 얼음의 양을 의미. 0인 경우 얼음이 없는 것

파이어스톰을 시전하려면 시전할 때마다 단계 L결정
파이어스톰은 먼저 격자를 2^L x 2^L 크기의 부분 격자로 나눈다.
그 후, 모든 부분 격자를 시계 방향으로 90도 회전시킨다.
이후 얼음이 있는 칸 3개 또는 그 이상과 인접해있지 않은 칸은 얼음의 양이 1 줄어든다.

마법사 상어는 파이어스톰을 총 Q번 시전하려고 한다. 모든 파이어스톰을 시전한 후, 다음 2가지를 구해보자
1. 남아있는 얼음 A[r][c]의 합
2. 남아있는 얼음 중 가장 큰 덩어리가 차지하는 칸의 개수
얼음이 있는 칸이 얼음이 있는 칸과 인접해 있으면, 두 칸을 연결되어 있다고 한다. 덩어리는 연결된 칸의 집합이다.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>
#include <queue>
using namespace std;

const int GRIDSIZE = 64;

int N, Q;
int A[GRIDSIZE + 10][GRIDSIZE + 10];
int next_A[GRIDSIZE + 10][GRIDSIZE + 10];
int full_sz;

int ice_sum;
int max_cluster_sz;

bool visited[GRIDSIZE + 10][GRIDSIZE + 10];

int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };

void print() {
	cout << "A" << "\n";
		for (int i = 0; i < full_sz; i++) {
				for (int j = 0; j < full_sz; j++) {
							cout << A[i][j] << " ";
									}
											cout << "\n";
												}
													cout << "\n";
													}

													void moveGrid(int cx, int cy, int sz, int dir) {
														for (int x = 0; x < sz; x++) {
																for (int y = 0; y < sz; y++) {
																			next_A[cx + x + dx[dir] * sz][cy + y + dy[dir] * sz] = A[cx + x][cy + y]; // 좌표!!
																					}
																						}
																						}

																						void rotateGrid(int level) {
																							for (int i = 0; i < full_sz; i++) {
																									for (int j = 0; j < full_sz; j++) {
																												next_A[i][j] = 0;
																														}
																															}

																																if (level == 0) return;
																																	int l_sz = pow(2, level);
																																		int half_sz = l_sz / 2;

																																			for (int cx = 0; cx < full_sz; cx += l_sz) {
																																					for (int cy = 0; cy < full_sz; cy += l_sz) {
																																								moveGrid(cx, cy, half_sz, 1);
																																											moveGrid(cx, cy + half_sz, half_sz, 2);
																																														moveGrid(cx + half_sz, cy + half_sz, half_sz, 3);
																																																	moveGrid(cx + half_sz, cy, half_sz, 0); // 좌표와 길이 구분
																																																			}
																																																				}

																																																					for (int i = 0; i < full_sz; i++) {
																																																							for (int j = 0; j < full_sz; j++) {
																																																										A[i][j] = next_A[i][j];
																																																												}
																																																													}
																																																													}

																																																													bool inRange(int x, int y) {
																																																														return (x >= 0 && x < full_sz && y >= 0 && y < full_sz);
																																																														}

																																																														void meltGrid() {
																																																															for (int i = 0; i < full_sz; i++) {
																																																																	for (int j = 0; j < full_sz; j++) {
																																																																				next_A[i][j] = 0;
																																																																						}
																																																																							}

																																																																								for (int i = 0; i < full_sz; i++) {
																																																																										for (int j = 0; j < full_sz; j++) {
																																																																													if (A[i][j] == 0) {
																																																																																	next_A[i][j] = 0;
																																																																																					continue;
																																																																																								}

																																																																																											int cnt = 0;
																																																																																														for (int dir = 0; dir < 4; dir++) {
																																																																																																		int nx = i + dx[dir];
																																																																																																						int ny = j + dy[dir];

																																																																																																										if (inRange(nx, ny) && A[nx][ny] > 0) cnt++;
																																																																																																													}

																																																																																																																if (cnt < 3) {
																																																																																																																				if (A[i][j] == 1) next_A[i][j] = 0;
																																																																																																																								else next_A[i][j] = A[i][j] - 1;
																																																																																																																											}
																																																																																																																														else next_A[i][j] = A[i][j]; // 원래 격자에 옮기는 코드!!!
																																																																																																																																}
																																																																																																																																	}

																																																																																																																																		for (int i = 0; i < full_sz; i++) {
																																																																																																																																				for (int j = 0; j < full_sz; j++) {
																																																																																																																																							A[i][j] = next_A[i][j];
																																																																																																																																									}
																																																																																																																																										}
																																																																																																																																										}

																																																																																																																																										int BFS(int x, int y) {
																																																																																																																																											int cnt = 0;
																																																																																																																																												queue<pair<int, int>> q;
																																																																																																																																													q.push({ x, y });
																																																																																																																																														visited[x][y] = true;
																																																																																																																																															cnt++;

																																																																																																																																																while (!q.empty()) {
																																																																																																																																																		int cx = q.front().first;
																																																																																																																																																				int cy = q.front().second;
																																																																																																																																																						q.pop();

																																																																																																																																																								for (int dir = 0; dir < 4; dir++) {
																																																																																																																																																											int nx = cx + dx[dir];
																																																																																																																																																														int ny = cy + dy[dir];

																																																																																																																																																																	if (inRange(nx, ny) && !visited[nx][ny] && A[nx][ny] > 0) {
																																																																																																																																																																					q.push({ nx, ny });
																																																																																																																																																																									visited[nx][ny] = true;
																																																																																																																																																																													cnt++;
																																																																																																																																																																																}
																																																																																																																																																																																		}
																																																																																																																																																																																			}
																																																																																																																																																																																				return cnt;
																																																																																																																																																																																				}

																																																																																																																																																																																				int main() {
																																																																																																																																																																																					ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
																																																																																																																																																																																						//freopen("sample_input.txt", "r", stdin);

																																																																																																																																																																																							cin >> N >> Q;
																																																																																																																																																																																								full_sz = (int)pow(2, N);
																																																																																																																																																																																									for (int i = 0; i < full_sz; i++) {
																																																																																																																																																																																											for (int j = 0; j < full_sz; j++) {
																																																																																																																																																																																														cin >> A[i][j];
																																																																																																																																																																																																}
																																																																																																																																																																																																	}

																																																																																																																																																																																																		//print();

																																																																																																																																																																																																			for (int i = 1; i <= Q; i++) {
																																																																																																																																																																																																					//cout << "turn : " << i << "\n";

																																																																																																																																																																																																							int level; cin >> level;
																																																																																																																																																																																																									//cout << "rotateGrid" << "\n";
																																																																																																																																																																																																											rotateGrid(level);
																																																																																																																																																																																																													//print();

																																																																																																																																																																																																															//cout << "meltGrid" << "\n";
																																																																																																																																																																																																																	meltGrid();
																																																																																																																																																																																																																			//print();
																																																																																																																																																																																																																				}

																																																																																																																																																																																																																					// 1. 남아있는 얼음 A[r][c]의 합
																																																																																																																																																																																																																						ice_sum = 0;
																																																																																																																																																																																																																							for (int i = 0; i < full_sz; i++) {
																																																																																																																																																																																																																									for (int j = 0; j < full_sz; j++) {
																																																																																																																																																																																																																												if (A[i][j] > 0) ice_sum += A[i][j];
																																																																																																																																																																																																																														}
																																																																																																																																																																																																																															}
																																																																																																																																																																																																																																cout << ice_sum << "\n";

																																																																																																																																																																																																																																	// 2. 남아있는 얼음 중 가장 큰 덩어리가 차지하는 칸의 개수
																																																																																																																																																																																																																																		max_cluster_sz = 1;
																																																																																																																																																																																																																																			for (int i = 0; i < full_sz; i++) {
																																																																																																																																																																																																																																					for (int j = 0; j < full_sz; j++) {
																																																																																																																																																																																																																																								visited[i][j] = false;
																																																																																																																																																																																																																																										}
																																																																																																																																																																																																																																											}
																																																																																																																																																																																																																																												for (int i = 0; i < full_sz; i++) {
																																																																																																																																																																																																																																														for (int j = 0; j < full_sz; j++) {
																																																																																																																																																																																																																																																	if (!visited[i][j] && A[i][j] > 0) {
																																																																																																																																																																																																																																																					int cluster_sz = BFS(i, j);
																																																																																																																																																																																																																																																									if (max_cluster_sz < cluster_sz) max_cluster_sz = cluster_sz;
																																																																																																																																																																																																																																																												}
																																																																																																																																																																																																																																																														}
																																																																																																																																																																																																																																																															}

																																																																																																																																																																																																																																																																if (max_cluster_sz == 1) cout << 0 << "\n";
																																																																																																																																																																																																																																																																	else cout << max_cluster_sz << "\n";
																																																																																																																																																																																																																																																																		return 0;
																																																																																																																																																																																																																																																																		}