/*
i번 줄의 결과는 무조건 i번으로 가야함
데이터가 제대로 옮겨지지 않은 경우를 버그라고 함
가로선 = 메모리 유실선이 있을 수 있는 위치 = 취약 지점, 이웃한 선과만 이어질 수 있음
메모리 유실선을 추가할 때 선이 겹쳐지도록 추가하는 것은 불가
최소한의 메모리 유실선을 추가해서 버그를 없애는 프로그램
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <climits>
#include <vector>
#include <algorithm>
#include <tuple>
using namespace std;

const int MAXH = 30;
const int MAXN = 10;

int n, m, h; // 고객의 수 n, 메모리 유실 선의 개수 m, 취약 지점의 개수 h
int line[MAXH + 10][MAXN + 10];
int ans;
int num[MAXN + 10];

vector<pair<int, int>> candidate;

bool isPossible() {
	// 겹치는 선분 확인
		for (int i = 1; i <= h; i++) {
				for (int j = 1; j < n ; j++) {
							if (line[i][j] == 1 && line[i][j + 1] == 1) return false;
									}
										}
											
												for (int i = 1; i <= n; i++) num[i] = i;

													for (int i = 1; i <= h; i++) {
															for (int j = 1; j < n; j++) {
																		if (line[i][j]) {
																						int tmp = num[j];
																										num[j] = num[j + 1];
																														num[j + 1] = tmp;
																																	}
																																			}
																																				}

																																					for (int i = 1; i <= n; i++) {
																																							if (num[i] != i) return false;
																																								}

																																									return true;
																																									}

																																									void selectLine(int cnt, int start) {
																																										if (isPossible()) ans = min(ans, cnt);

																																											if (cnt == 3 || start == (int)candidate.size())return;
																																												
																																													selectLine(cnt, start + 1);

																																														int a, b;
																																															tie(a, b) = candidate[start];
																																																line[a][b] = 1;
																																																	selectLine(cnt + 1, start + 1);
																																																		line[a][b] = 0;
																																																		}

																																																		int main() {
																																																			ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
																																																				//freopen("sample_input.txt", "r", stdin);

																																																					cin >> n >> m >> h;
																																																						for (int i = 1; i <= m; i++) {
																																																								int a, b; cin >> a >> b;
																																																										line[a][b] = 1;
																																																											}

																																																												for (int i = 1; i <= h; i++) {
																																																														for (int j = 1; j < n; j++) {
																																																																	if (line[i][j] == 0) candidate.push_back({ i, j });
																																																																			}
																																																																				}

																																																																					ans = INT_MAX;
																																																																						selectLine(0, 0);
																																																																							if (ans == INT_MAX) cout << -1 << "\n";
																																																																								else cout << ans << "\n";

																																																																									return 0;
																																																																									}