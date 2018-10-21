#include <iostream>

using namespace std;

struct Time
{
	int hour, minute;
	bool contains7()
	{
		return (hour % 10 == 7 || minute % 10 == 7);
	}
	void setBack(int x)
	{
		if (minute >= x) {
			minute -= x;
			return;
		}
		minute = (minute + 60 - x) % 60;
		hour = (hour + 24 - 1) % 24;
	}
};

int main()
{
	int x, hh, mm;
	cin >> x >> hh >> mm;
	Time time = {hh,mm};
	int ans = 0;
	while (!time.contains7()) {
		time.setBack(x);
		ans++;
	}
	cout << ans << '\n';
};