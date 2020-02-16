import datetime

delta = datetime.timedelta(1)

def getFirstFriday(year, month):
    d = datetime.date(year,month,1)
    for i in range(10):
        if d.weekday() == 4: 
            return d.day
        d = d + delta

def getPenultimateSunday(year, month):
    d = datetime.date(year + (month == 12), (month + 1 if month < 12 else 1), 1) - delta
    sundays = 0
    for i in range(20):
        if d.weekday() == 6:
            sundays += 1
        if (sundays == 2):
            return d.day
        d = d - delta

def intersect(year, month):
    d1 = getFirstFriday(year,month)
    d2 = getPenultimateSunday(year,month)
    return 1 if d2-d1 <= 10 else 0

cnt = [{}]*400
cf = 0

def precompute():
    global cf, cnt
    for year in range(2000,2400):
        for month in range(1,12+1):
            c = intersect(year,month)
            cnt[year%400].update(month=c)
            if c == 1:
                cf = cf + 1
            #print(year%400,month,cnt[year%400][month])

def pref(year, month):
    ans = 0
    print(year,month)
    while True:
        if year % 400 == 0 and month == 12:
            ans += (year//400)*cf
            break
        ans += cnt[year%400][month]
        #print(year%400,month,cnt[year%400][month])
        month -= 1
        if month == 0:
            month = 12
            year -= 1
    print("ans:",ans)
    return ans

def main():
    precompute()
    t = int(input())
    for x in range(t):
        m1, y1 = [int(x) for x in input().split()]
        m2, y2 = [int(x) for x in input().split()]
        a2 = pref(y2,m2)

        m1 -= 1
        if m1 == 0:
            m1 = 12
            y1 -= 1
        a1 = pref(y1,m1)

        print(a2-a1)
main()
