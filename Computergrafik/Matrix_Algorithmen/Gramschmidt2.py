import numpy as np

def gram_schmidt(vectors, tol=1e-10):

    #Rückgabe:
    #Liste von orthonormalen Vektoren (NumPy-Arrays)
    #ValueError bei linearer Abhängigkeit

    orthonormal_basis = []

    for v in vectors:
        v = np.array(v, dtype=float)

        # Orthogonalisierung
        for u in orthonormal_basis:
            v = v - np.dot(v, u) * u # np.dot berechnet das skalar Produkt, es wird sonst wie inder Vorlesung gezeigt gerechnet

        norm = np.linalg.norm(v) # berechnet die normale

        if norm < tol:                                                           # optimalerweise müsste hier if norm = 0 stehen dann sind Vektorenabhängig aber Rundungsfehler können enstehen
            raise ValueError("Die eingegebenen Vektoren sind linear abhängig.")

        # Normierung
        v = v / norm
        orthonormal_basis.append(v)

    return orthonormal_basis

u_vectors = [
    [1, -1, 1],
    [1, 0, 1],
    [1, 1, 2]
]

basis = gram_schmidt(u_vectors)

for i, v in enumerate(basis, 1):
    print(f"e{i} = {[f'{x:.2f}' for x in v]}")