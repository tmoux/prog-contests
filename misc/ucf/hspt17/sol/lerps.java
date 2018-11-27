import java.util.ArrayList;
import java.util.Scanner;

public class lerps {
/*
Explanation:
We want to remove walls to combine rooms with an odd number of lerps to form rooms with an even number of lerps.
If there is one or more rooms with an even number of lerps in between two odd rooms we are trying to combine, we can just
remove all of the walls between them to make one room with an even number of lerps, so we are really only concerned with the odd rooms.
Start with a list of the odd rooms and greedily remove the adjacent pair of rooms with the highest sum until there is only one room left.
The number of lerps in that room will be the number of unhappy lerps, so our answer will be the sum minus that number.
 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner scan=new Scanner(System.in);
		
		//scan in number of test cases
		int e=scan.nextInt();
		
		//loop through the cases
		for(int i=0;i<e;i++){
			
			//scan in number of rooms
			int n=scan.nextInt();
			
			//rooms will store the number of lerps in each room (that are odd)
			ArrayList<Integer> rooms =new ArrayList<Integer>();
			
			int sum=0;
			
			//scan in the number of lerps in each room
			for(int j=0;j<n;j++){
				int q=scan.nextInt();
				sum+=q;
				if(q%2==1){
					rooms.add(q);
				}
			}
			
			//if the sum is even, all lerps can be made happy by removing all the walls
			if(sum%2==0){
				System.out.println("Environment #"+(i+1)+": "+sum+" lerps");
				continue;
			}
			
			
			while(rooms.size()>1){
				int maxSum=0;
				int maxi=0;
				
				//find the maximum sum of two adjacent rooms
				for(int j=0;j<rooms.size()-1;j++){
					if(rooms.get(j)+rooms.get(j+1)>maxSum){
						maxSum=rooms.get(j)+rooms.get(j+1);
						maxi=j;
					}
				}
				
				//remove the rooms 
				rooms.remove(maxi);
				rooms.remove(maxi);
			}
			
			System.out.println("Environment #"+(i+1)+": "+(sum-rooms.get(0))+" lerps");
		}
	}

}
