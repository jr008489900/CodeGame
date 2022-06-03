import sys
import math
import numpy as np
import pandas as pd   
# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.

def flatten(A):
    rt = []
    for i in A:
        if isinstance(i,list): rt.extend(flatten(i))
        else: rt.append(i)
    return rt

def distance(x1:int,y1:int ,x2:int,y2:int):
    return math.sqrt((x1-x2)**2+(y1-y2)**2)
maps = []
# game loop

myprepos=[0,0]
oppoprepos=[0,0]
myspeed=[0,0]
oppospeed=[0,0]



def isinPod(me,map):
    mindist=2147483647
    for i in range(0,len(map)):
        mindist = min(mindist,distance(me[0],me[1],map[i][0],map[i][1]))
        if distance(me[0],me[1],map[i][0],map[i][1]) <= 600:
            return [True,distance(me[0],me[1],map[i][0],map[i][1])]
    return [False,mindist]

def nextck(pos:list):

    for i in range(0,len(maps)):
        if(maps[i] == pos):
            return  maps[(i+1)%len(maps)]
        
    return []

def BasisTransform(vec): #transform the basis of the vector to Euclidean geometry    
    basis = [1,-1]
    return [vec[0]*basis[0] , vec[1]*basis[1]]

def angle_between_2p(p1 , p2):
    np1 = BasisTransform(p1)
    np2 = BasisTransform(p2)
    vecx = [1,0]
    vecz = [np2[0]-np1[0] , np2[1]-np1[1]]

    dot = vecx[0]*vecz[0]
    x= 1
    z=math.sqrt(vecz[0]**2+vecz[1]**2)
    return math.atan2((np2[1] -np1[1]) , (np2[0]-np1[0]) )*180/math.pi


def find_optimal_chckpoint(mypos,ckpos,nextckpos,next_checkpoint_dist):
    r=0
    if next_checkpoint_dist <=10000:
        r= min((10000-next_checkpoint_dist)/10000*600,450)
    if  nextckpos == None  :
        ckangle = angle_between_2p(ckpos , mypos)
        print("Angle ckkkkk  %f" %ckangle , file=sys.stderr, flush=True)
        radians = math.radians(ckangle)
        optx = ckpos[0] + r * math.cos(radians)
        opty = ckpos[1] - r * math.sin(radians)
        return [int(optx) , int(opty)]
    else:
        angle2 = angle_between_2p(ckpos,nextckpos)
        print("Angle ckkkkk----  %f %f" %(angle2 , angle2) , file=sys.stderr, flush=True)
        radians = math.radians(angle2)
        optx = ckpos[0] + r * math.cos(radians)
        opty = ckpos[1] - r * math.sin(radians)
        return [int(optx) , int(opty)]
def AnalyzeRecord(record):
    temp = [record[0]]
    res=0
    for i in range(1,len(record)):
        if record[i-1] != record[i]:
            if record[i] not in temp:
                temp.append(record[i])
            else:
                res+=1
    return res

def Lengthen(mypos,targetpos):
    r = 1000
    vecx = int(targetpos[0])-int(mypos[0])
    vecy = int(targetpos[1])-int(mypos[1])
    tarxpos = mypos[0]+r*vecx
    tarypos = mypos[1]+r*vecy

    return [tarxpos,tarypos]

class Brake:

    def __init__(self,state,times):
        self.state=0
        self.times=int(0)
    def setTimes(self,n:int):
        self.times=n
    def brake(self,mypos,speed):
        res= [mypos[0]+(-1)*speed[0] , mypos[1]-speed[1] ]
        return res

    
    


time=0
#checkisopt =0
Boost=0
Boostmaxs=1
Record=[]
Rounds=0
_XDATA=[]
_YDATA=[]
brakeobj = Brake(0,1)

pre_next_checkpoint_dist=0

