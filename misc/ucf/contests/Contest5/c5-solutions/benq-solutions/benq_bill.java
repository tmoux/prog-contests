import java.util.*;

public class benq_bill {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int n = in.nextInt();
		int[] c = new int[n], d = new int[n];
		for (int i = 0; i < n; ++i) c[i] = in.nextInt();
		for (int i = 0; i < n; ++i) d[i] = in.nextInt();

		long min = c[0];
		long cost = 0;
		for (int i = 0; i < n; ++i) {
			min = Math.min(min, c[i]);
			cost += d[i] * min;
		}

		System.out.println(cost);
	}
}
