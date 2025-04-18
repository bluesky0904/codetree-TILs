/*
참가자 : M명
미로 : N x N, 1 based index
- 빈칸 : 참가자가 이동 가능한 칸
- 벽 : 참가자가 이동할 수 없는 칸 / 1~9 내구도를 가짐 / 회전할 때 내구도가 1씩 깎임 / 내구도가 0이 되면 빈칸으로 변경
- 출구 : 참가자가 해당 칸에 도달하면, 즉시 탈출

1. 1초마다 모든 참가자는 한 칸씩 움직임.
두 위치의 최단거리는 맨허튼거리
모든 참가자는 동시에 움직임
상하좌우로 움직일 수 있으며, 벽이 없는 곳으로 이동할 수 있음
움직인 칸은 현재 머물러 있던 칸보다 출구까지의 최단 거리가 가까워야 함
움직일 수 있는 칸이 2개 이상이라면, 상하로 움직이는 것을 우선
참가자가 움직일 수 없는 상황이라면, 움직이지 않음
한 칸에 2명 이상의 참가자가 있을 수 있음

2. 모든 참가자가 이동을 끝냈으면, 다음 조건에 의해 미로가 회전
한 명 이상의 참가자와 출구를 포함한 가장 작은 정사각형을 잡음
우선 순위 : 정사각형 크기 최소 > 좌상단 r 최소 > c 좌표 최소
선택된 정사각형은 시계방향으로 90도 회전, 회전된 벽은 내구도가 1씩 깎임

K초 동안 위의 과정을 계속 반복. 만약 K초 전에 모든 참가자가 탈출에 성공한다면, 게임이 끝남
게임이 끝났을 때, 모든 참가자들의 이동 거리 합과 출구 좌표를 출력하는 프로그램
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <tuple>
#include <cmath>
using namespace std;

const int MAXN = 10;

int N, M, K; // 미로의 크기 N, 참가자의 수 M, 게임 시간 K
int grid[MAXN + 10][MAXN + 10];
int next_grid[MAXN + 10][MAXN + 10];
int player[MAXN + 10][MAXN + 10];
int next_player[MAXN + 10][MAXN + 10];
int move_dist;
int exit_x, exit_y;

int dx[4] = { -1,1,0,0 };
int dy[4] = { 0,0,-1,1 };

void print() {
	cout << "grid" << "\n";
		for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
							cout << grid[i][j] << " ";
									}
											cout << "\n";
												}
													cout << "\n";

														cout << "player" << "\n";
															for (int i = 0; i < N; i++) {
																	for (int j = 0; j < N; j++) {
																				cout << player[i][j] << " ";
																						}
																								cout << "\n";
																									}
																										cout << "\n";

																											cout << "move_dist : " << move_dist << "\n";
																												cout << "exit : " << exit_x << " " << exit_y << "\n";
																												}

																												bool isOver() {
																													for (int i = 0; i < N; i++) {
																															for (int j = 0; j < N; j++) {
																																		if (player[i][j] > 0) return false;
																																				}
																																					}
																																						return true;
																																						}

																																						bool inRange(int x, int y) {
																																							return (x >= 0 && x < N && y >= 0 && y < N);
																																							}

																																							int getDist(int x1, int y1, int x2, int y2) {
																																								return abs(x1 - x2) + abs(y1 - y2);
																																								}

																																								pair<int, int> getNextPos(int x, int y) {
																																									for (int dir = 0; dir < 4; dir++) {
																																											int nx = x + dx[dir];
																																													int ny = y + dy[dir];

																																															if (inRange(nx, ny) && grid[nx][ny] == 0 && getDist(x, y, exit_x, exit_y) > getDist(nx, ny, exit_x, exit_y)) {
																																																		move_dist += player[x][y];
																																																					return { nx,ny };
																																																							}
																																																								}
																																																									return { x, y };
																																																									}

																																																									void moveAllPlayer() {
																																																										for (int i = 0; i < N; i++) {
																																																												for (int j = 0; j < N; j++) {
																																																															next_player[i][j] = 0;
																																																																	}
																																																																		}

																																																																			for (int i = 0; i < N; i++) {
																																																																					for (int j = 0; j < N; j++) {
																																																																								if (player[i][j] == 0) continue;

																																																																											int nx, ny;
																																																																														tie(nx, ny) = getNextPos(i, j);
																																																																																	if(!(nx == exit_x && ny == exit_y)) next_player[nx][ny] += player[i][j]; // 플레이어가 출구에 도달하면 그냥 탈출!!!
																																																																																			}
																																																																																				}

																																																																																					for (int i = 0; i < N; i++) {
																																																																																							for (int j = 0; j < N; j++) {
																																																																																										player[i][j] = next_player[i][j];
																																																																																												}
																																																																																													}
																																																																																													}

																																																																																													/*
																																																																																													2. 모든 참가자가 이동을 끝냈으면, 다음 조건에 의해 미로가 회전
																																																																																													한 명 이상의 참가자와 출구를 포함한 가장 작은 정사각형을 잡음
																																																																																													우선 순위 : 정사각형 크기 최소 > 좌상단 r 최소 > c 좌표 최소
																																																																																													선택된 정사각형은 시계방향으로 90도 회전, 회전된 벽은 내구도가 1씩 깎임
																																																																																													*/

																																																																																													bool isPossible(int sz, int stand_x, int stand_y) {
																																																																																														if (stand_x + sz - 1 >= N || stand_y + sz - 1 >= N) return false;
																																																																																															if (!(stand_x <= exit_x && exit_x < stand_x + sz && stand_y <= exit_y && exit_y < stand_y + sz)) return false;

																																																																																																for (int x = stand_x; x < stand_x + sz; x++) {
																																																																																																		for (int y = stand_y; y < stand_y + sz; y++) {
																																																																																																					if (player[x][y] > 0) return true;
																																																																																																							}
																																																																																																								}
																																																																																																									return false;
																																																																																																									}

																																																																																																									void rotate(int sz, int stand_x, int stand_y) {
																																																																																																										// 격자 회전 + 내구도 -1
																																																																																																											for (int i = 0; i < N; i++) {
																																																																																																													for (int j = 0; j < N; j++) {
																																																																																																																next_grid[i][j] = grid[i][j];
																																																																																																																		}
																																																																																																																			}

																																																																																																																				for (int x = stand_x; x < stand_x + sz; x++) {
																																																																																																																						for (int y = stand_y; y < stand_y + sz; y++) {
																																																																																																																									int ox = x - stand_x;
																																																																																																																												int oy = y - stand_y;
																																																																																																																															int rx = oy;
																																																																																																																																		int ry = sz - ox - 1;

																																																																																																																																					if(grid[x][y] > 0) next_grid[rx + stand_x][ry + stand_y] = grid[x][y] - 1;
																																																																																																																																								else next_grid[rx + stand_x][ry + stand_y] = grid[x][y];
																																																																																																																																										}
																																																																																																																																											}

																																																																																																																																												for (int i = 0; i < N; i++) {
																																																																																																																																														for (int j = 0; j < N; j++) {
																																																																																																																																																	grid[i][j] = next_grid[i][j];
																																																																																																																																																			}
																																																																																																																																																				}

																																																																																																																																																					// player 회전
																																																																																																																																																						for (int i = 0; i < N; i++) {
																																																																																																																																																								for (int j = 0; j < N; j++) {
																																																																																																																																																											next_player[i][j] = player[i][j];
																																																																																																																																																													}
																																																																																																																																																														}

																																																																																																																																																															for (int x = stand_x; x < stand_x + sz; x++) {
																																																																																																																																																																	for (int y = stand_y; y < stand_y + sz; y++) {
																																																																																																																																																																				int ox = x - stand_x;
																																																																																																																																																																							int oy = y - stand_y;
																																																																																																																																																																										int rx = oy;
																																																																																																																																																																													int ry = sz - ox - 1;

																																																																																																																																																																																next_player[rx + stand_x][ry + stand_y] = player[x][y];
																																																																																																																																																																																		}
																																																																																																																																																																																			}

																																																																																																																																																																																				for (int i = 0; i < N; i++) {
																																																																																																																																																																																						for (int j = 0; j < N; j++) {
																																																																																																																																																																																									player[i][j] = next_player[i][j];
																																																																																																																																																																																											}
																																																																																																																																																																																												}

																																																																																																																																																																																													// 출구 회전
																																																																																																																																																																																														int ox = exit_x - stand_x;
																																																																																																																																																																																															int oy = exit_y - stand_y;
																																																																																																																																																																																																int rx = oy;
																																																																																																																																																																																																	int ry = sz - ox - 1;
																																																																																																																																																																																																		exit_x = rx + stand_x;
																																																																																																																																																																																																			exit_y = ry + stand_y;
																																																																																																																																																																																																			}

																																																																																																																																																																																																			void rotateGrid() {
																																																																																																																																																																																																				for (int sz = 2; sz <= N; sz++) {
																																																																																																																																																																																																						for (int x = 0; x < N; x++) {
																																																																																																																																																																																																									for (int y = 0; y < N; y++) {
																																																																																																																																																																																																													if (isPossible(sz, x, y)) {
																																																																																																																																																																																																																		rotate(sz, x, y);
																																																																																																																																																																																																																							return;
																																																																																																																																																																																																																											}
																																																																																																																																																																																																																														}
																																																																																																																																																																																																																																}
																																																																																																																																																																																																																																	}
																																																																																																																																																																																																																																	}

																																																																																																																																																																																																																																	int main() {
																																																																																																																																																																																																																																		ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
																																																																																																																																																																																																																																			//freopen("sample_input.txt", "r", stdin);

																																																																																																																																																																																																																																				cin >> N >> M >> K;
																																																																																																																																																																																																																																					for (int i = 0; i < N; i++) {
																																																																																																																																																																																																																																							for (int j = 0; j < N; j++) {
																																																																																																																																																																																																																																										cin >> grid[i][j];
																																																																																																																																																																																																																																												}
																																																																																																																																																																																																																																													}

																																																																																																																																																																																																																																														for (int i = 0; i < N; i++) {
																																																																																																																																																																																																																																																for (int j = 0; j < N; j++) {
																																																																																																																																																																																																																																																			player[i][j] = 0;
																																																																																																																																																																																																																																																					}
																																																																																																																																																																																																																																																						}
																																																																																																																																																																																																																																																							for (int i = 1; i <= M; i++) {
																																																																																																																																																																																																																																																									int r, c; cin >> r >> c;
																																																																																																																																																																																																																																																											r--; c--;
																																																																																																																																																																																																																																																													player[r][c]++;
																																																																																																																																																																																																																																																														}

																																																																																																																																																																																																																																																															cin >> exit_x >> exit_y;
																																																																																																																																																																																																																																																																exit_x--; exit_y--;
																																																																																																																																																																																																																																																																	move_dist = 0;

																																																																																																																																																																																																																																																																		//print();
																																																																																																																																																																																																																																																																			for (int turn = 1; turn <= K; turn++) {
																																																																																																																																																																																																																																																																					//cout << "turn : " << turn << "\n";

																																																																																																																																																																																																																																																																							//cout << "moveAllPlayer" << "\n";
																																																																																																																																																																																																																																																																									moveAllPlayer();
																																																																																																																																																																																																																																																																											//print();

																																																																																																																																																																																																																																																																													if (isOver()) break;

																																																																																																																																																																																																																																																																															//cout << "rotateGrid" << "\n";
																																																																																																																																																																																																																																																																																	rotateGrid();
																																																																																																																																																																																																																																																																																			//print();
																																																																																																																																																																																																																																																																																				}

																																																																																																																																																																																																																																																																																					cout << move_dist << "\n";
																																																																																																																																																																																																																																																																																						cout << exit_x + 1 << " " << exit_y + 1 << "\n";// 풀이는 0based index로 진행했으나 문제 설정은 1based index 이기 때문에 +1 해줘야 함
																																																																																																																																																																																																																																																																																							return 0;
																																																																																																																																																																																																																																																																																							}