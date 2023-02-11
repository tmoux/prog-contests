import requests
from bs4 import BeautifulSoup
from tabulate import tabulate
from functools import cmp_to_key

url = 'https://naq22.kattis.com/standings'
url2 = 'https://naq22.kattis.com/contests/naq22/standings'

r = requests.get(url+"?filter=4648")
html = r.text
soup = BeautifulSoup(html,features="lxml")
team_list = soup.find("select",{"class":"selectify-style"})

def get_teams_from_school(school_id):
    r = requests.get(url2+school_id)
    html = r.text
    soup = BeautifulSoup(html,features="lxml")
    # standings = soup.find("table",id="table2 standings-table")
    standings = soup.find("table",{"class": "table2 standings-table"})
    # print(html)
    # print(standings)

    ret = []
    for row in standings.find_all("tr"):
        name = row.find("td",{"class":"standings-cell--expand"})
        # school = row.find("td",{"class":"university-logo table-min-wrap"})
        school = row.find("img", {"class": "image_info-image-table"})
        # print(name, school)
        if name is not None and school is not None:
            team_name = name.div.find('a').contents[0].strip()
            team_school = school["alt"].strip()
            # print(team_name, team_school)
            num_problems = row.find("td", {"class": "table-item-autofit table-align-right standings-cell-score"}).contents[0]
            penalty = row.find("td", {"class": "table-item-autofit table-align-right standings-cell-time"}).contents[0]
            # print(team_name, team_school, num_problems, penalty)
            ret.append([team_name, team_school, num_problems, penalty])
            # print(row)
    return ret

data = []
for team in team_list.find_all("option"):
    # print(team)
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

