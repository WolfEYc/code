def findDupes(a):
    tortoise = a[0]
    hare = a[0]
    while True:
        tortoise = a[tortoise]
        hare = a[a[hare]]
        if(tortoise == hare):
            break

    ptr1 = a[0]
    ptr2 = tortoise
    while (ptr1 != ptr2):
        ptr1 = a[ptr1]
        ptr2 = a[ptr2]
    print (ptr1)


# code will find and print guarunteed duplicate of list of ints 1 to n-1 of size n
#not counted in the time or space complexity as it only serves converting the array to int
a = input().split()
for num in range(len(a)):
    a[num] = int(a[num])

findDupes(a)