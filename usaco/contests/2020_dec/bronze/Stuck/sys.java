import java.io.*;
import java.util.*;

// Author: Matthew Zhang
/*
Comments: This problem is definitely the most challenging of the entire set. I will preface this by saying that I may have missed an easy trick or something, because my solution was a bit more complex than I was imagining. For my solution, I computed all the pairwise intersections (if they exist) between all points i and j that are given. We know an intersection exists only if the points i and j are moving in different directions and their intersection must be located to the top and to the right of both points so it is reachable. Afterwards, we can compute based on their distances (which is analogous to time in this case) which point reaches the intersection first, meaning that point will block the other. I sorted all these pairwise intersections by their distances in increasing order (to simulate which cows are blocked first) and looped through them to check which blockings are valid (there is a bit of a special case mentioned below). Finally, if a cow was not blocked during this loop, it must be eating for infinity. 

12/27/20 Update: After the release of the official USACO solutions, my solution matches their 2nd solution, without the sorting (students can simply loop to find the earliest intersectoin rather than sorting). Furthermore, I have now made an adjustment to store (a, b, a_dist, b_dist) in my list instead of (a, b, a_dist) because that makes it easier to check the case where b is stopped, but it still blocks a because it moved past the intersection already. 
*/

class Point 
{
	int x, y, d; 
	
	public Point(int a, int b, int c) 
	{
		x = a; // x-coordinate
		y = b; // y-coordinate
		d = c; // direction: 0 for E and 1 for N
	}
}

class Main {
  public static void main(String[] args) throws IOException {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int n = Integer.parseInt(br.readLine()); 
		
		int[] dist = new int[n];
		
		// all distances are at least 1 - the spot the cow is currently in 
		Arrays.fill(dist, 1); 
		
		// checks if cow i has stopped 
		boolean[] stopped = new boolean[n];

    // holds all the cows stored as Points
		Point[] points = new Point[n];
		
		// read in the points 
		for (int i = 0; i < n; i++) 
		{
			StringTokenizer st = new StringTokenizer(br.readLine());
			String dir = st.nextToken(); 
			int xcoord = Integer.parseInt(st.nextToken());
			int ycoord = Integer.parseInt(st.nextToken());
			
			if (dir.equals("E"))
			{
				points[i] = new Point(xcoord, ycoord, 0); 
			}
			
			else 
			{
				points[i] = new Point(xcoord, ycoord, 1); 
			}
		}
		
		// list that keeps track of the intersections between all pairs of points (i, j) 
		// elements of intersections will be of the form (a, b, a_dist, b_dist) 
		// a = index of point a, b = index of point b 
		// a_dist = distance/time for point a to reach the intersection of a and b
    // b_dist = distance/time for point b to reach the intersection of a and b
    // this notation means that point a should be blocked by point b where it takes a_dist for a to reach and b_dist for b to reach (b_dist < a_dist)
		ArrayList<ArrayList<Integer>> intersections = new ArrayList<ArrayList<Integer>>();
		
		// find all pairs of points (i, j) that may intersect
		for (int i = 0; i < n; i++) 
		{
			for (int j = i + 1; j < n; j++) 
			{
				
				Point a = points[i];
				Point b = points[j]; 
				
				// both are going E direction, no intersection 
				if (a.d == 0 && b.d == 0) 
				{
					continue; 
				}
				
				// both are going N direction, no intersection  
				if (a.d == 1 && b.d == 1) 
				{
					continue; 
				}
				
				int xi = 0;
				int yi = 0;
				
				// the intersection should be the x-coordinate of the point going N and the y-coordinate of the point going E 
				
				// a is going E, b is going N 
				if (a.d == 0 && b.d == 1) 
				{
					xi = b.x;
					yi = a.y; 
				}
				
				else
				{
					xi = a.x;
					yi = b.y; 
				}
				
				// calculate the distance/time it takes for a and b to get to that intersection 
				int a_dist = (xi - a.x) + (yi - a.y);
				int b_dist = (xi - b.x) + (yi - b.y);
				
				// no intersection if the point is unreachable / behind the cows
				if (a_dist < 0 || b_dist < 0) 
				{
					continue; 
				}
				
				// intersection where a will be stopped by b because b reaches the intersection first
				if (b_dist < a_dist) 
				{
					ArrayList<Integer> l = new ArrayList<Integer>();
					l.add(i);
					l.add(j);
					l.add(a_dist); 
          l.add(b_dist);
					intersections.add(l);
				}
				
				// intersection where b will be stopped by a because a reaches the intersection first
				else if (a_dist < b_dist) 
				{
					ArrayList<Integer> l = new ArrayList<Integer>();
					l.add(j);
					l.add(i);
					l.add(b_dist); 
          l.add(a_dist);
					intersections.add(l);
				}
			}
		}
		
		// sort the intersections by the distance/time in which they happen (we care about blockings so we sort by a_dist) 
    // this is not necessary to solve the problem 
		Collections.sort(intersections, (a, b)-> a.get(2) - b.get(2)); 
		
		for (ArrayList<Integer> l: intersections) 
		{
			int a = l.get(0);
			int b = l.get(1); 
			int a_dist = l.get(2); 
      int b_dist = l.get(3); 

			// try to stop point a with point b if a has not been stopped 
      // two cases: b is not blocked yet or b is blocked but has moved past the intersection point between a and b 
			if (!stopped[a] && (!stopped[b] || dist[b] > b_dist))
			{
					dist[a] = a_dist; 
					stopped[a] = true;
			}
		}
		
		// if something has not been stopped, it has infinity distance
		for (int i = 0; i < n; i++) 
		{
			if (stopped[i]) 
			{
				System.out.println(dist[i]);
			}
			
			else 
			{
				System.out.println("Infinity");
			}
		}
  }
}
