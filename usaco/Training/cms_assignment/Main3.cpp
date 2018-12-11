//Vinay Tummarakota, CMS Random Stuff
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main()
{
	cout << "Please wait for program to complete..." << endl;
	ifstream file;
	file.open("english.txt");
	if (file.fail())
	{
		cerr << "Error Opening File" << endl;
		exit(2);
	}
	/*I used the video: https://www.youtube.com/watch?v=Iho2EdJgusQ&t=186s" to help me learn how to insert a file into a program
	  In the above code, I inserted the dictionary text file into the program */
	string word;
	int wordCount = 0;
	//Initializing wordCount variable
	while (getline(file,word)) 
	//for (int qwer = 0; qwer<1000;qwer++)

	//the loop always occurs when there is word on the next line in the file that the program can read; once all words run out, the loop stops
	{
		//getline(file,word);
		string wordCopy = word;
		int position = word.find("a"); //finds the first occurrence of letter a, and returns its index into variable position
		int a = 0; //initialize variable a to 0, if no a's are found
		while (position >= 0) //if a is present, index is positive causing loop to activate; if a is not present, index = -1
		{
			a++; //a is increased by 1 because the program found an occurrence of a
			word.erase(position, 1); //the program deletes the index where the first a is
			position = word.find("a"); //the program then tries to find another a to account for words that use more than one a
		}
		//the above code is then repeated for every letter to find the amount of times a letter occurs in a word
		position = word.find("b"); 
		int b = 0;
		while (position >= 0)
		{
			b++;
			word.erase(position, 1);
			position = word.find("b");
		}
		position = word.find("c");
		int c = 0;
		while (position >= 0)
		{
			c++;
			word.erase(position, 1);
			position = word.find("c");
		}
		position = word.find("d");
		int d = 0;
		while (position >= 0)
		{
			d++;
			word.erase(position, 1);
			position = word.find("d");
		}
		position = word.find("e");
		int e = 0;
		while (position >= 0)
		{
			e++;
			word.erase(position, 1);
			position = word.find("e");
		}
		position = word.find("f");
		int f = 0;
		while (position >= 0)
		{
			f++;
			word.erase(position, 1);
			position = word.find("f");
		}
		position = word.find("g");
		int g = 0;
		while (position >= 0)
		{
			g++;
			word.erase(position, 1);
			position = word.find("g");
		}
		position = word.find("h");
		int h = 0;
		while (position >= 0)
		{
			h++;
			word.erase(position, 1);
			position = word.find("h");
		}
		position = word.find("i");
		int i = 0;
		while (position >= 0)
		{
			i++;
			word.erase(position, 1);
			position = word.find("i");
		}
		position = word.find("j");
		int j = 0;
		while (position >= 0)
		{
			j++;
			word.erase(position, 1);
			position = word.find("j");
		}
		position = word.find("k");
		int k = 0;
		while (position >= 0)
		{
			k++;
			word.erase(position, 1);
			position = word.find("k");
		}
		position = word.find("l");
		int l = 0;
		while (position >= 0)
		{
			l++;
			word.erase(position, 1);
			position = word.find("l");
		}
		position = word.find("m");
		int m = 0;
		while (position >= 0)
		{
			m++;
			word.erase(position, 1);
			position = word.find("m");
		}
		position = word.find("n");
		int n = 0;
		while (position >= 0)
		{
			n++;
			word.erase(position, 1);
			position = word.find("n");
		}
		position = word.find("o");
		int o = 0;
		while (position >= 0)
		{
			o++;
			word.erase(position, 1);
			position = word.find("o");
		}
		position = word.find("p");
		int p = 0;
		while (position >= 0)
		{
			p++;
			word.erase(position, 1);
			position = word.find("p");
		}
		position = word.find("q");
		int q = 0;
		while (position >= 0)
		{
			q++;
			word.erase(position, 1);
			position = word.find("q");
		}
		position = word.find("r");
		int r = 0;
		while (position >= 0)
		{
			r++;
			word.erase(position, 1);
			position = word.find("r");
		}
		position = word.find("s");
		int s = 0;
		while (position >= 0)
		{
			s++;
			word.erase(position, 1);
			position = word.find("s");
		}
		position = word.find("t");
		int t = 0;
		while (position >= 0)
		{
			t++;
			word.erase(position, 1);
			position = word.find("t");
		}
		position = word.find("u");
		int u = 0;
		while (position >= 0)
		{
			u++;
			word.erase(position, 1);
			position = word.find("u");
		}
		position = word.find("v");
		int v = 0;
		while (position >= 0)
		{
			v++;
			word.erase(position, 1);
			position = word.find("v");
		}
		position = word.find("w");
		int w = 0;
		while (position >= 0)
		{
			w++;
			word.erase(position, 1);
			position = word.find("w");
		}
		position = word.find("x");
		int x = 0;
		while (position >= 0)
		{
			x++;
			word.erase(position, 1);
			position = word.find("x");
		}
		position = word.find("y");
		int y = 0;
		while (position >= 0)
		{
			y++;
			word.erase(position, 1);
			position = word.find("y");
		}
		position = word.find("z");
		int z = 0;
		while (position >= 0)
		{
			z++;
			word.erase(position, 1);
			position = word.find("z");
		}
		position = word.find("0");
		int zero = 0;
		while (position >= 0)
		{
			zero++;
			word.erase(position, 1);
			position = word.find("0");
		}
		position = word.find("1");
		int one = 0;
		while (position >= 0)
		{
			one++;
			word.erase(position, 1);
			position = word.find("1");
		}
		position = word.find("2");
		int two = 0;
		while (position >= 0)
		{
			two++;
			word.erase(position, 1);
			position = word.find("2");
		}
		position = word.find("3");
		int three = 0;
		while (position >= 0)
		{
			three++;
			word.erase(position, 1);
			position = word.find("3");
		}
		position = word.find("4");
		int four = 0;
		while (position >= 0)
		{
			four++;
			word.erase(position, 1);
			position = word.find("4");
		}
		position = word.find("5");
		int five = 0;
		while (position >= 0)
		{
			five++;
			word.erase(position, 1);
			position = word.find("5");
		}
		position = word.find("6");
		int six = 0;
		while (position >= 0)
		{
			six++;
			word.erase(position, 1);
			position = word.find("6");
		}
		position = word.find("7");
		int seven = 0;
		while (position >= 0)
		{
			seven++;
			word.erase(position, 1);
			position = word.find("7");
		}
		position = word.find("8");
		int eight = 0;
		while (position >= 0)
		{
			eight++;
			word.erase(position, 1);
			position = word.find("8");
		}
		position = word.find("9");
		int nine = 0;
		while (position >= 0)
		{
			nine++;
			word.erase(position, 1);
			position = word.find("9");
		}

		//cout << wordCopy << " " << a << " " << b << " " << c << " " << d <<" " << e << " " << f << " " << g << " " << h << " " << i << " " << j << " " << k << " " << l << " " << m << " " << n << " " << o << " " << p << " " << q << " " << r << " " << s << " " << t << " " << u << " " << v << " " << w << " " << x << " " << y << " " << z << " " << endl;
		if (a <= 4 && b <= 0 && c <= 0 && d <= 0 && e <= 0 && f <= 0 && g <= 0 && h <= 0 && i <= 2 && j <= 0 && k <= 1 && l <= 0 && m <= 2 && n <= 1 &&
			o <= 1 && p <= 0 && q <= 0 && r <= 2 && s <= 1 && t <= 2 && u <= 1 && v <= 1 && w <= 0 && x <= 0 && y <= 1 && z <= 0 && one <= 0 && two <= 0 &&
			three <= 0 && four <= 0 && five <= 0 && six <= 0 && seven <= 0 && eight <= 0 && nine <= 0)
		{
			wordCount++; /*if the amount of each letter is less than or equal to the amount of times each letter occurs in my name, then the program
						   adds one to the variable wordCount to signal that one new word has been found that meets the conditions*/
			cout << wordCopy << endl;
		}
	}
	cout << "The number of words that I can make using the letters in my name is " << wordCount << " words" << endl;
	/*std::cin.get(); /*If the "std::" isn't there, then it says "cin.get()" is ambiguous. I don't know why it would say that as I'm using namespace std
					  and I wasn't sure how to fix this other than by adding the "std::". Also, I chose to use "cin.get()" insetad of 
					  "system("pause")" since the latter is not actually C++, it's just a Windows-only feature. */
	return 0;
}








		
	







