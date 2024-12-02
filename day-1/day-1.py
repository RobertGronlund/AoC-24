# Day 1
with open('day_1/data.txt', 'r') as file:
    listA = []
    listB = []

    for line in file:
        data = line.strip().split('   ')
        # Append the data to the respective lists
        listA.append(int(data[0]))
        listB.append(int(data[1]))

listA.sort()
listB.sort()

dataLength = len(listA)

# Solution 1
deltaDist = 0
for dist in range(0, dataLength):
    deltaDist += abs(listA[dist] - listB[dist])

print(deltaDist)

# Solution 2
simScore = 0
for num in range(0, dataLength):
    count = 0
    for compare in range(0, dataLength):
        if listA[num] == listB[compare]:
            count += 1
        elif listA[num] < listB[compare]:
            break 
    simScore += listA[num] * count

print(simScore)