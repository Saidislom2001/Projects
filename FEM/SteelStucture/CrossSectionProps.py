import numpy as np
from typing import List, Dict


class PlateSegment:
    """
    Represents a single thin-walled rectangular plate element using NumPy vectors.
    Defined by start node a(y_a, z_a) and end node e(y_e, z_e), and thickness t.
    """
    def __init__(self, y_a: float, z_a: float, y_e: float, z_e: float, t: float):
        self.node_a = np.array([y_a, z_a], dtype=np.float64)
        self.node_e = np.array([y_e, z_e], dtype=np.float64)
        self.t = float(t)

        # Midpoint vector
        self.midpoint = 0.5 * (self.node_a + self.node_e)

        # Difference vector (dy, dz)
        self.delta = self.node_e - self.node_a
        self.dy, self.dz = self.delta[0], self.delta[1]

        # Geometric properties
        self.length = float(np.linalg.norm(self.delta))
        self.area = self.t * self.length

        # Unit directional vector and sine/cosine (Slide 14)
        if self.length > 0:
            self.unit = self.delta / self.length
            self.cos_beta = self.unit[0]
            self.sin_beta = self.unit[1]
        else:
            self.unit = np.array([1.0, 0.0])
            self.cos_beta = 1.0
            self.sin_beta = 0.0

    def get_self_moments_of_inertia(self) -> np.ndarray:
        """
        Computes Self Moments of Inertia (SMI) tensor in initial system (Slide 14):
        Returns 2x2 matrix: [[A_yy_SMI, A_yz_SMI],
                             [A_yz_SMI, A_zz_SMI]]
        """
        factor = self.area * (self.length ** 2) / 12.0
        a_yy_smi = factor * (self.cos_beta ** 2)
        a_zz_smi = factor * (self.sin_beta ** 2)
        a_yz_smi = factor * self.sin_beta * self.cos_beta

        return np.array([
            [a_yy_smi, a_yz_smi],
            [a_yz_smi, a_zz_smi]
        ], dtype=np.float64)


