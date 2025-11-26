#!/usr/bin/env python3
"""
Static circular visualization of a 16-LED POV matrix.
Each LED is plotted at its corresponding angle and radius.
"""

import matplotlib.pyplot as plt
import math
import os

# === CONFIGURATION ===
BASE_DIR = os.path.dirname(os.path.abspath(__file__))
OUTPUT_DIR = os.path.join(BASE_DIR, "converted_images")
MATRIX_FILE = os.path.join(OUTPUT_DIR, "test.txt")
NUM_LEDS = 16
THETA_RES = 3  

# === LOAD MATRIX ===
def load_matrix(file_path):
    matrix = []
    with open(file_path, "r") as f:
        for line in f:
            line = line.strip()
            if line.startswith("{") and line.endswith("},"):
                row = line[1:-2].split(",")
                row = [x.strip().strip('"') for x in row]
                matrix.append(row)
            elif line.startswith("{") and line.endswith("}"):
                row = line[1:-1].split(",")
                row = [x.strip().strip('"') for x in row]
                matrix.append(row)
    return matrix

# === MAIN ===
matrix = load_matrix(MATRIX_FILE)
num_angles = len(matrix)

# Convert to polar coordinates
theta_vals = []  # angle in radians
r_vals = []      # radius
for j, row in enumerate(matrix):
    angle_rad = math.radians(j * THETA_RES)
    for r_index, val in enumerate(row):
        if val == "1":  # LED on
            r = r_index + 0.5
            theta_vals.append(angle_rad)
            r_vals.append(r)

# === PLOT ===
plt.figure(figsize=(6,6))
ax = plt.subplot(111, polar=True)
ax.set_theta_direction(1)  # anticlockwise
ax.set_theta_zero_location("N")  # 0° at the top
ax.scatter(theta_vals, r_vals, c='black', s=50)  # draw points for LEDs
ax.set_rticks(range(0, NUM_LEDS+1))  # optional radial ticks
ax.set_rmax(NUM_LEDS)
ax.set_axis_off()  # hide axes for better POV look
plt.show()
