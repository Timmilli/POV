#!/usr/bin/env python3
"""
Convert a set of 32x32 PNG images into monochrome tables for a 16-LED POV display.
Generates one matrix per image, with names like c1n0, c2n3, etc.
"""

from PIL import Image
import math
import os
import glob

# === CONFIGURATION ===

NUM_LEDS = 16               # Number of LEDs per POV bar
THETA_RES = 12               # Angular resolution in degrees
FINAL_RES = int(360 / THETA_RES)

BASE_DIR = os.path.dirname(os.path.abspath(__file__))
CHIFFRES_DIR = os.path.join(BASE_DIR, "3_chiffres")
OUTPUT_DIR = os.path.join(BASE_DIR, "..", "converted_images", "challenge_3")
os.makedirs(OUTPUT_DIR, exist_ok=True)
OUTPUT_FILE = os.path.join(OUTPUT_DIR, f"encoding_{FINAL_RES}.h")

EXPECTED_SIZE = (NUM_LEDS * 2, NUM_LEDS * 2)

# === UTILITAIRES ===

def pixel_to_led(value):
    """Convert a grayscale pixel value (0-255) to LED state: '0' off, '1' on"""
    return "1" if value < 80 else "0"

def safe_pixel(pixels, w, h, x, y):
    """Return the pixel value within image bounds."""
    x = max(0, min(w - 1, int(round(x))))
    y = max(0, min(h - 1, int(round(y))))
    return pixels[x, y]

# === PARCOURIR LES SOUS-DOSSIERS ET IMAGES ===

subfolders = sorted(glob.glob(os.path.join(CHIFFRES_DIR, "*")),
key=lambda x: int(os.path.basename(x)))  # tri numérique des dossiers

with open(OUTPUT_FILE, "w") as f:
    first_matrix = True

    for folder_path in subfolders:
        folder_name = os.path.basename(folder_path)
        png_files = sorted(glob.glob(os.path.join(folder_path, "*.png")),
                        key=lambda x: int(os.path.splitext(os.path.basename(x))[0]))  # tri numérique des fichiers

        for png_file in png_files:
            image_name = os.path.splitext(os.path.basename(png_file))[0]

            # --- CHARGEMENT IMAGE ---
            im = Image.open(png_file).convert("L")
            im = im.rotate(90, expand=True)
            w, h = im.size
            if (w, h) != EXPECTED_SIZE:
                print(f"Warning: {png_file} ignored (wrong size {w}x{h})")
                continue

            pixels = im.load()
            center = (w - 1) / 2.0

            # --- GENERATION MATRICE ---
            num_angles = int(360 / THETA_RES)
            display_matrix = [[0] * NUM_LEDS for _ in range(num_angles)]
            for j, theta in enumerate(range(0, 360, THETA_RES)):
                angle_rad = math.radians(theta)
                for r in range(NUM_LEDS):
                    r_prime = r + 0.5
                    x = r_prime * math.cos(angle_rad) + center
                    y = -r_prime * math.sin(angle_rad) + center
                    display_matrix[j][r] = pixel_to_led(safe_pixel(pixels, w, h, x, y))

            # --- NOM DE LA MATRICE ---
            matrix_name = f"c{folder_name}n{image_name}"

            if first_matrix:
                number_of_positions = len(display_matrix)
                f.write(
                f"#ifndef __ENCODING_H_{FINAL_RES}__\n"
                f"#define __ENCODING_H_{FINAL_RES}__\n"
                f"#include \"constants.h\"\n"
                f"#include <avr/io.h>\n\n"
                f"#include <avr/pgmspace.h>\n\n"
                f"#define NUMBER_OF_POSITIONS {number_of_positions}\n\n"
            )
                first_matrix = False

            # --- ECRITURE DANS LE FICHIER ---
            f.write(f"const uint16_t {matrix_name}[NUMBER_OF_POSITIONS] PROGMEM = " + "{" + "\n")
            for idx, row in enumerate(display_matrix):
                row_str = "".join(str(b) for b in row)
                f.write(f"  0b{row_str}")
                if idx < len(display_matrix) - 1:
                    f.write(",\n")
            f.write("\n}" + f";\n#define {matrix_name.upper()} {matrix_name}\n\n")

    f.write(f"#endif // __ENCODING_H_{FINAL_RES}__\n")

print(f"Success: File generated → {OUTPUT_FILE}")
