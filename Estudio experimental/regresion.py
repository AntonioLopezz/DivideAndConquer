import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from scipy import stats

# 1. Leer CSV y limpiar nombres de columnas
df = pd.read_csv('resultados_tiempos.csv')
df.columns = df.columns.str.strip() # Quita espacios por si acaso

# 2. Calcular variables auxiliares para las regresiones
df['n'] = df['Longitud(n)']
# OJO: Para nuestro Mejor Caso la complejidad teórica es log(n)
df['logn'] = np.log2(df['Longitud(n)']) 

# --- REGRESIÓN PARA PEOR CASO: T(n) vs n ---
# Nuestro peor caso es lineal: O(n)
slope_peor, intercept_peor, r_peor, p_peor, _ = stats.linregress(df['n'], df['DyV_Peor(ms)'])

# --- REGRESIÓN PARA MEJOR CASO: T(n) vs log(n) ---
# Nuestro mejor caso (con poda) es logarítmico: O(log n)
slope_mejor, intercept_mejor, r_mejor, p_mejor, _ = stats.linregress(df['logn'], df['DyV_Mejor(ms)'])

# Resultados por consola
print("   Regresión lineal PeorCaso ~ n")
print(f"  Pendiente: {slope_peor:.6e}")
print(f"  R²: {r_peor**2:.4f}")
print(f"  MSE: {np.mean((df['DyV_Peor(ms)'] - (slope_peor * df['n'] + intercept_peor))**2):.4f}")
print(f"  p-valor: {p_peor:.4e}\n")

print("   Regresión lineal MejorCaso ~ log n")
print(f"  Pendiente: {slope_mejor:.6e}")
print(f"  R²: {r_mejor**2:.4f}")
print(f"  MSE: {np.mean((df['DyV_Mejor(ms)'] - (slope_mejor * df['logn'] + intercept_mejor))**2):.4f}")
print(f"  p-valor: {p_mejor:.4e}")

# ==========================================
# GRÁFICAS (ESCALA LOGARÍTMICA EN EJE X)
# ==========================================

# 1. Gráfico de dispersión sin ajuste (Escala Log)
plt.figure()
plt.scatter(df['n'], df['DyV_Mejor(ms)'], label='MejorCaso', marker='o')
plt.scatter(df['n'], df['DyV_Peor(ms)'], label='PeorCaso', marker='x')
plt.xscale('log', base=2)
from matplotlib.ticker import FormatStrFormatter
plt.gca().xaxis.set_major_formatter(FormatStrFormatter('$2^{%d}$'))
plt.xlabel('n')
plt.ylabel('Tiempo (ms)')
plt.title('Mejor y Peor Caso (Eje X Logarítmico)')
plt.legend()
plt.grid(True)
plt.savefig('scatter_plot_log.pdf')

# 2. Ajuste Peor Caso ~ Θ(n) (Escala Log)
plt.figure()
plt.plot(df['n'], df['DyV_Peor(ms)'], 'x', label='PeorCaso')
plt.plot(df['n'], slope_peor * df['n'] + intercept_peor, label=r'Ajuste $\Theta(n)$')
plt.xscale('log', base=2)
from matplotlib.ticker import FormatStrFormatter
plt.gca().xaxis.set_major_formatter(FormatStrFormatter('$2^{%d}$'))
plt.xlabel('n')
plt.ylabel('Tiempo (ms)')
plt.title(r'Peor caso $\sim \Theta(n)$')
plt.legend()
plt.grid(True)
plt.savefig('ajuste_peor_log.pdf')

# ==========================================
# GRÁFICAS (ESCALA NORMAL)
# ==========================================

# 3. Gráfico de dispersión sin ajuste (Escala Normal)
plt.figure()
plt.scatter(df['n'], df['DyV_Mejor(ms)'], label='MejorCaso', marker='o')
plt.scatter(df['n'], df['DyV_Peor(ms)'], label='PeorCaso', marker='x')
plt.xlabel('n')
plt.ylabel('Tiempo (ms)')
plt.title('Mejor y Peor Caso')
plt.legend()
plt.grid(True)
plt.savefig('scatter_plot.pdf')

# 4. Ajuste Peor caso ~ Θ(n) (Escala Normal)
plt.figure()
plt.plot(df['n'], df['DyV_Peor(ms)'], 'x', label='PeorCaso')
plt.plot(df['n'], slope_peor * df['n'] + intercept_peor, label=r'Ajuste $\Theta(n)$')
plt.xlabel('n')
plt.ylabel('Tiempo (ms)')
plt.title(r'Peor caso $\sim \Theta(n)$')
plt.legend()
plt.grid(True)
plt.savefig('ajuste_peor.pdf')

# 5. Ajuste Mejor caso ~ Θ(log n) (Escala Log)
# Se hace aparte para que se vea bien, ya que los tiempos son muy bajos
plt.figure()
plt.plot(df['n'], df['DyV_Mejor(ms)'], 'o', label='MejorCaso')
plt.plot(df['n'], slope_mejor * df['logn'] + intercept_mejor, label=r'Ajuste $\Theta(\log n)$')
plt.xscale('log', base=2)
from matplotlib.ticker import FormatStrFormatter
plt.gca().xaxis.set_major_formatter(FormatStrFormatter('$2^{%d}$'))
plt.xlabel('n')
plt.ylabel('Tiempo (ms)')
plt.title(r'Mejor caso $\sim \Theta(\log n)$')
plt.legend()
plt.grid(True)
plt.savefig('ajuste_mejor_log.pdf')