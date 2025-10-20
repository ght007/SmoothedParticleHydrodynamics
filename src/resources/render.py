import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib.animation import FuncAnimation

# === CONFIG ===
DATA_FILE = "C:\\Users\\pc\\CLionProjects\\untitled1\\src\\resources\\particle_positions.txt"
INTERVAL_MS = 200  # time between frames

# === LOAD DATA ===
data = np.loadtxt(DATA_FILE)

# Handle single-line files (1D array)
if data.ndim == 1:
    data = data[np.newaxis, :]  # make it 2D (1, N)

num_columns = data.shape[1]
if num_columns % 4 != 0:
    raise ValueError("Each particle must have 4 columns: x y z f")

num_particles = num_columns // 4
num_timesteps = data.shape[0]
print(f"Detected {num_particles} particles over {num_timesteps} timestep(s)")

# Reshape to (timesteps, particles, 4)
particles = data.reshape((num_timesteps, num_particles, 4))

# === SETUP PLOT ===
fig = plt.figure(figsize=(8, 6))
ax = fig.add_subplot(111, projection='3d')
scat = ax.scatter([], [], [], s=30, c='blue')

# Axis limits
x_min, x_max = data[:, 0::4].min(), data[:, 0::4].max()
y_min, y_max = data[:, 1::4].min(), data[:, 1::4].max()
z_min, z_max = data[:, 2::4].min(), data[:, 2::4].max()
ax.set_xlim(x_min, x_max)
ax.set_ylim(y_min, y_max)
ax.set_zlim(z_min, z_max)
ax.set_xlabel("X")
ax.set_ylabel("Y")
ax.set_zlabel("Z")

# === UPDATE FUNCTION ===
def update(frame_idx):
    frame = particles[frame_idx]
    # NOW: visible if f == 0
    visible = frame[frame[:, 3] == 0]
    scat._offsets3d = (visible[:, 0], visible[:, 1], visible[:, 2])
    ax.set_title(f"Particle Simulation (timestep={frame_idx})")
    return scat,

# === ANIMATE OR STATIC ===
if num_timesteps > 1:
    ani = FuncAnimation(fig, update, frames=num_timesteps,
                        interval=INTERVAL_MS, blit=False, repeat=True)
else:
    # Only one timestep — static plot
    update(0)

plt.show()
