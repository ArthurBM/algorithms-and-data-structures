Q = 2

N = int(input())

list_names = []
list_ways = []
for y in range(0, N):
    list_names.append(input())

for z in range(0, Q):
    list_ways.append(input())

for way in list_ways:
    for way_letter in way:
        print(way_letter)

