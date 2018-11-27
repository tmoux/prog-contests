import java.util.Scanner;

public class optimal {

	static int originalVal;
	
	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);

		// Generate the prime sieve.
		generateSieve(10_000_000);

		int runs = scan.nextInt();
		for (int i = 0; i < runs; i++) {
			originalVal = scan.nextInt();
			if (isComposite[originalVal]) {
				// The original value is not prime.
				System.out.println("Battle #" + (i+1) + ": Oh no, the autobots are doomed!");
			} else {
				data = Integer.toString(originalVal).toCharArray();
				perms = new char[data.length];
				used = new boolean[data.length];
				if (!perms(0, data.length)) {
					// None of the permutations of the original value are prime.
					System.out.println("Battle #" + (i+1) + ": Oh no, the autobots are doomed!");
				} else {
					System.out.println("Battle #" + (i+1) + ": Autobots, roll out!");
				}
			}
		}
	}

	static char[] data, perms;
	static boolean[] used;
	static boolean perms(int position, int len) {
		if (position >= len) {
			// Check if the permutation is a prime.
			String currPerm = String.valueOf(perms);
			int val = Integer.parseInt(currPerm);
			// The permutation had one or more leading zeroes, which is not allowed.
			if (String.valueOf(val).length() != currPerm.length()) return false;
			/*
			 * Return whether the permutation is not the same as the original 
			 * value and it's prime.
			 */
			return (val != originalVal && !isComposite[val]);
		} else {
			for (int j = 0; j < data.length; j++) {
				if (!used[j]) {
					used[j] = true;
					perms[position] = data[j];
					// Check if any of the permutations are prime.
					if (perms(position+1, len)) return true;
					used[j] = false;
				}
			}
		}
		return false;
	}

	// Generates the Sieve of Eratosthenes.
	static boolean[] isComposite;
	static void generateSieve(int upperBound) {
		isComposite = new boolean[upperBound+1];
		
		// 0 and 1 are not prime.
		isComposite[0] = isComposite[1] = true;
		
		// We only have to go to the square root of the upper bound.
		int boundary = (int)Math.sqrt(upperBound) + 1;
		for (int i = 2; i <= boundary; i++) {
			// If i is prime, mark its multiples as composite.
			if (!isComposite[i]) {
				for (int j = i*i; j <= upperBound; j += i) {
					isComposite[j] = true;
				}
			}
		}
	}

}
