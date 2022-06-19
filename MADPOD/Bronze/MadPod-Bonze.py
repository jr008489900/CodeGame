import sys
import math
import numpy as np

# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.

def distance(x1:int,y1:int ,x2:int,y2:int):
    return math.sqrt((x1-x2)**2+(y1-y2)**2)
maps = []
# game loop

myprepos=[0,0]
oppoprepos=[0,0]
myspeed=[0,0]
oppospeed=[0,0]



def istoward(me,oppo):
    norspeed = [float(i) for i in myspeed]

    c1= math.sqrt(norspeed[0]**2 + norspeed[1]**2)
    norspeed[0]= norspeed[0]/c1
    norspeed[1]= norspeed[1]/c1

    vecx=oppo[0]-me[0]
    vecy=oppo[1]-me[1]
    c2 = math.sqrt(vecx**2+vecy**2)
    vecx /=c2
    vecy /=c2
    res= str(abs(norspeed[0] -vecx))+ " vec " +  str( abs(vecy-norspeed[1] )) 
    print(res, file=sys.stderr, flush=True)
    if(abs(norspeed[0] -vecx) <=0.2 and abs(vecy-norspeed[1] ) <=0.2):
        return True; 
    

    """for i in range(0,10000):
        if abs(me[0]+myspeed[0]*i*0.01 - oppo[0]) <=300 and abs(me[1]+myspeed[1]*i*0.01 - oppo[1]) <=300:
            return True"""
    return False
 
def isinPod(me,map):
    for i in range(0,len(map)):
        if distance(me[0],me[1],map[i][0],map[i][1]) <= 500:
            return True
    return False

def nextck(pos:list):
    for i in range(0,len(maps)):
        if(maps[i] == pos):
            return  maps[(i+1)%len(maps)]
        
    return []

time=0
Lap=0
while True:
    # next_checkpoint_x: x position of the next check point
    # next_checkpoint_y: y position of the next check point
    # next_checkpoint_dist: distance to the next checkpoint
    # next_checkpoint_angle: angle between your pod orientation and the direction of the next checkpoint
    x, y, next_checkpoint_x, next_checkpoint_y, next_checkpoint_dist, next_checkpoint_angle = [int(i) for i in input().split()]
    opponent_x, opponent_y = [int(i) for i in input().split()]
    myspeed[0]=x-myprepos[0]
    myspeed[1]=y-myprepos[1]
    if time >=2:
        oppospeed[0]=opponent_x-oppoprepos[0]
        oppospeed[1]=opponent_y-oppoprepos[1]
    myprepos=[x,y]
    oppoprepos=[opponent_x,opponent_y]
    print(maps, file=sys.stderr, flush=True)
    time+=1
    thrust=0
    Boost=0
    Boostmaxs=1
    print(next_checkpoint_angle, file=sys.stderr, flush=True)
    print(next_checkpoint_dist, file=sys.stderr, flush=True)
    nextnextpos =  nextck([next_checkpoint_x,next_checkpoint_y])

    if [next_checkpoint_x,next_checkpoint_y] not in maps:
        maps.append([next_checkpoint_x,next_checkpoint_y])
    else:
        Lap=1
    resx=str(next_checkpoint_x)
    resy=str(next_checkpoint_y)

    myspeedrate = math.sqrt(myspeed[0]**2+myspeed[1]**2)
    print("myspeedrate %f " %myspeedrate, file=sys.stderr, flush=True)

    if(next_checkpoint_angle >90 or  next_checkpoint_angle < -90):
        thrust= 0
    else:
        
        if time>=100 and next_checkpoint_dist <=800 and myspeedrate >=400 :
                resx=str(nextnextpos[0])
                resy=str(nextnextpos[1])
                thrust=int(next_checkpoint_dist /800*50)
                print("TESSSSTTT", file=sys.stderr, flush=True)
        elif next_checkpoint_dist<=1250:
            thrust = int(next_checkpoint_dist /1250*100)
        elif (isinPod([x,y],maps)):
            if myspeedrate <=250:
                thrust=100
            else:
                thrust=0
        else:
            thrust=100
    

    res=""


    oppotocheck = distance(opponent_x,opponent_y,next_checkpoint_x,next_checkpoint_y)
    opponextpos =[int(opponent_x+oppospeed[0]) , int(opponent_y+oppospeed[1])]

    """if(distance(x,y ,opponent_x,opponent_y) <=2000 and istoward([x,y],[opponent_x,opponent_y]) and Boost < Boostmaxs and istoward([x,y],[next_checkpoint_x,next_checkpoint_y])) and distance(x,y , next_checkpoint_x,next_checkpoint_y)>distance(opponent_x,opponent_y,next_checkpoint_x,next_checkpoint_y):
        res= str(opponextpos[0])+" " +str(opponextpos[1])+ " " + "BOOST"
        Boost+=1"""
    if  next_checkpoint_dist >=6000 and abs(next_checkpoint_angle) <60 :
        res = resx +" " + resy + " BOOST"
    elif distance(x,y ,opponent_x,opponent_y) <=2000 and istoward([x,y],[opponent_x,opponent_y]) and istoward([x,y],[next_checkpoint_x,next_checkpoint_y]) and distance(x,y , next_checkpoint_x,next_checkpoint_y)>distance(opponent_x,opponent_y,next_checkpoint_x,next_checkpoint_y):
        res= str(opponextpos[0])+" " +str(opponextpos[1]) + " " +  str(thrust)
    else:
        res=resx + " " + resy + " " + str(thrust)

 
    print(myspeed, file=sys.stderr, flush=True)
    print(oppospeed, file=sys.stderr, flush=True)
    print(distance(x,y ,opponent_x,opponent_y), file=sys.stderr, flush=True)
    # You have to output the target position
    # followed by the power (0 <= thrust <= 100)
    # i.e.: "x y thrust"
    print(res)