q_input = [1,0,0,3,1,1,2,3,1,3,4,3,1,5,0,3,2,6,1,19,1,19,10,23,2,13,23,27,1,5,27,31,2,6,31,35,1,6,35,39,2,39,9,43,1,5,43,47,1,13,47,51,1,10,51,55,2,55,10,59,2,10,59,63,1,9,63,67,2,67,13,71,1,71,6,75,2,6,75,79,1,5,79,83,2,83,9,87,1,6,87,91,2,91,6,95,1,95,6,99,2,99,13,103,1,6,103,107,1,2,107,111,1,111,9,0,99,2,14,0,0]

memory = []

intcode = {1: '+', 2: '*'}

target_val = 19690720

for num in range(0, len(q_input)+1):
    noun = num
    for num in range(0, len(q_input)+1):
        verb = num 

        memory = q_input.copy()
        memory[1] = noun
        memory[2] = verb

        for pos in range(0, len(memory) + 1, 4):
            if memory[pos] != 1 and memory[pos] != 2:
                break

            operator = intcode[memory[pos]]

            num1_pos = memory[pos + 1]
            num2_pos = memory[pos + 2]
            result_pos = memory[pos + 3]

            if num1_pos >= 121 or num2_pos >= 121 or result_pos >= 121:
                break

            num1 = str(memory[num1_pos])
            num2 = str(memory[num2_pos])
            memory[result_pos] = eval(num1 + operator + num2)

        print(memory[0])
        if memory[0] >= target_val:
            break

    if memory[0] == target_val:
        break

print(100 * noun + verb)

#count how many numbers before it jumps to 1
#all numbers before it jumps to 1 is consecutive numbers??