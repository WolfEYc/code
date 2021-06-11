def avg(nums):
    return sum(nums)/len(nums)

def l_sqr(nums):
    for num in range(len(nums)):
        nums[num]*=nums[num]
    return nums

def var(nums):
    a = avg(nums)
    for num in range(len(nums)):
        nums[num] -= a
    nums = l_sqr(nums)
    return avg(nums)
    