class ThinWalledCrossSectionNumPy:
    """
    Computes cross-sectional properties using NumPy arrays and matrix operations based on
    the RUB Lecture Presentation (CE-P-03).
    """
    def __init__(self, segments: List[PlateSegment]):
        self.segments = segments

        # Results Placeholders
        self.area: float = 0.0
        self.centroid = np.zeros(2, dtype=np.float64)  # [y_S, z_S]
        self.alpha: float = 0.0
        self.I_y: float = 0.0  # Principal Moment of Inertia about y-axis (A_zz)
        self.I_z: float = 0.0  # Principal Moment of Inertia about z-axis (A_yy)

        # Warping & Shear Center
        self.shear_center = np.zeros(2, dtype=np.float64)  # [y_M, z_M]
        self.I_w: float = 0.0  # Warping Constant (I_omega)

        # Run calculation pipeline automatically
        self._compute_basic_properties()
        self._compute_warping_properties()

    def _compute_basic_properties(self):
        """Standardization Part I - Centroid, Principal Axes & Moments of Inertia (Slides 11, 13, 14)"""
        # Step 1: Baseline Properties in initial system (y_bar, z_bar)
        self.area = sum(seg.area for seg in self.segments)
        
        # Static moments vector [A_y_bar, A_z_bar]
        static_moments = sum(seg.area * seg.midpoint for seg in self.segments)

        # Step 2: Center of Gravity (S) vector (Slide 11)
        self.centroid = static_moments / self.area

        # Step 3 & 4: Moments of inertia tensor relative to centroid (tilde system)
        I_tilde_tensor = np.zeros((2, 2), dtype=np.float64)

        for seg in self.segments:
            # Self Moments of Inertia Matrix
            I_smi = seg.get_self_moments_of_inertia()
            
            # Distance vector from segment centroid to section centroid S
            r_S = seg.midpoint - self.centroid
            y_bar_S, z_bar_S = r_S[0], r_S[1]

            # Parallel Axis Theorem (Steiner parts) tensor (Slide 13)
            I_steiner = np.array([
                [y_bar_S**2,         y_bar_S * z_bar_S],
                [y_bar_S * z_bar_S, z_bar_S**2        ]
            ]) * seg.area

            I_tilde_tensor += I_smi + I_steiner

        A_yy_tilde = I_tilde_tensor[0, 0]
        A_zz_tilde = I_tilde_tensor[1, 1]
        A_yz_tilde = I_tilde_tensor[0, 1]

        # Step 5: Rotation angle of principal axes (alpha) (Slide 11)
        denom = A_yy_tilde - A_zz_tilde
        if np.abs(denom) < 1e-12:
            self.alpha = 0.0
        else:
            self.alpha = 0.5 * np.arctan2(2.0 * A_yz_tilde, denom)

        # Step 6: Principal Moments of Inertia using Transformation Matrix (Slide 11)
        cos_a = np.cos(self.alpha)
        sin_a = np.sin(self.alpha)

        # Principal Moments of Inertia (Method B)
        self.I_z = A_yy_tilde * (cos_a**2) + A_zz_tilde * (sin_a**2) + 2.0 * A_yz_tilde * sin_a * cos_a
        self.I_y = A_zz_tilde * (cos_a**2) + A_yy_tilde * (sin_a**2) - 2.0 * A_yz_tilde * sin_a * cos_a

    def _compute_warping_properties(self):
        """Standardization Part II - Shear Center and Warping Constant (Slide 37, 38)"""
        # Pivot D set at centroid S(0,0) in principal system for simplicity
        pivot_D = np.zeros(2, dtype=np.float64)

        # Unstandardized warping integrals
        A_w_bar = 0.0
        A_yw_bar = 0.0
        A_zw_bar = 0.0
        A_ww_bar = 0.0

        # Current running unstandardized warping ordinate
        w_a = 0.0

        for seg in self.segments:
            # Transform segment node coordinates to principal centroidal system
            node_a_p = self._to_principal_system(seg.node_a)
            node_e_p = self._to_principal_system(seg.node_e)

            # Perpendicular distance r_t from pivot point D to element (Slide 33)
            r_S = seg.midpoint - self.centroid
            r_t = r_S[0] * seg.sin_beta - r_S[1] * seg.cos_beta
            
            # Warping ordinate at end node e
            w_e = w_a + r_t * seg.length
            w_m = (w_a + w_e) / 2.0
            dw = w_e - w_a

            # Analytical Integration over single plate using NumPy vectors (Slide 38)
            A_w_bar += w_m * seg.area
            
            delta_p = node_e_p - node_a_p
            dy_p, dz_p = delta_p[0], delta_p[1]
            midpoint_p = 0.5 * (node_a_p + node_e_p)

            A_yw_bar += (dy_p * dw * seg.area / 12.0) + (midpoint_p[0] * w_m * seg.area)
            A_zw_bar += (dz_p * dw * seg.area / 12.0) + (midpoint_p[1] * w_m * seg.area)
            A_ww_bar += ((dw**2) * seg.area / 12.0) + ((w_m**2) * seg.area)

            # Pass warping value to next connected element
            w_a = w_e

        # Transformation constant for warping ordinate (Slide 37)
        w_k_bar = A_w_bar / self.area

        # Position of Shear Center M relative to pivot D (Slide 37)
        dy_M = A_zw_bar / self.I_y if np.abs(self.I_y) > 1e-12 else 0.0
        dz_M = -A_yw_bar / self.I_z if np.abs(self.I_z) > 1e-12 else 0.0

        self.shear_center = pivot_D + np.array([dy_M, dz_M])

        # Warping Constant I_omega (Slide 37)
        self.I_w = (
            A_ww_bar
            - (w_k_bar**2) * self.area
            - (dy_M**2) * self.I_y
            - (dz_M**2) * self.I_z
        )

    def _to_principal_system(self, point: np.ndarray) -> np.ndarray:
        """Transforms point coordinates vector [y, z] to principal centroidal system (Slide 11)"""
        point_tilde = point - self.centroid
        cos_a = np.cos(self.alpha)
        sin_a = np.sin(self.alpha)

        # 2D Rotation Matrix
        R = np.array([
            [ cos_a, sin_a],
            [-sin_a, cos_a]
        ], dtype=np.float64)

        return R @ point_tilde

    def get_summary(self) -> Dict[str, float]:
        """Returns a dictionary of all calculated cross-section properties."""
        return {
            "Area (A)": float(self.area),
            "Centroid y_S": float(self.centroid[0]),
            "Centroid z_S": float(self.centroid[1]),
            "Principal Axis Angle (alpha deg)": float(np.degrees(self.alpha)),
            "Moment of Inertia I_y": float(self.I_y),
            "Moment of Inertia I_z": float(self.I_z),
            "Shear Center y_M (Principal C.S.)": float(self.shear_center[0]),
            "Shear Center z_M (Principal C.S.)": float(self.shear_center[1]),
            "Warping Constant (I_w)": float(self.I_w),
        }


# ==========================================
# Example Execution: Channel Section (U-Section)
# ==========================================
if __name__ == "__main__":
    # Define a U-Section: Height h = 200 mm, Width b = 100 mm, Thickness t = 10 mm
    h, b, t = 200.0, 100.0, 10.0

    # Define segments as NumPy-driven PlateSegments
    top_flange = PlateSegment(y_a=b, z_a=-h/2, y_e=0.0, z_e=-h/2, t=t)
    web        = PlateSegment(y_a=0.0, z_a=-h/2, y_e=0.0, z_e=h/2, t=t)
    bot_flange = PlateSegment(y_a=0.0, z_a=h/2, y_e=b, z_e=h/2, t=t)

    section = ThinWalledCrossSectionNumPy([top_flange, web, bot_flange])

    print("--- Calculated Cross Section Properties (NumPy) ---")
    for key, val in section.get_summary().items():
        print(f"{key:35s}: {val:12.4f}")