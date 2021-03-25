num_range = 1000
result = 0

for a in range(3,num_range//3):
    for b in range (a + 1, (num_range - a)//2):
        c = num_range - (a + b)

        if a**2 + b**2 == c**2:
            result = a*b*c
            break
    
    if result > 0:
        print(result)
        break