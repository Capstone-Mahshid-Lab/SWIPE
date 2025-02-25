
import pandas as pd
import matplotlib.pyplot as plt

# Load CSV file
def plot_cv_from_csv(csv_file):
    # Read CSV (assuming no headers)
    df = pd.read_csv(csv_file, header=None)
    
    # Extract data
    index = df.iloc[:, 0]  # First column (index)
    y_values = df.iloc[:, 1]  # Second column (current values)
    
    # Calculate x-axis values using the given formula
    x_values = -abs(index % 400 - 200) * 700 / 200 + 500
    
    # Plot CV graph
    plt.figure(figsize=(8, 6))
    plt.plot(x_values, y_values, marker='o', linestyle='-', color='b')
    plt.xlabel("Potential (mV)")
    plt.ylabel("Current (uA)")
    plt.title("Cyclic Voltammetry (CV) Plot")
    plt.grid()
    plt.show()

# Example usage (replace 'data.csv' with your actual file path)
plot_cv_from_csv("C:/Users/Dell/Desktop/14g.csv")
