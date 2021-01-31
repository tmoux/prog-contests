import java.io.*;
import java.util.*;

public class UdderedButNotHerd {
    public static void main(String[] args) throws IOException  {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String alphabet = br.readLine();
        String word = br.readLine();
        int idx = 0;
        int ans = 0;
        while (idx < word.length()) {
            ans++;
            for (int i = 0; i < alphabet.length(); i++) {
                if (idx < word.length() && alphabet.charAt(i) == word.charAt(idx)) {
                    idx++;
                }
            }
        }
        System.out.println(ans);
    }
}
