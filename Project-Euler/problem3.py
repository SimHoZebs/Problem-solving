prime_list = set()
value = 600851475143

for num in range(2, (value//2) + 1):
    print("num:", num, "end range:", value//2 + 1)
    if value % num == 0:
        # print(f"{num} is a factor of {value}." )
        value = (value / num)
        # print(f"value changing to {value} because num after it aren't factors.")
        # print(f"Check prime in range {(num//2) + 2}")
        if value == 1:
            # print(f"Adding {num} to prime_list")
            prime_list.add(num)
            break
        for num2 in range(2, (num//2) + 2):
            # print(f"Checking if {num} can be divided by {num2}")
            if num%num2 == 0 and num2 != num:
                # print(f"It can be divided and it's not {num}, so it's not a prime.")
                break
            else:
                # print(f"Adding {num} to prime_list")
                prime_list.add(num)
    else:
        # print(f"{num} is not a factor of {value}.")
        pass

prime_list = list(prime_list)
prime_list.sort()            
# print(prime_list[-1])

#Below is an alternate answer. Only true because of the question's specific value.
"""
prime_list = []
value = 600851475143

for num in range(2, (value + 1) // 2):
    if value == 1:
        break
    if value % num == 0:
        value = (value / num)
        prime_list.append(num)

# print(prime_list[-1])
"""