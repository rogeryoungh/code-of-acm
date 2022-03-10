n = int(input())
x = n
base1 = 1
for i in range(1, x+1):
    base1 = base1 * i

s = str(base1 * base1 * (10 ** 12) // (x**x))
print(s[:-12] + "." + s[-12:])
