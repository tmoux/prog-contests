int nxt[maxn]; //next array
/*Core KMP @param nxt: the resulting "next" array*/
void build_nxt(char * str,int * nxt, int length){
	int k = 0;
	nxt[0] = 0;
	for (int i = 1;i < length;i++){
		while (k > 0 && str[k] != str[i]){
			k = nxt[k - 1];
		}
		if (str[k] == str[i]){
			k++;
		}
		nxt[i] = k;
	}
}
/*Matching the string with the pattern
@return number of occurences of pattern string in the original string
*/
int match(char * str, char * pattern, int length_str, int length_pattern){
	int total = 0;
	int p = 0;
	for (int i = 0;i < length_str;i++){
		while (p > 0 && pattern[p] != str[i]){
			p = nxt[p - 1];
		}
		if (pattern[p] == str[i]){
			p++;
		}
		if (p == length_pattern){
			total++;
			p = nxt[p - 1];
		}
	}
	return total;
}
//build nxt for pattern
build_nxt(pattern, nxt, len_pattern);
