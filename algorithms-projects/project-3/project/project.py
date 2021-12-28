

def knapsack(wList,vList,w):
	knapsackArr = [0 for i in range(w+1)]
	for i in range(len(wList)):
		for j in range(w+1):
			if j >= wList[i]:
				knapsackArr[j] = max(knapsackArr[j],knapsackArr[j-wList[i]]+vList[i])
	return knapsackArr[w]

def sumOf(arr):
	mySum = 0
	for i in range(len(arr)):
		mySum = mySum + arr[i]
	return mySum

def findSum(arr,subArr,i):
	if i < len(arr):
		if sumOf(subArr)+arr[i] == 0:
			print(subArr+[arr[i]])
		findSum(arr,subArr,i+1)
		findSum(arr,subArr+[arr[i]],i+1)

def tree(arr,depth,index):
	if depth == len(arr)-1:
		return [arr[index]]
	left = [arr[index]]+tree(arr[depth+1:],depth+1,index)
	right = [arr[index]]+tree(arr[depth+1:],depth+1,index+1)
	if sumOf(left) < sumOf(right):
		return left
	return right


print()

arr = [2,3,-5,-8,6,-1]
print("List:")
print(arr)
print("Subsets that sum of their elements is zero:")
findSum(arr,[],0)
print()
arrTree = [2,5,4,1,4,7,8,6,9,6]
print("Tree:")
index = 0
depth = 0
while index < len(arrTree):
	for i in range(index,index+depth+1):
		print(str(arrTree[i])+" ",end = "")
	print()
	index = index + depth + 1
	depth = depth + 1
print("Apex with minimum sum:")
print(tree(arrTree,0,0))

print()
print("Items (w,v):")
arrW = [5,4,2]
arrV = [10,4,3]
limitW = 9
for i in range(len(arrW)):
	print("("+str(arrW[i])+","+str(arrV[i])+")",end=" ")
print()
print("Maximum value of a bag with a weight limit of "+str(limitW)+":")
print(knapsack(arrW,arrV,limitW))