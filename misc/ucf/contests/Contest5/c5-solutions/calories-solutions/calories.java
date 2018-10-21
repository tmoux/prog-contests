// Arup Guha
// 7/17/2018
// Solution to 2018 SI@UCF Contest #5 Problem: Cookie Calories

import java.util.Scanner;

public class calories {

	public static void main(String[] args) {
		
		// Get # of ingredients.
		Scanner stdin = new Scanner(System.in);
		int n = stdin.nextInt();
		
		// Store results here.
		int min = 0, max = 0;
		
		// Loop through each ingredient.
		for (int i=0; i<n; i++) {
			
			// Get # of choices, set min/max to first.
			int numChoices = stdin.nextInt();
			int itemMin = stdin.nextInt();
			int itemMax = itemMin;
			
			// Go through rest of the choices, updating min and max as necessary.
			for (int j=0; j<numChoices-1; j++) {
				int choice = stdin.nextInt();
				itemMin = Math.min(itemMin, choice);
				itemMax = Math.max(itemMax, choice);
			}
			
			// Update total min and max accordingly.
			min += itemMin;
			max += itemMax;
		}
		
		// Ta da!
		System.out.println(min+" "+max);
	}
}
