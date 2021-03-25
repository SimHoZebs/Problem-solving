q_value = 2_000_000

prime = 3

result = 0
answer = 0
comp_num_list = []
starter = 3
step = 2
increase = 2

while prime <= q_value:
    # print(f"prime = {prime}")
    if prime in comp_num_list:
        # print(f"{prime} is not a prime")
        prime += increase
        continue

    if prime > q_value // 2:
        starter = 2
        prime = 2
        step = 1
    
    for num in range(starter, q_value // prime, step):
        result = prime*num

        if result >= q_value:
            break
        else:
            # print(f"composite number = {result}")
            comp_num_list.append(result)

    if prime == 2:
        comp_num_list = list(set(comp_num_list))
        for num in comp_num_list:
            answer += num
        break
    
    print(prime)
    prime += increase
    # print(f"starter = {starter}")
    starter += increase

print(answer)