// Arup Guha
// 7/18/2018
// Alternate Solution to 2018 SI@UCF Final Contest Problem: Ballerina Rage

import java.util.*;

public class rage_arup {

	public static int nEqns;
	public static int nVars;
	public static double[][] myCoeff;
	
	public static void main(String[] args) {
		
		Scanner stdin = new Scanner(System.in);
		
		// Get basic parameters.
		nEqns = stdin.nextInt();
		nVars = stdin.nextInt();
		int numCases = stdin.nextInt();
		
		myCoeff = new double[nEqns][nVars];
		
		// Read in the coefficients of our equation.
		for (int j=0; j<nVars; j++) 
			for (int i=0; i<nEqns; i++)
				myCoeff[i][j] = stdin.nextInt();
		
		// Try all of our cases.
		for (int loop=0; loop<numCases; loop++) {
			
			// Copy new answer column.
			double[][] myeqns = new double[nEqns][nVars+1];
			for (int i=0; i<nEqns; i++)
				myeqns[i][nVars] = stdin.nextInt();
			
			// Just wanted to be sure these copied over...
			for (int i=0; i<nEqns; i++)
				for (int j=0; j<nVars; j++)
					myeqns[i][j] = myCoeff[i][j];
			
			// Set up the equations.
			syseqn mine = new syseqn(myeqns);
			
			// Output according to whether or not the system has a solution.
			if (mine.hasSoln())
				System.out.println("YES");
			else
				System.out.println("NO");
		}
		
	}
}

class syseqn {
	
	// n = # of equations.
	private int n;
	
	// nV = # of variables.
	private int nV;
	private double[][] eqnsOrig;
	private double[][] eqns;
	
	public syseqn(double[][] myeqns) {
		n = myeqns.length;
		nV = myeqns[0].length-1;
		eqns = myeqns;
	}
	
	private int getNextVar(int i, int curVar) {
		
		// Search for the next variable to eliminate.
		for (int j=curVar; j<nV; j++) 
			for (int k=i; k<n; k++)
				if (Math.abs(eqns[k][j]) > 1e-9)
					return j;
		
		// If we get here, all coefficients in equations i to n-1 were 0.
		return nV;
	}
	
	// Returns the row >= varI such that coeff to varI is maximal.
	private int getMaxRow(int row, int var) {
		
		int res = row;
		for (int i=row+1; i<n; i++)
			if (Math.abs(eqns[i][var]) > Math.abs(eqns[res][var]))
				res = i;
		
		return res;
	}
	
	// Swaps rows i and j.
	private void swapRows(int i, int j) {
		double[] tmp = eqns[i];
		eqns[i] = eqns[j];
		eqns[j] = tmp;
	}
	
	// Reduces equation j by equation i, assumes that all coeff of vars < i
	// are 0 and that i < j.
	private void reduce(int i, int j, int curVar) {
		double factor = eqns[j][curVar]/eqns[i][curVar];
		for (int k=curVar; k<=nV; k++)
			eqns[j][k] -= (factor*eqns[i][k]);
	}
	
	// This returns true iff the system has a solution. We can just attempt
	// to get the equations into upper triangular form and check 0 0 0 eqns
	// that are leftover.
	public boolean hasSoln() {
		
		// Go down the main diagonal.
		int curVar = 0;
		for (int i=0; i<n-1; i++) {
			
			// Find the next variable that has a non-zero coefficient.
			curVar = getNextVar(i, curVar);
			
			// Rest of the equations are all 0s.
			if (curVar == nV) break;
			
			// Do our usual get the best row...
			int best = getMaxRow(i, curVar);
			swapRows(i, best);
			
			// Reduce remaining equations based on equation i, to eliminate variable curVar in these equations.
			for (int j=i+1; j<n; j++) 
				reduce(i, j, curVar);
			
			// We eliminated curVar, go to next.
			curVar++;
		}
		
		// Look to find any equations with all 0s.
		// If any have a non-zero constant on the RHS, there is no solution.
		for (int i=0; i<n; i++) {
			
			// See if this row has all zeroes for coefficients.
			boolean allZeroCoeff = true;
			for (int j=0; j<nV; j++) {
				if (Math.abs(eqns[i][j]) > 1e-9) {
					allZeroCoeff = false;
					break;
				}
			}
			
			// This is bad, this means no solution.
			if (allZeroCoeff && Math.abs(eqns[i][nV]) > 1e-6) return false;
		}
		
		// If we get here, we are good.
		return true;
		
	}
		
}