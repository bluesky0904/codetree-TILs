/*
격자 : n x n
팀
머리
꼬리
이동 선
점수

3명 이상이 한 팀
모든 사람들은 자신의 앞 사람의 허리를 잡고 움직임
맨 앞에 있는 사람을 머리사람
맨 뒤에 있는 사람을 꼬리사람
각 팀은 게임에서 주어진 이동 선을 따라서만 이동
각 팀의 이동 선은 끝이 이어져 있음
각 팀의 이동 선은 서로 겹치지 않음

라운드
1. 먼저 각 팀은 머리사람을 따라서 한 칸 이동
2. 각 라운드마다 공이 정해진 선을 따라 던져짐
n개의 행, n개의 열이 주어진다고 했을 때,
행 오름차순으로 오른쪽
열 오름차순으로 위쪽
행 내림차순으로 왼쪽
열 내림차순으로 아래쪽
4n번째 라운드를 넘어가는 경우에는 다시 1번째 라운드의 방향으로 돌아감
3. 공이 던져지는 경우에 해당 선에 사람이 있으면 최초에 만나게 되는 사람만이 공을 얻게 되어 점수를 얻게 됨
점수는 해당 사람이 머리사람을 시작으로 팀 내에서 k번째 사람이라면 k의 제곱만큼 점수를 얻게 됨.
아무도 공을 받지 못하는 경우에는 아무 점수도 획듣하지 못함
공을 획득한 팀의 경우에는 머리사람과 꼬리사람이 바뀜. 즉 방향을 바꾸게 됨
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 20;
const int MAXM = 5;

int n, m, k;
int grid[MAXN + 10][MAXN + 10];
int id_grid[MAXN + 10][MAXN + 10];
bool visited[MAXN + 10][MAXN + 10];

int team_cnt;
vector<pair<int, int>> team[MAXM + 10];
int tail[MAXM + 10];
int score[MAXM + 10];
int ball_team;

int dx[4] = {0,-1,0,1};
int dy[4] = {1,0,-1,0};

void print() {
	cout << "grid" << "\n";
		for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
							cout << grid[i][j] << " ";
									}
											cout << "\n";
												}
													cout << "\n";

														cout << "id_grid" << "\n";
															for (int i = 0; i < n; i++) {
																	for (int j = 0; j < n; j++) {
																				cout << id_grid[i][j] << " ";
																						}
																								cout << "\n";
																									}
																										cout << "\n";

																											for (int i = 1; i <= team_cnt; i++) {
																													cout << "team " << i << " : ";
																															for (int j = 0; j < (int)team[i].size(); j++) {
																																		cout << "(" << team[i][j].first << ", " << team[i][j].second << ") ";
																																				}
																																						cout << "\n";
																																							}
																																								cout << "\n";

																																									for (int i = 1; i <= team_cnt; i++) {
																																											cout << "tail : " << tail[i] << "\n";
																																												}
																																													cout << "\n";

																																														for (int i = 1; i <= team_cnt; i++) {
																																																cout << "score : " << score[i] << "\n";
																																																	}
																																																		cout << "\n";
																																																		}

																																																		bool inRange(int x, int y) {
																																																			return (x >= 0 && x < n && y >= 0 && y < n);
																																																			}

																																																			void dfs(int x, int y, int id) { // bfs가 아니라 dfs를 사용해야 하는 이유
																																																				visited[x][y] = true;
																																																					id_grid[x][y] = id;

																																																						for (int dir = 0; dir < 4; dir++) {
																																																								int nx = x + dx[dir];
																																																										int ny = y + dy[dir];

																																																												if (inRange(nx, ny) && !visited[nx][ny] && grid[nx][ny] != 0) {
																																																															if ((int)team[id].size() == 1 && grid[nx][ny] != 2) continue; // 여기서 이어줄라믄 == 4가 아니라 != 2
																																																																		if (grid[nx][ny] == 3) tail[id] = team[id].size();
																																																																					team[id].push_back({ nx, ny });
																																																																								dfs(nx, ny, id);
																																																																										}
																																																																											}
																																																																											}

																																																																											void makeTeam() {
																																																																												for (int i = 0; i < n; i++) {
																																																																														for (int j = 0; j < n; j++) {
																																																																																	visited[i][j] = false;
																																																																																				id_grid[i][j] = 0;
																																																																																						}
																																																																																							}

																																																																																								for (int id = 1; id <= team_cnt; id++) {
																																																																																										int x = team[id][0].first;
																																																																																												int y = team[id][0].second;
																																																																																														dfs(x, y, id);
																																																																																															}
																																																																																															}

																																																																																															/*
																																																																																															라운드
																																																																																															1. 먼저 각 팀은 머리사람을 따라서 한 칸 이동
																																																																																															2. 각 라운드마다 공이 정해진 선을 따라 던져짐
																																																																																															n개의 행, n개의 열이 주어진다고 했을 때,
																																																																																															행 오름차순으로 오른쪽
																																																																																															열 오름차순으로 위쪽
																																																																																															행 내림차순으로 왼쪽
																																																																																															열 내림차순으로 아래쪽
																																																																																															4n번째 라운드를 넘어가는 경우에는 다시 1번째 라운드의 방향으로 돌아감
																																																																																															3. 공이 던져지는 경우에 해당 선에 사람이 있으면 최초에 만나게 되는 사람만이 공을 얻게 되어 점수를 얻게 됨
																																																																																															점수는 해당 사람이 머리사람을 시작으로 팀 내에서 k번째 사람이라면 k의 제곱만큼 점수를 얻게 됨.
																																																																																															아무도 공을 받지 못하는 경우에는 아무 점수도 획득하지 못함
																																																																																															공을 획득한 팀의 경우에는 머리사람과 꼬리사람이 바뀜. 즉 방향을 바꾸게 됨
																																																																																															*/

																																																																																															void moveAllTeam() {
																																																																																																for (int id = 1; id <= team_cnt; id++) {

																																																																																																		int team_sz = team[id].size();
																																																																																																				pair<int, int> tmp = team[id][team_sz - 1];
																																																																																																						for (int i = team_sz - 1; i >= 1; i--) {
																																																																																																									team[id][i] = team[id][i - 1];
																																																																																																											}
																																																																																																													team[id][0] = tmp;

																																																																																																															for (int i = 0; i < team_sz; i++) {
																																																																																																																		int x = team[id][i].first;
																																																																																																																					int y = team[id][i].second;

																																																																																																																								if (i == 0) grid[x][y] = 1;
																																																																																																																											else if (i > 0 && i < tail[id]) grid[x][y] = 2;
																																																																																																																														else if (i == tail[id]) grid[x][y] = 3;
																																																																																																																																	else grid[x][y] = 4;
																																																																																																																																			}
																																																																																																																																				}
																																																																																																																																				}

																																																																																																																																				void getScore(int id, int x, int y) {
																																																																																																																																					int order = 0;
																																																																																																																																						for (int i = 0; i < (int)team[id].size(); i++) {
																																																																																																																																								if (x == team[id][i].first && y == team[id][i].second) {
																																																																																																																																											order = i;
																																																																																																																																														break;
																																																																																																																																																}
																																																																																																																																																	}
																																																																																																																																																		
																																																																																																																																																			score[id] += (order + 1) * (order + 1);
																																																																																																																																																			}

																																																																																																																																																			void throwBall(int turn) {
																																																																																																																																																				turn = (turn - 1) % (4 * n) + 1;
																																																																																																																																																					ball_team = 0;

																																																																																																																																																						if (turn <= n) {
																																																																																																																																																								for (int i = 0; i < n; i++) {
																																																																																																																																																											if (grid[turn - 1][i] != 0 && grid[turn - 1][i] != 4) {
																																																																																																																																																															getScore(id_grid[turn - 1][i], turn - 1, i);
																																																																																																																																																																			ball_team = id_grid[turn - 1][i];
																																																																																																																																																																							return;
																																																																																																																																																																										}
																																																																																																																																																																												}
																																																																																																																																																																													}
																																																																																																																																																																														else if (turn <= 2 * n) {
																																																																																																																																																																																for (int i = n - 1; i >= 0; i--) {
																																																																																																																																																																																			if (grid[i][(turn - 1) % n] != 0 && grid[i][(turn - 1) % n] != 4) {
																																																																																																																																																																																							getScore(id_grid[i][(turn - 1) % n], i, (turn - 1) % n); // 인덱스 처리가 빡셈. 0 based여서
																																																																																																																																																																																											ball_team = id_grid[i][(turn - 1) % n];
																																																																																																																																																																																															return;
																																																																																																																																																																																																		}
																																																																																																																																																																																																				}
																																																																																																																																																																																																					}
																																																																																																																																																																																																						else if (turn <= 3 * n) {
																																																																																																																																																																																																								for (int i = n - 1; i >= 0; i--) {
																																																																																																																																																																																																											if (grid[n - (((turn - 1) % n) + 1)][i] != 0 && grid[n - (((turn - 1) % n) + 1)][i] != 4) {
																																																																																																																																																																																																															getScore(id_grid[n - (((turn - 1) % n) + 1)][i], n - (((turn - 1) % n) + 1), i);
																																																																																																																																																																																																																			ball_team = id_grid[n - (((turn - 1) % n) + 1)][i];
																																																																																																																																																																																																																							return;
																																																																																																																																																																																																																										}
																																																																																																																																																																																																																												}
																																																																																																																																																																																																																													}
																																																																																																																																																																																																																														else {
																																																																																																																																																																																																																																for (int i = 0; i < n; i++) {
																																																																																																																																																																																																																																			if (grid[i][n - (((turn - 1) % n) + 1)] != 0 && grid[i][n - (((turn - 1) % n) + 1)] != 4) {
																																																																																																																																																																																																																																							getScore(id_grid[i][n - (((turn - 1) % n) + 1)], i, n - (((turn - 1) % n) + 1));
																																																																																																																																																																																																																																											ball_team = id_grid[i][n - (((turn - 1) % n) + 1)];
																																																																																																																																																																																																																																															return;
																																																																																																																																																																																																																																																		}
																																																																																																																																																																																																																																																				}
																																																																																																																																																																																																																																																					}
																																																																																																																																																																																																																																																					}

																																																																																																																																																																																																																																																					void reverseTeam() {
																																																																																																																																																																																																																																																						if (ball_team == 0) return;

																																																																																																																																																																																																																																																							vector<pair<int, int>> tmp;
																																																																																																																																																																																																																																																								for (int i = tail[ball_team]; i >= 0; i--) {
																																																																																																																																																																																																																																																										tmp.push_back(team[ball_team][i]);
																																																																																																																																																																																																																																																											}

																																																																																																																																																																																																																																																												for (int i = team[ball_team].size() - 1; i > tail[ball_team]; i--) {
																																																																																																																																																																																																																																																														tmp.push_back(team[ball_team][i]);
																																																																																																																																																																																																																																																															}

																																																																																																																																																																																																																																																																team[ball_team].clear();
																																																																																																																																																																																																																																																																	for (int i = 0; i < (int)tmp.size(); i++) {
																																																																																																																																																																																																																																																																			team[ball_team].push_back(tmp[i]);
																																																																																																																																																																																																																																																																				}

																																																																																																																																																																																																																																																																					for (int i = 0; i < (int)team[ball_team].size(); i++) {
																																																																																																																																																																																																																																																																							int x = team[ball_team][i].first;
																																																																																																																																																																																																																																																																									int y = team[ball_team][i].second;

																																																																																																																																																																																																																																																																											if (i == 0) grid[x][y] = 1;
																																																																																																																																																																																																																																																																													else if (i > 0 && i < tail[ball_team]) grid[x][y] = 2;
																																																																																																																																																																																																																																																																															else if (i == tail[ball_team]) grid[x][y] = 3;
																																																																																																																																																																																																																																																																																	else grid[x][y] = 4;
																																																																																																																																																																																																																																																																																		}
																																																																																																																																																																																																																																																																																		}

																																																																																																																																																																																																																																																																																		int main() {
																																																																																																																																																																																																																																																																																			ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
																																																																																																																																																																																																																																																																																				//freopen("sample_input.txt", "r", stdin);

																																																																																																																																																																																																																																																																																					cin >> n >> m >> k;
																																																																																																																																																																																																																																																																																						for (int i = 0; i < n; i++) {
																																																																																																																																																																																																																																																																																								for (int j = 0; j < n; j++) {
																																																																																																																																																																																																																																																																																											cin >> grid[i][j];
																																																																																																																																																																																																																																																																																													}
																																																																																																																																																																																																																																																																																														}

																																																																																																																																																																																																																																																																																															team_cnt = 0;
																																																																																																																																																																																																																																																																																																for (int i = 0; i < n; i++) {
																																																																																																																																																																																																																																																																																																		for (int j = 0; j < n; j++) {
																																																																																																																																																																																																																																																																																																					if (grid[i][j] == 1) {
																																																																																																																																																																																																																																																																																																									team_cnt++;
																																																																																																																																																																																																																																																																																																													team[team_cnt].push_back({ i, j });
																																																																																																																																																																																																																																																																																																																}
																																																																																																																																																																																																																																																																																																																		}
																																																																																																																																																																																																																																																																																																																			}

																																																																																																																																																																																																																																																																																																																				makeTeam();
																																																																																																																																																																																																																																																																																																																					//print();
																																																																																																																																																																																																																																																																																																																						for (int i = 1; i <= team_cnt; i++) {
																																																																																																																																																																																																																																																																																																																								score[i] = 0;
																																																																																																																																																																																																																																																																																																																									}
																																																																																																																																																																																																																																																																																																																										for (int turn = 1; turn <= k; turn++) {
																																																																																																																																																																																																																																																																																																																												//cout << "turn : " << turn << "\n";

																																																																																																																																																																																																																																																																																																																														//cout << "moveAllTeam" << "\n";
																																																																																																																																																																																																																																																																																																																																moveAllTeam();
																																																																																																																																																																																																																																																																																																																																		//print();

																																																																																																																																																																																																																																																																																																																																				//cout << "throwBall" << "\n";
																																																																																																																																																																																																																																																																																																																																						throwBall(turn);
																																																																																																																																																																																																																																																																																																																																								//print();

																																																																																																																																																																																																																																																																																																																																										//cout << "reverseTeam" << "\n";
																																																																																																																																																																																																																																																																																																																																												reverseTeam();
																																																																																																																																																																																																																																																																																																																																														//print();
																																																																																																																																																																																																																																																																																																																																															}

																																																																																																																																																																																																																																																																																																																																																int ans = 0;
																																																																																																																																																																																																																																																																																																																																																	for (int i = 1; i <= team_cnt; i++) {
																																																																																																																																																																																																																																																																																																																																																			ans += score[i];
																																																																																																																																																																																																																																																																																																																																																				}

																																																																																																																																																																																																																																																																																																																																																					cout << ans << "\n";
																																																																																																																																																																																																																																																																																																																																																						return 0;
																																																																																																																																																																																																																																																																																																																																																						}