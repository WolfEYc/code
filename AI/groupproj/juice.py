#import libraries
import numpy as np
import pygame
import math

boxSize=100

def writeArray(filename):
    with open(filename, 'w') as outfile:
    # I'm writing a header here just for the sake of readability
    # Any line starting with "#" will be ignored by numpy.loadtxt
        outfile.write('# Array shape: {0}\n'.format(q_values.shape))
    
    # Iterating through a ndimensional array produces slices along
    # the last axis. This is equivalent to data[i,:,:] in this case
        for data_slice1 in q_values:
            for data_slice2 in data_slice1:
            # The formatting string indicates that I'm writing out
            # the values in left-justified columns 7 characters in width
            # with 2 decimal places.
                for data_slice3 in data_slice2:
                    np.savetxt(outfile, data_slice3, fmt='%-7.2f')

                    # Writing out a break to indicate different slices...
                    outfile.write('# New slice\n')

def is_terminal_state(): #checks if state is terminal or not
    pflag = False
    dflag = False
    for i in P:
        if i != 0:
            pflag = True
    for i in D:
        if i != max_blocks:
            dflag = True

    return not (pflag and dflag)

def fetch_rewards(col,row): #will return 13 if picking up or dropping off, otherwise just -1
    if(X==1):
        for zone in range(len(Dzones)):
            if([col,row] == Dzones[zone] and D[zone] < max_blocks):
                return 13
    if(X==0):
        for zone in range(len(Pzones)):
            if([col, row] == Pzones[zone] and P[zone] > 0):
                return 13
    return -1

def toggle_block(col,row): #will pickup or dropoff if available
    global P,D,X
    if(X==1):
        for zone in range(len(Dzones)):
            if([col,row] == Dzones[zone] and D[zone] < max_blocks):
                X = 0
                D[zone]+=1
    if(X==0):
        for zone in range(len(Pzones)):
            if([col,row]== Pzones[zone] and P[zone] > 0):
                X = 1
                P[zone]-=1                

def biDec(bi): #not accurate btw but it works lol
    dec = 0
    for i in range(len(S)):   # [1,0,0,0]  ~ [0,0,0,0]
        dec+=(2**(i))*S[len(S)-1-i]
    return dec

def stuv(): #sets STUV to correct values (read slide 10 in pptx)
    global S
    if(X==1):
        for zone in range(len(S)):
            if zone < len(D) and D[zone] < max_blocks:
                S[zone] = 1
            else:
                S[zone] = 0        
    if(X==0):
        for zone in range(len(S)):
            if zone < len(P) and P[zone] > 0:
                S[zone] = 1
            else:
                S[zone] = 0
    
    return biDec(S)

def get_next_action(policy,s): #gets next action based on policy
    global state_space
    if(policy == 'PGreedy'):
        return np.argmax(q_values[current_column_index,current_row_index,X,s]) if state_space == 1 else np.argmax(q_values[current_column_index,current_row_index,X]) 
    if(policy == 'PRandom'):
        return np.random.randint(4)
    if(policy == 'PExploit'):
        if(np.random.random() < 0.8):
            return np.argmax(q_values[current_column_index,current_row_index,X,s]) if state_space==1 else np.argmax(q_values[current_column_index,current_row_index,X]) 
        else:
            return np.random.randint(4)

def get_next_location(action_index): #gets next location based on action index
    new_row_index = current_row_index
    new_column_index = current_column_index
    if actions[action_index] == 'up' and current_row_index > 0:
        new_row_index -= 1
    elif actions[action_index] == 'right' and current_column_index < environment_columns - 1:
        new_column_index += 1
    elif actions[action_index] == 'down' and current_row_index < environment_rows - 1:
        new_row_index += 1
    elif actions[action_index] == 'left' and current_column_index > 0:
        new_column_index -= 1

    return new_column_index,new_row_index

def init(): #reinitializes values
    global P, D, X, current_row_index, current_column_index
    P = np.full(len(Pzones),start_blocks) #pickup locations block counts
    D = np.full(len(Dzones),0) #dropoff locations block counts
    X = 0  

    current_row_index = start_row
    current_column_index = start_col


