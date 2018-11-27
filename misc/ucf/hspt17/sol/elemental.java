import java.util.HashSet;
import java.util.Scanner;

public class elemental {

	static HashSet<String> elements;
	static String phrase;

	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		
		int count = 0;
		while (true) {
			count++;
			
			int numElements = scan.nextInt();
			if (numElements == 0) break;
			
			// Add the elements to our HashSet.
			elements = new HashSet<>();
			for (int i = 0; i < numElements; i++) elements.add(scan.next());
			
			scan.nextLine();
			phrase = scan.nextLine();
			if (check(0)) {
				System.out.println("Phrase #" + count + ": Elemental");
			} else {
				System.out.println("Phrase #" + count + ": Not Elemental");
			}
			System.out.println();
		}
	}

	static boolean check(int position) {
		// If we've reached the end of the word, we successfully made the word with the elements.
		if (position == phrase.length()) return true;
		// If we're at a space, skip it.
		if (phrase.charAt(position) == ' ') return check(position+1);
		
		for (int i = 1; i <= 3; i++) {
			if (position + i > phrase.length()) return false;
			String sub = phrase.substring(position, position+i);
			if (elements.contains(sub)) {
				if (check(position+i)) return true;			
			}
		}
		
		return false;
	}
}
