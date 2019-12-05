import sys
import requests
import random

API = "https://codeforces.com/api/"
URL = "https://codeforces.com/contest/"

problem_statistics = {}

def weighted_choice(weights):
    rnd = random.random() * sum(weights)
    for i, w in enumerate(weights):
        rnd -= w
        if rnd < 0:
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

def getProblems(l, r):
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

#format: [handle] [lower_bound] [upper_bound] [count] [0=random, 1=#solved decreasing, weighted random# 
def main():
    if len(sys.argv) < 6:
        print("#format: [handle] [lower_bound] [upper_bound] [count] [0=random, 1=#solved decreasing, weighted random")
        sys.exit()

    handle = sys.argv[1]
    lb = int(sys.argv[2])
    ub = int(sys.argv[3])
    count = int(sys.argv[4])
    order = int(sys.argv[5])

    all_problems = getProblems(lb,ub)
    problem_list = filterSolved(all_problems,handle)

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

    print("Recommend %d problems:"%(count))
    for i in ret:
        print(URL+"%d/problem/%s"%(i["contestId"],i["index"]))

main()
