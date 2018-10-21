import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.PriorityQueue;
import java.util.StringTokenizer;

public class spencer_portillo
{
	static char grid[][];
	static int r, c;
	static int dx[] = {-1, 0, 1, 0};
	static int dy[] = {0, 1, 0, -1};
	public static void main(String[] args) throws IOException
	{
		FastScanner in = new FastScanner();
		r = in.nextInt();
		c = in.nextInt();
		grid = new char[r][];
		int sx = -1;
		int sy = -1;
		int sd = -1;
		
		for(int i = 0; i < r; i++)
		{
			grid[i] = in.next().toCharArray();
			for(int j = 0; j < c; j++)
				if(grid[i][j] != '_' && grid[i][j] != 'X')
				{
					sx = i;
					sy = j;
					sd = getDir(grid[i][j]);
				}
		}
		
		int dist[][][] = new int[r][c][4];
		for(int a[][] : dist) for(int b[] : a) Arrays.fill(b, Integer.MAX_VALUE);
		dist[sx][sy][sd] = 0;
		PriorityQueue<State> q = new PriorityQueue<>();
		q.add(new State(sx, sy, sd, 0));
		
		while(!q.isEmpty())
		{
			State cur = q.poll();
			if(cur.x == 0 || cur.x == r-1 || cur.y == 0 || cur.y == c-1)
			{
				System.out.println(cur.dist);
				return;
			}
			if(cur.dist > dist[cur.x][cur.y][cur.d])
				continue;
			
			for(int k = 0; k < dx.length; k++)
			{
				int cost = 4;
				if(k == cur.d)
					cost = 0;
				else if((k+1+4) % 4 == cur.d || (k-1+4) % 4 == cur.d)
					cost = 1;
				else
					continue;
				
				if(cur.dist + cost < dist[cur.x][cur.y][k])
				{
					dist[cur.x][cur.y][k] = cur.dist + cost;
					q.add(new State(cur.x, cur.y, k, dist[cur.x][cur.y][k]));
				}
				
				int nx = cur.x + dx[k];
				int ny = cur.y + dy[k];
				if(grid[nx][ny] == 'X') continue;
				
				if(cur.dist + cost < dist[nx][ny][k])
				{
					dist[nx][ny][k] = cur.dist + cost;
					q.add(new State(nx, ny, k, dist[nx][ny][k]));
				}
			}
		}
		
		System.out.println(-1);
	}
	
	public static class State implements Comparable<State>
	{
		int x, y, d, dist;
		
		public State(int xx, int yy, int dd, int dt)
		{
			x = xx;
			y = yy;
			d = dd;
			dist = dt;
		}

		@Override
		public int compareTo(State o)
		{
			return Integer.compare(dist, o.dist);
		}
	}

	private static int getDir(char c)
	{
		if(c == 'N')
			return 0;
		if(c == 'E')
			return 1;
		if(c == 'S')
			return 2;
		return 3;
	}

	public static class FastScanner
	{
		BufferedReader br;
		StringTokenizer st;

		public FastScanner(String s)
		{
			try {
				br = new BufferedReader(new FileReader(s));
			} catch (FileNotFoundException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}

		public FastScanner()
		{
			br = new BufferedReader(new InputStreamReader(System.in));
		}

		String nextToken()
		{
			while (st == null || !st.hasMoreElements())
			{
				try {
					st = new StringTokenizer(br.readLine());
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
			return st.nextToken();
		}

		int nextInt()
		{
			return Integer.parseInt(nextToken());
		}

		long nextLong()
		{
			return Long.parseLong(nextToken());
		}

		double nextDouble()
		{
			return Double.parseDouble(nextToken());
		}
		
		String next()
		{
			return nextToken();
		}
		
		public boolean hasNext()
		{
			if(st != null && st.hasMoreElements())
				return true;
			
			try {
				st = new StringTokenizer(br.readLine());
			} catch (Exception e) {
				// TODO Auto-generated catch block
				return false;
			}
			
			if(st == null) return false;
			return true;
		}
	}
}
