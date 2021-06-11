import sys

nums = []

for arg in range(1,len(sys.argv)):
    nums.append(int(sys.argv[arg]))

count = []

for num in nums:
    flag = 0
    for l in count:
        if(l[0] == num):
            flag = 1
    if not flag:
        count.append([num, nums.count(num)])
    
print(count)



