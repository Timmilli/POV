#!/usr/bin/env python3
"""
Convert a circular 32*32 PNG image into a monochrome table for a 16-LED POV display.
White pixels → LED off, Black pixels → LED on.
Compatible with Python 3 and Pillow.
"""

from PIL import Image
import math
import sys
import os

# === CONFIGURATION ===
NAME = "barre"
NUM_LEDS = 16               # Number of LEDs per POV bar
THETA_RES = 6               # Angular resolution in degrees, to update
BASE_DIR = os.path.dirname(os.path.abspath(__file__))  # Folder containing the script
IMG_PATH = os.path.join(BASE_DIR, "rough_images", f"{NAME}.png")

EXPECTED_SIZE = (NUM_LEDS * 2, NUM_LEDS * 2)

# === LOAD IMAGE ===
try:
    im = Image.open(IMG_PATH).convert("L")  # grayscale
except FileNotFoundError:
    sys.exit(f"Error: File not found → {IMG_PATH}")

# Rotate 90° counterclockwise and mirror
im = im.rotate(90, expand=True)
im = im.transpose(Image.FLIP_LEFT_RIGHT)

w, h = im.size
if (w, h) != EXPECTED_SIZE:
    sys.exit(f"Error: Image must be {EXPECTED_SIZE[0]}x{EXPECTED_SIZE[1]} pixels, not {w}x{h}")

pixels = im.load()
center = (w - 1) / 2.0

# === CREATE MATRIX ===
num_angles = int(360 / THETA_RES)
display_matrix = [[0] * NUM_LEDS for _ in range(num_angles)]

def pixel_to_led(value):
    """
    Convert a grayscale pixel value (0-255) to LED state.
    0 (black) -> LED on ('1')
    255 (white) -> LED off ('0')
    """
    return "1" if value < 128 else "0"

def safe_pixel(x, y):
    """Return the pixel value within image bounds."""
    x = max(0, min(w - 1, int(round(x))))
    y = max(0, min(h - 1, int(round(y))))
    return pixels[x, y]

# === MAIN LOOP ===
for j, theta in enumerate(range(0, 360, THETA_RES)):
    angle_rad = math.radians(theta)
    for r in range(NUM_LEDS):
        r_prime = r + 0.5 
        x = r_prime * math.cos(angle_rad) + center
        y = -r_prime * math.sin(angle_rad) + center
        display_matrix[j][r] = pixel_to_led(safe_pixel(x, y))

# === WRITE OUTPUT FILE ===
OUTPUT_DIR = os.path.join(BASE_DIR, "converted_images")
os.makedirs(OUTPUT_DIR, exist_ok=True)  # creates directory if it doesn't exist

OUTPUT_FILE = os.path.join(OUTPUT_DIR, f"{NAME}.h")

with open(OUTPUT_FILE, "w") as f:
    f.write(f"#ifndef __ENCODING_H__ \n#define __ENCODING_H__ \n#include \"constants.h\" \n#include <avr/io.h> \n\n#define NUMBER_OF_POSITIONS {len(display_matrix)}")
    f.write(f"\nconst uint16_t led_list[NUMBER_OF_POSITIONS] PROGMEM = " + "{ \n")
    for idx, row in enumerate(display_matrix):
        row_str = "".join(row)
        f.write(f"  0b{row_str}")
        if idx < len(display_matrix) - 1:
            f.write(",\n")
    f.write("\n};\n")

print(f"Success: File generated → {OUTPUT_FILE}")
