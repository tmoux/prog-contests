#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

const char vowels[] = {'a','e','i','o','u','y'};
bool isVowel(char c)
{
	for (int i = 0; i < 6; i++)
	{
		if (c == vowels[i]) return true;
	}
	return false;
}

int main()
{
	int a;
	string s; cin >> a >> s;
	for (int i = 0; i < s.size() -1; )
	{
		if (isVowel(s[i]) && isVowel(s[i+1]))
		{
			s.erase(i+1,1);
		}
		else {
			i++;
		}
	}
	cout << s << '\n';
	
	return 0;
}
