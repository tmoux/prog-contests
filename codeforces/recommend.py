#!/usr/bin/env python
import sys
import requests
import random
import argparse
from argparse import RawTextHelpFormatter

#Recommends unsolved problems within a specified rating range.
#The "weighted random" option is intended to give you random problems, but be biased towards problems that have more solves.
#See --help for more details

API = "https://codeforces.com/api/"
URL = "https://codeforces.com/contest/"

problem_statistics = {}

def weighted_choice(weights):
    rnd = random.random() * sum(weights)
    for i, w in enumerate(weights):
        rnd -= w
        if rnd <= 0:
            return i

def weighted_shuffle(a,w):
    w = list(w) # make a copy of w
    if len(a) != len(w):
        print("weighted_shuffle: Lenghts of lists don't match.")
        return

    r = [0]*len(a) # contains the random shuffle
    for i in range(len(a)):
        j = weighted_choice(w)
        r[i]=a[j]
        w[j] = 0
    return r

def getProblems(l, r, tags):
    request = requests.get(API+"problemset.problems").json()
    if request["status"] != "OK":
        print("Problemset request failed")
        sys.exit()
    problems = request["result"]["problems"]
    stats = request["result"]["problemStatistics"]
    #make problem_statistics map
    for s in stats:
        problem_statistics[(s["contestId"],s["index"])] = s["solvedCount"]
    #return map of contestId to list of contests
    mp = {}
    problems = list(filter(lambda x: "rating" in x and l <= x["rating"] and x["rating"] <= r,problems))
    if tags:
        problems = list(filter(lambda x: any(y in x["tags"] for y in tags),problems))
    return problems

def filterSolved(all_problems,handle):
    unsolved = []
    request = requests.get(API+"user.status?handle=%s"%(handle)).json()
    if request["status"] != "OK":
        print("Submission request failed")
        sys.exit()
    submissions = request["result"]
    submissions = list(filter(lambda x: x["verdict"]=="OK",submissions))
    ac_problems = list(map(lambda x: x["problem"],submissions))
    ac_names = set(map(lambda x: x["name"],ac_problems))

    unsolved_problems = list(filter(lambda x: x["name"] not in ac_names,all_problems))

    return unsolved_problems

def main():
    parser = argparse.ArgumentParser(description="Recommends unsolved Codeforces problems within a difficulty range",formatter_class=RawTextHelpFormatter)
    parser.add_argument("-n","--handle", help="Codeforces handle",type=str,default="silxi")
    parser.add_argument("-r","--rating", help="Upper and lower bound for problem rating. Default behavior is to fetche all problems.",nargs=2,type=int,default=[0,5000])
    parser.add_argument("-c","--count",help="Number of problems to be recommended",type=int,default=5)
    parser.add_argument("-o","--order",help="Method by which problems are recommended.\n0 = Pure random\n1 = Sorted decreasing by solve count\n2 = Random, but biased towards problems which that have more solves",type=int,default=2)
    parser.add_argument("-t","--tags",help="Filters problems that match at least one of the tags",type=str,nargs='*',default=[])

    args = parser.parse_args()
    handle = args.handle
    lb = int(args.rating[0])
    ub = int(args.rating[1])
    count = int(args.count)
    order = int(args.order)
    tags = args.tags

    """
    print("handle = %s"%handle)
    print("rating = [%d, %d]"%(lb,ub))
    print("count = %d"%count)
    print("order = %d"%order)
    """

    all_problems = getProblems(lb,ub,tags)
    problem_list = filterSolved(all_problems,handle)

    #print(len(all_problems),len(problem_list))

    ret = []

    if order == 0:
        random.shuffle(problem_list)
        ret = problem_list[:count]
    elif order == 1:
        problem_list.sort(key=lambda x: problem_statistics[(x["contestId"],x["index"])])  
        problem_list.reverse()
        ret = problem_list[:count]
    elif order == 2:
        w = list(map(lambda x: problem_statistics[(x["contestId"],x["index"])]**2,problem_list))
        problem_list = weighted_shuffle(problem_list,w)
        ret = problem_list[:count]

    print("Recommended %d problems:"%(count))
    for i in ret:
        print(URL+"%d/problem/%s"%(i["contestId"],i["index"]))

main()
