import java.io.*;
import java.util.*;

class Cow {
  char dir; //'E' or 'N'
  int x;
  int y;
  int id; //original order
  Cow (char _dir, int _x, int _y, int _id) {
    dir = _dir;
    x = _x;
    y = _y;
    id = _id;
  }
}

class Pair {
  int x;
  int y;
  Pair (int _x, int _y) {
    x = _x;
    y = _y;
  }
}

class Event implements Comparable<Event> {
  int t;
  Pair p;
  int id; //of cow
  Event(int _t, Pair _p, int _id) {
    t = _t;
    p = _p;
    id = _id;
  }

  //Override the compareTo function, 
  //defining an ordering on events (sorted by time)
  //It's not necessary to completely understand this, but the 
  //Collections.sort function requires that the type of the list 
  //implement the Comparable interface,
  //which is done by implementing the compareTo function.
  @Override
  public int compareTo(Event r) {
    return t-r.t;
  }
}

class Stuck {
  public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    int n = Integer.parseInt(br.readLine());
    Cow[] cows = new Cow[n];
    //Read input into an array of cows
    for (int i = 0; i < n; i++) {
			StringTokenizer st = new StringTokenizer(br.readLine());
      char dir = st.nextToken().charAt(0);
      int x = Integer.parseInt(st.nextToken());
      int y = Integer.parseInt(st.nextToken());
      cows[i] = new Cow(dir,x,y,i);
    }
    //Since we can't simulate the process directly (the bounds are too large),
    //let's come up with a list of "events", or special moments in time, that we care about.
    //Each pair of cows may possibly arrive at the same square, at times t1 and t2.
    //If a cow arrives at a square that has already been eaten, we stop it and mark it as inactive.
    ArrayList<Event> events = new ArrayList<Event>();
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        //Two cows intersect iff one is E and the other is N, and they are positioned in a particular way
        if (cows[i].dir == 'E' && cows[j].dir == 'N'
         && cows[i].x < cows[j].x 
         && cows[i].y > cows[j].y) {
         //These cows will both go to the point (cows[j].x,cows[i].y) 
         int inter_x = cows[j].x;
         int inter_y = cows[i].y;
         int dx = inter_x-cows[i].x;
         int dy = inter_y-cows[j].y;
         if (dx == dy) continue; //If both reach at the same time, ignore it
         events.add(new Event(dx,new Pair(inter_x,inter_y),cows[i].id)); //event for East cow
         events.add(new Event(dy,new Pair(inter_x,inter_y),cows[j].id)); //event for North cow
       }
      }
    }
    //Now process the events. 
    //We sort the events list by time, so we are processing them in order
    Collections.sort(events);
    boolean[] alive = new boolean[n];
    Arrays.fill(alive,true);
    int[] ans = new int[n];
    //We maintain an arraylist, which are the squares that have already been eaten
    ArrayList<Pair> eaten = new ArrayList<Pair>();
    for (Event e: events) {
      if (!alive[e.id]) continue; //If the cow's already inactive, skip this event
      if (contains(eaten,e.p)) { //If the square has already been eaten, stop the cow now
        alive[e.id] = false;
        ans[e.id] = e.t;
      }
      else { 
        //Otherwise, this is the first cow to eat the square, so it gets to keep going
        //Add the square to the list of eaten squares and move on
        eaten.add(e.p);
      }
    }

    //output answer
    for (int i = 0; i < n; i++) {
      if (alive[i]) System.out.println("Infinity");
      else System.out.println(ans[i]);
    }
  }

  //helper function to determine whether a pair is present in the list
  //It's better to use a HashSet or dictionary for this,
  //but I wanted to limit the number of additional data structures that would be used
  static boolean contains(ArrayList<Pair> a, Pair p) {
    for (Pair i: a) {
      if (i.x == p.x && i.y == p.y) return true;
    }
    return false;
  }
}
