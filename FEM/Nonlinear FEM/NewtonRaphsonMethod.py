def f(x):
    return x**3 - x - 2

def df_dx(x):
    return 3*x**2 - 1

def newton_raphson(initial_guess, tolerance=1e-7, max_iterations=100):
    x = initial_guess
    for i in range(max_iterations):
        fx = f(x)
        dfx = df_dx(x)
        
        if dfx == 0:
            raise ValueError("Derivative is zero. No solution found.")
        
        x_new = x - fx / dfx
        
        if abs(x_new - x) < tolerance:
            return x_new, i
        
        x = x_new

    raise ValueError("Exceeded maximum iterations. No solution found.")
     

if __name__ == "__main__":
    initial_guess = 1.0
    try:
        root, iterations = newton_raphson(initial_guess)
        print(f"Root found: {root} in {iterations} iterations")
    except ValueError as e:
        print(e)