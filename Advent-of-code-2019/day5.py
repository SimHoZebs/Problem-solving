q_input = [3,225,1,225,6,6,1100,1,238,225,104,0,1102,40,93,224,1001,224,-3720,224,4,224,102,8,223,223,101,3,224,224,1,224,223,223,1101,56,23,225,1102,64,78,225,1102,14,11,225,1101,84,27,225,1101,7,82,224,1001,224,-89,224,4,224,1002,223,8,223,1001,224,1,224,1,224,223,223,1,35,47,224,1001,224,-140,224,4,224,1002,223,8,223,101,5,224,224,1,224,223,223,1101,75,90,225,101,9,122,224,101,-72,224,224,4,224,1002,223,8,223,101,6,224,224,1,224,223,223,1102,36,63,225,1002,192,29,224,1001,224,-1218,224,4,224,1002,223,8,223,1001,224,7,224,1,223,224,223,102,31,218,224,101,-2046,224,224,4,224,102,8,223,223,101,4,224,224,1,224,223,223,1001,43,38,224,101,-52,224,224,4,224,1002,223,8,223,101,5,224,224,1,223,224,223,1102,33,42,225,2,95,40,224,101,-5850,224,224,4,224,1002,223,8,223,1001,224,7,224,1,224,223,223,1102,37,66,225,4,223,99,0,0,0,677,0,0,0,0,0,0,0,0,0,0,0,1105,0,99999,1105,227,247,1105,1,99999,1005,227,99999,1005,0,256,1105,1,99999,1106,227,99999,1106,0,265,1105,1,99999,1006,0,99999,1006,227,274,1105,1,99999,1105,1,280,1105,1,99999,1,225,225,225,1101,294,0,0,105,1,0,1105,1,99999,1106,0,300,1105,1,99999,1,225,225,225,1101,314,0,0,106,0,0,1105,1,99999,1007,226,677,224,1002,223,2,223,1005,224,329,1001,223,1,223,1007,226,226,224,1002,223,2,223,1006,224,344,101,1,223,223,1107,677,226,224,102,2,223,223,1006,224,359,1001,223,1,223,108,677,677,224,1002,223,2,223,1006,224,374,1001,223,1,223,107,677,677,224,1002,223,2,223,1005,224,389,101,1,223,223,8,677,677,224,1002,223,2,223,1005,224,404,1001,223,1,223,108,226,226,224,1002,223,2,223,1005,224,419,101,1,223,223,1008,677,677,224,1002,223,2,223,1005,224,434,101,1,223,223,1008,226,226,224,1002,223,2,223,1005,224,449,101,1,223,223,7,677,226,224,1002,223,2,223,1006,224,464,1001,223,1,223,7,226,226,224,1002,223,2,223,1005,224,479,1001,223,1,223,1007,677,677,224,102,2,223,223,1005,224,494,101,1,223,223,1108,677,226,224,102,2,223,223,1006,224,509,1001,223,1,223,8,677,226,224,102,2,223,223,1005,224,524,1001,223,1,223,1107,226,226,224,102,2,223,223,1006,224,539,1001,223,1,223,1008,226,677,224,1002,223,2,223,1006,224,554,1001,223,1,223,1107,226,677,224,1002,223,2,223,1006,224,569,1001,223,1,223,1108,677,677,224,102,2,223,223,1005,224,584,101,1,223,223,7,226,677,224,102,2,223,223,1006,224,599,1001,223,1,223,1108,226,677,224,102,2,223,223,1006,224,614,101,1,223,223,107,226,677,224,1002,223,2,223,1005,224,629,101,1,223,223,108,226,677,224,1002,223,2,223,1005,224,644,101,1,223,223,8,226,677,224,1002,223,2,223,1005,224,659,1001,223,1,223,107,226,226,224,1002,223,2,223,1006,224,674,101,1,223,223,4,223,99,226]

operator_dict = {1: '+', 2: '*'}

class MainFuncs:
    
    def __init__(self):
        global q_input
        global operator_dict

        self.q_input = q_input
        self.operator_dict = operator_dict

    def paramModeList(self, curr_address = curr_address):
        instructions = self.q_input[curr_address]
        return_list = []
        if (instructions == 3 
        or instructions == 4 
        or len(str(instructions)) == 4):
            return_list.append(0)
        elif instructions == 3 or instructions == 4:
            return_list.append(instructions)
        else:        
            for num in str(instructions):
                return_list.append(int(num))
            return_list.pop(-2)
        return return_list

    def operationNumList(
        self,
        curr_address= curr_address, 
        param_mode_list = param_mode_list):
        return_list = []
        for enumerator, num in enumerate(param_mode_list, 1):
            addr_ipara_num = self.q_input[curr_address + enumerator] #address or immediate parameter mode's number
            ppara_num = self.q_input[addr_ipara_num] #Position parameter mode's number
            if enumerator == 4:
                return_list.append(self.operator_dict[num]) 
            elif num == 1 or num == 3 or num == 4 or enumerator == 3:
                return_list.append(addr_ipara_num)
            elif num == 0:
                return_list.append(ppara_num) #num from address of address
            else:
                program_error = True
                break
        return return_list

    def operation(
        self,
        input_num,
        operation_num_list = operation_num_list):
        if len(param_mode_list) == 1:
            self.q_input[operation_num_list] = input_num
        else:
            num1 = operation_num_list[0]
            num2 = operation_num_list[1]
            save_pos = operation_num_list[2]
            operator = operation_num_list[3]
            self.q_input[save_pos] = eval(f"{num1}", operator, f"{num2}")


main = MainFuncs()
curr_address = 0

while True:
    param_mode_list = main.paramModeList()
    operation_num_list = main.operationNumList()
    main.operation(1)

    if len(param_mode_list) == 1:
        curr_address += 2
    else:
        curr_address += 4