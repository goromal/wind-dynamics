import matplotlib.pyplot as plt
import numpy as np
from wind_dynamics import DrydenWind

t = 100.0
dt = 0.05
x_mean = 0.0
y_mean = 1.0
z_mean = 0.0
x_sigma = 10.0
y_sigma = 0.0
z_sigma = 70.0

plt.rcParams.update({
    "text.usetex": True,
    "font.family": "serif",
    "font.serif": ["Palatino"],
})

wind = DrydenWind()
wind.initialize(x_mean,  y_mean,  z_mean, 
                x_sigma, y_sigma, z_sigma, 2.0)

n = int(np.floor(t / dt)) + 1
x = np.linspace(0, t, n)
y = np.zeros((3,x.size))

for i in range(n):
    y[:,i] = wind.getWind(dt)

fig, axs = plt.subplots(3)
fig.suptitle('Dryden Gust Velocities\n$\sigma_x=%f$, $\sigma_y=%f$, $\sigma_z=%f$' % (x_sigma, y_sigma, z_sigma))
axs[0].plot([0, t],[x_mean, x_mean])
axs[0].plot(x, y[0,:])
axs[0].set_ylabel('X Velocity')
axs[1].plot([0, t],[y_mean, y_mean])
axs[1].plot(x, y[1,:])
axs[1].set_ylabel('Y Velocity')
axs[2].plot([0, t],[z_mean, z_mean])
axs[2].plot(x, y[2,:])
axs[2].set_ylabel('Z Velocity')
axs[2].set_xlabel('Time (s)')

plt.show()
