import java.io.*;
import java.util.*;

public class coins{
	
	// in case a spelling error is made, writing the names like this makes it
	// easier to fix the code.
	static String[] players = new String[]{"Matthew", "Bill"};
	
	public static void main(String[] args) throws IOException{
		
		Scanner in = new Scanner(System.in);
		
		int T = in.nextInt();
		for(int t = 1; t <= T; t++){
			
			// input
			int N = in.nextInt(), K = in.nextInt();
			int playerOne = (in.next().compareTo(players[0]) == 0)? 0: 1;
			
			// the solution is much simpler than one would expect.
			
			// what you can do if you're playing the game is, always take an
			// amount of coins that leaves the stack with a multiple of (K+1)
			// coins, which you will always be able to do unless you are the
			// one who has to make a move during this kind of state.
			
			// that way, when there are (K+1) coins left, the other player will
			// be forced to take some amount of coins which leaves the stack
			// with some amount of coins between 1 and K. you will then be able
			// to take all the coins, including the coin on the bottom.
			
			StringBuilder sb = new StringBuilder();
			sb.append("Game #" + t + ": ");
			if(N % (K+1) == 0){
				// the player going first will lose
				sb.append(players[(playerOne + 1) % 2]);
			}
			else{
				// the player going first will win
				sb.append(players[playerOne]);
			}
			System.out.println(sb);
		}
	}
}