#include <stdio.h>
#include <queue>
using namespace std;
int n;
int visit[1000005]; int step[1000005];
queue<int>q;
bool safe(int x) {
  if(1<=x) return true;
  return false;
}
int main() {
  scanf("%d",&n);
  visit[n]=1; q.push(n);
  while(!q.empty()) {
    if(q.front()==1) {
      printf("%d",step[1]);
      break;
    }
    if(safe(q.front()-1)&&!visit[q.front()-1]) {
      visit[q.front()-1]=1;
      q.push(q.front()-1);
      step[q.front()-1]=step[q.front()]+1;
    }
    if(!visit[q.front()+1]) {
      visit[q.front()+1]=1;
      q.push(q.front()+1);
      step[q.front()+1]=step[q.front()]+1;
    }
    if(q.front()%3==0&&!visit[q.front()/3]) {
      visit[q.front()/3]=1;
      q.push(q.front()/3);
      step[q.front()/3]=step[q.front()]+1;
    }
    if(q.front()%2==0&&!visit[q.front()/2]) {
      visit[q.front()/2]=1;
      q.push(q.front()/2);
      step[q.front()/2]=step[q.front()]+1;
    }
    q.pop();
  }
  return 0;
}