def makeCustom():
    global environment_rows, environment_columns, start_row, start_col, Dzones, Pzones, boxSize, P, D, font, gameDisplay

    environment_rows = int(input("rows "))
    environment_columns = int(input("columns "))

    boxSize = 1000/(environment_rows+environment_columns)

    gameDisplay = pygame.display.set_mode((int(environment_columns*boxSize),int(environment_rows*boxSize)))

    font = pygame.font.SysFont(None, int(boxSize))

    start_row = -1
    start_col = -1
    Dzones = []
    Pzones = []
    P = []
    D = []

    show = True
    while show:
        gameDisplay.fill(black)

        if(start_row != -1  and start_col != -1):
            pygame.draw.rect(gameDisplay,red,(start_col*boxSize,start_row*boxSize,boxSize,boxSize))        

        for zone in range(len(Dzones)):
            num = font.render(str(D[zone]),True,white)
            gameDisplay.blit(num,(Dzones[zone][0]*boxSize+2,Dzones[zone][1]*boxSize+6))
            pygame.draw.rect(gameDisplay,green,(Dzones[zone][0]*boxSize,Dzones[zone][1]*boxSize,boxSize,boxSize),3)

        for zone in range(len(Pzones)):
            num = font.render(str(P[zone]),True,white)
            gameDisplay.blit(num,(Pzones[zone][0]*boxSize+2,Pzones[zone][1]*boxSize+6))
            pygame.draw.rect(gameDisplay,blue,(Pzones[zone][0]*boxSize,Pzones[zone][1]*boxSize,boxSize,boxSize),3)
        
        pygame.display.update()
        clock.tick(15)

        for event in pygame.event.get(): #closes window for that run
            if event.type == pygame.QUIT or (event.type == pygame.KEYDOWN and event.key == pygame.K_r):
                show = None
            if pygame.mouse.get_pressed()[0]:
                try:
                    row, col = event.pos
                    row = int(row/boxSize)
                    col = int(col/boxSize)
                    flag = False
                    for dzone in Dzones:
                        if [row,col] == dzone:
                            Dzones.remove(dzone)
                            D.pop()
                            flag = True
                            break
                    for pzone in Pzones:
                        if [row,col] == pzone:
                            Pzones.remove(pzone)
                            Dzones.append([row,col])
                            P.pop()
                            D.append(0)
                            flag = True
                            break
                    if not flag:
                        Pzones.append([row,col])
                        P.append(8)

                except AttributeError:
                    pass
            if pygame.mouse.get_pressed()[2]:
                try:
                    col, row = event.pos
                    row = int(row/boxSize)
                    col = int(col/boxSize)
                    
                    start_row = row
                    start_col = col
                except AttributeError:
                    pass

    Q_reset()


