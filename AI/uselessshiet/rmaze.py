import os
import pygame
#import random
import numpy as np
from numba import njit
from concurrent.futures import ThreadPoolExecutor

def Q_reset():
    global q_values
    q_values = np.zeros((rows,cols,action_index))

@njit(nogil = True)
def get_next_action(row,col,randy,q_vals,monkey_mag): #gets next action based on policy
        if (not randy) or np.random.random() < monkey_mag:
            return np.argmax(q_vals[row,col])
        else:
            return np.random.randint(4)

@njit(nogil = True)
def get_next_location(action_index,row,col,actionz,maz): #gets next location based on action index
    new_row_index = row
    new_column_index = col
    if actionz[action_index] == 'up' and row > 0:
        new_row_index -= 1
    elif actionz[action_index] == 'right' and col < cols - 1:
        new_column_index += 1
    elif actionz[action_index] == 'down' and row < rows - 1:
        new_row_index += 1
    elif actionz[action_index] == 'left' and col > 0:
        new_column_index -= 1
    if maz[new_row_index][new_column_index] != -100:
        return new_row_index, new_column_index
    else:
        return row,col

def draw_maze(current_pos):
    Display.fill(black)
    for row in range(rows):
        for col in range(cols):
            if maze[row][col] == -1:
                pygame.draw.rect(Display,white,(col*ps,row*ps,ps,ps))
            if [end_pos[0],end_pos[1]] == [row,col]:
                pygame.draw.rect(Display,red,(col*ps,row*ps,ps,ps))
            if [current_pos[0],current_pos[1]] == [row,col]:
                pygame.draw.rect(Display,green,(col*ps,row*ps,ps,ps))    
    clock.tick(10)
    pygame.display.update()

def setup_maze():
    global start_pos,end_pos,maze
    show = True
    while show:
        draw_maze(start_pos)
        for event in pygame.event.get(): #closes window for that run
            curr_clicked = [0,0]
            if event.type == pygame.QUIT:
                show = False
            if event.type == pygame.MOUSEBUTTONDOWN:
                col, row = pygame.mouse.get_pos()
                curr_clicked = [int(row/ps),int(col/ps)]
                if event.button == 3:
                    if [start_pos[0],start_pos[1]] == curr_clicked:
                        end_pos = np.array(curr_clicked)
                        start_pos = np.array([-1,-1])
                    elif [end_pos[0],end_pos[1]] == curr_clicked:
                        start_pos = np.array(curr_clicked)
                        end_pos = np.array([-1,-1])
                    else:
                        [start_pos[0],start_pos[1]] = curr_clicked
                        
            if pygame.mouse.get_pressed()[0]:
                try:
                    col, row = event.pos
                    row = int(row/ps)
                    col = int(col/ps)
                    if maze[curr_clicked[0],curr_clicked[1]] == -100:
                        maze[row][col] = -1
                    elif [row,col]!=[start_pos[0],start_pos[1]] and [row,col]!=[end_pos[0],end_pos[1]]:
                        maze[row][col] = -100
                except AttributeError:
                    pass        
     
    maze[end_pos[0]][end_pos[1]] = 100

@njit(nogil=True)
def speedQ(q_vals,maz,old_row,old_col,row,col,action_index,learning_rate=0.3,discount_factor=0.5):
    reward = maz[row][col]
    old_q_val = q_vals[old_row,old_col,action_index]
    temporal_diff = reward + (discount_factor * np.max(q_vals[row,col])) - old_q_val
    new_q_val = old_q_val + (learning_rate*temporal_diff)
    q_vals[old_row,old_col,action_index] = new_q_val
    return new_q_val

@njit(nogil=True)
def train(times,q_vals,actionz,maz,start_pos,end_pos,monkey_mag,learning_rate = 0.3,discount_factor=0.5,rando=True):    
    for ep in range(times):
        row, col = [start_pos[0],start_pos[1]]
        while maze[row,col]==-1:
            action_index = get_next_action(row,col,rando,q_vals,monkey_mag)
            old_row, old_col = row, col
            row, col = get_next_location(action_index,row,col,actionz,maz)
            q_vals[old_row,old_col,action_index] = speedQ(q_vals,maz,old_row,old_col,row,col,action_index,learning_rate,discount_factor)

    return q_vals

def run(times=3,learning_rate = 0.3,discount_factor=0.5,visual=True,rando=True):    
    for ep in range(times):
        row, col = [start_pos[0],start_pos[1]]
        while maze[row,col]==-1:
            action_index = get_next_action(row,col,rando,q_values,monkey_magic)
            old_row, old_col = row, col
            row, col = get_next_location(action_index,row,col,actions,maze)
            q_values[old_row,old_col,action_index] = speedQ(q_values,maze,old_row,old_col,row,col,action_index,learning_rate,discount_factor)
            if visual and [old_row,old_col] != [row,col]:
                draw_maze([row,col])
                for event in pygame.event.get(): #closes window for that run
                    if event.type == pygame.QUIT:
                        visual = False


def avgfrommap(row,col,action_index,map):
    avg = 0
    for index in range(len(map)):
        avg+=map[index,row,col,action_index]
    return avg/len(map)
                    


cores = os.cpu_count()
black = (0,0,0)
white = (255,255,255)
red = (255,0,0)
green = (0,255,0)
ps = 10 #pixel size
monkey_magic = 0.9
start_pos = np.array([-1,-1])
end_pos = np.array([-1,-1])
actions = np.array(['up', 'right', 'down', 'left'])
print('\nEnter rows:')
rows = int(input())
print('Enter cols:')
cols = int(input())
maze = np.full((rows,cols),-100)#fill closed maze
q_values = np.zeros((rows,cols,4))
pygame.init()
Display = pygame.display.set_mode((cols*ps,rows*ps))
clock = pygame.time.Clock()
setup_maze()

'''
with ThreadPoolExecutor(cores) as ex:
    q_avgs = ex.map(run,np.full(shape=cores,fill_value=(100,q_values,actions,maze)))
    for row in range(rows):
        for col in range(cols):
            for action_index in range(4):
                q_values[row,col,action_index] = avgfrommap(row,col,action_index,q_avgs)
                '''

q_values = train(6000,q_values,actions,maze,start_pos,end_pos,0)
print(q_values)

'''with ThreadPoolExecutor(cores) as ex:
    q_avgs = q_values
    for _ in range(cores):
        q_avgs = np.append(q_avgs,ex.submit(train,100,q_values,actions,maze,start_pos,end_pos,0.8).result())
    ex.submit(train,np.full(shape=(cores,7),fill_value=np.array([100,q_values,actions,maze,start_pos,end_pos,0.8],dtype=object)))
    for row in range(rows):
        for col in range(cols):
            for action_index in range(4):
                q_values[row,col,action_index] = avgfrommap(row,col,action_index,q_avgs)'''

q_values = train(1000,q_values,actions,maze,start_pos,end_pos,0.8) 
print('done2')

run(3)