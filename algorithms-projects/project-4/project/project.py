A = [[120 ,240 ,219 ,114 , 29 ,221 ,221 , 80 ,117 ,191 ,151 ,133 ,180 ,140 ,206],
[175 ,183 ,130 , 53 , 35 ,159 ,190 ,166 ,170 ,  5 , 93 ,216 ,102 ,  5 ,200],
[200 ,204 ,132 ,234 , 14 ,129 ,116 , 33 ,186 ,209 , 65 , 99 ,138 ,150 , 61],
[135 ,103 ,229 ,215 , 46 ,161 ,107 ,244 ,212 ,154 ,230 , 53 ,113 ,223 ,146],
[209 ,  6 ,232 ,184 ,242 ,168 ,  2 ,112 , 80 , 21 ,203 ,163 ,  7 ,150 , 47],
[ 85 , 33 , 39 ,227 , 93 , 19 ,207 , 92 , 42 ,118 , 24 ,221 ,109 ,208 , 88],
[228 , 34 ,  2 ,247 ,104 ,161 ,115 , 81 ,117 ,126 , 62 , 60 ,191 , 66 , 40],
[183 ,107 , 97 ,242 , 25 ,109 ,107 , 69 ,240 ,227 , 97 ,200 ,142 , 48 ,237],
[152 , 30 , 35 ,210 , 91 ,201 , 28 , 40 ,235 ,146 ,134 ,244 ,104 ,141 ,165],
[135 ,222 , 98 ,219 ,134 ,221 , 76 ,217 ,108 ,106 , 32 ,160 ,223 ,118 ,229],
[ 31 , 83 ,142 ,202 ,221 ,148 ,230 ,123 ,120 ,120 ,193 ,109 ,115 ,217 , 76],
[138 , 23 , 31 ,116 ,117 , 10 ,132 , 69 ,  8 ,180 , 83 ,233 ,126 ,142 ,211],
[ 59 ,170 ,182 ,169 ,154 , 27 , 74 , 88 , 71 , 13 ,211 ,216 , 75 , 33 , 44],
[246 ,196 ,  3 ,177 , 49 , 12 , 53 ,155 ,234 ,192 ,194 ,151 ,142 , 63 ,161],
[ 99 ,134 , 22 , 99 ,109 , 92 ,182 ,246 ,176 , 50 ,188 ,  3 ,125 , 67 , 58]]

B =  [85 , 90 ,199 ,240 , 61 , 65 ,241 , 96 ,  8 , 36 ,219 ,186 , 62 , 10 , 70,
 98 , 57 , 19 ,100 , 79 ,245 ,195 , 31 ,135 ,167 ,237 ,100 , 95 , 56 , 82,
 48 ,114 ,218 ,240 , 53 ,244 ,177 ,  8 ,132 ,202 ,141 , 68 ,138 , 99 , 37,
143 ,  7 , 22 ,201 ,131 , 22 ,103 ,220 ,243 , 43 ,157 , 73 ,177 , 57 ,112,
109 ,107 , 36 ,105 ,124 ,189 , 30 , 40 ,197 , 12 ,137 ,125 ,151 ,189 ,143,
187 , 30 , 62 ,100 , 68 ,234 ,179 ,244 ,192 , 57 , 48 ,224 ,  1 ,104 , 51,
 44 ,229 , 49 , 34 ,160 ,106 , 90 ,103 , 51 ,220 , 10 , 12 ,217 ,223 ,228,
214 ,182 ,  6 ,152 , 22 , 85 , 21 ,134 , 55 , 75 ,112 ,165 , 74 , 89 , 54,
146 ,192 ,147 , 81 ,148 ,187 ,211 , 97 ,203 ,214 , 23 , 95 ,144 ,192 ,204,
192 ,  7 , 42 , 30 ,140 ,135 , 59 ,233 ,130 ,214 ,190 ,166 ,173 , 57 ,  4,
 90 , 64 ,179 ,227 ,213 ,191 , 35 , 70 ,208 , 64 ,208 ,106 ,106 , 16 ,  7,
187 ,227 ,209 ,229 , 55 ,198 , 70 , 20 ,151 , 41 , 42 ,235 , 97 ,228 , 56,
 26 , 57 ,102 ,  4 , 88 , 55 ,131 ,144 , 13 ,249 , 95 ,194 ,111 ,161 ,172,
 83 ,189 ,189 , 26 ,236 ,160 ,230 ,240 ,126 ,226 , 31 ,  6 ,155 ,238 ,197,
134 , 36 , 87 ,248 ,141 ,149 ,230 , 16 , 64 ,137 ,153 ,181 ,188 , 96 ,  3]

