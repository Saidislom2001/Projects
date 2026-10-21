"""
Arc-Length (Riks/Crisfield, cylindrical, psi=0) method for a 1-DOF nonlinear spring.

    F_int(u) = 1000*u - 40*u^3          (softening / snap-through spring)
    K_T(u)   = dF_int/du = 1000 - 120*u^2
    R(u, lam) = F_int(u) - lam*Pref

We trace the full equilibrium path (u, lam), including past the limit point,
by stepping a fixed arc-length radius `dl` each increment and solving the
resulting scalar quadratic for the load-factor increment.
"""

import numpy as np

# ---------------------------------------------------------------
# 1. Problem definition
# ---------------------------------------------------------------
def F_int(u):
    return 1000*u - 40*u**3

def K_T(u):
    return 1000 - 120*u**2

Pref = 2000.0      # reference load
dl   = 1.0         # arc-length radius per increment
tol  = 1e-8        # residual tolerance
max_iter = 30
n_increments = 8

# ---------------------------------------------------------------
# 2. Path storage
# ---------------------------------------------------------------
u_path, lam_path = [0.0], [0.0]
u, lam = 0.0, 0.0
prev_du_dir = 1.0     # sign of the last converged total du (defines "forward")

# ---------------------------------------------------------------
# 3. Arc-length increments
# ---------------------------------------------------------------
for step in range(n_increments):

    # ---- Predictor: move along the tangent, onto the arc-length circle ----
    Kt0  = K_T(u)
    du_t = Pref / Kt0                         # tangential du per unit dlam
    # choose sign of dlam so the predicted du continues in prev_du_dir
    dlam = dl / abs(du_t) * np.sign(prev_du_dir * du_t)
    du   = dlam * du_t

    u_i, lam_i   = u + du, lam + dlam
    du_total     = du                          # cumulative du for this step

    # ---- Newton corrector iterations ----
    for it in range(max_iter):
        R = F_int(u_i) - lam_i * Pref
        if abs(R) < tol:
            break

        Kt   = K_T(u_i)
        du_t = Pref / Kt                       # tangential increment per unit dlam
        du_R = -R / Kt                         # residual-driven correction

        # scalar constraint: (du_total + du_R + a*du_t)^2 = dl^2 , solve for a=dlam
        A = du_t**2
        B = 2*du_t*(du_total + du_R)
        C = (du_total + du_R)**2 - dl**2
        disc = max(B**2 - 4*A*C, 0.0)
        sq = np.sqrt(disc)

        dlam1, dlam2 = (-B + sq)/(2*A), (-B - sq)/(2*A)
        du1,   du2   = du_R + dlam1*du_t, du_R + dlam2*du_t

        # --- root selection: keep the cumulative du moving in prev_du_dir ---
        cand = [(dlam1, du1), (dlam2, du2)]
        cand.sort(key=lambda c: -np.sign(du_total + c[1]) * prev_du_dir)  # forward-moving first
        dlam_sel, du_sel = cand[0]

        u_i   += du_sel
        lam_i += dlam_sel
        du_total += du_sel

    prev_du_dir = np.sign(du_total)
    u, lam = u_i, lam_i
    u_path.append(u); lam_path.append(lam)

    print(f"Step {step+1}: u = {u:7.4f}   lambda = {lam:7.4f}   "
          f"K_T = {K_T(u):9.2f}   F_int = {F_int(u):8.2f}")

# ---------------------------------------------------------------
# 4. Reference: exact limit point
# ---------------------------------------------------------------
u_star   = np.sqrt(1000/120)
lam_star = F_int(u_star) / Pref
print(f"\nLimit point (exact): u* = {u_star:.4f},  lambda* = {lam_star:.4f}")