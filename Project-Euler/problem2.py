value1 = 1
value2 = 1
alist = []
result = 0

while value1 < 4000000 or value2 < 4000000:
    value1 += value2
    alist.append(value1)
    value2 += value1
    alist.append(value2)

for num in alist:
    if num % 2 == 0 and num < 4000000:
        result += num

print(result)