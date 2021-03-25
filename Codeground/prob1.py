import sys
inf = open('Codeground\prob1.txt')

T = inf.readline()

for t in range(0, int(T)):
    
    Answer = 0
    T = inf.readline()
    n_list = inf.readline().rstrip().split()
    print(n_list)
    
    new_n_list = list(int(num) for num in n_list if n_list.count(num) % 2 != 0)
    
    for num in new_n_list:
        Answer ^= num
    
    # Print the answer to standard output(screen).
    print('Case #%d' %(int(t)+1))    
    print(Answer)
inf.close()