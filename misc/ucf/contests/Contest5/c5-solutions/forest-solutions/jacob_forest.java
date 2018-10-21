import java.io.ByteArrayInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.Collections;
import java.util.InputMismatchException;

public class jacob_forest implements Runnable {

	public static void main(String[] args) {
		new Thread(null, new jacob_forest(), "name", (1L << 30)).start();
	}

	static class Solver {

		int N, C, K;
		double a, p, l;
		ArrayList<Vector> hull, pts;

		void solve(int testNumber, FastScanner s, PrintWriter out) {
			N = s.nextInt();
			C = s.nextInt();
			pts = new ArrayList<>();
			for (int i = 0; i < N; i++)
				pts.add(new Vector(s.nextDouble(), s.nextDouble()));
			hull = getHull(pts);
			K = hull.size();
			a = Math.PI * C * C;
			p = 0;
			Vector u, v;
			for (int i = 0; i < K; i++) {
				u = hull.get(i);
				v = hull.get((i + 1) % K);
				p += u.sub(v).mag();
				a += 0.5 * (u.x * v.y - u.y * v.x);
			}
			a += C * p;
			p += 2 * Math.PI * C;

			out.printf("%.2f %.2f%n", p, a);

		}

		// Returns the convex hull in COUNTER-CLOCKWISE order. Vector: Compare X then Y.
		ArrayList<Vector> getHull(ArrayList<Vector> ps) {
			@SuppressWarnings("unchecked")
			ArrayList<Vector> s = (ArrayList<Vector>) ps.clone();
			Collections.sort(s);

			int n = s.size(), j = 2, k = 2;

			if (s.size() < 3) {
				return s;
			}

			Vector[] lo = new Vector[n], up = new Vector[n];
			lo[0] = s.get(0);
			lo[1] = s.get(1);

			for (int i = 2; i < n; i++) {
				Vector p = s.get(i);
				while (j > 1 && !RT(lo[j - 2], lo[j - 1], p))
					j--;
				lo[j++] = p;
			}

			up[0] = s.get(n - 1);
			up[1] = s.get(n - 2);

			for (int i = n - 3; i >= 0; i--) { // note difference
				Vector p = s.get(i);
				while (k > 1 && !RT(up[k - 2], up[k - 1], p))
					k--;
				up[k++] = p;
			}

			ArrayList<Vector> res = new ArrayList<Vector>();
			for (int i = 0; i < k; i++)
				res.add(up[i]);
			for (int i = 1; i < j - 1; i++)
				res.add(lo[i]);

			return res;
		}

		static boolean RT(Vector a, Vector b, Vector c) {
			return b.sub(a).cross(c.sub(a)).z > 0;
		}

		class Vector implements Comparable<Vector> {
			double x, y, z;

			public Vector(double xx, double yy, double zz) {
				x = xx;
				y = yy;
				z = zz;
			}

			public Vector(double xx, double yy) {
				x = xx;
				y = yy;
				z = 0.0;
			}

			public Vector sub(Vector v) {
				return new Vector(x - v.x, y - v.y, z - v.z);
			}

			public Vector cross(Vector v) {
				return new Vector(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
			}

			public double mag() {
				return Math.sqrt((x * x) + (y * y) + (z * z));
			}

			public int compareTo(Vector p) {
				if (y == p.y)
					return Double.compare(x, p.x);
				return Double.compare(y, p.y);
			}

			public String toString() {
				return String.format("(%.3f, %.3f)", x, y);
			}
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
