#include <bits/stdc++.h>
#define endl '\n'
#define fastio ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll, ll> pll;
typedef tuple<int,int,int> tiii;
const int INF=1e9+1;

struct Rabbit {
    int x, y;
    int pid;
    int d;
    int jump_count;
    // 토끼 우선순위
    bool operator<(const Rabbit& cmp) const {
        if(jump_count==cmp.jump_count) {
            if(x+y==cmp.x+cmp.y) {
                if(x==cmp.x) {
                    if(y==cmp.y) return pid>cmp.pid;
                    return y>cmp.y;
                }
                return x>cmp.x;
            }
            return x+y>cmp.x+cmp.y;
        }
        return jump_count>cmp.jump_count;
    }
};

bool cmp(pii& a, pii& b) {
    // 토끼 이동 정렬
    if(a.first+a.second==b.first+b.second) {
        if(a.first==a.second) return a.second>b.second;
        return a.first>b.first;
    }
    return a.first+a.second>b.first+b.second;
}

bool cmp2(Rabbit& a, Rabbit& b) {
    // 점수를 추가할 토끼 정렬
    if(a.x+a.y==b.x+b.y) {
        if(a.x==b.x) {
            if(a.y==b.y) return a.pid>b.pid;
            return a.y>b.y;
        }
        return a.x>b.x;
    }
    return a.x+a.y>b.x+b.y;
}

unordered_map<int,Rabbit> rabbits; // (토끼 id, 토끼)
unordered_map<int,ll> score; // (토끼 id, 점수)
priority_queue<Rabbit> pq;
int n, m, p;

void init(int p) {
    cin>>n>>m>>p;
    for(int i=0;i<p;i++) {
        int pid, d; cin>>pid>>d;
        rabbits[pid]={0,0,pid,d,0};
    }
    for(auto it : rabbits) {
        pq.push(it.second);
        score[it.first]=0;
    }
}

// 토끼 이동은 반복되므로 나머지 연산을 적용한다
// distance %= 2 * ((N or M) -1)
// 한 방향으로 이동, 반대로 이동, 다시 반대로 이동이 하나의 사이클이 된다

pii right(int x, int y, int d) {
    int dist=d%(2*(m-1));
    if(m-y-1<dist) {
        dist-=m-y-1;
        if(m-1<dist) {
            dist-=m-1;
            y=dist;
        }
        else y=m-1-dist;
    }
    else y+=dist;
    return {x,y};
}

pii left(int x, int y, int d) {
    int dist=d%(2*(m-1));
    if(y<dist) {
        dist-=y;
        if(m-1<dist) {
            dist-=m-1;
            y=m-1-dist;
        }
        else y=dist;
    }
    else y-=dist;
    return {x,y};
}

pii up(int x, int y, int d) {
    int dist=d%(2*(n-1));
    if(x<dist) {
        dist-=x;
        if(n-1<dist) {
            dist-=n-1;
            x=n-1-dist;
        }
        else x=dist;
    }
    else x-=dist;
    return {x,y};
}

pii down(int x, int y, int d) {
    int dist=d%(2*(n-1));
    if(n-x-1<dist) {
        dist-=n-x-1;
        if(n-1<dist) {
            dist-=n-1;
            x=dist;
        }
        else x=n-1-dist;
    }
    else x+=dist;
    return {x,y};
}

void race(int k, int s) { // 토끼 이동
    set<int> selected;
    while(k--) {
        auto [x,y,pid,dist,jump_count]=pq.top();
        pq.pop();
        selected.insert(pid);

        vector<pii> v;
        pii r=right(x,y,dist);
        v.push_back(r);
        pii l=left(x,y,dist);
        v.push_back(l);
        pii u=up(x,y,dist);
        v.push_back(u);
        pii d=down(x,y,dist);
        v.push_back(d);
        
        sort(v.begin(),v.end(),cmp);
        x=v.front().first, y=v.front().second;

        rabbits[pid].x=x, rabbits[pid].y=y, rabbits[pid].jump_count++;
        pq.push(rabbits[pid]);
        
        // score
        for(auto& it : score) {
            if(it.first!=pid) it.second+=x+y+2;
        }
    }
    vector<Rabbit> v;
    for(auto pid : selected) v.push_back(rabbits[pid]);
    sort(v.begin(),v.end(),cmp2);
    score[v.front().pid]+=s;
}

void multiply(int pid, int l) { // 이동거리 곱
    rabbits[pid].d*=l;
    while(!pq.empty()) pq.pop();
    for(auto it : rabbits) pq.push(it.second);
}

ll bestRabbit() { // 최고의 토끼를 선정, 점수는 int 범위를 넘어간다
    ll max_score=0;
    for(auto it : score) max_score=max(max_score, it.second);
    return max_score;
}

int main() {
    fastio
    //freopen("input.txt","r",stdin);
    int query_cnt; cin>>query_cnt;
    while(query_cnt--) {
        int cmd; cin>>cmd;
        switch(cmd) {
            case 100: {
                init(p);
                break;
            }
            case 200: {
                int k,s; cin>>k>>s;
                race(k,s);
                break;
            }
            case 300: {
                int pid, l; cin>>pid>>l;
                multiply(pid,l);
                break;
            }
            case 400: {
                cout<<bestRabbit()<<endl;
                break;
            }
            default:
                break;
        }
    }
    return 0;
}