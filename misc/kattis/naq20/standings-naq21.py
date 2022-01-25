import requests
from bs4 import BeautifulSoup
from tabulate import tabulate
from functools import cmp_to_key

url = 'https://naq21.kattis.com/standings'

r = requests.get(url+"?filter=3419")
html = r.text
soup = BeautifulSoup(html,features="lxml")
team_list = soup.find("select",{"class":"selectify-style"})

def get_teams_from_school(school_id):
    r = requests.get(url+school_id)
    html = r.text
    soup = BeautifulSoup(html,features="lxml")
    standings = soup.find("table",id="standings")

    ret = []
    for row in standings.find_all("tr"):
        name = row.find("td",{"class":"overflow-hidden"})
        school = row.find("td",{"class":"university-logo table-min-wrap"})
        if name is not None and school is not None:
            team_name = name.div.string.strip()
            team_school = school.img["alt"]
            #print(team_name, team_school)
            score = row.find_all("td",{"class":"total table-min-wrap table-td-align-right"})
            num_problems = score[0].string
            penalty = score[1].string
            # print(team_name, team_school, num_problems, penalty)
            ret.append([team_name, team_school, num_problems, penalty])
            # print(row)
    return ret

data = []
for team in team_list.find_all("option"):
    data.extend(get_teams_from_school(team["value"]))

def comp(a, b):
    if int(a[2]) != int(b[2]):
        return int(a[2])-int(b[2])
    return int(b[3])-int(a[3])
for c in data:
    if len(c[0]) > 30: c[0] = c[0][:27]+"..."
data.sort(key=cmp_to_key(comp), reverse = True)
table = tabulate(data, headers = ["Team Name", "School", "# Solved", "Penalty"], tablefmt = "orgtbl")
print(table)

