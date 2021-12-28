
#part1

def insertion(arr):
	l = len(arr)
	for i in range(1,l):
		for j in range(i,0,-1):
			if arr[j] < arr[j-1]:
				temp = arr[j]
				arr[j] = arr[j-1]
				arr[j-1] = temp
			else:
				break
	return

#part3

def merge(start,end,arr):
	if end > start:
		merge(start,start+int((end-start)/2),arr)
		merge(start+int((end-start)/2)+1,end,arr)
		temp1 = arr[start:start+int((end-start)/2)+1]
		temp2 = arr[start+int((end-start)/2)+1:end+1]
		index = start
		while len(temp1)>0 or len(temp2)>0:
			if len(temp1)>0 and len(temp2)>0:
				if temp1[0] < temp2[0]:
					arr[index] = temp1[0]
					temp1 = temp1[1:]
					index += 1
				else:
					arr[index] = temp2[0]
					temp2 = temp2[1:]
					index += 1
			elif len(temp1) > 0:
				arr[index:index+len(temp1)] = temp1
				temp1 = []
			else:
				arr[index:index+len(temp2)] = temp2
				temp2 = []
	return

def pairs(arr,num):
	merge(0,len(arr)-1,arr)
	while len(arr) > 1:
		if arr[0]*arr[len(arr)-1] == num:
			print("(",arr[0],",",arr[len(arr)-1],")")
			arr = arr[1:len(arr)-1]
		elif arr[0]*arr[len(arr)-1] < num:
			arr = arr[1:len(arr)]
		else:
			arr = arr[0:len(arr)-1]
	return

#part5 

#find with mergind then iterating to two of the lists
#(O(n*logn) complexity)

def findWithMerging(arrA,arrB):
	merge(0,len(arrA)-1,arrA)
	merge(0,len(arrB)-1,arrB)
	found = 0
	while len(arrA)>0 and len(arrB)> 0:
		if arrA[0] == arrB[0]:
			print(arrA[0],"found in sorted list")
			temp = arrA[0]
			while len(arrA) > 0 and arrA[0] == temp:
				arrA = arrA[1:]
			while len(arrB) > 0 and arrB[0] == temp:
				arrB = arrB[1:]
			found += 1
		elif arrA[0] < arrB[0]:
			arrA = arrA[1:]
		else:
			arrB = arrB[1:]
	if found == 0:
		print("none found in sorted list")
	return

#find with mapping
#(O(n) average case complexity)
#(O(n^2) worst case complexity (n>m))

def findWithMapping(arrA,arrB):
	mp = dict()
	#to check if we are mapping the larger list
	tempA =	[]
	tempB = []
	if len(arrB) > len(arrA):
		tempB = arrB
		tempA = arrA
	else:
		tempA = arrB
		tempB = arrA
	for i in range(0,len(tempB)):
		if tempB[i] not in mp:
			mp[tempB[i]] = 0
	found = 0
	tp = dict()
	for i in range(0,len(tempA)):
		if tempA[i] in mp and tempA[i] not in tp:
			print(tempA[i],"found in hash table")
			tp[tempA[i]] = 0
			found += 1
	if found == 0:
		print("none found in hash table")
	return

a = [6,5,3,11,7,5,2]
b = [1,2,3,6,5,4]

findWithMapping(a,b)
print(" ")
pairs(b,6)
print(" ")
findWithMerging(a,b)