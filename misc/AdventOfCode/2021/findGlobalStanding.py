#!/usr/bin/python3
# This script lets you view a user's global standing, even if they aren't in the top 100 global scorers right now. 
# Of course, if you know that your user is already top 100, this isn't useful because you can see that person's standing on the AOC leaderboard. 
# But since AOC doesn't show anyone after position 100, this script can help you find out your position if you're not in the top 100.

# Note: this script was written quickly without much concern for uncommon edge cases or best practices (besides caching - love u eric). 
# For example, a somewhat major flaw of it is that it treats people with the same name as the same person, but I haven't yet found that to be a problem.

from sys import argv
from os import path, listdir, mkdir
from subprocess import check_call, DEVNULL
from datetime import datetime, timezone, timedelta
from time import sleep
from random import randint

CACHE = "./.leaderboard-cache/"

if not path.isdir(CACHE):
    mkdir(CACHE)

timezone_offset = -5.0
tzinfo = timezone(timedelta(hours=timezone_offset))
date = datetime.now(tzinfo)
day = int(date.strftime("%d"))

if len(argv) != 2:
    print("Usage: python3 getGlobalStanding.py <desired user's name>")
    print("NOTE: If you're an anonymous user, just enter '#<your number>' INCLUDING THE #.")
    exit(1)

user = argv[1]
days = listdir(CACHE)

cur = len(days) + 1
# downloads the leaderboard positions from the site if we haven't found them
# don't mess with this folder unless you plan to delete it entirely
days_to_acquire = day - cur + 1
r = [randint(20, 30) for _ in range(days_to_acquire - 1)]
if days_to_acquire > 1:
    print("Downloading %i leaderboard files." % days_to_acquire)
    print("This program sleeps for 20-30 seconds between requests to avoid " + \
          "bombarding the servers. To learn more about why that's necessary, see here:\n" + \
          "https://www.reddit.com/r/adventofcode/comments/rcxx2a/i_wrote_a_script_to_tell_you_your_global_rank/")

while days_to_acquire > 0:
    check_call(["curl", "https://adventofcode.com/2021/leaderboard/day/%i" % cur], stdout=open(".leaderboard-cache/day%i.txt" % cur, 'w'), stderr=DEVNULL)
    cur += 1
    days_to_acquire -= 1

    if days_to_acquire >= 1:
        i = len(r) - days_to_acquire
        print("Waiting for %i seconds before reading the next file. About %i seconds remaining overall." % (r[i], sum(r[i:])))
        sleep(r[i])
    else:
        print('\n')

# sloppily wait for all the files to download asynchronously
# I could just sleep here but I don't want to assume you'll download it quickly
while len(days) != day:
    days = listdir(CACHE)

# maps user name to accrued points
points = {}
for day in days:
    curPath = CACHE + day
    f = open(curPath, 'r', encoding = 'UTF-8')
    lines = f.readlines()
    f.close()

    # gather scores from the top 100 of part 2, and then part 1, respectively
    for s, e in ((97, 97 + 100), (196, 196 + 100)):
        lines[s] = lines[s][lines[s].index("First"):]
        for i in range(s, e):
            line = lines[i]
            ind = line.index(')')
            j = ind - 1
            while line[j].isdigit():
                j -= 1
            p = int(line[j+1:ind])

            start = None
            sent = '<'
            # gotta handle a bunch of different cases to parse the username
            if 'height="20' in line:
                start = line.index('height="20')+20
            elif "leaderboard-anon" in line:
                start = line.index('#')
                sent = ')'
            else:
                start = line.index('userphoto')+18
            j = start
            while line[j] != sent:
                j += 1

            u = line[start:j]
            points[u] = points.get(u, 0) + (101 - p)

# Want the entire leaderboard? Just uncomment this

#items = sorted(((points[u], u) for u in points), reverse=True)
#prev = None
#i = 0
#for p,u in items:
#    pass
#    if p != prev:
#        i += 1
#        print("POSITION %i" % i)
#        prev = p
#    print("%s has %i points." % (u, p))

uniqueScores = set(points.values())
print("There are %i users with at least one global point." % len(points))
print("There are %i unique scores on the leaderboard." % len(uniqueScores))
if user not in points:
    print("User %s doesn't have any global points, so they are not on the leaderboard at all." % user)
else:
    greater = sum(points[u] > points[user] for u in points)
    pos = sum(v > points[user] for v in set(points.values())) + 1
    print("User %s is in position %i, accounting for ties." % (user, pos))
    print("There are exactly %i users with a higher score than %s." % (greater, user))
