import java.io.OutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.util.Arrays;
import java.io.BufferedWriter;
import java.io.Writer;
import java.io.OutputStreamWriter;
import java.util.InputMismatchException;
import java.io.IOException;
import java.io.InputStream;

/**
 * Built using CHelper plug-in
 * Actual solution is at the top
 *
 * @author lewin
 */
public class another_coin_weighing_puzzle_lewin_mk {
    public static void main(String[] args) {
        InputStream inputStream = System.in;
        OutputStream outputStream = System.out;
        InputReader in = new InputReader(inputStream);
        OutputWriter out = new OutputWriter(outputStream);
        AnotherCoinWeighingPuzzle solver = new AnotherCoinWeighingPuzzle();
        solver.solve(1, in, out);
        out.close();
    }

    static class AnotherCoinWeighingPuzzle {
        int mod = 998244353;

        public void solve(int testNumber, InputReader in, OutputWriter out) {
            int m = in.nextInt(), k = in.nextInt();
            BinomialCoefficients bc = new BinomialCoefficients(m + 1, mod);
            int[] g = Utils.getMu(k + 1);
            long ans = 1;
            long[] w = new long[k + 1];
            Arrays.fill(w, 1);
            long a = 1;
            for (int r = 1; r <= m; r++) {
                long d = 0;
                for (int i = 1; i <= k; i++) {
                    w[i] = w[i] * (k / i) % mod;
                    d = (d + w[i] * g[i]) % mod;
                }
                a = a * 2 % mod;
                d = d * a % mod;
                d = d * bc.comb(m, m - r) % mod;
                ans += d;
            }
            ans %= mod;
            if (ans < 0) ans += mod;
            out.println(ans);
        }

    }

    static class OutputWriter {
        private final PrintWriter writer;

        public OutputWriter(OutputStream outputStream) {
            writer = new PrintWriter(new BufferedWriter(new OutputStreamWriter(outputStream)));
        }

        public OutputWriter(Writer writer) {
            this.writer = new PrintWriter(writer);
        }

        public void close() {
            writer.close();
        }

        public void println(long i) {
            writer.println(i);
        }

    }

    static class Utils {
        public static int[] getMu(int max) {
            int sqrt = (int) Math.sqrt(max);
            int[] mu = new int[max + 1];
            for (int i = 1; i <= max; i++)
                mu[i] = 1;
            for (int i = 2; i <= sqrt; i++) {
                if (mu[i] == 1) {
                    for (int j = i; j <= max; j += i)
                        mu[j] *= -i;
                    for (int j = i * i; j <= max; j += i * i)
                        mu[j] = 0;
                }
            }
            for (int i = 2; i <= max; i++) {
                if (mu[i] == i)
                    mu[i] = 1;
                else if (mu[i] == -i)
                    mu[i] = -1;
                else if (mu[i] < 0)
                    mu[i] = 1;
                else if (mu[i] > 0)
                    mu[i] = -1;
            }
            return mu;
        }

    }

    static class BinomialCoefficients {
        public long[] fact;
        public long[] ifact;
        public int mod;

        public BinomialCoefficients(int n, int mod) {
            this.mod = mod;
            long[][] x = Factorials.getFIF(n + 1010, mod);
            fact = x[0];
            ifact = x[1];
        }

        public long comb(int n, int k) {
            if (k < 0 || k > n) return 0;
            return fact[n] * ifact[n - k] % mod * ifact[k] % mod;
        }

    }

    static class Factorials {
        public static long[][] getFIF(int max, int mod) {
            long[] fact = new long[max];
            long[] ifact = new long[max];
            long[] inv = new long[max];
            inv[1] = 1;
            for (int i = 2; i < max; i++) {
                inv[i] = (mod - mod / i) * inv[mod % i] % mod;
            }
            fact[0] = 1;
            ifact[0] = 1;
            for (int i = 1; i < max; i++) {
                fact[i] = fact[i - 1] * i % mod;
                ifact[i] = ifact[i - 1] * inv[i] % mod;
            }
            return new long[][]{fact, ifact, inv};
        }

    }

    static class InputReader {
        private InputStream stream;
        private byte[] buf = new byte[1 << 16];
        private int curChar;
        private int numChars;

        public InputReader(InputStream stream) {
            this.stream = stream;
        }

        public int read() {
            if (this.numChars == -1) {
                throw new InputMismatchException();
            } else {
                if (this.curChar >= this.numChars) {
                    this.curChar = 0;

                    try {
                        this.numChars = this.stream.read(this.buf);
                    } catch (IOException var2) {
                        throw new InputMismatchException();
                    }

                    if (this.numChars <= 0) {
                        return -1;
                    }
                }

                return this.buf[this.curChar++];
            }
        }

        public int nextInt() {
            int c;
            for (c = this.read(); isSpaceChar(c); c = this.read()) {
                ;
            }

            byte sgn = 1;
            if (c == 45) {
                sgn = -1;
                c = this.read();
            }

            int res = 0;

            while (c >= 48 && c <= 57) {
                res *= 10;
                res += c - 48;
                c = this.read();
                if (isSpaceChar(c)) {
                    return res * sgn;
                }
            }

            throw new InputMismatchException();
        }

        public static boolean isSpaceChar(int c) {
            return c == 32 || c == 10 || c == 13 || c == 9 || c == -1;
        }

    }
}

