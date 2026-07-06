import numpy as np

def gram_schmidt(u_vectors, tol=1e-10):
    """
    u_vectors: Liste von Vektoren [u1, u2, u3] (NumPy-Arrays oder Listen)
    np.dot ist das Skalarprodukt
    """
    u1, u2, u3 = [np.array(v, dtype=float) for v in u_vectors]

    # v1
    v1 = u1
    norm_v1 = np.linalg.norm(v1)
    if norm_v1 < tol:                  # optimalerweise müsste hier if norm = 0 stehen dann sind Vektorenabhängig aber Rundungsfehler können enstehen
        raise ValueError("Vektor u1 ist Nullvektor.")
    e1 = v1 / norm_v1

    # v2
    proj_v1_u2 = (np.dot(u2, v1) / np.dot(v1, v1)) * v1
    v2 = u2 - proj_v1_u2
    norm_v2 = np.linalg.norm(v2)
    if norm_v2 < tol:
        raise ValueError("Die Vektoren sind linear abhängig.")
    e2 = v2 / norm_v2

    # v3
    proj_v1_u3 = (np.dot(u3, v1) / np.dot(v1, v1)) * v1
    proj_v2_u3 = (np.dot(u3, v2) / np.dot(v2, v2)) * v2
    v3 = u3 - proj_v1_u3 - proj_v2_u3
    norm_v3 = np.linalg.norm(v3)
    if norm_v3 < tol:
        raise ValueError("Die Vektoren sind linear abhängig.")
    e3 = v3 / norm_v3

    return [e1, e2, e3]

# Beispiel-Eingabe
u_vectors =  [
    [1, -1, 1],
    [1, 0, 1],
    [1, 1, 2] ]

#u_vectors =  [
#    [1, 0, 0],
#   [2, 0, 0],
#   [3, 0, 0] ]

# Gram-Schmidt anwenden
orthonormal_basis = gram_schmidt(u_vectors)

# Ausgabe
for i, v in enumerate(orthonormal_basis, 1):
    print(f"e{i} = {[f'{x:.2f}' for x in v]}")

