/*
격자 : n x n, 나무의 그루 수 1~100, 빈 칸 0, 벽 -1
제초제
제초제의 경우 k의 범위만큼 대각선으로 퍼짐
벽이 있는 경우 가로막혀서 전파 불가

총 박멸한 나무의 그루수

1년동안 나무의 성장과 억제
1. 인접한 네 개의 칸 중 나무가 있는 칸의 수만큼 나무가 성장
성장은 모든 나무에게 동시에 일어남

2. 기존에 있었던 나무들은 인접한 4개의 칸 중 벽, 다른 나무, 제초제 모두 없는 칸에 번식을 진행
이때 각 칸의 나무 그루 수에서 총 번식이 가능한 칸의 개수만큼 나누어진 그루 수만큼 번식이 되며, 나눌 때 생기는 나머지는 버림
번식의 과정은 모든 나무에서 동시에 일어나게 됨

3. 각 칸 중 제초제를 뿌렸을 때 나무가 가장 많이 박멸되는 칸에 제초제를 뿌림
나무가 없는 칸에 제초제를 뿌리면 박멸되는 나무가 전혀 없는 상태로 끝이 나지만
나무가 있는 칸에 제초제를 뿌리게 되면 4개의 대각선 방향으로 k칸만큼 전파되게 됨
단 전파되는 도중 벽이 있거나 나무가 아얘 없는 칸이 있는 경우, 그 칸까지는 제초제가 뿌려지며 그 이후의 칸으로는 제초제 전파x
제초제가 뿌려진 칸에는 c년만큼 제초제가 남아있다가 c + 1년째가 될 때 사라지게 됨
제초제가 뿌려진 곳에 다시 제초제가 뿌려지는 경우에는 새로 뿌려진 해로부터 다시 c년 동안 제초제가 유지

3개의 과정이 1년에 걸쳐 진행된다고 했을 때, m년 동안 총 박멸한 나무의 그루 수를 구하기
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

const int MAXN = 20;

int n, m, k, c;
int grid[MAXN + 10][MAXN + 10];
int next_grid[MAXN + 10][MAXN + 10];
int killer[MAXN + 10][MAXN + 10];

int ans;

void print() {
	cout << "grid" << "\n";
		for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
							cout << grid[i][j] << " ";
									}
											cout << "\n";
												}
													cout << "\n";

														cout << "killer" << "\n";
															for (int i = 0; i < n; i++) {
																	for (int j = 0; j < n; j++) {
																				cout << killer[i][j] << " ";
																						}
																								cout << "\n";
																									}
																										cout << "\n";

																											cout << "ans : " << ans << "\n";
																												cout << "\n";
																												}

																												bool inRange(int x, int y) {
																													return (x >= 0 && x < n && y >= 0 && y < n);
																													}

																													void growTree() {
																														for (int i = 0; i < n; i++) {
																																for (int j = 0; j < n; j++) {
																																			next_grid[i][j] = 0;
																																					}
																																						}

																																							for (int i = 0; i < n; i++) {
																																									for (int j = 0; j < n; j++) {

																																												if (grid[i][j] == -1) next_grid[i][j] = -1;
																																															else if (grid[i][j] == 0) continue;
																																																		else {
																																																						int cnt = 0;

																																																										int dx[4] = { 0,1,0,-1 };
																																																														int dy[4] = { 1,0,-1,0 };
																																																																		for (int dir = 0; dir < 4; dir++) {
																																																																							int nx = i + dx[dir];
																																																																												int ny = j + dy[dir];

																																																																																	if (inRange(nx, ny) && grid[nx][ny] > 0) cnt++;
																																																																																					}
																																																																																									next_grid[i][j] = grid[i][j] + cnt;
																																																																																												}

																																																																																														}
																																																																																															}

																																																																																																for (int i = 0; i < n; i++) {
																																																																																																		for (int j = 0; j < n; j++) {
																																																																																																					grid[i][j] = next_grid[i][j];
																																																																																																							}
																																																																																																								}
																																																																																																								}

																																																																																																								void reproduceTree(int turn) {
																																																																																																									for (int i = 0; i < n; i++) {
																																																																																																											for (int j = 0; j < n; j++) {
																																																																																																														next_grid[i][j] = 0;
																																																																																																																}
																																																																																																																	}

																																																																																																																		for (int i = 0; i < n; i++) {
																																																																																																																				for (int j = 0; j < n; j++) {

																																																																																																																							if (grid[i][j] == -1) next_grid[i][j] = -1;
																																																																																																																										else if (grid[i][j] == 0) continue;
																																																																																																																													else {
																																																																																																																																	next_grid[i][j] += grid[i][j];

																																																																																																																																					int cnt = 0;
																																																																																																																																									int dx[4] = {0,1,0,-1};
																																																																																																																																													int dy[4] = {1,0,-1,0};
																																																																																																																																																	for (int dir = 0; dir < 4; dir++) {
																																																																																																																																																						int nx = i + dx[dir];
																																																																																																																																																											int ny = j + dy[dir];

																																																																																																																																																																if (inRange(nx, ny) && grid[nx][ny] == 0 && killer[nx][ny] <= turn) cnt++;
																																																																																																																																																																				}

																																																																																																																																																																								if(cnt != 0){ // cnt가 0일 수 있음! 나누기 할 때 처리
																																																																																																																																																																													int reproduce_amount = grid[i][j] / cnt;

																																																																																																																																																																																		for (int dir = 0; dir < 4; dir++) {
																																																																																																																																																																																								int nx = i + dx[dir];
																																																																																																																																																																																														int ny = j + dy[dir];

																																																																																																																																																																																																				if (inRange(nx, ny) && grid[nx][ny] == 0 && killer[nx][ny] <= turn) next_grid[nx][ny] += reproduce_amount;
																																																																																																																																																																																																									}
																																																																																																																																																																																																													}
																																																																																																																																																																																																																}
																																																																																																																																																																																																																		}
																																																																																																																																																																																																																			}

																																																																																																																																																																																																																				for (int i = 0; i < n; i++) {
																																																																																																																																																																																																																						for (int j = 0; j < n; j++) {
																																																																																																																																																																																																																									grid[i][j] = next_grid[i][j];
																																																																																																																																																																																																																											}
																																																																																																																																																																																																																												}
																																																																																																																																																																																																																												}

																																																																																																																																																																																																																												int getCnt(int x, int y) {
																																																																																																																																																																																																																													int cnt = grid[x][y];

																																																																																																																																																																																																																														int dx[4] = { -1,1,1,-1 };
																																																																																																																																																																																																																															int dy[4] = { 1,1,-1,-1 };
																																																																																																																																																																																																																																for (int dir = 0; dir < 4; dir++) {
																																																																																																																																																																																																																																		for (int dist = 1; dist <= k; dist++) {
																																																																																																																																																																																																																																					int nx = x + dx[dir] * dist;
																																																																																																																																																																																																																																								int ny = y + dy[dir] * dist;
																																																																																																																																																																																																																																											
																																																																																																																																																																																																																																														if (!inRange(nx, ny)) break;
																																																																																																																																																																																																																																																	if (grid[nx][ny] == -1 || grid[nx][ny] == 0) break;
																																																																																																																																																																																																																																																				
																																																																																																																																																																																																																																																							cnt += grid[nx][ny];
																																																																																																																																																																																																																																																									}
																																																																																																																																																																																																																																																										}

																																																																																																																																																																																																																																																											return cnt;
																																																																																																																																																																																																																																																											}

																																																																																																																																																																																																																																																											void spreadKiller(int turn) {
																																																																																																																																																																																																																																																												int max_cnt = -1; // 구해오는 값이 초기값일 경우 처리
																																																																																																																																																																																																																																																													int max_x = -1;
																																																																																																																																																																																																																																																														int max_y = -1;

																																																																																																																																																																																																																																																															for (int i = 0; i < n; i++) {
																																																																																																																																																																																																																																																																	for (int j = 0; j < n; j++) {
																																																																																																																																																																																																																																																																				if (grid[i][j] == -1 || grid[i][j] == 0) continue;
																																																																																																																																																																																																																																																																							int cur_cnt = getCnt(i, j);
																																																																																																																																																																																																																																																																										if (max_cnt < cur_cnt) {
																																																																																																																																																																																																																																																																														max_cnt = cur_cnt;
																																																																																																																																																																																																																																																																																		max_x = i;
																																																																																																																																																																																																																																																																																						max_y = j;
																																																																																																																																																																																																																																																																																									}
																																																																																																																																																																																																																																																																																											}
																																																																																																																																																																																																																																																																																												}

																																																																																																																																																																																																																																																																																													//cout << "max_x : " << max_x << "\n";
																																																																																																																																																																																																																																																																																														//cout << "max_y : " << max_y << "\n";

																																																																																																																																																																																																																																																																																															// 제초제 뿌리기
																																																																																																																																																																																																																																																																																																if (max_cnt == -1) return; // 제초제를 뿌릴 수 없는 경우 고려
																																																																																																																																																																																																																																																																																																	ans += max_cnt;
																																																																																																																																																																																																																																																																																																		grid[max_x][max_y] = 0;
																																																																																																																																																																																																																																																																																																			killer[max_x][max_y] = turn + c + 1;
																																																																																																																																																																																																																																																																																																				int dx[4] = { -1,1,1,-1 };
																																																																																																																																																																																																																																																																																																					int dy[4] = { 1,1,-1,-1 };
																																																																																																																																																																																																																																																																																																						for (int dir = 0; dir < 4; dir++) {
																																																																																																																																																																																																																																																																																																								for (int dist = 1; dist <= k; dist++) {
																																																																																																																																																																																																																																																																																																											int nx = max_x + dx[dir] * dist;
																																																																																																																																																																																																																																																																																																														int ny = max_y + dy[dir] * dist;

																																																																																																																																																																																																																																																																																																																	if (!inRange(nx, ny)) break;
																																																																																																																																																																																																																																																																																																																				if (grid[nx][ny] == -1 || grid[nx][ny] == 0) {
																																																																																																																																																																																																																																																																																																																								killer[nx][ny] = turn + c + 1;
																																																																																																																																																																																																																																																																																																																												break;
																																																																																																																																																																																																																																																																																																																															}

																																																																																																																																																																																																																																																																																																																																		grid[nx][ny] = 0;
																																																																																																																																																																																																																																																																																																																																					killer[nx][ny] = turn + c + 1;
																																																																																																																																																																																																																																																																																																																																							}
																																																																																																																																																																																																																																																																																																																																								}
																																																																																																																																																																																																																																																																																																																																								}

																																																																																																																																																																																																																																																																																																																																								int main() {
																																																																																																																																																																																																																																																																																																																																									ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
																																																																																																																																																																																																																																																																																																																																										//freopen("sample_input.txt", "r", stdin);

																																																																																																																																																																																																																																																																																																																																											cin >> n >> m >> k >> c;
																																																																																																																																																																																																																																																																																																																																												for (int i = 0; i < n; i++) {
																																																																																																																																																																																																																																																																																																																																														for (int j = 0; j < n; j++) {
																																																																																																																																																																																																																																																																																																																																																	cin >> grid[i][j];
																																																																																																																																																																																																																																																																																																																																																				killer[i][j] = 0;
																																																																																																																																																																																																																																																																																																																																																						}
																																																																																																																																																																																																																																																																																																																																																							}

																																																																																																																																																																																																																																																																																																																																																								ans = 0;

																																																																																																																																																																																																																																																																																																																																																									//print();
																																																																																																																																																																																																																																																																																																																																																										for (int turn = 1; turn <= m; turn++) {
																																																																																																																																																																																																																																																																																																																																																												//cout << "turn : " << turn << "\n";

																																																																																																																																																																																																																																																																																																																																																														//cout << "growTree" << "\n";
																																																																																																																																																																																																																																																																																																																																																																growTree();
																																																																																																																																																																																																																																																																																																																																																																		//print();

																																																																																																																																																																																																																																																																																																																																																																				//cout << "reproduceTree" << "\n";
																																																																																																																																																																																																																																																																																																																																																																						reproduceTree(turn);
																																																																																																																																																																																																																																																																																																																																																																								//print();

																																																																																																																																																																																																																																																																																																																																																																										//cout << "spreadKiller" << "\n";
																																																																																																																																																																																																																																																																																																																																																																												spreadKiller(turn);
																																																																																																																																																																																																																																																																																																																																																																														//print();
																																																																																																																																																																																																																																																																																																																																																																															}

																																																																																																																																																																																																																																																																																																																																																																																cout << ans << "\n";
																																																																																																																																																																																																																																																																																																																																																																																	return 0;
																																																																																																																																																																																																																																																																																																																																																																																	}