isbrake=0

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
    thrust=0
    print(next_checkpoint_angle, file=sys.stderr, flush=True)
    print(next_checkpoint_dist, file=sys.stderr, flush=True)

    if [next_checkpoint_x,next_checkpoint_y] not in maps:
        maps.append([next_checkpoint_x,next_checkpoint_y])

    nextnextpos =  nextck([next_checkpoint_x,next_checkpoint_y])
    opponextpos =[int(opponent_x+oppospeed[0]) , int(opponent_y+oppospeed[1])]
    mynextpos = [int(x+myspeed[0]),int(y+myspeed[1])]

    Record.append([next_checkpoint_x,next_checkpoint_y])
    Rounds= AnalyzeRecord(Record)
    resx=str(next_checkpoint_x)
    resy=str(next_checkpoint_y)

    if  Rounds == 0:
         optpos = find_optimal_chckpoint([x,y],[next_checkpoint_x,next_checkpoint_y],None,next_checkpoint_dist)
    else:
        optpos = find_optimal_chckpoint([x,y],[next_checkpoint_x,next_checkpoint_y], nextnextpos,next_checkpoint_dist)


    resx = str(optpos[0])
    resy = str(optpos[1])

    resz=""

    myspeedrate = math.sqrt(myspeed[0]**2+myspeed[1]**2)
    oppospeedrate = math.sqrt(oppospeed[0]**2+oppospeed[1]**2)
    print("myspeedrate %f " %myspeedrate, file=sys.stderr, flush=True)

    Record.append([next_checkpoint_x,next_checkpoint_y])
    if(next_checkpoint_angle >90 or  next_checkpoint_angle < -90) :
        thrust= 0
        print("bug here!!!  " , file=sys.stderr, flush=True)
    else:
        thrust=100

    if  next_checkpoint_dist <=2000 and Rounds!=0:
        temp = brakeobj.brake([x,y],myspeed)
        angle1=angle_between_2p([x,y] , [next_checkpoint_x,next_checkpoint_y])
        angle2=angle_between_2p([x,y] , nextnextpos)
        thrust=100
        if abs(angle1-angle2)>=90 :
            resx = temp[0]
            resy = temp[1]    
    
    oppotocheck = distance(opponent_x,opponent_y,next_checkpoint_x,next_checkpoint_y)
    res=""
    resz = thrust

    angle =  angle_between_2p([x,y],[opponent_x,opponent_y])
    print("Angle %f" %angle , file=sys.stderr, flush=True)

    pridictdistance=distance(x+myspeed[0],y+myspeed[1] , opponextpos[0],opponextpos[1])


    print("prdict distance %f " %pridictdistance , file=sys.stderr, flush=True)

    """
        if  next_checkpoint_dist >=6000 and abs(next_checkpoint_angle) <60 and Boost<Boostmaxs:
        Boost+=1
        resz="BOOST
    """

    if (pridictdistance <=2000 and abs(angle_between_2p(mynextpos,opponextpos) - angle_between_2p(mynextpos , [next_checkpoint_x,next_checkpoint_y])) <=40 and Boost < Boostmaxs and distance(mynextpos[0],mynextpos[1] , next_checkpoint_x,next_checkpoint_y)>distance(mynextpos[0],mynextpos[1],next_checkpoint_x,next_checkpoint_y)and abs(next_checkpoint_angle) <60  ) :
        #res= str(opponextpos[0])+" " +str(opponextpos[1])+ " " + "BOOST"
        resx = str(opponextpos[0]) 
        resy = str(opponextpos[1])
        Boost+=1
        resz="BOOST"
    elif (pridictdistance <=2000 and abs(angle_between_2p(mynextpos,opponextpos) - angle_between_2p(mynextpos , [next_checkpoint_x,next_checkpoint_y])) <=40  and distance(mynextpos[0],mynextpos[1] , next_checkpoint_x,next_checkpoint_y)>distance(mynextpos[0],mynextpos[1],next_checkpoint_x,next_checkpoint_y) and abs(next_checkpoint_angle) <60 ):
        resx = str(opponextpos[0]) 
        resy = str(opponextpos[1])
        resz = "100"
    elif pridictdistance <=2000 and distance(x,y,int(resx),int(resy)) <  distance(x,y,opponent_x,opponent_y) and  abs(angle_between_2p([x,y],[opponent_x,opponent_y]) - angle_between_2p([x,y],[next_checkpoint_x,next_checkpoint_y]) ) <=20 and distance(mynextpos[0],mynextpos[1],opponextpos[0],opponextpos[1]) <=1000:
        resx = str(opponextpos[0]) 
        resy = str(opponextpos[1])
        if Boost < Boostmaxs:
            Boost+=1
            resz="BOOST"
        else:
            resz="100"
    else:
        if  pridictdistance <=800 :
            angle1 = angle_between_2p([x,y],[next_checkpoint_x,next_checkpoint_y])
            angle2 = angle_between_2p([x,y],[opponent_x,opponent_y])
            if abs(angle1 - angle2) >=30 and distance(x,y,next_checkpoint_x,next_checkpoint_y) < distance(opponent_x,opponent_y,next_checkpoint_x,next_checkpoint_y ):
                resz = "SHIELD"
                print("Shield!!!!!!!! " , file=sys.stderr, flush=True)

    lengthenpos =Lengthen([x,y] , [resx,resy])
    resx=lengthenpos[0]
    resy=lengthenpos[1]
    res=str(resx) + " " + str(resy) + " " + str(resz)

 
    print(myspeed, file=sys.stderr, flush=True)
    print(oppospeed, file=sys.stderr, flush=True)
    print(distance(x,y ,opponent_x,opponent_y), file=sys.stderr, flush=True)
    # You have to output the target position
    # followed by the power (0 <= thrust <= 100)
    # i.e.: "x y thrust"

   

    """NN Method """
    """ 
     reszisnum = str(resz).isdigit()
    if str(resz).isdigit():
        reszisnum=1
    else:
        reszisnum=0
    reszz = None
    if resz =="SHIELD":
        reszz=1
    elif resz == "BOOST":
        reszz=0
    else:  
        reszz = thrust
    
    _XDATA.append([time,x, y, next_checkpoint_x, next_checkpoint_y, next_checkpoint_dist, next_checkpoint_angle, opponent_x, opponent_y , myspeed,oppospeed,maps,thrust,pridictdistance,angle_between_2p(mynextpos,opponextpos),angle_between_2p(mynextpos , [next_checkpoint_x,next_checkpoint_y]),distance(mynextpos[0],mynextpos[1] , next_checkpoint_x,next_checkpoint_y),distance(mynextpos[0],mynextpos[1],next_checkpoint_x,next_checkpoint_y),resx,resy,reszisnum,reszz]) #reszmapping  is rez a skill? 0/1   | 0:BOOST 1: SHIELD  
    _YDATA.append([resx,resy,reszisnum,reszz]
    
    _XDATA[time]=flatten(_XDATA[time])
    _YDATA[time]=flatten(_YDATA[time])
    
    for i in range(0,len(_XDATA[time])):
        _XDATA[time][i] = int(_XDATA[time][i])
    for i in range(0,len(_YDATA[time])):
        _YDATA[time][i] = int(_YDATA[time][i])"""

    time+=1
    prenext_checkpoint_dist = next_checkpoint_dist
    print(res)