from collections import deque
global n,m

n,m = map(int,input().split())
l = [list(map(int,input().split())) for i in range(n)]
visited = {}
DIR = [(0,-1),(0,1),(1,0),(-1,0)]

def canGo(x,y):
    if x>=0 and x<n and y>=0 and y<m:
        return True
    else:
        return False

def meltDown(x,y):
    global n,m
    if x>=0 and x<n and y>=0 and y<m and (x,y) in visited:
        return True
    return False

def bfs(start):
    q = deque([start])
    visited[start]=True
    while q:
        x,y = q.popleft()
        for dx,dy in DIR:
            if canGo(dx+x,dy+y) and (dx+x,dy+y) not in visited and l[x+dx][y+dy] == 0:
                q.append((x+dx,y+dy))
                visited[(x+dx,y+dy)]=True

bfs((0,0))
turn = 0
count = 0
glaciers = {}

for i in range(n):
    for j in range(m):
        if l[i][j] == 1:
            glaciers[(i,j)]=True

while True:
    turn += 1
    toDel = {}
    for i,j in glaciers:
        flag = False
        for dx,dy in DIR:
            flag = flag or meltDown(i+dx,j+dy)
        if flag:
            toDel[(i,j)]=True

    if len(toDel)==0:
        turn -= 1
        break


    count = len(toDel)
    for i,j in toDel:
        l[i][j]=0
        del glaciers[(i,j)]
    for i,j in toDel:
        if (i,j) not in visited:
            bfs((i,j))

print(turn, count)