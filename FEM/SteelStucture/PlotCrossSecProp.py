import CrossSectionProps
import matplotlib.pyplot as plt
import matplotlib.patches as patches
import numpy as np

# ---------------------------------------------------------
# Option A: Import classes directly from the module
# ---------------------------------------------------------
from CrossSectionProps import ThinWalledCrossSectionNumPy, PlateSegment


def plot_cross_section(section: ThinWalledCrossSectionNumPy, title: str = "2D Cross Section Geometry"):
    """
    Visualizes a thin-walled cross-section in 2D with Matplotlib.
    Renders plate thicknesses, centroid (S), principal axes, and shear center (M).
    """
    fig, ax = plt.subplots(figsize=(8, 8))

    # ---------------------------------------------------------
    # 1. Plot Plate Thickness Polygons & Center Lines
    # ---------------------------------------------------------
    for i, seg in enumerate(section.segments):
        # Centerline coordinates in baseline system
        y_a, z_a = seg.node_a[0], seg.node_a[1]
        y_e, z_e = seg.node_e[0], seg.node_e[1]

        # Plot Centerline
        ax.plot([y_a, y_e], [z_a, z_e], 'k--', linewidth=1.2, label="Centerline" if i == 0 else "")
        ax.scatter([y_a, y_e], [z_a, z_e], color='black', s=25, zorder=4)

        # Normal vector to segment for thickness rendering
        # Perpendicular vector to delta = (-dz, dy)
        normal = np.array([-seg.dz, seg.dy], dtype=np.float64)
        if seg.length > 0:
            normal /= seg.length
        
        # 4 Corners of the rectangular plate polygon
        half_t = seg.t / 2.0
        c1 = seg.node_a + normal * half_t
        c2 = seg.node_e + normal * half_t
        c3 = seg.node_e - normal * half_t
        c4 = seg.node_a - normal * half_t

        polygon_pts = np.array([c1, c2, c3, c4])
        poly = patches.Polygon(polygon_pts, closed=True, facecolor='lightgray', edgecolor='black', alpha=0.7, zorder=2)
        ax.add_patch(poly)

    # ---------------------------------------------------------
    # 2. Plot Centroid (S) and Shear Center (M)
    # ---------------------------------------------------------
    y_S, z_S = section.centroid[0], section.centroid[1]
    
    # Transform Shear Center from Principal System back to Baseline System
    cos_a = np.cos(section.alpha)
    sin_a = np.sin(section.alpha)
    R_inv = np.array([[cos_a, -sin_a], [sin_a, cos_a]]) # Inverse rotation matrix
    
    shear_center_base = section.centroid + R_inv @ section.shear_center
    y_M, z_M = shear_center_base[0], shear_center_base[1]

    # Plot Centroid S
    ax.scatter(y_S, z_S, color='red', s=100, marker='o', zorder=5, label=f"Centroid S ({y_S:.1f}, {z_S:.1f})")
    
    # Plot Shear Center M
    ax.scatter(y_M, z_M, color='blue', s=100, marker='X', zorder=5, label=f"Shear Center M ({y_M:.1f}, {z_M:.1f})")

    # ---------------------------------------------------------
    # 3. Plot Principal Axes (y-z Principal Coordinate System)
    # ---------------------------------------------------------
    # Determine axis length dynamically based on section size
    all_y = [seg.node_a[0] for seg in section.segments] + [seg.node_e[0] for seg in section.segments]
    all_z = [seg.node_a[1] for seg in section.segments] + [seg.node_e[1] for seg in section.segments]
    axis_len = 0.4 * max(max(all_y) - min(all_y), max(all_z) - min(all_z))

    # Unit vectors for principal y-axis and z-axis in baseline system
    u_y = np.array([cos_a, sin_a])
    u_z = np.array([-sin_a, cos_a])

    # Draw Principal y-axis
    ax.quiver(y_S, z_S, u_y[0]*axis_len, u_y[1]*axis_len, angles='xy', scale_units='xy', scale=1, 
              color='red', linestyle='-', linewidth=1.5, zorder=4)
    ax.text(y_S + u_y[0]*axis_len*1.1, z_S + u_y[1]*axis_len*1.1, 'y', color='red', fontsize=12, fontweight='bold')

    # Draw Principal z-axis
    ax.quiver(y_S, z_S, u_z[0]*axis_len, u_z[1]*axis_len, angles='xy', scale_units='xy', scale=1, 
              color='red', linestyle='-', linewidth=1.5, zorder=4)
    ax.text(y_S + u_z[0]*axis_len*1.1, z_S + u_z[1]*axis_len*1.1, 'z', color='red', fontsize=12, fontweight='bold')

    # ---------------------------------------------------------
    # 4. Formatting and Layout
    # ---------------------------------------------------------
    ax.set_aspect('equal', adjustable='datalim')
    ax.grid(True, which='both', linestyle=':', alpha=0.6)
    
    # Invert z-axis to match standard structural mechanics convention (z pointing downwards)
    ax.invert_yaxis()

    ax.set_xlabel(r"$\bar{y}$ [mm]", fontsize=11)
    ax.set_ylabel(r"$\bar{z}$ [mm] (downwards)", fontsize=11)
    ax.set_title(title, fontsize=13, fontweight='bold', pad=12)
    ax.legend(loc='best', framealpha=0.9)

    plt.tight_layout()
    plt.show()


# ==========================================
# Example Usage: U-Section & Angle Section
# ==========================================
if __name__ == "__main__":
    # Example 1: Standard Channel (U-Section)
    h, b, t = 200.0, 100.0, 10.0
    u_top = PlateSegment(y_a=b, z_a=-h/2, y_e=0.0, z_e=-h/2, t=t)
    u_web = PlateSegment(y_a=0.0, z_a=-h/2, y_e=0.0, z_e=h/2, t=t)
    u_bot = PlateSegment(y_a=0.0, z_a=h/2, y_e=b, z_e=h/2, t=t)

    u_section = ThinWalledCrossSectionNumPy([u_top, u_web, u_bot])
    plot_cross_section(u_section, title="Channel Cross Section (U-Profile)")

    # Example 2: Unsymmetrical Angle (L-Section to demonstrate rotated principal axes)
    l_vert = PlateSegment(y_a=0.0, z_a=-120.0, y_e=0.0, z_e=0.0, t=10.0)
    l_horz = PlateSegment(y_a=0.0, z_a=0.0, y_e=80.0, z_e=0.0, t=10.0)

    l_section = ThinWalledCrossSectionNumPy([l_vert, l_horz])
    plot_cross_section(l_section, title="Angle Cross Section (L-Profile)")