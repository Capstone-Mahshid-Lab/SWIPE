import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

def plot_cv_from_csv(csv_file):
    df = pd.read_csv(csv_file, header=None)
    
    index = df.iloc[:, 0]  # Step index
    y_values = df.iloc[:, 1]  # Current values

    # Define parameters
    num_steps = 400
    V_start = -0.5
    V_end = 0.5

    # Create a true triangle wave for voltage
    half_cycle = np.linspace(V_start, V_end, num_steps // 2)
    x_values = np.concatenate([half_cycle, half_cycle[::-1]])  # Forward + Reverse

    # Repeat pattern if needed
    x_values = np.tile(x_values, len(index) // num_steps + 1)[:len(index)]

    # Plot CV graph
    plt.figure(figsize=(8, 6))
    plt.plot(x_values, y_values, marker='o', linestyle='-', color='b')
    plt.xlabel("Potential (V)")
    plt.ylabel("Current (uA)")
    plt.title("Cyclic Voltammetry (CV) Plot")
    plt.grid()
    plt.show()

# Run the function
plot_cv_from_csv("C:/Users/Dell/Desktop/15e.csv")
