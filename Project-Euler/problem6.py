made_list = []

def make_list(num):
    global made_list
    
    for _ in range(1, num +1):
        made_list.append(_)

make_list(100)

res1 = 0
for num in made_list:
    res1 += num**2
    
res2 = 0
for num in made_list:
    res2 += num

res2 = res2**2

print(res2 - res1)