n = int(input())
cows = []
for i in range(n):
    [a,b,c] = input().split()
    cows.append([a,int(b),int(c),i])

# Simple class to represent an event
class Event:
    def __init__(self, time, point, id):
        self.time = time
        self.point = point
        self.id = id

events = []
for i in cows:
    for j in cows:
        if i[0] == 'E' and j[0] == 'N' and i[1] < j[1] and i[2] > j[2]:
            x = j[1]
            y = i[2]
            dx = x-i[1]
            dy = y-j[2]
            if dx != dy: 
                #if both cows arrive at the intersection at the same time,
                #ignore the intersection
                events.append(Event(dx,(x,y),i[3]))
                events.append(Event(dy,(x,y),j[3]))
# Sort the event list based the time
events.sort(key=lambda x:x.time)
dead = [] #list of id's of cows that have stopped
eaten = [] #list of cells that have already been eaten
ans = [0] * n
for e in events:
    if e.id not in dead: #if the cows has stopped, skip it
        if e.point in eaten: #if this point has been eaten already, stop
            ans[e.id] = e.time
            dead.append(e.id)
        else: #add the point to the list and keep going
            eaten.append(e.point)
# output answer
for i in range(n):
    if i not in dead:
        print("Infinity")
    else:
        print(ans[i])
