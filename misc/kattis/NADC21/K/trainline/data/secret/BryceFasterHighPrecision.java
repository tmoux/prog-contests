// O(n log (1/EPS) log (range)) time solution to trainline.
// Uses a fill-forward strategy to avoid having to deal with walking pointers.

import java.io.*;
import java.util.*;

public class BryceFasterHighPrecision {
    public static int M = 120;   // max effective distance

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        int k = in.nextInt();
        k = Math.min(k, n);

        int[] p = new int[n];
        double[] d = new double[n];
        for (int i = 0; i < n; ++i) {
            p[i] = in.nextInt();
            d[i] = in.nextInt();
        }

        double hi = 300;    // station utility cannot exceed 300
        double lo = 0;
        while(true) {
            double l = (hi+lo)/2;
        //    System.out.println(lo + " " + l + " " + hi);

            double[] dp_over = new double[n]; // dp_over[i] := max utility in prefix [0 to i]
            int[] over_cnt = new int[n];    // count of stations in dp_over[i]
            for (int i = 0; i < n; ++i) {
                double station_i = -l + p[i];   // max utility in [0, i] placing a station at i
                int cnt_i = 1;          // number of stations placed in max utility solution in [0, i] with station at i
                double cur = -l + p[i];
                for (int j = i-1; j >= Math.max(0, i-M-1); --j) {   // last station covers from 1 to M populations
                    if (cur + dp_over[j] > station_i) {
                        station_i = cur + dp_over[j];
                        cnt_i = over_cnt[j] + 1;
                    }
                    cur += p[j] * Math.pow(2, -(d[i]-d[j]));
                }
                if (cur > station_i) {  // place first station
                    station_i = cur;
                    cnt_i = 1;
                }

                // forward fill dp_over
                if (i > 0) {
                    if (dp_over[i-1] > dp_over[i]) {    // either the last population is not covered
                        dp_over[i] = dp_over[i-1];
                        over_cnt[i] = over_cnt[i-1];
                    }
                }
                cur = station_i;
                for (int j = i; j <= Math.min(i+M,n-1); ++j) {
                    if (j > i) {
                        cur += p[j] * Math.pow(2, -(d[j]-d[i]));
                    }
                    if (cur > dp_over[j]) {     // or it is covered by a station within distance M
                        dp_over[j] = cur;       // dp_over[j] will have the proper value by the time i > j
                        over_cnt[j] = cnt_i;
                    }
                }
            }

        //    System.out.println(over_cnt[n-1]);
        //    System.out.println(dp_over[n-1] + " " + (dp_over[n-1] + k*l));
            if (hi-lo < 1e-10 || over_cnt[n-1] == k) {
                System.out.printf("%.12f\n", dp_over[n-1] + k*l);
                break;
            }

            if (over_cnt[n-1] > k) {
                lo = l;
            } else {
                hi = l;
            }
        }
    }
}
