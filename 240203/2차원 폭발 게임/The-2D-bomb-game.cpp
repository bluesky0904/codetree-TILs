#include <iostream>

#define MAX_NUM 100
#define BLANK -1
#define WILL_EXPLODE 0

using namespace std;

int n, m, k, end_of_numbers_1d, end_of_temp_1d;
int numbers_2d[MAX_NUM][MAX_NUM];
int numbers_1d[MAX_NUM];
int temp_2d[MAX_NUM][MAX_NUM];
int temp_1d[MAX_NUM];

// 주어진 시작점에 대하여 
// 부분 수열의 끝 위치를 반환합니다.
int GetEndIdxOfExplosion(int start_idx, int curr_num) {
    int end_idx = start_idx + 1;
    while(end_idx < end_of_numbers_1d) {
        if(numbers_1d[end_idx] == curr_num)
            end_idx++;
        else{
            break;
        }
    }

    return end_idx - 1;
}

// 터져야 할 폭탄들에 대해 터졌다는 의미로 0을 채워줍니다.
void FillZero(int start_idx, int end_idx) {
    for(int i = start_idx; i <= end_idx; i++) {
        numbers_1d[i] = WILL_EXPLODE;
    }
}

// Arr에서 폭탄이 터진 이후의 결과를 Temp에 임시로 저장합니다. 
void MoveToTemp() {
    end_of_temp_1d = 0;
    for(int i = 0; i < end_of_numbers_1d; i++) {
        if(numbers_1d[i] != WILL_EXPLODE) {
            temp_1d[end_of_temp_1d++] = numbers_1d[i];
        }
    }
}

// Temp배열을 그대로 Copy하여 Arr에 저장합니다.
void CopyFromTemp() {
    end_of_numbers_1d = end_of_temp_1d;
    for(int i = 0; i < end_of_numbers_1d; i++) {
        numbers_1d[i] = temp_1d[i];
    }
}

void Explode() {

    bool did_explode;
    do {
        did_explode = false;
        for(int curr_idx = 0; curr_idx < end_of_numbers_1d; curr_idx++) {  
            // 각 위치마다 그 뒤로 폭탄이 m개 이상 있는지 확인합니다.

            // 이미 터지기로 예정되어있는 폭탄은 패스합니다.
            if(numbers_1d[curr_idx] == WILL_EXPLODE) { 
                continue;
            }
            // curr_idx로부터 연속하여 같은 숫자를 갖는 폭탄 중 
            // 가장 마지막 위치를 찾아 반환합니다.
            int end_idx = GetEndIdxOfExplosion(curr_idx, numbers_1d[curr_idx]);

            if(end_idx - curr_idx + 1 >=  m) {
                // 연속한 숫자의 개수가 m개 이상인 경우 폭탄이 터졌음을 기록해줍니다.
                FillZero(curr_idx, end_idx);
                did_explode = true;
            }
        }

        // Arr에서 폭탄이 터진 이후의 결과를 Temp에 임시로 저장합니다. 
        MoveToTemp();
        // Temp배열을 그대로 Copy하여 Arr에 저장합니다.
        CopyFromTemp();       
    }
    while(did_explode); // 더 이상 폭탄이 터질 수 없을 때까지 반복합니다.

}

//////////////////////////////////////////////////////////////////////////////////
//이 줄을 기준으로 위에 있는 함수들에 대한 설명은 1차원 폭발 게임을 참조해주세요//
//////////////////////////////////////////////////////////////////////////////////

// 격자의 특정 열을 일차원 배열에 복사해줍니다.
void CopyColumn(int col){
    end_of_numbers_1d = 0;
    for(int i = 0; i < n; i++)
        if(numbers_2d[i][col] != BLANK)
            numbers_1d[end_of_numbers_1d++] = numbers_2d[i][col];

    return;
}

// 폭탄이 터진 결과를 격자의 해당 열에 복사해줍니다. 
void CopyResult(int col){
    int result_idx = end_of_numbers_1d - 1;
    for(int i = n - 1; i >= 0; i--) {
        if(result_idx >= 0)
            numbers_2d[i][col] = numbers_1d[result_idx--];
        else
            numbers_2d[i][col] = BLANK;
    }
}

// 폭탄이 터지는 과정을 시뮬레이션 합니다.
void Simulate() {
    for(int col = 0; col < n; col++) {
        CopyColumn(col);
        Explode();
        CopyResult(col);
    }
}

// 시계 방향으로 90도 회전해줍니다.
void Rotate() {
    // 임시 격자를 빈 칸으로 초기화해줍니다.
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            temp_2d[i][j] = BLANK;

    // 기존 격자를 시계 방향으로 90도 회전했을 때의 결과를
    // 임시 격자에 저장해줍니다.
    int curr_idx;
    for(int i = n - 1; i >= 0; i--) {
        curr_idx = n - 1;
        for(int j = n - 1; j >= 0; j--) {
            if(numbers_2d[i][j] != BLANK)
                temp_2d[curr_idx--][n - i - 1] = numbers_2d[i][j];
        }
    }

    // 임시 격자에 저장된 값들을 기존 격자에 복사합니다.
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            numbers_2d[i][j] = temp_2d[i][j];
}

int main() {
    // 입력:
    cin >> n >> m >> k;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            cin >> numbers_2d[i][j];

    // 주어진 입력에 따라 폭탄이 터지는 것을 시뮬레이션 합니다.
    Simulate();
    for(int i = 0; i < k; i++) {
        Rotate();
        Simulate();
    }

    // 격자를 순회하며 남아 있는 폭탄의 개수를 세줍니다.
    int answer = 0;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            if(numbers_2d[i][j] != BLANK)
                answer++;
    
    cout << answer;


    return 0;
}