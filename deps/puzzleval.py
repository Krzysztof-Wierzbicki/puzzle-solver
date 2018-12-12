import sys

state = []

with open(sys.argv[1], 'r') as f:
    f.readline()
    state.append(list(map(int, f.readline().split(' '))))
    state.append(list(map(int, f.readline().split(' '))))
    state.append(list(map(int, f.readline().split(' '))))
    state.append(list(map(int, f.readline().split(' '))))
    
zero = None
for i in range(4):
    for j in range(4):
        if state[i][j] == 0:
            zero = [i, j]
            
with open(sys.argv[2], 'r') as f:
    if int(f.readline()) == -1:
        print('No solution', sys.argv[1])
        exit(0)
    solution = f.readline()
    for m in solution:
        if m == 'U':
            if zero[0] == 0:
                print('Incorrect solution', sys.argv[1])
                exit(2137)
            new_zero = [zero[0]-1, zero[1]]
            state[zero[0]][zero[1]], state[new_zero[0]][new_zero[1]] = state[new_zero[0]][new_zero[1]], state[zero[0]][zero[1]]
            zero = new_zero
        elif m == 'D':
            if zero[0] == 3:
                print('Incorrect solution', sys.argv[1])
                exit(2137)
            new_zero = [zero[0]+1, zero[1]]
            state[zero[0]][zero[1]], state[new_zero[0]][new_zero[1]] = state[new_zero[0]][new_zero[1]], state[zero[0]][zero[1]]
            zero = new_zero
        elif m == 'L':
            if zero[1] == 0:
                print('Incorrect solution', sys.argv[1])
                exit(2137)
            new_zero = [zero[0], zero[1]-1]
            state[zero[0]][zero[1]], state[new_zero[0]][new_zero[1]] = state[new_zero[0]][new_zero[1]], state[zero[0]][zero[1]]
            zero = new_zero
        elif m == 'R':
            if zero[1] == 3:
                print('Incorrect solution', sys.argv[1])
                exit(2137)
            new_zero = [zero[0], zero[1]+1]
            state[zero[0]][zero[1]], state[new_zero[0]][new_zero[1]] = state[new_zero[0]][new_zero[1]], state[zero[0]][zero[1]]
            zero = new_zero
        else:
            raise KeyError('Invalid move ' + sys.argv[1])
            
print('Correct solution', sys.argv[1])
