#!/usr/bin/env python3
# # -*- coding: utf-8 -*-
""" 8 Queens program """
__author__=""

import sys
import random
from math import *

def eval(state):
    counter = 0

    for i in range(len(state)):

        row = state[i]
        for tl in range(i-1,-1,-1):
            row+=1
            if row == 8:
                break
            if state[tl] == row:
                counter+=1

        row = state[i]
        for tr in range(i+1,8):
            row+=1
            if row == 8:
                break
            if state[tr] == row:
                counter+=1

        row = state[i]
        for bl in range(i-1,-1,-1):
            row-=1
            if row == -1:
                break
            if state[bl] == row:
                counter+=1

        row = state[i]
        for br in range(i+1,8):
            row-=1
            if row == -1:
                break
            if state[br] == row:
                counter+=1

    return int(counter/2)
        
def swap(state):
    r_state = list(state)
    first = random.randint(0,7)
    second = random.randint(0,7)
    while second == first:
        second = random.randint(0,7)

    temp = r_state[first]
    r_state[first] = r_state[second]
    r_state[second] = temp

    return r_state

def rrestart(state):
    
    r_allowed = 2000
    states_searched = 0
    bval = inf
    best = state

    while states_searched < r_allowed:
        cstate = list(state)
        not_better = 0
        cutoff = random.randint(3,5)
        while not_better < cutoff:

            rating = eval(cstate)

            if rating == 0:
                return cstate, states_searched

            if rating >= bval:
                not_better += 1
            else:
                bval = rating
                best = cstate
                not_better = 0

            cstate = swap(cstate)

            states_searched += 1

            

            

    return False, states_searched

def sim_anneal(state, T, dT):
    cstate = list(state)
    r_allowed = 2000
    states_searched = 0
    bval = inf
    best = cstate

    while states_searched < r_allowed:
        
        cval = eval(cstate)

        if cval < bval:
            bval = cval
            best = cstate

        if cval == 0:
            return cstate, states_searched

        states_searched += 1

        t_state = swap(cstate)

        tval = eval(t_state)

        if tval < cval or random.random() < exp((cval - tval)/T):
            cstate = t_state

        T -= dT

    return False, states_searched


num_tests = int(sys.argv[1])

states = []

ssum = 0
rsum = 0
ssearches = 0
rsearches = 0

#generate random initial states
for _ in range(num_tests):
    state = []
    for i in range(8):
        row = random.randint(0,7)
        while row in state:
            row = random.randint(0,7)
        state.append(row)
    states.append(state)

for state in states:
    result, searches = sim_anneal(state, 10, 0.1)
    ssearches += searches
    if result != False:
        ssum += 1
    
    result, searches = rrestart(state)
    rsearches += searches
    if result != False:
        rsum += 1


print(f'{num_tests} puzzles')
print(f'Random Restarts:{int(rsum*100/num_tests)}% solved, average search cost:{int(rsearches/num_tests)}')
print(f'Simm. Annealing:{int(ssum*100/num_tests)}% solved, average search cost:{int(ssearches/num_tests)}')

