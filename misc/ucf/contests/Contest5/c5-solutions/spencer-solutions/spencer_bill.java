import java.util.*;
import java.io.*;
public class spencer_bill {
	static final int[] dr = {-1, 0, 1, 0};
	static final int[] dc = {0, -1, 0, 1};
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		PrintStream out = System.out;
		int R = in.nextInt();
		int C = in.nextInt();
		char[][] grid = new char[R][];
		for (int i = 0; i < R; ++i) grid[i] = in.next().toCharArray();
		int sr = -1, sc = -1, sd = -1;
		out: for (int i = 0; i < R; ++i) {
			     for (int j = 0; j < C; ++j) {
				     if (grid[i][j] != 'X' && grid[i][j] != '_') {
					     sr = i;
					     sc = j;
					     switch (grid[i][j]) {
						     case 'N':
							     sd = 0;
							     break;
						     case 'E':
							     sd = 3;
							     break;
						     case 'S':
							     sd = 2;
							     break;
						     case 'W':
							     sd = 1;
							     break;
					     }
					     break out;
				     }
			     }
		}
		Deque<Integer> q = new ArrayDeque<>();
		Deque<Integer> mq = new ArrayDeque<>();
		boolean[] visited = new boolean[1<<16];
		visited[state(sd, sr, sc)] = true;
		q.add(state(sd, sr, sc));
		mq.add(0);
		while (!q.isEmpty()) {
			int u = q.pollFirst();
			int d = getDir(u);
			int r = getR(u);
			int c = getC(u);
			int moves = mq.pollFirst();
			if (r == 0 || r == R-1 || c == 0 || c == C-1) {
				out.println(moves);
				return;
			}
			for (int i = -1; i <= 1; i += 2) {
				int nd = (d + i + 4) % 4;
				int v = state(nd, r, c);
				if (!visited[v]) {
					visited[v] = true;
					q.addLast(v);
					mq.addLast(moves + 1);
				}
			}
			int nr = r + dr[d];
			int nc = c + dc[d];
			if (0 <= nr && 0 <= nc && nr < R && nc < C && grid[nr][nc] != 'X') {
				int v = state(d, nr, nc);
				if (!visited[v]) {
					visited[v] = true;
					q.addFirst(v);
					mq.addFirst(moves);
				}
			}
		}
		out.println(-1);
	}

	static int getDir(int state) {
		return state >>> 12;
	}

	static int getR(int state) {
		return state >>> 6 & ~-(1 << 6);
	}

	static int getC(int state) {
		return state & ~-(1 << 6);
	}

	static int state(int dir, int r, int c) {
		return dir << 12 | r << 6 | c;
	}
}
