from numpy import matrix
import random
N = int(input("input scale N:"))  # 输入矩阵大小
#  随机生成两个N*N的矩阵
li_1 = [[random.randint(1, 99) for i in range(N)] for j in range(N)]
li_2 = [[random.randint(1, 99) for i in range(N)] for j in range(N)]
matrix_1 = matrix(li_1)
matrix_2 = matrix(li_2)
#  打印矩阵
print(matrix_1)
print(matrix_2)
result = matrix_1 * matrix_2
print(result)
