// Arup Guha
// 7/17/2018
// Solution to 2018 SI@UCF Contest #5 Problem: Farmer John's Problems

import java.util.*;

public class problems {

	public static void main(String[] args) {
		
		Scanner stdin = new Scanner(System.in);
		int n = stdin.nextInt();
		
		// Store # of problems and a map from author->#probs here.
		int numP = 0;
		HashMap<String,Integer> probMap = new HashMap<String,Integer>();
		
		// Loop through each operation.
		for (int i=0; i<n; i++) {
			
			// Get next operation.
			int op = stdin.nextInt();
			String name = stdin.next();
			
			// Add a problem.
			if (op == 1) {
				
				// Just put this person in the map with no problems.
				if (!probMap.containsKey(name)) probMap.put(name, 0);
				
				// Now, add 1 to this person's count, and the global count.
				probMap.put(name, probMap.get(name)+1);
				numP++;
			}
			
			// Query...
			else {
				
				// Get the number of problems by this person.
				int num = !probMap.containsKey(name) ? 0 : probMap.get(name);
				
				// Get the common factor of our fraction, and the output...
				int div = gcd(num, numP);
				System.out.println((num/div)+"/"+(numP/div) );
			}
		}
	}
	
	public static int gcd(int a, int b) {
		return b == 0 ? a : gcd(b, a%b);
	}
}
