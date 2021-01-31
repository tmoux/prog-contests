import java.io.*;
import java.util.*;

public class EvenMoreOddPhotos {
    public static void main(String[] args) throws IOException  {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int N = Integer.parseInt(br.readLine());
        StringTokenizer st = new StringTokenizer(br.readLine());
        int even = 0, odd = 0;
        for (int i = 0; i < N; i++) {
            int x = Integer.parseInt(st.nextToken());
            if (x % 2 == 0) even++;
            else odd++;
        }
        while (even < odd) {
            even++;
            odd -= 2;
        }
        int ans = odd + Math.min(odd+1,even);
        System.out.println(ans);
    }
}
