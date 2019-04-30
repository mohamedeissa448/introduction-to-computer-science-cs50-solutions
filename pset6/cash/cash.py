import cs50
cash =cs50.get_float("Change owed: ")
while cash<0:
    cash =cs50.get_float("Change owed: ")
cent=round(cash*100)
counter=0

while cent>=25:

    cent-=25
    counter+=1

while cent>=10:

    cent-=10
    counter+=1

while cent>=5:

    cent-=5
    counter+=1

while cent>=1:

    cent-=1
    counter+=1

print(counter)