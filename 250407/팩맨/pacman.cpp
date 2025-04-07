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