def run(steps,terminals_allowed=-1,learning_rate=0.3,discount_factor=0.5,policy='PExploit',sarsa=False,visual=None, showFinal = False, filename=None, outputArray=False, ): #runs for each expirement
    global P,D,X,current_row_index,current_column_index,q_values,reward_avg,move_avg, state_space
    step = 0
    terminals = 0
    while step < steps and (terminals_allowed==-1 or terminals < terminals_allowed):
        rewards = 0
        moves = 0
        while not is_terminal_state() and step < steps:    
            if(step==steps-1):
                print("...")
                pass    
            s = int(stuv())
            action_index = get_next_action(policy,s)            
            old_row_index, old_column_index = current_row_index, current_column_index
            current_column_index, current_row_index = get_next_location(action_index)
            reward = fetch_rewards(current_column_index,current_row_index)
            rewards+=reward          
            
            if(state_space==1):
                old_q_value = q_values[old_column_index,old_row_index,X,s,action_index]
            else:
                old_q_value = q_values[old_column_index, old_row_index,X, action_index]

            if sarsa:
                if (state_space==1):
                    temporal_difference = reward + (discount_factor * q_values[current_column_index,current_row_index,X,s,get_next_action(policy,s)]) - old_q_value
                else:
                    temporal_difference = reward + (discount_factor * q_values[current_column_index,current_row_index,X,get_next_action(policy,s)]) - old_q_value
            else:
                if (state_space==1):
                    temporal_difference = reward + (discount_factor * np.max(q_values[current_column_index,current_row_index,X,s])) - old_q_value
                else:
                    temporal_difference = reward + (discount_factor * np.max(q_values[current_column_index,current_row_index,X])) - old_q_value


            new_q_value = old_q_value + (learning_rate * temporal_difference)
            if(state_space==1):
                q_values[old_column_index, old_row_index, X, s, action_index] = new_q_value
            else:
                q_values[old_column_index, old_row_index,X, action_index] = new_q_value

            if(reward == 13):
                toggle_block(current_column_index,current_row_index)
            
            if([current_row_index,current_column_index] != [old_row_index,old_column_index]):
                moves+=1
                step+=1
                if visual=="A" and (not showFinal or step==steps):
                    gameDisplay.fill(black)

                    if(X == 1):
                        pygame.draw.rect(gameDisplay,red,(current_column_index*boxSize,current_row_index*boxSize,boxSize,boxSize))
                    else:
                        pygame.draw.rect(gameDisplay,darkred,(current_column_index*boxSize,current_row_index*boxSize,boxSize,boxSize))

                    for zone in range(len(Dzones)):
                        num = font.render(str(D[zone]),True,white)
                        gameDisplay.blit(num,(Dzones[zone][0]*boxSize+17,Dzones[zone][1]*boxSize+12))
                        pygame.draw.rect(gameDisplay,green,(Dzones[zone][0]*boxSize,Dzones[zone][1]*boxSize,boxSize,boxSize),3)

                    for zone in range(len(Pzones)):
                        num = font.render(str(P[zone]),True,white)
                        gameDisplay.blit(num,(Pzones[zone][0]*boxSize+17,Pzones[zone][1]*boxSize+12))
                        pygame.draw.rect(gameDisplay,blue,(Pzones[zone][0]*boxSize,Pzones[zone][1]*boxSize,boxSize,boxSize),3)
                    
                    pygame.display.update()
                    clock.tick(environment_rows*3)

                    for event in pygame.event.get(): #closes window for that run
                        if event.type == pygame.QUIT:
                            visual = None
                    
                    if(showFinal and step==steps):
                        if filename:
                            pygame.image.save(gameDisplay,filename)
                        if outputArray:
                            writeArray(filename+".csv")
                        input("Hit enter to continue")
                        
                if visual =="B" or visual == "C" and (not showFinal or step==steps):
                    gameDisplay.fill(black)

                    for x in range(environment_rows):
                        for y in range(environment_columns):
                            for actionInd in range(len(q_values[x,y,X,s] if state_space==1 else q_values[x,y,X])):
                                centerX = x * boxSize + boxSize/2
                                centerY = y * boxSize + boxSize/2
                                center_point = (centerX, centerY)
                                rads = math.radians(90-actionInd*90)
                                cos_val = math.cos(rads)
                                sin_val = math.sin(rads)
                                x_offset = 14 if actionInd==0 or actionInd==2 else 0
                                leftOffset = 20 if actionInd == 3 else 0
                                bottomOffset = 10 if actionInd == 2 else 0  
                                if(state_space==1):
                                    action = q_values[x,y,X,s,actionInd]
                                else: 
                                    action = q_values[x,y,X,actionInd]
                                # print(action)
                                num = smallFont.render("{:.3f}".format(action),True,white)
                                # need to get the x and y position relative to the center of the current block, let centerX,centerY = below calculation
             
                                # print(iterCorners[actionInd], iterCorners[(actionInd+1)%4])
                                left_corner = (centerX+iterCorners[actionInd][0]*boxSize/2,centerY+iterCorners[actionInd][1]*boxSize/2)
                                right_corner = (centerX+iterCorners[(actionInd+1)%4][0]*boxSize/2, centerY+iterCorners[(actionInd+1)%4][1]*boxSize/2)
                                triangle_points = [(centerX, centerY), left_corner, right_corner]
                                # pygame.draw.line(gameDisplay, green, center_point, right_corner, width=1)
                                color = None
                                if action > 0:
                                    color = (0,int(action/np.amax(q_values) * 255),0)
                                else:
                                    color = (int(action/np.amin(q_values) * 255),0,0)
                     
                                pygame.draw.polygon(gameDisplay,color,triangle_points, width=0)
                                if(visual == "B"):
                                    pygame.draw.polygon(gameDisplay,white,triangle_points, width=1)
                                    # gameDisplay.blit(num,(centerX+(50/10)*boxSize*cos_val-x_offset-leftOffset, centerY-(50/15)*boxSize*sin_val-bottomOffset))
                                    gameDisplay.blit(num,(centerX+(10)*boxSize/50*cos_val-x_offset-leftOffset, centerY-15*boxSize/50*sin_val-bottomOffset))
                                    pygame.draw.rect(gameDisplay,gray,(x*boxSize,y*boxSize,boxSize,boxSize),1)

                                
                    
                    if(X == 1):
                        pygame.draw.circle(gameDisplay,green,(current_column_index*boxSize+boxSize/2,current_row_index*boxSize+boxSize/2),10)
                    else:
                        pygame.draw.circle(gameDisplay,blue,(current_column_index*boxSize+boxSize/2, current_row_index*boxSize+boxSize/2),10)
                    for zone in range(len(Dzones)):
                        num = font.render(str(D[zone]),True,green)
                        gameDisplay.blit(num,(Dzones[zone][0]*boxSize+10,Dzones[zone][1]*boxSize+10))
                        pygame.draw.rect(gameDisplay,green,(Dzones[zone][0]*boxSize,Dzones[zone][1]*boxSize,boxSize,boxSize),3)

                    for zone in range(len(Pzones)):
                        num = font.render(str(P[zone]),True,blue)
                        gameDisplay.blit(num,(Pzones[zone][0]*boxSize+10,Pzones[zone][1]*boxSize+10))
                        pygame.draw.rect(gameDisplay,blue,(Pzones[zone][0]*boxSize,Pzones[zone][1]*boxSize,boxSize,boxSize),3)
                    pygame.display.set_caption("S:{0}, X:{1}, Y:{2}".format(s, current_column_index, current_row_index))
                    # gameDisplay.blit(sValue, (10, 10))
                    pygame.display.update()
                    if(visual == "C"):
                        clock.tick(environment_rows*3)
                    else:
                        clock.tick(10)

                    for event in pygame.event.get(): #closes window for that run
                        if event.type == pygame.QUIT:
                            visual = None

                    if(showFinal and step==steps):
                        if filename:
                            pygame.image.save(gameDisplay,filename)
                        if outputArray:
                            writeArray(filename+".csv")
                        input("Hit enter to continue")

        
        reward_avg[len(reward_avg)-1] += rewards #adds ending rewards and moves to rewards and moves list
        move_avg[len(move_avg)-1] += moves

        if is_terminal_state(): #starts adding to next rewards and moves list, also resets world
            init()
            terminals+=1
            reward_avg.append(0)
            move_avg.append(0)
      

