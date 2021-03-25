num = 1
factors = []

while len(factors) < 500:
    num += 1                                # num = 2
    tri_num = num*(num + 1)//2              # tri_num = 3
    step = 1 if tri_num % 2 == 0 else 2
    range_limit = tri_num//2 + 1 
    range_start = 1

    while range_start < range_limit:
        for divisor in range(range_start, range_limit, step):
            if tri_num % divisor == 0:
                factors.append(divisor)
                range_start = divisor + step
                range_limit = tri_num//divisor//2 + 1
                break
    if len(factors)*2 + 2>= 500:
        print("answer", tri_num)
        break
    else:
        print(factors)
        # print("Len of factor list:", len(factors)*2)
        factors.clear()
