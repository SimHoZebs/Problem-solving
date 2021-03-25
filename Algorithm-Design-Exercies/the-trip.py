def round_down_decimal (num, position = 0):

    whole_num, decimal = str(num).split(".")

    if len(decimal) <= position:
        return num
    else:
        return float(whole_num + "." + decimal[:position])

init_expense_lists_list = []
student_count = int(input())

while student_count != 0:
    init_expense_lists_list.append([float(input()) for _ in range(student_count)])

    student_count = int(input())

for init_expense_list in init_expense_lists_list:
    total_expense = exchanged_cash = 0
    total_students = len(init_expense_list)

    for init_expense in init_expense_list:
        total_expense = round(total_expense + init_expense, 2)

    equalized_expense = round_down_decimal((total_expense / total_students), 2)
    final_expense_list = [equalized_expense for student in range(total_students)]
    remaining_cash = round(total_expense - equalized_expense*total_students,2)

    for index in range(int(remaining_cash*100)):
        final_expense_list[index] = round(final_expense_list[index] + 0.01, 2)

    init_expense_list.sort(reverse=True)

    for init_expense, final_expense in zip(init_expense_list, final_expense_list):
        if init_expense >= final_expense:
            exchanged_cash += init_expense - final_expense
        else:
            break
    
    print(f"${exchanged_cash:.2f}")