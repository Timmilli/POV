import re
import matplotlib.pyplot as plt
import math
import os

# === CONFIG ===
BASE_DIR = os.path.dirname(os.path.abspath(__file__))
OUTPUT_DIR = os.path.join(BASE_DIR, "..", "converted_images", "challenge_2")
ENC_FILE = os.path.join(OUTPUT_DIR, "encoding_120.h") 

# Exemple : "15:12" → unités secondes, dizaines secondes, ":", unités minutes, dizaines minutes, ":", unités heures, dizaines heures
SYMBOL_ORDER = [
    "s_units", "s_tens", "colon",
    "m_units", "m_tens", "colon",
    "h_units", "h_tens"
]

# === UTIL ===
def extract_array(content, name):
    """Extrait un tableau binaire de l'encodage C et retourne une liste d'entiers"""
    pattern = rf"const uint16_t {name}\[.*?\] PROGMEM = \{{(.*?)\}};"
    m = re.search(pattern, content, re.S)
    if not m:
        raise ValueError(f"Array {name} not found")
    block = m.group(1)
    lines = [x.strip().rstrip(",") for x in block.splitlines() if "0b" in x]
    return [int(x, 2) for x in lines]

def to_binary_rows(values, num_leds=16):
    """Convertit une liste d'entiers en liste de listes de 0/1 string par ligne"""
    rows = []
    for v in values:
        b = format(v, f"0{num_leds}b")
        rows.append([c for c in b])
    return rows

def make_empty_matrix(height, width):
    """Crée une matrice vide (espace)"""
    return [["0"] * width for _ in range(height)]

# === READ ENC FILE ===
with open(ENC_FILE, "r") as f:
    content = f.read()

# === BUILD CONCATENATED MATRIX ===
# On récupère la résolution depuis le nom de fichier (après "_")
resolution = int(ENC_FILE.split("_")[-1].split(".")[0])
num_leds = 16
height = num_leds
full_matrix = []

# Largeurs spéciales
space_width = resolution // 20
trail_space_width = resolution // 4
symbol_width = resolution // 4

# Exemple : tu peux remplacer ces noms par les vrais symboles dans ton encoding.h
symbol_names = {
    "s_units": "0",
    "s_tens": "1",
    "m_units": "2",
    "m_tens": "3",
    "h_units": "4",
    "h_tens": "5",
    "colon": "6"  # si tu as un symbole ":" en index 6
}

# Crée une matrice vide pour concaténation ligne par ligne
full_matrix = [[] for _ in range(height)]

# Fonction pour concaténation ligne par ligne
def append_matrix(matrix, target_matrix):
    for i, row in enumerate(matrix):
        target_matrix[i].extend(row)

# 1. espace de départ
append_matrix(make_empty_matrix(height, trail_space_width), full_matrix)

# 2. symbole ou espace intermédiaire
for key in SYMBOL_ORDER:
    append_matrix(make_empty_matrix(height, space_width), full_matrix)  # marge
    arr = extract_array(content, symbol_names[key])
    rows = to_binary_rows(arr)
    append_matrix(rows, full_matrix)

# 3. espace de fin
append_matrix(make_empty_matrix(height, trail_space_width), full_matrix)

# === PLOT POLAR ===
theta_vals = []
r_vals = []
for x, row in enumerate(full_matrix[0]):  # largeur = nombre de colonnes
    for y in range(height):
        if full_matrix[y][x] == "1":
            theta_rad = math.radians(x * 360 / len(full_matrix[0]))
            r_vals.append(height - y - 0.5)  # y=0 → LED la plus haute
            theta_vals.append(theta_rad)

plt.figure(figsize=(6,6))
ax = plt.subplot(111, polar=True)
ax.set_theta_direction(-1)
ax.set_theta_zero_location("N")
ax.scatter(theta_vals, r_vals, c='black', s=50)
ax.set_rticks(range(0, num_leds+1))
ax.set_rmax(num_leds)
ax.set_axis_off()
plt.show()
