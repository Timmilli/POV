#!/usr/bin/env python3

"""
- Lire l'image alphabet.png
- NB colonnes = largeur image
- NB lignes = hauteur image
- Initialiser une matrice vide encoding_image en fonction de la taille de l'image
- Pour chaque ligne, chaque colonne, lire le pixel associé
- Si c'est noir, mettre 0, si c'est blanc, mettre 1
- Générer un fichier encoding.h

"""

#!/usr/bin/env python3
from PIL import Image
import os

# === CONFIG ===
IMAGE_FILE = "alphabet.png"
OUTPUT_FILE = "encoding.h"

def pixel_to_led(value):
    return "1" if value > 128 else "0"   # blanc → 1, noir → 0

# === LOAD IMAGE ===
im = Image.open(IMAGE_FILE).convert("L")
width, height = im.size
pixels = im.load()

# === BUILD MATRIX ===
display_matrix = []

for y in range(height):          # ligne = LED MSB → LSB (haut → bas)
    row = []
    for x in range(width):       # colonne = défilement POV
        row.append(pixel_to_led(pixels[x, y]))
    display_matrix.append(row)

# === WRITE encoding.h ===
matrix_name = "alphabet"  

with open(OUTPUT_FILE, "w") as f:

    # HEADER
    f.write(
        f"#ifndef __ALPHABET_H__\n"
        f"#define __ALPHABET_H__\n"
        f"#include \"constants.h\"\n"
        f"#include <avr/io.h>\n\n"
        f"#define TOTAL_SIZE {width}\n\n"
    )

    # MATRIX
    f.write(f"const uint16_t {matrix_name}[TOTAL_SIZE] PROGMEM = " + "{ \n")

    for idx, row in enumerate(display_matrix):
        row_str = "".join(row)
        f.write(f"  0b{row_str}")
        if idx < len(display_matrix) - 1:
            f.write(",\n")

    f.write("\n};\n\n")

    # FOOTER
    f.write(f"#endif //  __ALPHABET_H__\n")

print(f"OK → {OUTPUT_FILE} generated.")
