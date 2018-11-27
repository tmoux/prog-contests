import java.util.*;
import java.io.*;
// Author: Derek Goodwin

public class dinner{
	public static void main(String[] args) throws FileNotFoundException{
		// max string size
		int strsize = 101;
		
		boolean[] isPrime = new boolean[strsize];
		Arrays.fill(isPrime, true);
		isPrime[0] = isPrime[1] = false;
		for(int i = 2; i*i < strsize; i++){
			if(isPrime[i]){
				for(int ki = i+i; ki < strsize; ki += i){
					isPrime[ki] = false;
				}
			}
		}
		
		boolean[] isPerfectSquare = new boolean[strsize];
		for(int i = 0; i*i < strsize; i++){
			isPerfectSquare[i*i] = true;
		}
		
		// for console input/output
		Scanner in = new Scanner(System.in);
		PrintWriter out = new PrintWriter(System.out);
		
		// for file input/output
//		Scanner in = new Scanner(new File("dinner.in"));
//		PrintWriter out = new PrintWriter(new File("dinner.out2"));
		
		int P = Integer.parseInt(in.nextLine());
		
		for(int p = 1; p <= P; p++){
			
			int N = Integer.parseInt(in.nextLine());
			String[] strs = new String[N];
			for(int n = 0; n < N; n++) strs[n] = in.nextLine();
			
			// the following two variables say which strings are valid and how
			// strings are valid, respectively
			boolean[] isValid = new boolean[N];
			int numValid = 0;
			for(int n = 0; n < N; n++){
				// testing Tyler's standards
				boolean firstCondition = true;
				
				// the length of the string has to be prime...
				if(!isPrime[strs[n].length()]){
					firstCondition = false;
				}
				
				// ...AND the number of vowels plus half the number of 'y's
				// must equal an odd integer.
				// here, we count the number of vowels and 'y's
				int vowels = 0, y = 0;
				for(int i = 0; i < strs[n].length(); i++){
					switch(strs[n].charAt(i)){
					case 'a': case 'e': case 'i': case 'o': case 'u':
						vowels++;
						break;
					case 'y':
						y++;
						break;
					}
				}
				// testing the condition
				if(y % 2 == 1 || (vowels + y / 2) % 2 != 1){
					firstCondition = false;
				}
				
				// testing Michael's standards
				boolean secondCondition = true;
				
				// both the number of characters in the string and the number
				// of vowels plus the number of 'y's must be perfect squares
				if(!isPerfectSquare[strs[n].length()]
						|| !isPerfectSquare[vowels + y / 2]
						|| y % 2 == 1){
					secondCondition = false;
				}
				
				// is this restaurant an option then?
				if(firstCondition || secondCondition){
					numValid++;
					isValid[n] = true;
				}
			}
			
			out.print("Practice #"+p+": ");
			
			if(numValid == 0){
				out.println("It\'s hopeless!");
			}
			else{
				out.println(numValid+" valid options");
				for(int n = 0; n < N; n++){
					if(isValid[n]){
						out.println(strs[n]);
					}
				}
			}
			
			out.println();
		}
		out.close();
	}
}
