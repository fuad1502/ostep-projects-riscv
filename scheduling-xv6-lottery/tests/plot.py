import matplotlib.pyplot as plt

log = {}
f = open("scheduler-log.txt", "r")
for line in f.readlines():
    tokens = line.split(",");
    pid = tokens[0].split("(")[1][:-1]
    ticks = int(tokens[2])
    if pid in log:
        log[pid].append(ticks)
    else:
        log[pid] = [ticks]

for key in log:
    l = log[key].copy()
    for i in range(1,len(log[key])):
        l[i] = log[key][i] - log[key][i-1]
    log[key] = l
    
averages = []
for key in log:
    plt.plot(log[key])
    averages.append(sum(log[key]) / len(log[key]))

for i in range(len(averages)):
    print(averages[i] / averages[0])

plt.show()
