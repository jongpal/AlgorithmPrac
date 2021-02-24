def counting_sort(arr, factor):
    temp_arr=[] # array that will save limited value of original array
    for i in range(len(arr)):
      temp_el = (arr[i] % 10**(factor+1)) // 10**factor # according to each factor, first digit, second digit . . .
      temp_arr.append(temp_el)
    # make count array a reduced number using base based number
    max_ = max(temp_arr)
    min_ = min(temp_arr)
    count = [[] for _ in range(max_ - min_ + 1)] 
    #key = temp_arr - min
    for i in range(len(arr)):
        count[temp_arr[i] - min_].append(arr[i])
#the position itself of count is already in order
    temp_arr = sum(count, [])
    for i in range(len(temp_arr)):
        arr[i] = temp_arr[i]
def toDecimal (arr, base):
  for i in range(len(arr)):
    getOri = 0
    s = str(arr[i])
    k = 0
    for j in range(len(s)-1,-1,-1):
      getOri += int(s[k]) * (base**j)
      k+=1
    arr[i] = getOri

# make arr number into desired numeral system
def toBase (arr, base):
    arr_based = []
    for i in range(len(arr)):
        k = 0
        new_base = 0
        isMinus = False
        if arr[i] < 0:
            isMinus = True
        temp = abs(arr[i])
        while ((temp // base) >= 1):
            mod = temp % base
            temp = temp // base
            new_base += mod * (10**k)
            k += 1
        new_base += (temp % base) * (10**k)
        if isMinus:
            arr_based.append(-new_base)
        else:
            arr_based.append(new_base)
    return arr_based

"""
  radix_sort : O(n) of complexity when sorting. if k (in logbK) is in a reasonable range(<= n^c, which is much higher than that of counting sort(<= c*n )
"""
def radix_sort(arr, base):
    arr_based = toBase(arr, base)
    factor = 0
    while (max(arr_based) // 10**factor) >= 1:
      counting_sort(arr_based, factor)
      factor += 1 
    toDecimal(arr_based, base)
    return arr_based


arr = [322,342,311,455,3344,386,987,385,966]
print(radix_sort(arr, 2))


