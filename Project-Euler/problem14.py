import time 

a = time.time_ns()
class Euler:

    def __init__(self):
        self.q_val = 0
        self.chain = []
        self.chain_len_list = [0]
        self.reoccuring_num = 0

        # self.x_list = []
        # self.y_list = []

    def numProcessing(self, num):
        self.chain.append(num)
        while num != 1:
            if num % 2 == 0:
                num //= 2
            else:
                num = 3*num + 1
            if num < self.q_val:
                self.reoccuring_num = num
                break            
            self.chain.append(num)

    # def plotting(self, a_list):
    #     for x,y in enumerate(a_list):
    #         self.x_list.append(x)
    #         self.y_list.append(y)

    #     plt.plot(self.x_list, self.y_list)
    #     pass

q = Euler()
ans = 0

# while not ans_found:
if __name__ == "__main__":
    while q.q_val != 1_000_000:
        q.q_val += 1
        # print("Testing num:", q.q_val)
        q.numProcessing(q.q_val)
        q.curr_chain_len = len(q.chain) + q.chain_len_list[q.reoccuring_num]       
        q.chain_len_list.append(q.curr_chain_len)

        if q.chain_len_list[q.q_val] >= ans:
            ans = q.chain_len_list[q.q_val]
        q.chain.clear()

    print("Answer", q.chain_len_list.index(ans))
    b = time.time_ns()
    print("time taken", (b-a)/1000000000, "seconds")
    # import matplotlib.pyplot as plt
    # q.plotting(q.chain_len_list)
    # plt.show()