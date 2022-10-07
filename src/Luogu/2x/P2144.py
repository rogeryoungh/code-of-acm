n = int(input())

f = [0] * (n + 5)

f[1] = 1
f[2] = 5
for i in range(3, n + 1):
	f[i] = f[i - 1] * 3 - f[i - 2] + 2
print(f[n])
