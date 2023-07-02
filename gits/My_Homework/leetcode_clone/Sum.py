import sys
def Sum(a,b): 
    return int(a) + int(b)
result = Sum(sys.argv[1],sys.argv[2])
file1 = open("result.txt","w")
file1.write(str(result))