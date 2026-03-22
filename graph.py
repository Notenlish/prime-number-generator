import matplotlib.pyplot as plt
import numpy as np

data = {
    10_000: {
        "basic":0.009,
        "better":0.0,
        "cached":0.002,
        "eratosthenes":0.0,
        "pritchard":0.002,
        "atkin":0.0,
        "sundaram":0.0
    },
    50_000: {
        "basic":0.17,
        "better":0.002,
        "cached":0.008,
        "eratosthenes":0.001,
        "pritchard":0.019,
        "atkin":0.001,
        "sundaram":0.0
    },
    100_000: {
        "basic":0.684,
        "better":0.006,
        "cached":0.024,
        "eratosthenes":0.002,
        "pritchard":0.047,
        "atkin":0.001,
        "sundaram":0.001
    },
    250_000: {
        "basic":4.213,
        "better":0.045,
        "cached":0.166,
        "eratosthenes":0.011,
        "pritchard":0.223,
        "atkin":0.004,
        "sundaram":0.005
    },
    500_000: {
        "basic":14.22,
        "better":0.053,
        "cached":0.204,
        "eratosthenes":0.013,
        "pritchard":0.412,
        "atkin":0.007,
        "sundaram":0.007
    },
    1_000_000: {
        "basic":52.795,
        "better":0.131,
        "cached":0.529,
        "eratosthenes":0.024,
        "pritchard":1.072,
        "atkin":0.015,
        "sundaram":0.016
    },
    2_000_000: {
        "better":0.337,
        "cached":1.404,
        "eratosthenes":0.051,
        "pritchard":2.833,
        "atkin":0.036,
        "sundaram":0.027
    },
    4_000_000: {
        "better":0.946,
        "cached":3.712,
        "eratosthenes":0.104,
        "pritchard":7.871,
        "atkin":0.078,
        "sundaram":0.062
    }
}

sizes = sorted(data.keys())

algorithms = {
    "basic","better","cached","eratosthenes", "pritchard","atkin","sundaram"
}
algorithms = sorted(algorithms)

series = {algo:[] for algo in algorithms}

for size in sizes:
    for algo in algorithms:
        if algo in data[size]:
            series[algo].append(data[size][algo])
        else:
            series[algo].append(np.nan)

plt.figure(figsize=(10,6))

for algo in algorithms:
    plt.plot(sizes, series[algo], marker="o", label=algo)

plt.xscale("log")
plt.yscale("log")

plt.xlabel("Input Size (N)")
plt.ylabel("Processing Time (seconds)")

plt.title("Prime Generation Algorithms Performance Visualized")

plt.legend()

plt.grid(True, which="both",linestyle="--",linewidth=0.5)

plt.tight_layout()

plt.show()