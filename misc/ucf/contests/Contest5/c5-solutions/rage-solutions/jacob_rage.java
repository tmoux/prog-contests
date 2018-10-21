import java.io.ByteArrayInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.nio.charset.StandardCharsets;
import java.util.InputMismatchException;

public class jacob_rage {

	static class Solver {

		int N, I, L;
		double[][] og, wrk;

		void solve(FastScanner s, PrintWriter out) {
			N = s.nextInt();
			I = s.nextInt();
			L = s.nextInt();
			og = new double[N][I + 1];
			wrk = new double[N][I + 1];
			for (int j = 0; j < I; j++)
				for (int i = 0; i < N; i++)
					og[i][j] = s.nextInt();

			for (int l = 0; l < L; l++) {
				for (int i = 0; i < N; i++) {
					System.arraycopy(og[i], 0, wrk[i], 0, I);
					wrk[i][I] = s.nextInt();
				}

				out.println(gaussian(wrk) ? "YES" : "NO");
			}
		}

		boolean gaussian(double[][] m) {
			int R = m.length, C = m[0].length;
			int pc = 0, pr = 0;
			while (pr < R && pc < C) {
				int sr = pr;
				for (int j = pr + 1; j < R; j++)
					if (Math.abs(m[j][pc]) > Math.abs(m[sr][pc]))
						sr = j;
				swap(m, sr, pr);
				if (eq(m[pr][pc], 0)) {
					pc++;
					continue;
				}
				double piv = m[pr][pc];
				for (int j = pc; j < C; j++)
					m[pr][j] /= piv;
				for (int j = 0; j < R; j++) {
					if (j == pr)
						continue;
					double ratio = -m[j][pc];
					for (int k = pc; k < C; k++) {
						m[j][k] += m[pr][k] * ratio;
					}
				}
				pc++;
				pr++;
			}

			for (int r = 0; r < N; r++)
				for (int c = 0; c <= I; c++)
					if (!eq(m[r][c], 0)) {
						if (c == I)
							return false;
						break;
					}
			return true;
		}

		void swap(double[][] a, int u, int v) {
			double[] t = a[u];
			a[u] = a[v];
			a[v] = t;
		}

		boolean eq(double a, double b) {
			return Math.abs(a - b) < 1e-6;
		}

	}

	public static void main(String[] args) {

		FastScanner s = new FastScanner(System.in);
		PrintWriter out = new PrintWriter(System.out);

		Solver solver = new Solver();
		solver.solve(s, out);

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
