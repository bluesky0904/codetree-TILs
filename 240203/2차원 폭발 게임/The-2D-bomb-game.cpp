#include <iostream>
#define MAX_N 100
#define MAX_M 100
#define MAX_K 1000
using namespace std;

int n, m, k;
int grid[MAX_N][MAX_N];     // 폭탄이 들어있는 격자
int temp[MAX_N][MAX_N];     // 임시로 저장할 격자
bool IsBombed;                       // 이번 턴에서 터졌는지 확인하는 변수
int ans;    // 남아있는 폭탄 개수

void makeZero(int startRow, int endRow, int col){   // col열의 startRow부터 endRow까지 숫자를 0으로 만드는 함수
    for(int i=startRow; i <= endRow; i++){
        grid[i][col] = 0;
    }
}

void doBomb(){              // m개 이상의 연속된 수를 0으로 만들어 터뜨리는 함수
    // j열을 차례대로 볼껀데
    for(int j=0; j<n; j++){
        int curNum = grid[0][j], curCnt = 1, startIdx = 0;   // 맨 처음 수를 cur으로 보
        for(int i=1; i<n; i++){  // 그 다음 인덱스부터 확인 
            if(grid[i][j] == 0) continue;   // 0이면 넘어가기
            if(curNum == grid[i][j]){       // 만약 현재 확인하려는 수와 똑같은 것이 나온다면
                curCnt++;                   // 개수 증가
            }
            else{                           // 만약 다른 수가 나온다면
                if(curCnt >=m){             // 그 전까지 수가 m개 이상이라면
                    // startIdx부터 i-1까지 0으로 만들기 
                    IsBombed = true;
                    makeZero(startIdx,i-1, j);
                }
                curNum = grid[i][j], curCnt = 1, startIdx = i;  // 현재 수로 업데이트 하기
            }
        }
        // 마지막까지 연속인지 확인
        if(curCnt >= m && curNum != 0){
            IsBombed = true;
            makeZero(startIdx, n-1, j);
        }
    }
}

void InitializeTmp(){    // temp변수를 초기화하는 함수 
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++)
            temp[i][j] = 0;
    }
}

void doGravity(){
    // 먼저 temp 배열 초기화
    InitializeTmp();

     // 아래로 내리기
    for(int j=0; j<n; j++){
        int tempLastIdx = n-1;
        for(int i=n-1; i>=0; i--){
            if(grid[i][j]){
                temp[tempLastIdx--][j] = grid[i][j];
            }
        }
    }
    // temp를 grid로 옮기기
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            grid[i][j] = temp[i][j];
}

void FindStraightNumbers(){     // m개 이상의 연속 수를 0으로 만들고, 중력작용하는 함수
    IsBombed = false;
    while(true){       
        doBomb();               // 터뜨리고
        if(IsBombed){           // 터진게 있다면 
            doGravity();        // 중력 작용하고
            IsBombed = false;   // 다시 터진게 없다고 바꿔놓기
        }
        else{                   // 터진게 없다면
            doGravity();        // 중력 작용하고
            break;              // 반복문 나가기
        }
    }
}

void RotateClockWise(){         // grid를 회전하는 함수
    // 1. temp에 grid 회전한 것 넣기
    InitializeTmp();
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            temp[j][n-1-i] = grid[i][j];
        }
    }

    // 2. temp를 grid로 옮기기
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            grid[i][j] = temp[i][j];
}

int main() {
    // 입력:
    cin >> n >> m >> k;

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> grid[i][j];
        }
    }
    while(k--){
        // 1. m개 이상이면 0으로 만들고, 중력작용하기
        FindStraightNumbers();
        // 2. 회전하기
        RotateClockWise();
        // 3. 한 번 더 0으로 만들고, 중력작용하기
        FindStraightNumbers();

    }

    // 출력:
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
           if(grid[i][j]) ans++;
        }
    }
    cout << ans << '\n';
    return 0;
}