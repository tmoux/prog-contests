import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.math.BigInteger;
import java.util.Arrays;
import java.util.StringTokenizer;

public class together_slow
{
	static int n;
	static long cs[], ls[], memo[][];
	public static void main(String[] args) throws IOException
	{
		FastScanner in = new FastScanner();
		n = in.nextInt();
		cs = new long[n];
		ls = new long[n];
		memo = new long[n][n];
		
		for(int i = 0; i < n; i++)
			ls[i] = in.nextInt();
		for(int i = 0; i < n; i++)
			cs[i] = in.nextInt();
		
		for(long a[] : memo)
			Arrays.fill(a, -1);
		long ans = go(0, n-1);
		System.out.println(ans);
	}
 
	private static long go(int s, int e)
	{
		if(s >= e)
			return 0;
		if(memo[s][e] != -1)
			return memo[s][e];
		
		long ans = Long.MAX_VALUE;
		
		for(int i = s; i < e; i++)
		{
			long cost = 0;
			for(int j = s; j <= e; j++)
				cost += ls[j];
			ans = Math.min(ans, Math.min(cs[i], cs[i+1]) * cost + go(s, i) + go(i+1, e));
		}
		
		return memo[s][e] = ans;
	}

	private static long sum(int l, int r)
	{
		if(l > r)
			return 0;
		if(l == 0)
			return ls[r];
		
		return ls[r] - ls[l-1];
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
