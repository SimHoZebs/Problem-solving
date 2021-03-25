pairList = []
memoryDict = {1: 1}

while True:
    try:
        inputPair = [int(num) for num in input().split()]
        pairList.append(inputPair)
    except Exception as e:
        #print(e)
        break

def CycleLen(num):
    chainLen = 1
    while num > 1:
        #print(f"the num is now {num}")
        try:
            chainLen += memoryDict[num] - 1
            #print("Have it memorized!")
            break
        except KeyError:
            chainLen += 1
            num = num // 2 if num % 2 == 0 else 3*num + 1
    return chainLen

for inputPair in pairList:
    countList = []
    minRange = min(inputPair[0], inputPair[1])
    maxRange = max(inputPair[0], inputPair[1])
    for num in range(minRange, maxRange + 1):
        #print(f"Finding sequence for {num}")
        countList.append(CycleLen(num))
        #print(f"the sequence length is: {countList[-1]}")
        memoryDict[num] = countList[-1]

    countList.sort()
    print(inputPair[0], inputPair[1], countList[-1])