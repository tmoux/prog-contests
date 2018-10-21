#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp>
#include <functional> // for less
using namespace std;
using namespace __gnu_pbds;
typedef long long ll;
typedef tree<int, null_type, less<int>, rb_tree_tag,
             tree_order_statistics_node_update>
    new_data_set;


int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    new_data_set p;
    p.insert(5);
    p.insert(2);
    cout << *p.find_by_order(0) << '\n';


    return 0;
}
	

