list_pali = []
pali_num = 1

for num1 in range(100, 1000):
    for num2 in range(100, 1000):
        #print(f"Multiplying {num1} with {num2}")
        result = num1 * num2
        #print(f"Got {result}. Checking for palidrome")
        pali_check = list(str(result))
        #print(f"pali_check list is: {pali_check}")
        #print(f"Checking from 0 to {len(pali_check)}")
        for place in range (0, len(pali_check)):
            #print(f"comparing placement {place} and {-(place +1)}")
            if pali_check[place] != pali_check[-(place + 1)]:
                #print("They are not the same!")
                break
            if place == len(pali_check) - 1:
                #print(f"{result} is the largest palidrome for {num1}!")
                list_pali.append(result)
                break
        if len(list_pali) == pali_num:
            pali_num += 1
            break

list_pali.sort()
print(list_pali[-1])