def solution(x, y):
    sum_of_x = sum(x)
    sum_of_y = sum(y)
    diff = sum_of_x - sum_of_y
    if (diff not in x and diff in y) or (diff not in y and diff in x):
        return diff
    else:
        return -diff
