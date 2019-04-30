from cs50 import get_int
height=get_int("Height: ")
while height<0 or height>23:
      height=get_int("Height: ")
counter_of_tabs=0
i=height
while i>0:
    tab=i-1
    while tab>0:
        print(" ",end="")
        counter_of_tabs+=1
        tab-=1

    hash=0
    while hash<height+1-counter_of_tabs:

        print("#",end="")
        hash+=1
    print()
    counter_of_tabs=0
    i-=1
