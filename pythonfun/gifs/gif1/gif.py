import os
import pygame
import numpy as np
from PIL import Image

def pngs(arr):
    pngs = []
    for i in arr:
        if i[-3:] == 'png':
            pngs = np.append(pngs,i)
    return pngs

def loop(arr,framerate=15):
    i = 0
    while True:
        if i >= len(arr):
            i=0
        img = pygame.image.load(arr[i])
        Display.fill(black)
        Display.blit(img,(0,0))
        pygame.display.update()
        clock.tick(framerate)
        i+=1
        for event in pygame.event.get(): #closes window for that run
            if event.type == pygame.QUIT:
                exit()
        

pygame.init()
pics = pngs(os.listdir(os.getcwd()))
black = (0,0,0)

im = Image.open(pics[0])
Display = pygame.display.set_mode(im.size)
pygame.display.set_caption('gif')
clock = pygame.time.Clock()

loop(pics,framerate=30)


