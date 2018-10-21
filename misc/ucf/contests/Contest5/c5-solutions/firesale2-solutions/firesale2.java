import java.io.*;
import java.util.*;

public class firesale2
{
	public static void main(String[] args)
	{
		FastScanner in = new FastScanner();
		int n = in.nextInt();
		int k = in.nextInt();
		int data[] = new int[n];
		for(int i = 0; i < n; i++)
			data[i] = in.nextInt()-k;
		
		TreeMap<Long, Integer> map = new TreeMap<>();
		long sum = 0;
		int ans = 0;
		for(int i = 0; i < n; i++)
		{
			sum += data[i];
			Long upper = map.ceilingKey(sum);
			if(upper != null)
			{
				int left = map.get(upper);
				ans = Math.max(ans, i-left);
				
			}
			else
				map.put(sum, i);
			
			if(sum <= 0)
				ans = Math.max(ans, i+1);
		}
					
		System.out.println(ans);
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
	}
}
