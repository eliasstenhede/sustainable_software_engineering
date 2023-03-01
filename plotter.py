import os
import matplotlib.pyplot as plt
import numpy as np


if __name__ == "__main__":
    violin_data = {"energy":[], "time":[]}
    labels = []
    benchmark_dir = "benchmarks" # Replace with your directory name
    for folder in os.listdir(benchmark_dir):
        folder_path = os.path.join(benchmark_dir, folder)
        if os.path.isdir(folder_path):
            energy_values = []
            time_values = []
            for file in os.listdir(folder_path):
                file_path = os.path.join(folder_path, file)
                if os.path.isfile(file_path) and file.endswith(".csv"):
                    with open(file_path, "r") as f:
                        for line in f:
                            if "Cumulative Processor Energy_0 (Joules)" in line:
                                energy_values.append(float(line.split("=")[-1].strip()))
                            if "Total Elapsed Time (sec)" in line:
                                time_values.append(float(line.split("=")[-1].strip()))
        violin_data["energy"].append(energy_values)
        violin_data["time"].append(time_values)
        labels.append(folder)
    
    fig, ax = plt.subplots()
    ax.set_title('Benchmarks of energy consumption')
    ax.set_xlabel('Language')
    ax.set_ylabel('Cumulative Processor Energy [J]')
    ax.set_yscale('log')
    ax.grid(True)
    ax.violinplot(violin_data["energy"], showmedians=True, showextrema=True)

    # Add x-axis labels
    x_pos = np.arange(len(labels))+1
    ax.set_xticks(x_pos)
    ax.set_xticklabels(labels)

    # Show the plot
    plt.show()
    
    fig, ax = plt.subplots()
    ax.set_title('Correlation Between Time Elapsed and Energy Consumption')
    ax.set_xlabel('Time Elapsed [S]')
    ax.set_ylabel('Cumulative Processor Energy [J]')
    ax.set_yscale('log')
    ax.set_xscale('log')
    ax.grid(True)
    for i in range(3):
        ax.scatter(violin_data["time"][i], violin_data["energy"][i], label=labels[i])
    ax.legend()

    # Show the plot
    plt.show()
