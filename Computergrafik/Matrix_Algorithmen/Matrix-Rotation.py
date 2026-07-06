import numpy as np
#Aufgabe in Python
# Winkel
angle_deg = 135
# winkel zu bogenmaß
angle_rad = np.deg2rad(angle_deg) # entspricht mathtoradions in ejml

# Rotationsmatrizen:
#x 1    0       0
#x 0 cos_angle -sin_angle
#x 0 sin_angle cos_angle

#y cos_angle 0 sin_angle
#y   0       1    0
#y-sin_angle 0 cos_angle

#z  cos_angle -sin_angle 0
#z  sin_angle cos_angle  0
#z    0          0       1
# z wählen da um z-Achse gedreht werden soll

Rz = np.array([
    [np.cos(angle_rad), -np.sin(angle_rad), 0],
    [np.sin(angle_rad),  np.cos(angle_rad), 0],
    [0,                  0,                 1]
])

# Vektor
v = np.array([2, 1, 5])

# Rotation
Result = Rz @ v   # Hier wird Matrix * vektor gerechnet (M @ V)

print(Result)


