import fluid_flow_simulator

if __name__ == "__main__":
    # Initialize the fluid flow simulator
    simulator = fluid_flow_simulator.FluidFlowSimulator()

    # Set simulation parameters
    simulator.set_parameters(velocity=5.0, viscosity=0.001, density=1000)

    # Run the simulation
    results = simulator.run_simulation()

    # Output the results
    print("Simulation Results:")
    print(results)