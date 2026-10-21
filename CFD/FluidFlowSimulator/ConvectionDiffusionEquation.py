import numpy as np
import matplotlib.pyplot as plt

# Параметры сетки и физические константы
L = 1.0          # Длина домена
nx = 50          # Количество узлов сетки
dx = L / (nx - 1)
x = np.linspace(0, L, nx)

rho = 1.0        # Плотность
u = 1.0          # Скорость
Gamma = 0.05     # Коэффициент диффузии

# Граничные условия
phi_0 = 0.0      # Левая граница (x = 0)
phi_L = 1.0      # Правая граница (x = L)

# Инициализация матрицы коэффициентов A и правого вектора b
A = np.zeros((nx, nx))
b = np.zeros(nx)

# Задание граничных условий
A[0, 0] = 1.0
b[0] = phi_0

A[-1, -1] = 1.0
b[-1] = phi_L

# Интенсивность конвекции (F) и диффузии (D)
F = rho * u
D = Gamma / dx

# Заполнение внутренних узлов (схема Upwind)
for i in range(1, nx - 1):
    a_left = D + max(F, 0)
    a_right = D + max(-F, 0)
    a_center = a_left + a_right
    
    A[i, i - 1] = -a_left
    A[i, i] = a_center
    A[i, i + 1] = -a_right
    b[i] = 0.0

# Решение системы линейных уравнений
phi = np.linalg.solve(A, b)

# Визуализация результатов
plt.plot(x, phi, 'bo-', label='Числовое решение (Upwind)')
plt.xlabel('Координата x')
plt.ylabel('Фокусная переменная phi')
plt.title('1D Steady-State Convection-Diffusion')
plt.legend()
plt.grid(True)
plt.show()