def avgs(): #prints the report of each expirement and reinits report for next expirement
    global move_avg, reward_avg
    if not is_terminal_state(): #removes last dataset if terminal state not reached
        move_avg.pop()
        reward_avg.pop()
    avg_rewards = int(sum(reward_avg)/len(reward_avg))
    avg_moves = int(sum(move_avg)/len(move_avg))
    
    print('\nTerminal States Reached:',len(move_avg))
    print('Average Rewards:',avg_rewards)
    print('Average Moves:',avg_moves)
    print('Smartness:',"{:.2f}".format(reward_avg[len(reward_avg)-1]/move_avg[len(move_avg)-1]),'\n')

    for i in range(len(move_avg)):
        print(i+1,'Rewards:',reward_avg[i],'Moves:',move_avg[i])
        
    move_avg = [0]
    reward_avg = [0]
    Q_reset()

def Q_reset(): #resets the Q-table and World
    global q_values,S,gameDisplay, state_space
    init()
    S = np.zeros((np.max([len(D),len(P)])))
    gameDisplay = pygame.display.set_mode((int(environment_columns*boxSize),int(environment_rows*boxSize)))
    if(state_space==1):
        q_values = np.zeros((environment_columns,environment_rows,2, pow(2,len(S)), 4))
    else:
        q_values = np.zeros((environment_columns, environment_rows, 2,4))

    
