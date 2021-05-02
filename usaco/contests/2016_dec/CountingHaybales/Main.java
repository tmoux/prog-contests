import java.util.*;
import java.io.*;

class Main {
  static int[] loc;
  static int N, Q;
  public static void main(String[] args) throws IOException {
    BufferedReader br = new BufferedReader(new FileReader("haybales.in"));
    StringTokenizer st = new StringTokenizer(br.readLine());
    N = Integer.parseInt(st.nextToken());
    Q = Integer.parseInt(st.nextToken());
    loc = new int[N];
    st = new StringTokenizer(br.readLine());
    for (int i = 0; i < N; i++) {
      loc[i] = Integer.parseInt(st.nextToken());
    }
    Arrays.sort(loc);

    PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("haybales.out")));
    for (int i = 0; i < Q; i++) {
      st = new StringTokenizer(br.readLine());
      int A = Integer.parseInt(st.nextToken());
      int B = Integer.parseInt(st.nextToken());
      //Calculate the answer using prefix sums
      int ans = calc(B) - calc(A-1);
      out.println(ans);
    }
    out.close();
  }

  //Returns the number of haybales with position <= x
  static int calc(int x) {
    //Note how we initialize lo and hi.
    //The invariant here is that lo will always be the index
    //of a haybale with position <= x.
    //We initialize lo to be -1, since we don't know if the 
    //first haybale has position <= x.
    int lo = -1, hi = N;
    while (lo+1 < hi) {
      int mid = (lo+hi)/2;
      if (loc[mid] <= x) {
        lo = mid;
      }
      else {
        hi = mid;
      }
    }
    return lo+1;
  }
}

