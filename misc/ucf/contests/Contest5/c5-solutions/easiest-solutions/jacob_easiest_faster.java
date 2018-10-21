import java.io.ByteArrayInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.InputMismatchException;

public class jacob_easiest_faster implements Runnable {

	public static void main(String[] args) {
		new Thread(null, new jacob_easiest_faster(), "name", (1L << 30)).start();
	}

	static class Solver {

		class Node {

			ArrayList<Node> adj = new ArrayList<>();
			boolean t, dead = false;
			int size = 0, id;

			Node(boolean tt, int i) {
				t = tt;
				id = i + 1;
			}

			Node centroid() {
				for (Node n : adj) {
					if (n.dead) {
						continue;
					}
					if (n.size > size / 2) {
						int os = size;
						size = os - n.size;
						n.size = os;
						return n.centroid();
					}
				}
				return this;
			}

			void build(int dep, Node p, ArrayList<Integer> a) {
				a.add(dep);
				for (Node n : adj)
					if (n != p && !n.dead && n.t == t)
						n.build(dep + 1, this, a);
			}

			long count(ArrayList<Integer> ar) {
				Collections.sort(ar);
				long res = 0;
				int len = ar.size(), p = len - 1;
				for (int i = 0; i < len; i++) {
					if (p < 0 || ar.get(i) > K)
						break;
					while (p >= 0 && ar.get(p) + ar.get(i) > K)
						p--;
					res += Math.max(p - i, 0);
				}
				return res;
			}

			long calc2() {
				long rem = 0;
				all.clear();
				all.add(0);
				for (Node n : adj) {
					if (n.dead || n.t != t)
						continue;
					ff.clear();
					n.build(1, this, ff);
					rem += count(ff);
					all.addAll(ff);
				}
				long aaa = count(all);
				return aaa - rem;
			}

		}

		void dfs(Node n, Node p) {
			n.size = 1;
			for (Node e : n.adj) {
				if (e == p || e.dead)
					continue;
				dfs(e, n);
				n.size += e.size;
			}
		}

		void go(Node s) {
			dfs(s, null);
			cc = s.centroid();
			long c = cc.calc2();
			tot += c;
			cc.dead = true;
			for (Node n : cc.adj) {
				if (!n.dead)
					go(n);
			}
		}

		long tot = 0;
		int N, K, cs[], f[];
		Node cc, nodes[];
		ArrayList<Integer> all = new ArrayList<>(), ff = new ArrayList<>();

		void solve(int testNumber, FastScanner s, PrintWriter out) {

			N = s.nextInt();
			K = s.nextInt();
			cs = new int[N + 1];
			f = new int[N];
			nodes = new Node[N];
			for (int i = 0; i < N; i++)
				nodes[i] = new Node(s.next().charAt(0) == 'G', i);
			for (int i = 1; i < N; i++) {
				int u = s.nextInt() - 1, v = s.nextInt() - 1;
				nodes[u].adj.add(nodes[v]);
				nodes[v].adj.add(nodes[u]);
			}

			go(nodes[0]);
			out.println(tot);

		}

	}

	public void run() {

		FastScanner s = new FastScanner(System.in);
		PrintWriter out = new PrintWriter(System.out);

		Solver solver = new Solver();
		solver.solve(1, s, out);

		out.close();

	}

	static class FastScanner {
		private InputStream stream;
		private byte[] buf = new byte[1024];
		private int curChar;
		private int numChars;

		public FastScanner(InputStream stream) {
			this.stream = stream;
		}

		public FastScanner(File f) throws FileNotFoundException {
			this(new FileInputStream(f));
		}

		public FastScanner(String s) {
			this.stream = new ByteArrayInputStream(s.getBytes(StandardCharsets.UTF_8));
		}

		int read() {
			if (numChars == -1)
				throw new InputMismatchException();
			if (curChar >= numChars) {
				curChar = 0;
				try {
					numChars = stream.read(buf);
				} catch (IOException e) {
					throw new InputMismatchException();
				}
				if (numChars <= 0)
					return -1;
			}
			return buf[curChar++];
		}

		boolean isSpaceChar(int c) {
			return c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1;
		}

		boolean isEndline(int c) {
			return c == '\n' || c == '\r' || c == -1;
		}

		public int nextInt() {
			return Integer.parseInt(next());
		}

		public long nextLong() {
			return Long.parseLong(next());
		}

		public double nextDouble() {
			return Double.parseDouble(next());
		}

		public String next() {
			int c = read();
			while (isSpaceChar(c))
				c = read();
			StringBuilder res = new StringBuilder();
			do {
				res.appendCodePoint(c);
				c = read();
			} while (!isSpaceChar(c));
			return res.toString();
		}

		public String nextLine() {
			int c = read();
			while (isEndline(c))
				c = read();
			StringBuilder res = new StringBuilder();
			do {
				res.appendCodePoint(c);
				c = read();
			} while (!isEndline(c));
			return res.toString();
		}

		// Jacob Garbage

		public int[] nextIntArray(int N) {
			int[] ret = new int[N];
			for (int i = 0; i < N; i++)
				ret[i] = this.nextInt();
			return ret;
		}

		public int[][] next2DIntArray(int N, int M) {
			int[][] ret = new int[N][];
			for (int i = 0; i < N; i++)
				ret[i] = this.nextIntArray(M);
			return ret;
		}

		public long[] nextLongArray(int N) {
			long[] ret = new long[N];
			for (int i = 0; i < N; i++)
				ret[i] = this.nextLong();
			return ret;
		}

		public long[][] next2DLongArray(int N, int M) {
			long[][] ret = new long[N][];
			for (int i = 0; i < N; i++)
				ret[i] = nextLongArray(M);
			return ret;
		}

		public double[] nextDoubleArray(int N) {
			double[] ret = new double[N];
			for (int i = 0; i < N; i++)
				ret[i] = this.nextDouble();
			return ret;
		}

		public double[][] next2DDoubleArray(int N, int M) {
			double[][] ret = new double[N][];
			for (int i = 0; i < N; i++)
				ret[i] = this.nextDoubleArray(M);
			return ret;
		}

	}

}
