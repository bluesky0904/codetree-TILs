#include <iostream>

#define MAX_NUM 100

using namespace std;

int n, m, end_of_array;
int numbers[MAX_NUM];

int GetEndIdxOfExplosion(int start_idx, int curr_num) {
    int end_idx = start_idx + 1;
    while(end_idx < end_of_array) {
        if(numbers[end_idx] == curr_num)
            end_idx++;
        else{
            break;
        }
    }

    return end_idx - 1;
}

void CutArray(int start_idx, int end_idx) {
    int cut_len = end_idx - start_idx + 1;
    for(int i = end_idx + 1; i < end_of_array; i++) {
        numbers[i - cut_len] = numbers[i];
    }
    
    end_of_array -= cut_len;
}

int main() {
    cin >> n >> m;
    for(int i = 0; i < n; i++)
        cin >> numbers[i];
    end_of_array = n;

    bool did_explode;
    int curr_idx;
    do {
        did_explode = false;
        curr_idx = 0;

        while(curr_idx < end_of_array) {
            int end_idx = GetEndIdxOfExplosion(curr_idx, numbers[curr_idx]);

            if(end_idx - curr_idx + 1 >=  m) {
                // 연속한 숫자의 개수가 m개 이상이면
                // 폭탄이 터질 수 있는 경우 해당 부분 수열을 잘라내고
                // 폭탄이 터졌음을 기록해줍니다.
                CutArray(curr_idx, end_idx);
                did_explode = true;
            }
            else {
                // 폭탄이 터질 수 없는 경우 
                // 순회할 필요가 없는 원소에 대한 탐색을 생략해줍니다.
                curr_idx = end_idx + 1;
            }
        }
    }
    while(did_explode); 

    cout << end_of_array << endl;
    for(int i = 0; i < end_of_array; i++)
        cout << numbers[i] << endl;

    return 0;
}