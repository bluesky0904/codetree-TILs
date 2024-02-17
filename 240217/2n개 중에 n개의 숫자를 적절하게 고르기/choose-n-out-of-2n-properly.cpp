#include <iostream>
#include <algorithm>
#include <cmath>
#include <climits>

#define MAX_N 10

using namespace std;

int n;
int num[2 * MAX_N];
bool visited[2 * MAX_N];

int ans = INT_MAX;

int Calc() {
    int diff = 0;
    for(int i = 0; i < 2 * n; i++)
        diff = (visited[i]) ? (diff + num[i]) : (diff - num[i]);
    
    return abs(diff);
}

void FindMin(int idx, int cnt) {
	if(cnt == n) {
		ans = min(ans, Calc());
        return;
    }
    
    if(idx == 2 * n)
		return;
    
    // 현재 숫자를 첫 번째 그룹에 사용한 경우입니다.
    visited[idx] = true;
	FindMin(idx + 1, cnt + 1);
    visited[idx] = false;
    
    // 현재 숫자를 두 번째 그룹에 사용한 경우입니다.
	FindMin(idx + 1, cnt);
}

int main() {
	cin >> n;
	
	for(int i = 0; i < 2 * n; i++)
		cin >> num[i];
	
	FindMin(0, 0);
	
	cout << ans;
	return 0;
}