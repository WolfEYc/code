degsPerMinute = 18.5

print("Enter oven 1 current temp: ")
temp1 = float(input())

print("Enter oven 2 current temp: ")
temp2 = float(input())

print("Enter oven 3 current temp: ")
temp3 = float(input())

print("Preheat oven 1 to: ")
preheat1 = float(input())

print("Preheat oven 2 to: ")
preheat2 = float(input())

print("Preheat oven 3 to: ")
preheat3 = float(input())

heat1 = preheat1 - temp1
heat2 = preheat2 - temp2
heat3 = preheat3 - temp3

time1 = 0
time2 = 0
time3 = 0

if heat1 <= 0:
    print("It's an oven not an A/C unit!!!")
else:
    time1 = heat1 / degsPerMinute

if heat2 <= 0:
    print("It's an oven not an A/C unit!!!")
else:
    time2 = heat2 / degsPerMinute

if heat3 <= 0:
    print("It's an oven not an A/C unit!!!")
else:
    time3 = heat3 / degsPerMinute

time1 = format(time1, '.1f')
time2 = format(time2, '.1f')
time3 = format(time3, '.1f')

print("\nOven 1 will take",time1,"minutes to preheat")
print("Oven 2 will take",time2,"minutes to preheat")
print("Oven 3 will take",time3,"minutes to preheat")
