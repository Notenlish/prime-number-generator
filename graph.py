import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
import numpy as np
import csv


reader = csv.DictReader(open('results.csv'))
data = {}
while True:
    try:
        dictobj = next(reader) 
    except StopIteration:
        break
    upto_val = int(dictobj.pop("upto"))
    data[upto_val] = dictobj



sizes = sorted(data.keys())

algorithms = {
    "basic","better","cached","eratosthenes", "pritchard","atkin","sundaram"
}
algorithms = sorted(algorithms)

series = {algo:[] for algo in algorithms}

for size in sizes:
    for algo in algorithms:
        if algo in data[size]:
            v = float(data[size][algo])
            series[algo].append(v if v > 0 else np.nan)  # or clamp to really tiny value
        else:
            series[algo].append(np.nan)

figure = plt.figure(figsize=(10,6))

for algo in algorithms:
    plt.plot(sizes, series[algo], marker="o", label=algo)

plt.xscale("log")
plt.yscale("log")

plt.xlabel("Input Size (N)")
plt.ylabel("Processing Time (seconds)")

plt.title("Prime Generation Algorithms Performance Visualized")

ax = plt.gca()
ax.xaxis.set_major_formatter(ticker.ScalarFormatter())
ax.xaxis.set_minor_formatter(ticker.NullFormatter())
ax.ticklabel_format(style='plain', axis='x')
ax.set_xticks(sizes)

plt.legend()

plt.grid(True, which="both",linestyle="--",linewidth=0.5)

plt.tight_layout()

plt.show()

figure.savefig("graph.png")