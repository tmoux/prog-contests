# https://adventofcode.com/2020/day/19

from collections import defaultdict
import regex

def parse(raw, add_loops=False):
    G = defaultdict(list)
    for line in raw:
        n, sub_rules = line.split(': ')
        for sr in sub_rules.split(' | '):
            if sr[0] == '"': G[n] = sr[1]
            else: G[n].append(sr.split())

    def dfs(n='0'):
        node = G[n]
        if type(node) == str: return node
        if type(node) == list:
            if add_loops and n == '8':
                return f'(?P<eight>{dfs("42")}|{dfs("42")}(?&eight))'
            if add_loops and n == '11':
                return f'(?P<eleven>{dfs("42")+dfs("31")}|{dfs("42")}(?&eleven){dfs("31")})'
            else:
                branches = ( ''.join(dfs(x) for x in branch) for branch in node )
                return f'({"|".join(branches)})'

    return f'^{dfs()}$'

def count_matches(rule, messeages): 
    return sum(bool(regex.match(rule, m)) for m in messeages) 

if __name__ == '__main__':
    rules = open('data/day19_rules.in').readlines()
    messeages = open('data/day19_messages.in').readlines()
    print(count_matches(parse(rules), messeages))
    print(count_matches(parse(rules, add_loops=True), messeages))
