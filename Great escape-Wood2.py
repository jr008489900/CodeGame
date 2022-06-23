import sys
import math
import numpy as np
import random


# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.

# w: width of the board
# h: height of the board
# player_count: number of players (2 or 3)
# my_id: id of my player (0 = 1st player, 1 = 2nd player, ...)
w, h, player_count, my_id = [int(i) for i in input().split()]
side = ''
track=[]

counter=0

def checkCanGo(pos,dir,walls):
    if dir == 'right':
        pos[0]+=1
        dir='left'
    elif dir =='left':
        pos[0]-=1
        dir='right'
    elif dir=='up':
        pos[1]-=1
        dir='down'
    else:
        pos[1]+=1
        dir='up'
    for i in range(0,len(walls)):
        if walls == pos:
            return False
    return True

def Algorithm(players,walls):
    hf=[]
    me = players[my_id]
    enemy=[]
    for i in range(player_count):
        if me!= players[i]:
            enemy = players[i]
            break
    if counter==0 and side == 'right':
        res = str(int(enemy[0]+1)) + ' ' + str(enemy[1]) + ' ' + 'V'
        return res

    if side == 'left':
        if not [me[0]+1,me[1]] in track and checkCanGo([me[0],me[1]],'right',walls):
            track.append([me[0]+1,me[1]])
            return 'RIGHT'
        else:
            rnum=random.randint(0,2)
            if rnum == 0:
                track.append([me[0],me[1]-1])
                return 'UP'
            elif rnum == 1:
                track.append([me[0],me[1]+1])
                return 'DOWN'
            else:
                track.append([me[0]-1,me[1]])
                return 'LEFT'
    else:
        if not [me[0]-1,me[1]] in track:
            track.append([me[0]-1,me[1]])
            return 'LEFT'
        else:
            rnum=random.randint(0,2)
            if rnum == 0:
                track.append([me[0],me[1]-1])
                return 'UP'
            elif rnum == 1:
                track.append([me[0],me[1]+1])
                return 'DOWN'
            else:
                track.append([me[0]+1,me[1]])
                return 'RIGHT'
    

# game loop
while True:
    players=[]
    walls=[]
    for i in range(player_count):
        # x: x-coordinate of the player
        # y: y-coordinate of the player
        # walls_left: number of walls available for the player
        x, y, walls_left = [int(j) for j in input().split()]
        players.append([x,y,walls_left])
    wall_count = int(input())  # number of walls on the board
    for i in range(wall_count):
        inputs = input().split()
        wall_x = int(inputs[0])  # x-coordinate of the wall
        wall_y = int(inputs[1])  # y-coordinate of the wall
        wall_orientation = inputs[2]  # wall orientation ('H' or 'V')
        walls.append([wall_x,wall_y,wall_orientation])

    if counter==0:
        if players[my_id][0]==0:
            side = 'left'
        else:
            side='right'
    res=Algorithm(players,walls)
    counter+=1
    print(side, file=sys.stderr, flush=True)
    # Write an action using print
    # To debug: print("Debug messages...", file=sys.stderr, flush=True)


    # action: LEFT, RIGHT, UP, DOWN or "putX putY putOrientation" to place a wall
    print(res)