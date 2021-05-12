from numpy import random

def valid():
    if N!=-1 and (N<0 or N>4): #range check on N
        return False
    high = 0
    low = 6
    for i in range(len(M)): #range check
        if M[i] != -1:     
            if M[i]<0 or M[i]>6:
                return False
            if N!=-1 and (M[i]>N+2 or M[i]<N-1):
                return False
            if N!=-1 and D[i] == 0 and M[i]>N:
                return False
            if N!=-1 and D[i] == 1 and M[i]<N:
                return False
            if M[i] > high:
                high = M[i]
            if M[i] != -1 and M[i] < low:
                low = M[i]
    
    if high > low+3:
        return False

    return True

def filled():
    if valid() and N!=-1:
        for m in M:
            if m<0 or m>6:
                return False
        for d in D:
            if d == -1:
                return False
        return True
    return False

def onlyAtOrAbove(nRange,val):
    newRange = []
    for i in nRange:
        if i >= val:
            newRange.append(i)
    return newRange

def onlyAtOrBelow(nRange,val):
    newRange = []
    for i in nRange:
        if i <= val:
            newRange.append(i)
    return newRange


def belif():
    global N, M, D
    if not valid():
        return
    
    if N!=-1: #we DO have the N value
        for i in range(len(M)):
            if M[i] != -1 and D[i] == -1: # given M not D
                if M[i] > N: #if overcounted, is drunk
                    D[i] = 1
                elif M[i] < N: #if undercount, not drunk
                    D[i] = 0
                elif random.uniform(0,1) < .05:
                    D[i] = 1
                else:
                    D[i] = 0
            elif D[i] != -1 and M[i] == -1: #we know drunk or not
                if D[i] == 1: #if drunk
                    M[i] = N+random.randint(3)
                elif N>0 and random.uniform(0,1) < .2:
                    M[i] = N-1
                else:
                    M[i] = N

            elif D[i] == -1 and M[i] == -1: # not given M or D
                if random.uniform(0,1) < .05:#drunk
                    D[i] = 1
                    M[i] = N+random.randint(3)
                elif N>0 and random.uniform(0,1) < .2:
                    D[i] = 0
                    M[i] = N-1
                else:
                    D[i] = 0
                    M[i] = N
    else:    #we do NOT have the N value (gets tricky)
        nRange = [0,1,2,3,4]
        for i in range(len(M)):
            if M[i] != -1: #regardless
                nRange = onlyAtOrAbove(nRange,M[i]-2)
                nRange = onlyAtOrBelow(nRange,M[i]+1)
                if nRange.count(M[i]) == 0: #does not contain number in range
                    if nRange[0] > M[i]:
                        D[i] = 0
                    if nRange[len(nRange)-1] < M[i]:
                        D[i] = 1
                if D[i] == 1:
                    nRange = onlyAtOrBelow(nRange,M[i])
                if D[i] == 0:
                    nRange = onlyAtOrAbove(nRange,M[i])

        if len(nRange) == 1:
            N = nRange[0]
        elif (random.uniform(0,1) < .2):
            N = nRange[random.randint(len(nRange))]
        else:
            N = nRange[0]
        
        belif()

def run():
    global N,M,D
    belif()
    if not filled():
        print("inconclusive")
    else:
        print("N:",N)
        print("M:",M)
        print("D:",D)
    clear()

def clear():
    global N, M, D
    N = -1 #default values
    M = [-1,-1,-1]
    D = [-1,-1,-1]
    print()

N = -1 #default values
M = [-1,-1,-1]
D = [-1,-1,-1]

print("\nCase 1")
M = [3,3,1]
run()

print('Case 2')
M = [3,3,0]
run()

print('Case 3')
N = 2
M = [-1, 1 ,0]
run()

print('Case 4')
D = [1, 0, -1]
M[2] = 3
run()

print('Case 5')
M = [6, 4, -1]
D[0] = 1
run()
