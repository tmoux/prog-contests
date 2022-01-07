import requests
import json
from dataclasses import dataclass
from ratelimiter import RateLimiter


def getContestStandings(id):
    response = requests.get(f"https://codeforces.com/api/contest.standings?contestId={id}&from=1&count=35000")
    if response.status_code != 200:
        return
    result = response.json()['result']
    (problems, rows) = (result['problems'], result['rows'])
    accepted = [0 for i in range(len(problems))]
    rejected = [0 for i in range(len(problems))]
    
    for rankrow in rows:
        for (i, result) in enumerate(rankrow['problemResults']):
             if result['points'] > 0:
                 accepted[i] += 1
             rejected[i] += result['rejectedAttemptCount']
    problemList = []
    with open('data.txt', 'a') as f:
        for i in range(len(problems)):
            if (accepted[i] + rejected[i] > 0):
                f.write(f'{problemName(problems[i]):5} {accepted[i]:5} {rejected[i]:5} {accepted[i]/(accepted[i]+rejected[i])}\n')


def problemName(problem):
    return str(problem['contestId']) + problem['index']

def processContests():
    problemList = []
    with open('data.txt') as f:
        for line in f.readlines():
            [name, a, r, ratio] = line.split()
            a = int(a)
            r = int(r)
            ratio = float(ratio)
            problemList.append([name, a, r, ratio])

    problemList.sort(key=lambda x:x[3])
    for x in problemList:
        print(x)

def getContests():
    rate_limiter = RateLimiter(max_calls = 1, period = 2)
    for i in range(1, 1630):
        with rate_limiter:
            print(i)
            getContestStandings(i)


# getContests()
processContests()
# problemList.sort(key=lambda x:x.ratio)

# for p in problemList:
#    print(p)
             
            
             