C = [1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1,
1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1,
1 ,1 ,1 ,1 ,0 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1,
1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1]

def minimizeTheMaxAssignment(A):
	n = len(A)
	maxVal = 0
	while maxVal >= 0:
			maxVal = -1
			cI = -1
			cJ = -1
			for i in range(0,n):
				for j in range(0,n):
					if maxVal < A[i][j]:
						cI = i
						cJ = j
						maxVal = A[i][j]
			if maxVal >= 0:
				okI = False
				for i in range(0,n):
					if i != cI:
						if A[i][cJ] != -1:
							okI = True
							break
				okJ = False
				for j in range(0,n):
					if j != cJ:
						if A[cI][j] != -1:
							okJ = True
							break
				if okI and okJ:
					A[cI][cJ] = -1
					temp = -1
					for i in range(0,n):
						if A[i][cJ] != -1:
							if temp < 0:
								temp = i
							else:
								temp = -1
								break
					if temp > 0:
						A[temp][cJ] = -2
						for j in range(0,n):
							if j != cJ:
								A[temp][j] = -1
					temp = -1
					for j in range(0,n):
						if A[cI][j] != -1:
							if temp < 0:
								temp = j
							else:
								temp = -1
								break
					if temp > 0:
						A[cI][temp] = -2
						for i in range(0,n):
							if i != cI:
								A[i][temp] = -1
				else:
					A[cI][cJ] = -2
					for i in range(0,n):
						if i != cI:
							A[i][cJ] = -1
					for j in range(0,n):
						if j != cJ:
							A[cI][j] = -1
	for i in range(0,n):
		for j in range(0,n):
			if A[i][j] == -1:
				A[i][j] = 0
			else:
				A[i][j] = 1
	return

def findTheAbsentInteger(A):
	n = len(A)
	for i in range(0,n):
		if A[i] == 0:
			return i
	return -1

def mergeSortWithInsertionSort(A,start,end):
	if(end-start < 17):
		for i in range(start,end+1):
			for j in range(i,start,-1):
				if A[j] < A[j-1]:
					temp = A[j]
					A[j] = A[j-1]
					A[j-1] = temp
				else:
					break
	else:
		k = end
		j = start
		for i in range(start,end):
			if A[i] < A[k]:
				temp = A[i]
				A[i] = A[j]
				A[j] = temp
				j += 1
		temp = A[k]
		A[k] = A[j]
		A[j] = temp
		mergeSortWithInsertionSort(A,0,j-1)
		mergeSortWithInsertionSort(A,j+1,end)
	return

print("List before sorting:")
print(B)

mergeSortWithInsertionSort(B,0,len(B)-1)

print("List after sorting with merge sort extended with insertion sort:")
print(B)

print("Cost matrix before minimizing the maximum assignment cost:")

for i in range(0,len(A)):
	print(A[i])

minimizeTheMaxAssignment(A)

print("Assignments after minimizing:")

for i in range(0,len(A)):
	print(A[i])

print("Binary existence list of integers that we will look for the absent one:")
print(C)

print("Result after linearly searching the binary list:")
print(findTheAbsentInteger(C))






