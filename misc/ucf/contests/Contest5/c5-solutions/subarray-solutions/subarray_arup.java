// Arup Guha
// 7/19/2018
// Alternate Solution to 2018 SI@UCF Final Contest Problem: FJ and Subarray

import java.util.*;

public class subarray_arup {
	
	public static void main(String[] args) {
		
		Scanner stdin = new Scanner(System.in);
		int n = stdin.nextInt();
		int k = stdin.nextInt();
		
		// Read in data as cumulative frequency.
		int[] cumfreq = new int[n+1];
		for (int i=1; i<=n; i++)
			cumfreq[i] = cumfreq[i-1] + stdin.nextInt();
		
		int res = sum(0, 2*k-1, cumfreq);
		int minDiff = Math.abs(sum(0,k-1,cumfreq) - sum(k, 2*k-1,cumfreq));
		
		// Try each other starting point(i).
		for (int i=1; i+2*k<=n; i++) {
			
			// Calculate current difference and sum.
			int curDiff = Math.abs(sum(i,i+k-1,cumfreq) - sum(i+k, i+2*k-1, cumfreq));
			int curSum = sum(i,i+2*k-1,cumfreq);
			
			// Update based on the rules.
			if (curDiff < minDiff || (curDiff == minDiff && curSum > res)) {
				res = curSum;
				minDiff = curDiff;
			}
		}
		
		// Ta da!
		System.out.println(res);
	}
	
	// Returns some of array[i..j] where cumfreq is the cumulative frequency of that array (off by 1 index)
	public static int sum(int i, int j, int[] cumfreq) {
		return cumfreq[j+1] - cumfreq[i];
	}
}