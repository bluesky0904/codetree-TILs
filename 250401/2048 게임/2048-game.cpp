#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 20;

int n;
int grid[MAXN + 10][MAXN + 10];
int next_grid[MAXN + 10][MAXN + 10];
int gravity_grid[MAXN + 10][MAXN + 10];
int max_block;

vector<int> dir_v;

int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };

void print() {
	cout << "gravity_grid" << "\n";
		for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
							cout << gravity_grid[i][j] << " ";
									}
											cout << "\n";
												}
													cout << "\n";
													}

													/*
													상하좌우 중 한 방향을 정하게 되면, 모든 숫자들이 해당 방향으로 전부 밀리게 됨
													같은 숫자끼리 만나게 되는 경우 두 숫자가 합쳐지게 됨
													단 한 번의 중력작용으로 이미 합쳐진 숫자가 연쇄적으로 합쳐지진 않음
													세 개 이상 같은 숫자가 중력 작용 방향으로 놓여 있으면, 중력에 의해 부딪히게 될 벽에서 가까운 숫자부터 두 개씩만 합쳐짐
													서너개 이상의 숫자가 하나로 합쳐질 순 없고 바닥에 가까운 순서대로 한 쌍씩 짝을 이뤄 합쳐짐
													2, 4, 8, 16 등 2의 거듭제곱꼴로 나타나는 2 이상 2048 이하의 숫자들로 구성된 4 x 4 격자판이 주어졌을 때
													5번 움직인 이후에 격자판에서 가장 큰 값의 최댓값을 구하기
													*/

													void setGravity() {

														for (int i = 0; i < n; i++) {
																for (int j = 0; j < n; j++) {
																			next_grid[i][j] = 0;
																					}
																						}

																							for (int j = 0; j < n; j++) {
																									int idx = n - 1;
																											for (int i = n - 1; i >= 0; i--) {
																														if (gravity_grid[i][j] != 0) {
																																		next_grid[idx][j] = gravity_grid[i][j];
																																						idx--;
																																									}
																																											}
																																												}

																																													for (int i = 0; i < n; i++) {
																																															for (int j = 0; j < n; j++) {
																																																		gravity_grid[i][j] = next_grid[i][j];
																																																				}
																																																					}

																																																					}

																																																					void sumBlock() {

																																																						for (int i = 0; i < n; i++) {
																																																								for (int j = 0; j < n; j++) {
																																																											next_grid[i][j] = 0;
																																																													}
																																																														}

																																																															for (int j = 0; j < n; j++) {
																																																																	for (int i = n - 1; i >= 0; i--) {
																																																																				if (gravity_grid[i][j] == 0) continue;
																																																																							if (i != 0 && gravity_grid[i][j] == gravity_grid[i - 1][j]) {
																																																																											next_grid[i][j] = gravity_grid[i][j] * 2;
																																																																															i--;
																																																																																		}
																																																																																					else {
																																																																																									next_grid[i][j] = gravity_grid[i][j];
																																																																																												}
																																																																																														}
																																																																																																/*
																																																																																																		while (1) {
																																																																																																					if (gravity_grid[idx][j] == gravity_grid[idx - 1][j]) {
																																																																																																									next_grid[idx][j] = gravity_grid[idx][j] * 2;
																																																																																																												}
																																																																																																															else {
																																																																																																																			next_grid[idx][j] = gravity_grid[idx][j];
																																																																																																																							next_grid[idx - 1][j] = gravity_grid[idx - 1][j];
																																																																																																																										}
																																																																																																																													idx -= 2;
																																																																																																																																if (idx <= 0) break;
																																																																																																																																		}
																																																																																																																																				*/
																																																																																																																																					}

																																																																																																																																						for (int i = 0; i < n; i++) {
																																																																																																																																								for (int j = 0; j < n; j++) {
																																																																																																																																											gravity_grid[i][j] = next_grid[i][j];
																																																																																																																																													}
																																																																																																																																														}

																																																																																																																																														}

																																																																																																																																														void rotate(int rot) {
																																																																																																																																															while (rot--) {
																																																																																																																																																	for (int i = 0; i < n; i++) {
																																																																																																																																																				for (int j = 0; j < n; j++) {
																																																																																																																																																								next_grid[i][j] = 0;
																																																																																																																																																											}
																																																																																																																																																													}

																																																																																																																																																															for (int i = 0; i < n; i++) {
																																																																																																																																																																		for (int j = 0; j < n; j++) {
																																																																																																																																																																						next_grid[j][n - i - 1] = gravity_grid[i][j];
																																																																																																																																																																									}
																																																																																																																																																																											}

																																																																																																																																																																													for (int i = 0; i < n; i++) {
																																																																																																																																																																																for (int j = 0; j < n; j++) {
																																																																																																																																																																																				gravity_grid[i][j] = next_grid[i][j];
																																																																																																																																																																																							}
																																																																																																																																																																																									}
																																																																																																																																																																																										}
																																																																																																																																																																																										}

																																																																																																																																																																																										void setAllGravity() {
																																																																																																																																																																																											for (int i = 0; i < n; i++) {
																																																																																																																																																																																													for (int j = 0; j < n; j++) {
																																																																																																																																																																																																gravity_grid[i][j] = grid[i][j];
																																																																																																																																																																																																		}
																																																																																																																																																																																																			}

																																																																																																																																																																																																				for (int dir : dir_v) { // dir 0 1 2 3 4가 아니라 dir_v의 값이 들어가야지
																																																																																																																																																																																																						if (dir == 0) rotate(2);
																																																																																																																																																																																																								else if (dir == 1) rotate(1); // 여기 왜 mssing?
																																																																																																																																																																																																										else if (dir == 3) rotate(3);

																																																																																																																																																																																																												setGravity();
																																																																																																																																																																																																														sumBlock();
																																																																																																																																																																																																																setGravity();

																																																																																																																																																																																																																		if (dir == 0) rotate(2);
																																																																																																																																																																																																																				else if (dir == 1) rotate(3);
																																																																																																																																																																																																																						else if (dir == 3) rotate(1);

																																																																																																																																																																																																																								//print();
																																																																																																																																																																																																																									}
																																																																																																																																																																																																																									}

																																																																																																																																																																																																																									void selectDir(int cnt) {
																																																																																																																																																																																																																										if (cnt == 5) {
																																																																																																																																																																																																																												/*
																																																																																																																																																																																																																														cout << "dir : ";
																																																																																																																																																																																																																																for (int dir = 0; dir < (int)dir_v.size(); dir++) {
																																																																																																																																																																																																																																			cout << dir_v[dir] << " ";
																																																																																																																																																																																																																																					}
																																																																																																																																																																																																																																							cout << "\n";
																																																																																																																																																																																																																																									*/

																																																																																																																																																																																																																																											setAllGravity();
																																																																																																																																																																																																																																													for (int i = 0; i < n; i++) {
																																																																																																																																																																																																																																																for (int j = 0; j < n; j++) {
																																																																																																																																																																																																																																																				if (max_block < gravity_grid[i][j]) max_block = gravity_grid[i][j];
																																																																																																																																																																																																																																																							}
																																																																																																																																																																																																																																																									}
																																																																																																																																																																																																																																																											return;
																																																																																																																																																																																																																																																												}

																																																																																																																																																																																																																																																													for (int dir = 0; dir < 4; dir++) {
																																																																																																																																																																																																																																																															dir_v.push_back(dir);
																																																																																																																																																																																																																																																																	selectDir(cnt + 1);
																																																																																																																																																																																																																																																																			dir_v.pop_back();
																																																																																																																																																																																																																																																																				}
																																																																																																																																																																																																																																																																				}

																																																																																																																																																																																																																																																																				int main() {
																																																																																																																																																																																																																																																																					ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
																																																																																																																																																																																																																																																																						//freopen("sample_input.txt", "r", stdin);

																																																																																																																																																																																																																																																																							cin >> n;
																																																																																																																																																																																																																																																																								for (int i = 0; i < n; i++) {
																																																																																																																																																																																																																																																																										for (int j = 0; j < n; j++) {
																																																																																																																																																																																																																																																																													cin >> grid[i][j];
																																																																																																																																																																																																																																																																															}
																																																																																																																																																																																																																																																																																}
																																																																																																																																																																																																																																																																																	/*
																																																																																																																																																																																																																																																																																		for (int i = 0; i < n; i++) {
																																																																																																																																																																																																																																																																																				for (int j = 0; j < n; j++) {
																																																																																																																																																																																																																																																																																							gravity_grid[i][j] = grid[i][j];
																																																																																																																																																																																																																																																																																									}
																																																																																																																																																																																																																																																																																										}
																																																																																																																																																																																																																																																																																											*/
																																																																																																																																																																																																																																																																																												
																																																																																																																																																																																																																																																																																													selectDir(0);
																																																																																																																																																																																																																																																																																														cout << max_block << "\n";
																																																																																																																																																																																																																																																																																															return 0;
																																																																																																																																																																																																																																																																																															}