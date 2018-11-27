import java.util.Scanner;

public class multiply {

	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		
		int runs = scan.nextInt();
		for (int i = 0; i < runs; i++) {
			// Scan in n and m, multiply them together, and print the answer.
			int m = scan.nextInt();
			int n = scan.nextInt();
			int ans = m * n;
			System.out.println(ans);
		}
	}
	
}
