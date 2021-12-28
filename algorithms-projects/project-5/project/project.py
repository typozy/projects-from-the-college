

def countInversions(arr,i,j):
	if i == j:
		return 0
	else:
		leftStart = i
		leftEnd = int((i+j)/2)
		rightStart = int((i+j)/2)+1
		rightEnd = j
		left = countInversions(arr,leftStart,leftEnd)
		right = countInversions(arr,rightStart,rightEnd)
		indexLeft = leftStart
		indexRight = rightStart
		count = 0
		while indexLeft <= leftEnd and indexRight <= rightEnd:
			if arr[indexLeft] > 2*arr[indexRight]:
				indexRight = indexRight + 1
			else:
				count = count + (indexRight-rightStart)
				indexLeft = indexLeft + 1
		while indexLeft <= leftEnd:
			count = count + (indexRight-rightStart)
			indexLeft = indexLeft+1
		indexLeft = leftStart
		indexRight = rightStart
		temp = []
		while indexLeft <= leftEnd and indexRight <= rightEnd:
			if arr[indexLeft] > arr[indexRight]:
				temp = temp + [arr[indexRight]]
				indexRight = indexRight +1
			else:
				temp = temp + [arr[indexLeft]]
				indexLeft = indexLeft +1
		while indexLeft <= leftEnd:
			temp = temp + [arr[indexLeft]]
			indexLeft = indexLeft +1
		while indexRight <= rightEnd:
			temp = temp + [arr[indexRight]]
			indexRight = indexRight +1
		arr[leftStart:rightEnd+1] = temp
		return left + right + count

def minimizeTheMaxAssignment(A):
	first = True
	result = -1
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
				if first:
					result = A[cI][cJ]
					first = False
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
	return result

def adsWithTheMostProfit(roadArr,valueArr,index):
	if valueArr[index] >= 0:
		return valueArr[index]
	elif index < 4:
		valueArr[index] = roadArr[index]
	else:
		valueArr[index] = \
		max(adsWithTheMostProfit(roadArr,valueArr,index-1),\
			adsWithTheMostProfit(roadArr,valueArr,index-2),\
			adsWithTheMostProfit(roadArr,valueArr,index-3),\
			roadArr[index]+adsWithTheMostProfit(roadArr,valueArr,index-4))
	return valueArr[index]

def findTheLongestSymmetricSubbarray(strArr,twoDarr,i,j):
	if i < 0 or j >= len(strArr):
		return 0
	elif i == j:
		twoDarr[i][j] = 1
		return max(1 + findTheLongestSymmetricSubbarray(strArr,twoDarr,i-1,j+1),findTheLongestSymmetricSubbarray(strArr,twoDarr,i,j+1))
	elif i == j-1:
		if(strArr[j] == strArr [j-1]):
			twoDarr[i][j] = 1
			return max(2+findTheLongestSymmetricSubbarray(strArr,twoDarr,i-1,j+1),findTheLongestSymmetricSubbarray(strArr,twoDarr,i+1,j))
		else:
			return findTheLongestSymmetricSubbarray(strArr,twoDarr,i+1,j)
	else:
		if strArr[i] == strArr[j]:
			twoDarr[i][j] = 1
			return 2 + findTheLongestSymmetricSubbarray(strArr,twoDarr,i-1,j+1)
		else:
			return 0




roadArr  = [ 8, 9,10,18, 7,19, 8, 9,14, 2,10, 8, 3, 7,18,16, 9, 6,14,13,15, 9, 1,15]
valueArr = [-1 for i in range(len(roadArr))]
print()
print("Road interval:")
for i in range(len(roadArr)):
	if(roadArr[i]<10):
		print(" ",end="")
	print(roadArr[i],end=" ")
print()
print("Maximum value of the possible add selections: ",end="")
print(adsWithTheMostProfit(roadArr,valueArr,len(roadArr)-1))


string = ['a','e','d','e','f','f','a','e','e','b','d','e','c','a','e','a','c','e','a','b','f','a','f','c']
array  = [[0 for i in range(len(string))] for i in range(len(string))]
print()
print("String: ",end="")
for i in range(len(string)):
	print(string[i],end="")
print()
print("Length of the longest symmetric substring: ",end="")
print(findTheLongestSymmetricSubbarray(string,array,0,0))


print("2D substring array:")
for i in range(len(array)):
	for j in range(len(array[i])):
		print(array[i][j],end=" ")
	print()
print()
adjArr = [[17,19,25, 8,50,95,91,34,68,97],
          [32,79,10,31,45,90,55,64,12,75],
          [59,67,56,30,22,40,81,43,80,42],
          [ 9,47,74,77,70,62,71,20,39,60],
          [84,78,73,65,76,28,54,93,23,99],
          [ 3,24,37,29,49,36,98,86,46, 6],
          [52,18,26,41, 2,92,85, 5,51,89],
          [15,14,16,21,94,27,87,83, 1, 0],
          [96,88,44,13, 7,48,69,53,33,57],
          [ 4,58,61,66,63,35,11,72,38,82]]
print("2D person-job array:")
for i in range(len(adjArr)):
	for j in range(len(adjArr[i])):
		if adjArr[i][j] < 10:
			print(" ",end="")
		print(adjArr[i][j],end=" ")
	print()
print()
print("Maximum cost among the assignments: ",end="")
print(minimizeTheMaxAssignment(adjArr))
print()
print("Adjacency matrix:")
for i in range(len(adjArr)):
	for j in range(len(adjArr[i])):
		print(" ",end="")
		print(adjArr[i][j],end=" ")
	print()


mergeArr = [61,59, 5, 8,92,55,31,39,19,91,61,10,28,47,66,16,67,93,71,87, 8,82,79,29,96,89,26,55, 4,40,95,49]
print()
print("Array to apply inversion:")
for i in range(len(mergeArr)):
	if mergeArr[i] < 10:
		print(" ",end="")
	print(mergeArr[i],end=" ")
print()
print("Total inversion count: ",end="")
print(countInversions(mergeArr,0,len(mergeArr)-1))