a = int(input())
n = int(input())
if(n == 1):
    print(a % 10)
elif(n == 2):
    print(pow(a, a % 4 + 4, 10))
else:
    x = pow(a, a % 2 + 2, 4)
    print(pow(a, x + 4, 10))
