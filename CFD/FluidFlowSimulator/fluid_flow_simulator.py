import numpy as np
import matplotlib.pyplot as plt

def main():
    # Grid dimensions & parameters
    Nx, Ny = 300, 100       # Domain size
    tau = 0.6               # Relaxation time (viscosity = (tau - 0.5)/3)
    Nt = 3000               # Total timesteps
    
    # Lattice velocities (D2Q9 model)
    cxs = np.array([0, 0, 1, 1, 1, 0, -1, -1, -1])
    cys = np.array([0, 1, 1, 0, -1, -1, -1, 0, 1])
    weights = np.array([4/9, 1/9, 1/36, 1/9, 1/36, 1/9, 1/36, 1/9, 1/36])
    
    # Initial conditions (uniform rightward velocity)
    f = np.ones((Ny, Nx, 9)) * weights
    u0 = 0.04
    f[:, :, [2, 3, 4]] += 2 * u0 * weights[[2, 3, 4]]
    
    # Obstacle: Cylinder placed off-center
    cy, cx, r = Ny // 2, Nx // 4, Ny // 10
    y, x = np.ogrid[:Ny, :Nx]
    obstacle = (x - cx)**2 + (y - cy)**2 <= r**2

    # Matplotlib Setup for real-time visualization
    plt.ion()
    fig, ax = plt.subplots(figsize=(10, 4))
    
    # Main Simulation Loop
    for it in range(Nt):
        # 1. Streaming (shift populations along velocity vectors)
        for i, (cx_i, cy_i) in enumerate(zip(cxs, cys)):
            f[:, :, i] = np.roll(f[:, :, i], shift=(cy_i, cx_i), axis=(0, 1))
            
        # 2. Boundary Condition: No-slip on obstacle (bounce-back)
        bndry = f[obstacle, :]
        f[obstacle, :] = bndry[:, [0, 5, 6, 7, 8, 1, 2, 3, 4]]
        
        # 3. Macroscopic quantities (Density & Velocity)
        rho = np.sum(f, axis=2)
        ux = np.sum(f * cxs, axis=2) / rho
        uy = np.sum(f * cys, axis=2) / rho
        
        # Enforce inflow / outflow conditions
        ux[:, 0] = u0
        uy[:, 0] = 0
        rho[:, 0] = 1
        
        # 4. Collision step (BGK approximation towards equilibrium)
        f_eq = np.zeros_like(f)
        for i, (cx_i, cy_i, w) in enumerate(zip(cxs, cys, weights)):
            u_dot_c = cx_i * ux + cy_i * uy
            u_sq = ux**2 + uy**2
            f_eq[:, :, i] = w * rho * (1 + 3 * u_dot_c + 4.5 * u_dot_c**2 - 1.5 * u_sq)
            
        f += -(1.0 / tau) * (f - f_eq)
        
        # Zero out velocities inside the obstacle for rendering
        ux[obstacle] = 0
        uy[obstacle] = 0
        
        # Render frame every 20 iterations
        if it % 20 == 0:
            vel_magnitude = np.sqrt(ux**2 + uy**2)
            ax.clear()
            ax.imshow(vel_magnitude, cmap='twilight', origin='lower')
            ax.add_patch(plt.Circle((cx, cy), r, color='black'))
            ax.set_title(f"Fluid Flow Simulation (LBM) - Step {it}")
            ax.set_axis_off()
            plt.pause(0.001)

    plt.ioff()
    plt.show()

if __name__ == "__main__":
    main()