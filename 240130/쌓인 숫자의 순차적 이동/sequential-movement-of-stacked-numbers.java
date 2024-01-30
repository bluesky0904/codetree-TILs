import java.io.*;
import java.util.*;

public class Main {

    static int n;
    static int m;
    static ArrayList<Integer>[][] grid;
    static int[][] pos;
    static int[] moves;
    static int[] dx = {-1, -1, -1, 0, 1, 1, 1, 0};
    static int[] dy = {-1, 0, 1, 1, 1, 0, -1, -1};

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
        StringBuilder sb = new StringBuilder();
        StringTokenizer st = new StringTokenizer(br.readLine(), " ");

        n = Integer.parseInt(st.nextToken());
        m = Integer.parseInt(st.nextToken());

        grid = new ArrayList[n][n];
        pos = new int[(n * n) + 1][3];
        moves = new int[m];

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                grid[i][j] = new ArrayList<>();
            }
        }

        for (int i = 0; i < n; i++) {
            st = new StringTokenizer(br.readLine(), " ");
            for (int j = 0; j < n; j++) {
                int index = Integer.parseInt(st.nextToken());
                grid[i][j].add(index);
                pos[index][0] = i;
                pos[index][1] = j;
                pos[index][2] = 0;
            }
        }

        st = new StringTokenizer(br.readLine(), " ");
        for (int i = 0; i < m; i++) {
            moves[i] = Integer.parseInt(st.nextToken());
        }

        for (int movePos : moves) {
            simulate(movePos);
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                ArrayList<Integer> list = grid[i][j];
                if (list.isEmpty()) {
                    sb.append("None").append("\n");
                    continue;
                }

                for (int k = list.size() - 1; k >= 0; k--) {
                    sb.append(list.get(k)).append(" ");
                }
                sb.append("\n");
            }
        }

        bw.write(sb.toString());
        bw.close();
        br.close();
    }

    private static void simulate(int movePos) {
        int[] cur = pos[movePos];
        int x = cur[0];
        int y = cur[1];
        int index = cur[2];
        ArrayList<Integer> currentList = grid[x][y];

        PriorityQueue<int[]> pq = new PriorityQueue<>((o1, o2) -> Integer.compare(o2[2], o1[2]));

        for (int i = 0; i < 8; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (isOutOfRange(nx, ny)) {
                continue;
            }

            ArrayList<Integer> adjList = grid[nx][ny];
            if (adjList.isEmpty()) {
                continue;
            }

            for (Integer num : adjList) {
                pq.offer(new int[]{nx, ny, num});
            }
        }

        if (pq.isEmpty()) {
            return;
        }

        int[] target = pq.poll();
        ArrayList<Integer> removeList = new ArrayList<>();
        addCurrentListToTargetList(index, target, currentList, removeList);
        removeCurrentListFromRemoveList(currentList, removeList);
    }

    private static void addCurrentListToTargetList(int index, int[] target,
                                                   ArrayList<Integer> currentList, ArrayList<Integer> removeList) {
        int targetX = target[0];
        int targetY = target[1];

        ArrayList<Integer> targetList = grid[targetX][targetY];

        for (int i = index; i < currentList.size(); i++) {
            int num = currentList.get(i);
            targetList.add(num);
            removeList.add(num);
            pos[num][0] = targetX;
            pos[num][1] = targetY;
            pos[num][2] = targetList.size() - 1;
        }
    }

    private static void removeCurrentListFromRemoveList(ArrayList<Integer> currentList, ArrayList<Integer> removeList) {
        for (Integer remove : removeList) {
            currentList.remove(remove);
        }
    }

    private static boolean isOutOfRange(int x, int y) {
        return x < 0 || x >= n || y < 0 || y >= n;
    }
}