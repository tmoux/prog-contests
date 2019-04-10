import java.io.EOFException;
import java.io.IOException;

public class xylophone_lib {
  private static final int QUERY_LIMIT = 10000;

  private static int N;
  private static int[] A;
  private static boolean[] answered;
  private static int queryCount, answerCount;

  public static int query(int s, int t) {
    if (queryCount >= QUERY_LIMIT) {
      WA();
    }
	++queryCount;
    if (!(1 <= s && s <= t && t <= N)) {
      WA();
    }
    int min = N + 1, max = 0;
    for (int i = s; i <= t; ++i) {
      if (min > A[i]) {
        min = A[i];
      }
      if (max < A[i]) {
        max = A[i];
      }
    }
    return max - min;
  }

  public static void answer(int i, int a) {
    if (!(1 <= i && i <= N)) {
      WA();
    }
    if (!(1 <= a && a <= N)) {
      WA();
    }
    if (answered[i]) {
      WA();
    }
    answered[i] = true;
    ++answerCount;
    if (a != A[i]) {
      WA();
    }
  }

  private static boolean isInitialized = false;

  public static void run() throws IOException {
    if (isInitialized) {
      System.out.println("Error: run() must not be called twice.");
      System.exit(1);
    }
    isInitialized = true;
    N = readInt();
    A = new int[N + 1];
    for (int i = 1; i <= N; ++i) {
      A[i] = readInt();
    }
    answered = new boolean[N + 1];
    for (int i = 1; i <= N; ++i) {
      answered[i] = false;
    }
    queryCount = 0;
    answerCount = 0;
    new xylophone().solve(N);
    if (answerCount != N) {
      WA();
    }
    System.out.println("Accepted : " + queryCount);
  }

  private static void WA() {
    System.out.println("Wrong Answer");
    System.exit(0);
  }

  private static int readInt() throws IOException {
    int x = 0, c;
    for (; ; ) {
      c = System.in.read();
      if ('0' <= c && c <= '9') break;
      if (c == -1) throw new EOFException();
      if (c == '-') return -readInt();
    }
    for (; ; ) {
      x = x * 10 + (c - '0');
      c = System.in.read();
      if (!('0' <= c && c <= '9')) return x;
    }
  }
}
