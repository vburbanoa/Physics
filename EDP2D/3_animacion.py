import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

# Función para cargar datos
def cargar_datos(tipo, num_archivos=26):
    data = []
    for i in range(num_archivos):
        filename = f"{tipo}/t_{i * 100}.txt"
        data.append(np.genfromtxt(filename, delimiter=" "))
    return data

# Función para configurar la figura y los ejes
def configurar_figura_ax(data, vmin, vmax, levels, cmap):
    fig, ax = plt.subplots()
    cont = ax.contourf(X, Y, data[0], vmin=vmin, vmax=vmax, levels=levels, cmap=cmap)
    cbar = fig.colorbar(cont, ax=ax, label="T(°C)")
    return fig, ax

# Función de animación general
def animate(i, ax, data, vmin, vmax, levels, cmap):
    ax.clear()
    cont = ax.contourf(X, Y, data[i], vmin=vmin, vmax=vmax, levels=levels, cmap=cmap)
    ax.set_title(f"Temperatura en t = {i * 100} segundos")
    ax.set_xlabel("x (m)")
    ax.set_ylabel("y (m)")
    return cont

x = np.linspace(0, 1, 100)
y = np.linspace(0, 1, 100)
X, Y = np.meshgrid(x, y)

vmin = 50
vmax = 59
levels = np.arange(vmin, vmax, 0.1)
cmap = "hot"

# Cargar datos para cada tipo de frontera
data_fija = cargar_datos("fija")
data_abierta = cargar_datos("abierta")
data_periodica = cargar_datos("periodica")

# Configurar figura y ejes para cada animación
fig_fija, ax_fija = configurar_figura_ax(data_fija, vmin, vmax, levels, cmap)
fig_abierta, ax_abierta = configurar_figura_ax(data_abierta, vmin, vmax, levels, cmap)
fig_periodica, ax_periodica = configurar_figura_ax(data_periodica, vmin, vmax, levels, cmap)

# Crear animaciones
anim_fija = animation.FuncAnimation(fig_fija, animate, fargs=(ax_fija, data_fija, vmin, vmax, levels, cmap), frames=20, interval=10, blit=False, repeat=True)
anim_abierta = animation.FuncAnimation(fig_abierta, animate, fargs=(ax_abierta, data_abierta, vmin, vmax, levels, cmap), frames=20, interval=10, blit=False, repeat=True)
anim_periodica = animation.FuncAnimation(fig_periodica, animate, fargs=(ax_periodica, data_periodica, vmin, vmax, levels, cmap), frames=12, interval=10, blit=False, repeat=True)

# Guardar animaciones
anim_fija.save('fija.gif', writer='imagemagick', fps=2)
anim_abierta.save('abierta.gif', writer='imagemagick', fps=2)
anim_periodica.save('periodica.gif', writer='imagemagick', fps=2)
