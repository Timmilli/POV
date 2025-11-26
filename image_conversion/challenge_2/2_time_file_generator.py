#!/usr/bin/env python3

"""
Ce programme lit toutes les images PNG dans CHIFFRES_DIR.
Chaque image représente un motif à afficher sur le POV.

Règles :
- LED 1 = haut = MSB
- LED 16 = bas = LSB
- Les images doivent avoir la taille :
      hauteur = NUM_LEDS
      largeur = FINAL_RES / (2 * BOXES_NUMBER)
- Chaque pixel -> LED : 1 si pixel < 50, sinon 0
- Une image = une variable C uint16_t[], nommée comme le fichier
- On génère un seul header .h contenant toutes les matrices
"""

from PIL import Image
import math
import os
import glob

# === CONFIG ===

NUM_LEDS = 16               # LEDs vertically
THETA_RES = 3               # degrees per step
BOXES_NUMBER = 10           # 6 digits + 2 margins
FINAL_RES = int(360 / THETA_RES)

BASE_DIR = os.path.dirname(os.path.abspath(__file__))
CHIFFRES_DIR = os.path.join(BASE_DIR, "2_chiffres")
OUTPUT_DIR = os.path.join(BASE_DIR, "..", "converted_images", "challenge_2")
os.makedirs(OUTPUT_DIR, exist_ok=True)
OUTPUT_FILE = os.path.join(OUTPUT_DIR, f"encoding_{FINAL_RES}.h")

EXPECTED_WIDTH = FINAL_RES // (2 * BOXES_NUMBER)
THRESHOLD = 50

# === UTILS ===

def pixel_to_led(v):
    return "1" if v < THRESHOLD else "0"

# === MAIN ===

png_files = sorted(
    glob.glob(os.path.join(CHIFFRES_DIR, "*.png")),
    key=lambda x: os.path.basename(x)
)

with open(OUTPUT_FILE, "w") as f:
    first_matrix = True
    print("Jusqu'ici tout va bien")

    for png_file in png_files:
        image_name = os.path.splitext(os.path.basename(png_file))[0]

        # --- LOADING AND RESIZING ---
        im = Image.open(png_file).convert("L")
        im_resized = im.resize((EXPECTED_WIDTH, NUM_LEDS))  # NE PAS ÉCRASER l'image si tu veux garder l'original
        pixels = im_resized.load()

        display_matrix = []

        for y in range(NUM_LEDS):
            row = []
            for x in range(EXPECTED_WIDTH):
                row.append(pixel_to_led(pixels[x, y]))
            display_matrix.append(row)

        # --- WRITE HEADER START ---
        if first_matrix:
            number_of_positions = EXPECTED_WIDTH
            f.write(
                f"#ifndef __ENCODING_H_{FINAL_RES}__\n"
                f"#define __ENCODING_H_{FINAL_RES}__\n"
                f"#include \"constants.h\"\n"
                f"#include <avr/io.h>\n\n"
                f"#define NUMBER_OF_POSITIONS {number_of_positions}\n\n"
            )
            first_matrix = False

        # --- WRITE MATRIX ---
        matrix_name = image_name
        f.write(f"const uint16_t {matrix_name}[NUMBER_OF_POSITIONS] PROGMEM = " + "{\n")

        for idx, row in enumerate(display_matrix):
            row_str = "".join(str(b) for b in row)
            f.write(f"  0b{row_str}")
            if idx < len(display_matrix) - 1:
                f.write(",\n")
        f.write("\n}" + f";\n\n")

    f.write(f"#endif // __ENCODING_H_{FINAL_RES}__\n")

print(f"OK → {OUTPUT_FILE}")
