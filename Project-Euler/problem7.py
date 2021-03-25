enum = 1

prime_place = 1

primelist = []
result = 0

while prime_place != 10_001:
    #print(f"Testing {enum}")
    if enum == 1:
        enum += 1
    else:
        for num in range(2, enum + 1):
            #print(f"{enum} / {num}")
            if enum % num == 0:
                enum += 1
                break
            
            elif num >= (enum +1)//2:
                #print(f"{enum} is a prime")
                primelist.append(enum)
                result = enum
                prime_place += 1
                enum += 1
                break
                
print(result)