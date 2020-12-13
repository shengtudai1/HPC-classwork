import random
N = int(input("请输入矩阵维度N:"))
arr_1 = [[random.randint(1,99) for i in range(N)] for j in range(N)]
arr_2 = [[random.randint(1,99) for i in range(N)] for j in range(N)]
result = [[ ] for i in range(N)]
print(arr_1)
print(arr_2)
for i in range(N):
	for j in range(N):
		tmp = 0
		for k in range(N):
			tmp += arr_1[i][k] * arr_2[k][j]
		result[i].append(tmp)
print(result)	
