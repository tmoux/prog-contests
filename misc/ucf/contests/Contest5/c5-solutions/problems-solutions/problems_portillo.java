import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashMap;
import java.util.StringTokenizer;

public class problems_portillo
{
	public static void main(String[] args) throws IOException
	{
		FastScanner in = new FastScanner();
		int n = in.nextInt();
		HashMap<String, Integer> map = new HashMap<>();
		int cnt = 0;
		
		for(int i = 0; i < n; i++)
		{
			int t = in.nextInt();
			String s = in.next();
			if(t == 1)
			{
				cnt++;
				add(map, s);
			}
			else
			{
				int num = map.getOrDefault(s, 0);
				int den = cnt;
				int g = gcd(num, den);
				
				num /= g;
				den /= g;
				
				System.out.println(num + "/" + den);
			}
		}
	}

	private static void add(HashMap<String, Integer> map, String key)
	{
		int val = map.getOrDefault(key, 0)+1;
		map.put(key, val);
	}

	private static int gcd(int a, int b)
	{
		return b == 0 ? a : gcd(b, a%b);
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
