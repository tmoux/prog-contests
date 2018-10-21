import java.util.*;

public class subarray_bill {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int n = in.nextInt();
		int k = in.nextInt();
		int[] a = new int[n];
		int[] s = new int[n+1];
		for (int i = 0; i < n; ++i) s[i+1] = s[i] + (a[i] = in.nextInt());

		int minDiff = Integer.MAX_VALUE;
		int total = 0;
		for (int i = 0; i <= n - k - k; ++i) {
			int j = i + k;
			int sum1 = s[j+k]-s[j];
			int sum2 = s[i+k]-s[i];
			int diff = Math.abs(sum1 - sum2);
			if (diff < minDiff || diff == minDiff && sum1 + sum2 > total) {
				minDiff = diff;
				total = sum1 + sum2;
			}
		}

		System.out.println(total);
	}
}
