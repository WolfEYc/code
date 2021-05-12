import numpy as np
import pygame

def draw_maze(current_pos,Path=[],iteration=0,framerate=30):
    Display.fill(black)
    for row in range(rows):
        for col in range(cols):
            if maze[row][col] == -1:
                pygame.draw.rect(Display,white,(col*ps,row*ps,ps,ps))
       
    for pt in range(iteration):
        row,col = Path[pt]
        pygame.draw.rect(Display,(0,0,127+127*(pt/len(Path))),(col*ps,row*ps,ps,ps))
    
    for i in range(len(end_pos)):
        row,col = end_pos[i]
        num = font.render(str(i),True,black)    
        pygame.draw.rect(Display,red,(col*ps,row*ps,ps,ps))
        Display.blit(num,(col*ps+ps/6,row*ps))

    if current_pos:
        pygame.draw.rect(Display,green,(current_pos[1]*ps,current_pos[0]*ps,ps,ps))

    clock.tick(framerate)
    pygame.display.update()

def display_maze(path):
    show = True
    i = 0
    while show:
        if i < len(path):
            i+=1
        draw_maze(start_pos,Path=path,iteration=i)
        for event in pygame.event.get(): #closes window for that run
            if event.type == pygame.QUIT:
                exit()
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_r:
                    show = False

def setup_maze():
    global start_pos,end_pos,maze
    show = True
    while show:
        draw_maze(start_pos)
        for event in pygame.event.get(): #closes window for that run
            curr_clicked = [0,0]
            if event.type == pygame.QUIT:
                exit()
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_r:
                    show = False
            if event.type == pygame.MOUSEBUTTONDOWN:
                col, row = pygame.mouse.get_pos()
                curr_clicked = [int(row/ps),int(col/ps)]
                if event.button == 3:
                    if start_pos == curr_clicked:
                        start_pos = []
                    elif end_pos.count(curr_clicked) != 0:
                        end_pos.remove(curr_clicked)
                        start_pos = curr_clicked
                    elif maze[curr_clicked[0],curr_clicked[1]] == -1:
                        end_pos.append(curr_clicked)

                        
            if pygame.mouse.get_pressed()[0]:
                try:
                    col, row = event.pos
                    row = int(row/ps)
                    col = int(col/ps)
                    if maze[curr_clicked[0],curr_clicked[1]] == -100:
                        maze[row][col] = -1
                    elif [row,col]!=start_pos and end_pos.count([row,col])==0:
                        maze[row][col] = -100
                except AttributeError:
                    pass

def getNeighbors(pos,Visited):
    n = []
    row,col = pos
    if row+1 < rows and maze[row+1][col] == -1 and Visited.count([row+1,col])==0:
        n.append([row+1,col])
    if row-1 >= 0 and maze[row-1][col] == -1 and Visited.count([row-1,col])==0:
        n.append([row-1,col])
    if col+1 < cols and maze[row][col+1] == -1 and Visited.count([row,col+1])==0:
        n.append([row,col+1])
    if col-1 >= 0 and maze[row][col-1] == -1 and Visited.count([row,col-1])==0:
        n.append([row,col-1])
    return n

def backtrack(Path,spos,epos):
    bestPath = [epos]
    while not spos == epos:
        for link in Path:            
            if link[1] == epos:                
                epos = link[0]
                bestPath.append(epos)
    bestPath.reverse()
    return bestPath

def bfs():
    end_list = end_pos.copy()
    FullPath = []
    begin_pos = start_pos

    while end_list:
        Open = []
        Path = [] 
        Visited = []

        Open.append(begin_pos)
        Visited.append(begin_pos)

        while Open:
            
            pos = Open.pop(0)

            if pos == end_list[0]:              
                end_list.remove(pos)
                FullPath.append(backtrack(Path,begin_pos,pos))
                begin_pos = pos
                break

            Neighbors = getNeighbors(pos,Visited)

            for neighbor in Neighbors:
                Visited.append(neighbor)
                Open.append(neighbor)
                Path.append([pos,neighbor])
    
    finalPath = []
    for path in FullPath:
        for point in path:
            finalPath.append(point)

    return finalPath

black = (0,0,0)
white = (255,255,255)
red = (255,0,0)
blue = (0,0,255)
green = (0,255,0)
ps = 10 #pixel size
start_pos = []
end_pos = []

print('\nEnter rows:')
rows = int(input())
print('Enter cols:')
cols = int(input())
maze = np.full((rows,cols),-100)#fill closed maze

pygame.init()
sysfont = pygame.font.get_default_font()
font = pygame.font.SysFont(None, ps+7)
Display = pygame.display.set_mode((cols*ps,rows*ps))
pygame.display.set_caption('Maze')
clock = pygame.time.Clock()

while True:
    setup_maze()
    Path = bfs()
    display_maze(Path)
