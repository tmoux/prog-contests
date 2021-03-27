/*
ID: timothy26
LANG: JAVA
TASK: milk3
*/

import java.io.*;
import java.util.*;

class milk3 {
  static int[] cap = new int[3];
  public static void main (String [] args) throws IOException {
    BufferedReader f = new BufferedReader(new FileReader("milk3.in"));
    StringTokenizer st = new StringTokenizer(f.readLine());
    for (int i = 0; i < 3; i++) {
      cap[i] = Integer.parseInt(st.nextToken());
    }

    ArrayList<Integer> answer = new ArrayList<>();
    //visited array will keep track of which states have been visited already
    boolean[][][] visited = new boolean[21][21][21];
    Stack<State> stack = new Stack<>();
    //Initialize the stack
    stack.push(new State(0,0,cap[2]));
    while (!stack.empty()) {
      State s = stack.pop();
      if (!visited[s.amt[0]][s.amt[1]][s.amt[2]]) {
        visited[s.amt[0]][s.amt[1]][s.amt[2]] = true;

        if (s.amt[0] == 0) {
          answer.add(s.amt[2]);
        }

        //Try all the ways to pour from one bucket to another
        //Notice we are adding some states we have already visited before (for instance, when from=to). Why is this still ok?
        for (int from = 0; from <= 2; from++) {
          for (int to = 0; to <= 2; to++) {
            State next = s.pour(from,to);
            stack.push(next);
          }
        }
      }
    }

    //Sort and output the answer
    Collections.sort(answer);
    
    PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("milk3.out")));
    for (int i = 0; i < answer.size(); i++) {
      out.print(answer.get(i));
      if (i < answer.size()-1) out.print(" ");
      else out.print("\n");
    }
    out.close();
  }

  //The State class represents a state of the three buckets.
  static class State {
    int[] amt;
    State(int a, int b, int c) {
      this.amt = new int[] {a,b,c};
    }
    //The pour method returns a new state which is the result of 
    //pouring from the "from" bucket into the "to" bucket
    State pour(int from, int to) {
      int amount = Math.min(amt[from],cap[to]-amt[to]);
      State ret = new State(amt[0],amt[1],amt[2]);
      ret.amt[from] -= amount;
      ret.amt[to] += amount;
      return ret;
    }
  }
}
