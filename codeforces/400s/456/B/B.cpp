#include <iostream>
#include <string>

int main()
{
    std::string s; std::cin >> s;
    int d0 = s.back() - '0';
    int d1 = s[s.size()-2] - '0';
    int d = d1*10+d0;
    std::cout << (d % 4 ? 0 : 4) << '\n';
}
