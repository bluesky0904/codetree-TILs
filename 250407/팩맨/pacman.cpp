/*
격자 : 4 x 4
몬스터 : m개, 위치(동일 위치에 여러 객체 가능), 방향(상하좌우, 대각선)
알 :
시체
팩맨 : 위치

턴
1. 몬스터 복제 시도
몬스터는 현재의 위치에서 자신과 같은 방향을 가진 몬스터를 복제
이때 복제된 몬스터는 아직은 부화되지 않은 상태로 움직이지 못함
그림에서 알의 형태를 띄고 있는 복제된 몬스터는 현재 시점을 기준으로 각 몬스터와 동일한 방향을 지니게 되며
이후 알이 부화할 시 해당 방향을 지닌 채로 깨어나게 됨

2. 몬스터 이동
몬스터는 현재 자신이 가진 방향대로 한 칸 이동
이때 움직이려는 칸에 (몬스터 시체가 있거나) || (팩맨이 있는 경우) || (격자를 벗어남) 일 경우
반시계 방향으로 45도를 회전한 뒤 해당 방향으로 갈 수 있는지 판단
만약 갈 수 없다면, 가능할 때까지 반시계 방향으로 45도씩 회전하며 해당 방향으로 갈 수 있는지를 확인
만약 8방향을 다 돌았는데도 불구하고, 모두 움직일 수 없었다면 해당 몬스터는 움직이지 않음

3. 팩맨 이동
팩맨의 이동은 총 3칸을 이동하게 되는데, 각 이동마다 상하좌우의 선택지를 가지게 됨
총 4가지의 방향을 3칸 이동하기 때문에 총 64개의 이동 방법이 존재
우선순위 : 먹는 몬스터 양 최대 > 상좌하우
이동하는 과정에 격자 바깥을 나가는 경우는 고려하지 않음
이때 이동할 때 이동하는 칸에 있는 몬스터는 모두 먹어치운 뒤, 그 자리에 몬스터의 시체를 남김
팩맨은 알은 먹지 않으며, 움직이기 전에 함께 있었던 몬스터도 먹지 않음
즉 이동하는 과정에 있는 몬스터만 먹음

4. 몬스터 시체 소멸
몬스터의 시체는 총 2턴동안만 유지. 즉, 시체가 생기고 나면 시체가 소멸되기 까지는 총 두 턴을 필요

5. 몬스터 복제 완성
알 형태였던 몬스터가 부화. 처음 복제가 된 몬스터의 방향을 지닌 채로 깨어남

모든 턴이 진행되고 난 뒤 살아 남은 몬스터의 마리 수를 출력
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

const int FOUR = 4;

int m, t; // 몬스터의 마리 수 m, 진행되는 턴의 수 t
int pac_x, pac_y;
vector<int> monster[FOUR + 10][FOUR + 10];
vector<int> next_monster[FOUR + 10][FOUR + 10];
vector<int> egg[FOUR + 10][FOUR + 10];
int ghost[FOUR + 10][FOUR + 10];

int dx[8] = {-1,-1,0,1,1,1,0,-1};
int dy[8] = {0,-1,-1,-1,0,1,1,1};

void print() {
	cout << "pac : " << pac_x << " " << pac_y << "\n";

		cout << "monster" << "\n";
			for (int x = 0; x < FOUR; x++) {
					for (int y = 0; y < FOUR; y++) {
								cout << "{ ";
											for (int i = 0; i < (int)monster[x][y].size(); i++) {
															cout << monster[x][y][i] << " ";
																		}
																					cout << "} ";
																							}
																									cout << "\n";
																										}
																											cout << "\n";

																												cout << "egg" << "\n";
																													for (int x = 0; x < FOUR; x++) {
																															for (int y = 0; y < FOUR; y++) {
																																		cout << "{ ";
																																					for (int i = 0; i < (int)egg[x][y].size(); i++) {
																																									cout << egg[x][y][i] << " ";
																																												}
																																															cout << "} ";
																																																	}
																																																			cout << "\n";
																																																				}
																																																					cout << "\n";

																																																						cout << "ghost" << "\n";
																																																							for (int i = 0; i < FOUR; i++) {
																																																									for (int j = 0; j < FOUR; j++) {
																																																												cout << ghost[i][j] << " ";
																																																														}
																																																																cout << "\n";
																																																																	}
																																																																		cout << "\n";
																																																																		}

																																																																		void layEgg() {
																																																																			for (int x = 0; x < FOUR; x++) {
																																																																					for (int y = 0; y < FOUR; y++) {
																																																																								egg[x][y].clear();
																																																																										}
																																																																											}

																																																																												for (int x = 0; x < FOUR; x++) {
																																																																														for (int y = 0; y < FOUR; y++) {
																																																																																	for (int i = 0; i < (int)monster[x][y].size(); i++) {
																																																																																					egg[x][y].push_back(monster[x][y][i]);
																																																																																								}
																																																																																										}
																																																																																											}
																																																																																											}

																																																																																											bool inRange(int x, int y) {
																																																																																												return (x >= 0 && x < FOUR && y >= 0 && y < FOUR);
																																																																																												}

																																																																																												tuple<int, int, int> getNextPos(int x, int y, int d, int turn) {
																																																																																													for (int dir = 0; dir < 8; dir++) {
																																																																																															int nd = (d + dir) % 8;
																																																																																																	int nx = x + dx[nd];
																																																																																																			int ny = y + dy[nd];
																																																																																																					if (inRange(nx, ny) && !(nx == pac_x && ny == pac_y) && ghost[nx][ny] <= turn) return { nx, ny ,nd };
																																																																																																						}
																																																																																																							return { x, y, d };
																																																																																																							}

																																																																																																							void moveMonster(int turn) {
																																																																																																								for (int x = 0; x < FOUR; x++) {
																																																																																																										for (int y = 0; y < FOUR; y++) {
																																																																																																													next_monster[x][y].clear();
																																																																																																															}
																																																																																																																}

																																																																																																																	for (int x = 0; x < FOUR; x++) {
																																																																																																																			for (int y = 0; y < FOUR; y++) {
																																																																																																																						for (int i = 0; i < (int)monster[x][y].size(); i++) {
																																																																																																																										int nx, ny, nd;
																																																																																																																														tie(nx, ny, nd) = getNextPos(x, y, monster[x][y][i], turn);
																																																																																																																																		next_monster[nx][ny].push_back(nd);
																																																																																																																																					}
																																																																																																																																							}
																																																																																																																																								}

																																																																																																																																									for (int x = 0; x < FOUR; x++) {
																																																																																																																																											for (int y = 0; y < FOUR; y++) {
																																																																																																																																														monster[x][y].clear();
																																																																																																																																																}
																																																																																																																																																	}
																																																																																																																																																		for (int x = 0; x < FOUR; x++) {
																																																																																																																																																				for (int y = 0; y < FOUR; y++) {
																																																																																																																																																							for (int i = 0; i < (int)next_monster[x][y].size(); i++) {
																																																																																																																																																											monster[x][y].push_back(next_monster[x][y][i]);
																																																																																																																																																														}
																																																																																																																																																																}
																																																																																																																																																																	}
																																																																																																																																																																	}

																																																																																																																																																																	int max_cnt;
																																																																																																																																																																	vector<int> max_dir;
																																																																																																																																																																	vector<int> selected;
																																																																																																																																																																	int pac_trail[FOUR + 10][FOUR + 10];

																																																																																																																																																																	int getCnt() {
																																																																																																																																																																		int cnt = 0;

																																																																																																																																																																			// 이동한 경로를 새로운 격자에 표시하여 중복을 제거
																																																																																																																																																																				for (int i = 0; i < FOUR; i++) {
																																																																																																																																																																						for (int j = 0; j < FOUR; j++) {
																																																																																																																																																																									pac_trail[i][j] = 0;
																																																																																																																																																																											}
																																																																																																																																																																												}

																																																																																																																																																																													int cx = pac_x;
																																																																																																																																																																														int cy = pac_y;
																																																																																																																																																																															for (int i = 0; i < (int)selected.size(); i++) {
																																																																																																																																																																																	cx += dx[selected[i]];
																																																																																																																																																																																			cy += dy[selected[i]];

																																																																																																																																																																																					if (!inRange(cx, cy)) return -1;
																																																																																																																																																																																							pac_trail[cx][cy] = 1;
																																																																																																																																																																																								}

																																																																																																																																																																																									for (int i = 0; i < FOUR; i++) {
																																																																																																																																																																																											for (int j = 0; j < FOUR; j++) {
																																																																																																																																																																																														if (pac_trail[i][j] == 1) cnt += (int)monster[i][j].size();
																																																																																																																																																																																																}
																																																																																																																																																																																																	}

																																																																																																																																																																																																		return cnt;
																																																																																																																																																																																																		}

																																																																																																																																																																																																		void selectDir(int cnt) {
																																																																																																																																																																																																			if (cnt == 3) {
																																																																																																																																																																																																					int cur_cnt = getCnt();
																																																																																																																																																																																																							if (cur_cnt != -1 && max_cnt < cur_cnt) {
																																																																																																																																																																																																										max_cnt = cur_cnt;

																																																																																																																																																																																																													max_dir.clear();
																																																																																																																																																																																																																for (int i = 0; i < (int)selected.size(); i++) {
																																																																																																																																																																																																																				max_dir.push_back(selected[i]);
																																																																																																																																																																																																																							}
																																																																																																																																																																																																																									}
																																																																																																																																																																																																																											return;
																																																																																																																																																																																																																												}

																																																																																																																																																																																																																													for (int dir = 0; dir < 8; dir += 2) {
																																																																																																																																																																																																																															selected.push_back(dir);
																																																																																																																																																																																																																																	selectDir(cnt + 1);
																																																																																																																																																																																																																																			selected.pop_back();
																																																																																																																																																																																																																																				}
																																																																																																																																																																																																																																				}

																																																																																																																																																																																																																																				void movePac(int turn) {
																																																																																																																																																																																																																																					max_cnt = -1; // 이 초기화가 중요했네
																																																																																																																																																																																																																																						selectDir(0);

																																																																																																																																																																																																																																							for (int i = 0; i < FOUR; i++) {
																																																																																																																																																																																																																																									for (int j = 0; j < FOUR; j++) {
																																																																																																																																																																																																																																												pac_trail[i][j] = 0;
																																																																																																																																																																																																																																														}
																																																																																																																																																																																																																																															}

																																																																																																																																																																																																																																																for (int i = 0; i < (int)max_dir.size(); i++) {
																																																																																																																																																																																																																																																		pac_x += dx[max_dir[i]]; // selected 아니고 max_dir
																																																																																																																																																																																																																																																				pac_y += dy[max_dir[i]];

																																																																																																																																																																																																																																																						pac_trail[pac_x][pac_y] = 1;
																																																																																																																																																																																																																																																							}

																																																																																																																																																																																																																																																								for (int i = 0; i < FOUR; i++) {
																																																																																																																																																																																																																																																										for (int j = 0; j < FOUR; j++) {
																																																																																																																																																																																																																																																													if (pac_trail[i][j] == 1 && !monster[i][j].empty()) { // 몬스터가 있어야 먹지
																																																																																																																																																																																																																																																																	monster[i][j].clear();
																																																																																																																																																																																																																																																																					ghost[i][j] = turn + 3;
																																																																																																																																																																																																																																																																								}
																																																																																																																																																																																																																																																																										}
																																																																																																																																																																																																																																																																											}
																																																																																																																																																																																																																																																																											}

																																																																																																																																																																																																																																																																											void reproduceMonster() {
																																																																																																																																																																																																																																																																												for (int x = 0; x < FOUR; x++) {
																																																																																																																																																																																																																																																																														for (int y = 0; y < FOUR; y++) {
																																																																																																																																																																																																																																																																																	for (int i = 0; i < (int)egg[x][y].size(); i++) {
																																																																																																																																																																																																																																																																																					monster[x][y].push_back(egg[x][y][i]);
																																																																																																																																																																																																																																																																																								}
																																																																																																																																																																																																																																																																																										}
																																																																																																																																																																																																																																																																																											}
																																																																																																																																																																																																																																																																																											}

																																																																																																																																																																																																																																																																																											int main() {
																																																																																																																																																																																																																																																																																												ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
																																																																																																																																																																																																																																																																																													//freopen("sample_input.txt", "r", stdin);

																																																																																																																																																																																																																																																																																														cin >> m >> t;
																																																																																																																																																																																																																																																																																															cin >> pac_x >> pac_y;
																																																																																																																																																																																																																																																																																																pac_x--; pac_y--;

																																																																																																																																																																																																																																																																																																	for (int i = 1; i <= m; i++) {
																																																																																																																																																																																																																																																																																																			int r, c, d; cin >> r >> c >> d;
																																																																																																																																																																																																																																																																																																					r--; c--; d--;
																																																																																																																																																																																																																																																																																																							monster[r][c].push_back(d);
																																																																																																																																																																																																																																																																																																								}

																																																																																																																																																																																																																																																																																																									//print();
																																																																																																																																																																																																																																																																																																										for (int turn = 1; turn <= t; turn++) {
																																																																																																																																																																																																																																																																																																												//cout << "turn : " << turn << "\n";

																																																																																																																																																																																																																																																																																																														//cout << "layEgg" << "\n";
																																																																																																																																																																																																																																																																																																																layEgg();
																																																																																																																																																																																																																																																																																																																		//print();
																																																																																																																																																																																																																																																																																																																				
																																																																																																																																																																																																																																																																																																																						//cout << "moveMonster" << "\n";
																																																																																																																																																																																																																																																																																																																								moveMonster(turn);
																																																																																																																																																																																																																																																																																																																										//print();

																																																																																																																																																																																																																																																																																																																												//cout << "movePac" << "\n";
																																																																																																																																																																																																																																																																																																																														movePac(turn);
																																																																																																																																																																																																																																																																																																																																//print();

																																																																																																																																																																																																																																																																																																																																		//cout << "reproduceMonster" << "\n";
																																																																																																																																																																																																																																																																																																																																				reproduceMonster();
																																																																																																																																																																																																																																																																																																																																						//print();
																																																																																																																																																																																																																																																																																																																																							}

																																																																																																																																																																																																																																																																																																																																								int ans = 0;
																																																																																																																																																																																																																																																																																																																																									for (int x = 0; x < FOUR; x++) {
																																																																																																																																																																																																																																																																																																																																											for (int y = 0; y < FOUR; y++) {
																																																																																																																																																																																																																																																																																																																																														ans += (int)monster[x][y].size();
																																																																																																																																																																																																																																																																																																																																																}
																																																																																																																																																																																																																																																																																																																																																	}
																																																																																																																																																																																																																																																																																																																																																		cout << ans << "\n";
																																																																																																																																																																																																																																																																																																																																																			return 0;
																																																																																																																																																																																																																																																																																																																																																			}