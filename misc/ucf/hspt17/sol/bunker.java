import java.util.*;

public class bunker {

  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);

    int numCases = in.nextInt();

    // Go through each test case.
    for(int tree = 1; tree <= numCases; ++tree) {
      int r = in.nextInt();
      int c = in.nextInt();

      // Read in the locations of the caterpillars.
      double[] angles = new double[c];
      for(int i = 0; i < c; ++i) {
        angles[i] = in.nextDouble();
      }

      // Loop through each possible location for the bunker and save the
      // minimum sum of angles for the caterpillars to travel. It is guaranteed
      // that the a possible best bunker placement will be at one of the
      // caterpillars homes.
      double best = 1E9;
      for(int bunker = 0; bunker < c; ++bunker) {

        // Loop through each caterpillar and add its distance to the current
        // selected bunker.
        double sum = 0;
        for(int caterpillar = 0; caterpillar < c; ++caterpillar) {
          // Caterpillers will walk around the tree whichever way is shorter.
          // Get the distance for clockwise and counter-clockwise, and add the
          // minimum of the two to our current sum.

          // Mod by 360 to keep the angles positive.
          double dist1 = (360 + angles[bunker] - angles[caterpillar]) %360;
          double dist2 = 360 - dist1;

          sum += Math.min(dist1, dist2);
        }
        // Save the best sum found.
        best = Math.min(best, sum);
      }

      // Calculate the distance around the tree all the caterpillars will walk.
      // Arc length = angle * r
      // Convert our angles sum to radians and multiply by the radius.
      double ans = best / 180 * Math.PI * r;

      System.out.printf("Tree #%d: %.3f\n", tree, ans);
    }
    in.close();
  }
}
