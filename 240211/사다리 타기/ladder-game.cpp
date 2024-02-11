#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>

#define MAX_N 11

using namespace std;

int n, m;

vector<pair<int, int> > lines;
vector<pair<int, int> > selected_lines;

int ans = INT_MAX;

// 처음 상황과, 선택한 가로줄만 사용했을 때의
// 상황을 시뮬레이션하여
// 둘의 결과가 같은지 확인합니다.
bool Possible() {
    // Step1. 시작 숫자를 셋팅합니다.
	int num1[MAX_N], num2[MAX_N];
	for(int i = 0; i < n; i++)
		num1[i] = num2[i] = i;
	
    // Step2. 위에서부터 순서대로 적혀있는 
    // 가로줄에 대해 양쪽 번호에 해당하는 숫자를 바꿔줍니다. 
	for(int i = 0; i < (int) lines.size(); i++) {
		int idx = lines[i].second;
		swap(num1[idx], num1[idx + 1]);
	}
	for(int i = 0; i < (int) selected_lines.size(); i++) {
		int idx = selected_lines[i].second;
		swap(num2[idx], num2[idx + 1]);
	}
	
    // Step3. 두 상황의 결과가 동일한지 확인합니다.
	for(int i = 0; i < n; i++)
		if(num1[i] != num2[i])
			return false;

	return true;
}

void FindMinLines(int cnt) {
	if(cnt == m) {
		if(Possible())
			ans = min(ans, (int) selected_lines.size());
		return;
	}
	
	selected_lines.push_back(lines[cnt]);
	FindMinLines(cnt + 1);
	selected_lines.pop_back();
	
	FindMinLines(cnt + 1);
}

int main() {
	cin >> n >> m;
	
	for(int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		lines.push_back(make_pair(b, a - 1));
	}
	
	sort(lines.begin(), lines.end());

	FindMinLines(0);
	
	cout << ans;
	return 0;
}