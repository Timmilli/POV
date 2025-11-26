import re

# Fichier encoding.c à lire
ENC_FILE = "converted_images/encoding.h"

# Symboles à extraire pour afficher 15h12
SYMBOLS = ["c1n1", "c2n5", "c3n1", "c4n2"]

def extract_array(content, name):
    pattern = rf"const uint16_t {name}\[.*?\] PROGMEM = \{{(.*?)\}};"
    m = re.search(pattern, content, re.S)
    if not m:
        raise ValueError(f"Array {name} not found")
    block = m.group(1)
    lines = [x.strip().rstrip(",") for x in block.splitlines() if "0b" in x]
    values = [int(x, 2) for x in lines]
    return values

def to_binary_rows(values):
    rows = []
    for v in values:
        b = format(v, "016b")  # 16 bits
        rows.append([c for c in b])
    return rows

# Charge le fichier C
with open(ENC_FILE, "r") as f:
    content = f.read()

# Construit la matrice complète
full_matrix = []
for sym in SYMBOLS:
    arr = extract_array(content, sym)
    rows = to_binary_rows(arr)
    full_matrix.extend(rows)

# Écrit la matrice finale au format accepté par ton script
with open("barre_1512.txt", "w") as f:
    for row in full_matrix:
        f.write("{" + ",".join(f'"{x}"' for x in row) + "},\n")

print("Fichier barre_1512.txt généré.")
