possible_pws = 0

for pw in range(307237, 769058 + 1):
    pw = str(pw)
    is_adjacent = False
    is_wrong_pw = False
    prev_num = 0

    for num in pw:  #3,4
        if int(num) >= prev_num:
            prev_num = int(num)
        else:
            is_wrong_pw = True
            break
    if is_wrong_pw:
        continue
    for num in pw:
        if pw.count(num) == 2:
            is_wrong_pw = False
            break
        else:
            is_wrong_pw = True
    if is_wrong_pw:
        continue
    
    print(pw)
    possible_pws += 1

print(possible_pws)