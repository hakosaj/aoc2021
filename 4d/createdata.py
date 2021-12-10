
import random
import math

pointcount=10000

maxvalue=1000
points=[]


for i in range(pointcount):
    select = random.randint(1,3)
    startx=random.randint(0,maxvalue)
    starty=random.randint(0,maxvalue)


    if select==1:
        #diagonal

        direction=random.randint(1,4)
        if direction==1:
            #left top-right bottom
            #max length: min of starts-maxvalue
            steps=random.randint(0,min(maxvalue-startx,maxvalue-starty))
            points.append(f"{startx},{starty} -> {startx+steps},{starty+steps}")

        elif direction==2:
            #right top-left bottom
            steps=random.randint(0,min(startx,maxvalue-starty))
            points.append(f"{startx},{starty} -> {startx-steps},{starty+steps}")


        elif direction==3:
            #left bottom-right top
            steps=random.randint(0,min(maxvalue-startx,starty))
            points.append(f"{startx},{starty} -> {startx+steps},{starty-steps}")
        else:
            #right bottom-left top
            steps=random.randint(0,min(startx,starty))
            points.append(f"{startx},{starty} -> {startx-steps},{starty-steps}")

    elif select==2:
        direction=random.randint(1,2)

        if direction==1:
            steps=random.randint(0,maxvalue-startx)
            points.append(f"{startx},{starty} -> {startx+steps},{starty}")

        else:
            steps=random.randint(0,startx)
            points.append(f"{startx},{starty} -> {startx-steps},{starty}")




    else:
        #vertical
        direction=random.randint(1,2)

        if direction==1:
            steps=random.randint(0,maxvalue-starty)
            points.append(f"{startx},{starty} -> {startx},{starty+steps}")

        else:
            steps=random.randint(0,starty)
            points.append(f"{startx},{starty} -> {startx},{starty-steps}")

    



with open("myfile.txt", "w") as f:
    for item in points:
        f.write(item+"\n")