def visualize_q_table(table):
    pass


iterCorners = [(-1,-1),(1,-1),(1,1),(-1,1)]

pygame.init()

sysfont = pygame.font.get_default_font()
font = pygame.font.SysFont(None, 40)
smallFont = pygame.font.SysFont(None, 15)
white = (255,255,255)
black = (0,0,0)
green = (0,255,0)
blue = (0,0,255)
darkred = (100,0,0)
red = (255,0,0)
gray = (125,125,125)
environment_rows = 5 #grid init
environment_columns = 5

max_blocks = 4 #dropoff allowed
start_blocks = 8 #starting blocks in p zones

reward_avg = [0] #list of rewards fetched from each terminal state in a run
move_avg = [0] #same for moves

actions = ['up', 'right', 'down', 'left']

Pzones = [[4,2],[1,3]] # Changing these values will allow you to change pickup and dropoff locations
Dzones = [[0,0],[4,0],[2,2],[4,4]]

P = np.full(len(Pzones),start_blocks) #pickup locations block counts
D = np.full(len(Dzones),0) #dropoff locations block counts
X = 0 #agent carrying block or not
S = np.zeros((np.max([len(D),len(P)]))) #read pptx slide 10

start_row = 4 #set this anywhere in the code if you want to change the start pos
start_col = 0

current_row_index = start_row #sets current pos to start pos initially
current_column_index = start_col

q_values = np.zeros((environment_columns,environment_rows,2, pow(len(S),2), 4)) #read slide 10 in pptx

gameDisplay = pygame.display.set_mode((environment_columns*boxSize,environment_rows*boxSize))
pygame.display.set_caption('PD World')

clock = pygame.time.Clock()

state_space=1

print('\nExpirement 1')

print('\nas1.')
run(steps=6000,policy='PRandom',showFinal=True, visual=None)
state_space=2
avgs()

print('\nas2')

run(steps=6000,policy='PRandom',showFinal=True, visual=None)
state_space=1
avgs()

print('\nbs1.')
run(steps=500,policy='PRandom')
run(steps=5500,policy='PGreedy',visual=None, filename="1b.png")
state_space=2
avgs()

print('\nbs2.')
run(steps=500,policy='PRandom')
run(steps=5500,policy='PGreedy',visual="B", filename="1b.png")
state_space=1
avgs()

print('\ncs1.')
run(steps=500,policy='PRandom',showFinal=True)
run(steps=5500,visual="B")
state_space=2
avgs()

print('\ncs2.')

run(steps=500,policy='PRandom',showFinal=True)
run(steps=5500,visual="B")
state_space=1
avgs()

print('\nExpirement 2s1')
run(steps=500,policy='PRandom',sarsa=True)
run(steps=5500,sarsa=True,visual="A")
state_space=2
avgs()

print('\nExpirement 2s2')
run(steps=500,policy='PRandom',sarsa=True)
run(steps=5500,sarsa=True,visual="A")
state_space=1
avgs()

print('\nExpirement 3s1')
run(steps=500,learning_rate=0.15,discount_factor=0.45,policy='PRandom')
run(steps=5500,learning_rate=0.15,discount_factor=0.45,visual="B")
state_space=2
avgs()

print('\nExpirement 3s2')
run(steps=500,learning_rate=0.15,discount_factor=0.45,policy='PRandom')
run(steps=5500,learning_rate=0.15,discount_factor=0.45,visual="B")
state_space=1
avgs()

print('\nExpirement 4s1')
run(steps=500,policy='PRandom')
run(steps=5500,terminals_allowed=3,visual="B")
Pzones = [[1,3],[3,1]]
run(steps=5500,terminals_allowed=3,visual="B")
state_space=2
Pzones = [[4,2],[1,3]]
avgs()

print('\nExpirement 4s2')
run(steps=500,policy='PRandom')
run(steps=5500,terminals_allowed=3,visual="B")
Pzones = [[1,3],[3,1]]
run(steps=5500,terminals_allowed=3,visual="B")
state_space=1
avgs()

print('\nExpirement 5')
makeCustom()
run(steps=600000,policy='PRandom')
run(steps=600000)
run(steps=6000,policy='PGreedy',visual="C")
avgs()

