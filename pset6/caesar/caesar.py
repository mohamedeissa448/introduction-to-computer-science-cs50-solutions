import sys
from cs50 import get_string
def main():
    #checking number of arguments
    if not len(sys.argv) == 2:

        print("command line arguments should be two!")
        return 1
    #changing string key to integer key
    key ,m ,n = 0,1,len(sys.argv[1])

    i =n-1
    while i >= 0:
        key = key + m * (int(sys.argv[1][i]) - 48)
        m *= 10
        i-=1

    #prompt user for plaintext
    s = get_string("plaintext:  ")
    #changing plaintext into cipher text
    i= 0
    no = len(s)
    while i<no:
        z=ord(s[i])
        if z>= 65 and z <= 90:

           z = z+ (key%26)
           if z>90 :

               z = z-90+64

        elif z>= 97 and z <= 122:

            holder = z+(key%26)
            if holder>122:

                z= holder-122+96

            else:

                z = z+(key%26)
        i+=1
    print(f"ciphertext: {s}")

if __name__=='__main__':
   main()