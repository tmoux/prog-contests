'''
ID: silxikys
PROG: wormhole
LANG: PYTHON3
'''
fin = open('wormhole.in','r')
N = int(fin.readline())
points = [[int(x) for x in fin.readline().split()] for i in range(N)]
fin.close()

def is_cycle(pairs):
    global N, points
    def teleport(pt):
        for pair in pairs:
            if pair[0] == pt: return pair[1]
            elif pair[1] == pt: return pair[0]
    def get_next(pt):
        minX = 2000000000
        ret = None
        for p in points:
            if p[1] == pt[1] and pt[0] < p[0] < minX:
                minX = p[0]
                ret = p
        return ret
    def helper(start):
        for i in range(N):
            start = get_next(teleport(start))
            if start is None:
                return False
        return True
    return any(map(helper,points))

ans = 0
def get_pairs(lst, pairs_so_far):
    global ans
    if not lst:
        ans += is_cycle(pairs_so_far)
    else:
        el1 = lst[0]
        for el2 in lst[1:]:
            lst2 = lst[1:]
            new_pairs = pairs_so_far + [[el1, el2]]
            lst2.remove(el2)
            get_pairs(lst2,new_pairs)

get_pairs(points,[])

fout = open('wormhole.out','w')
fout.write(str(ans)+'\n')
fout.close()
