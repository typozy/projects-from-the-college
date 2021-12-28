
class Counter:
	insertion = 0
	quick = 0

def insertionSort(arr):
	l = len(arr)
	for i in range(1,l):
		for j in range(i,0,-1):
			Counter.insertion += 1
			if arr[j] < arr[j-1]:
				temp = arr[j]
				arr[j] = arr[j-1]
				arr[j-1] = temp
			else:
				break
	return arr

def quickSort(arr):
	start = 0
	end = len(arr)-1
	if end > start:
		Counter.quick += 1
		k = end
		j = start
		for i in range(start,end):
			Counter.quick += 1
			if arr[i] < arr[k]:
				if i>j:
					temp = arr[i]
					arr[i] = arr[j]
					arr[j] = temp
				j += 1
		Counter.quick += 1
		temp = arr[k]
		arr[k] = arr[j]
		arr[j] = temp
		arr[0:j] = quickSort(arr[0:j].copy())
		arr[j+1:end+1] = quickSort(arr[j+1:end+1].copy())
	else:
		Counter.quick += end-start+2
	return arr

def comparison(arr):
	print("\nList: "+str(arr)+"\n")
	Counter.insertion = 0
	print("After applying insertion sort to the list, the sorted list is:\n"+ str(insertionSort(arr.copy())))
	print("After applying insertion sort to the list, the operation count is "+str(Counter.insertion)+"\n")
	Counter.quick = 0
	print("After applying quick sort to the list, the sorted list is:\n"+ str(quickSort(arr.copy())))
	print("After applying quick sort to the list, the operation count is "+str(Counter.quick)+"\n")
	return

C = [  9,  70,  19,  66,  98,  81,  55,  62,  57,   8,
10,  21,  83,  97,   4,  43,  44,  35,  64,  63,  94,
2,  78,  48,  80,  74,  91,  79,  15,  12,  51,  59,
7,  11,  73,   1,  50,  65,  71,  13,  47,  28,  88,
42,  95,  20,  49,   6,  30,  41,  29,  93,  45,  75,
92,  38,   0,  60,  16,  34,  18,  24,  25,  86,  31,
5,  89,  22, 100,  17,  53,   3,  54,  58,  23,  32,
68,  87,  14,  26,  82,  27,  56,  40,  90,  37,  61,
76,  85,  84,  99,  46,  69,  36,  33,  77,  52,  67,
96,  72,  39]

B = [35, 45, 5, 6, 31, 47, 17, 34, 19, 50, 32, 25, 1,
40, 44, 13, 48, 30, 43, 38, 24, 11, 36, 37, 29, 3, 15,
46, 16, 4, 18, 28, 49, 26, 27, 0, 12, 14, 42, 33, 2, 10,
20, 22, 7, 41, 21, 8, 9, 23, 39]

A = [16, 14, 9, 11, 5, 6, 8, 2, 18, 17, 4, 19, 12, 15, 0, 1, 7, 10, 20, 13, 3]

comparison(A)
comparison(B)
comparison(C)