import java.io.ByteArrayInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.nio.charset.StandardCharsets;
import java.util.Arrays;
import java.util.InputMismatchException;

public class laptop {

	static class Solver {

		char[] buttons;
		// N: number of buttons
		// rm, bm, and gm are bitmasks representing which buttons are R, G, B
		// i.e.: BBGRGRBGRB
		// ----> 0001010010
		int N, rm, bm, gm;
		double R, memo[][];

		// Returns the distance between two points on the polygon indexed a and b
		double dist(int a, int b) {
			int dist = (b - a + N) % N;
			dist = Math.min(dist, N - dist);
			double ang = (2 * Math.PI * dist / N);
			// Law of cosines: The three legs of the triangle are the two radii from the
			// center to the points, and the third leg is the distance we're looking for.
			return Math.sqrt(2 * R * R * (1 - Math.cos(ang)));
		}

		// Dynamic programming solution: Our state is a bitmask representing which
		// buttons we have left to press, and at is our current location.
		double dp(int mask, int at) {
			// If we have no more buttons to press, we're done.
			if (mask == 0)
				return 0;
			// If we've already computed an answer for this state, return it.
			if (memo[at][mask] >= 0)
				return memo[at][mask];
			// Set a minimum value to improve upon when we try future states.
			double min = 1e69;
			// nm will represent what states we can visit next. If our mask still has any
			// red bits on, then (mask & rm) will be nonzero. Otherwise, we have no red bits
			// left to visit, so we repeat the process with the greens and blues.
			int nm = mask & rm;
			if (nm == 0)
				nm = mask & gm;
			if (nm == 0)
				nm = mask & bm;
			// Iterate over possible next locations
			for (int i = 0; i < N; i++)
				// If this bit is on in our new mask of destination locations, give it a try
				if ((nm & 1 << i) > 0)
					// The cost for going to this button next is equal to the distance from our
					// current button to the next one, plus the minimum cost for pressing the
					// remaining buttons. When we subtract (1 << i) from our mask, that is
					// equivalent to marking it visited in our state.

					// For example, if our mask of unvisited locations is 10110, and we visit the
					// third location, our new mask will be 10010.
					min = Math.min(min, dist(at, i) + dp(mask - (1 << i), i));
			// Save and return our optimal answer.
			return memo[at][mask] = min;
		}

		void solve(int testNumber, FastScanner s, PrintWriter out) {
			// Read input
			N = s.nextInt();
			R = s.nextDouble();
			buttons = s.next().toCharArray();
			rm = bm = gm = 0;
			// Set up our red, green, and blue masks. If the i'th character is red, we'll
			// set the i'th bit of rm to 1, and so forth.
			for (int i = 0; i < N; i++)
				if (buttons[i] == 'R')
					rm += 1 << i;
				else if (buttons[i] == 'G')
					gm += 1 << i;
				else
					bm += 1 << i;
			// Initialize and fill memo array with dummy values
			memo = new double[N][1 << N];
			for (double[] a : memo)
				Arrays.fill(a, -1);
			// Save our best answer
			double min = 1e69;
			// Go over all possible starting buttons, and keep track of our best answer.
			for (int i = 0; i < N; i++)
				min = Math.min(min, dp((1 << N) - 1, i));
			// All done!
			out.printf("Scenario #%d: %.3f%n", testNumber, min);
		}

	}

	public static void main(String[] args) {

		FastScanner s = new FastScanner(System.in);
		PrintWriter out = new PrintWriter(System.out);

		Solver solver = new Solver();
		int T = s.nextInt();
		for (int t = 1; t <= T; t++)
			solver.solve(t, s, out);

		out.close();

	}

	static int swap(int a, int b) {
		return a;
	}

	static Object swap(Object a, Object b) {
		return a;
	}

	static String ts(Object... o) {
		return Arrays.deepToString(o);
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
