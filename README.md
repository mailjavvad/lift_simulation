# Lift Calculation Simulation

This project simulates the calculation of lift force on an airfoil based on uncertain parameters such as temperature, pressure, and relative humidity. Monte Carlo simulation is used to propagate uncertainties through the model.
# Four Defined functions
1. Normally distributed random number generator
2. Calculate air Density $\rho$ using the following formula:

$$
\rho = \frac{P_d}{R_d T_k} + \frac{e}{R_v T_k}
$$

where:
-  $\rho$  is the air density,
- \( P_d \) is the partial pressure of dry air, $Pd = P - RH \times E$ where RH is (randomly generated input)
- \( R_d \) is the specific gas constant for dry air, (constant input)
- \( e \) is the vapor pressure,
- \( R_v \) is the specific gas constant for water vapor, and (constant input)
- \( T_k \) is the temperature in Kelvin. \(T_c+273\) \(T_crandomly generated input\)

3. Calculate air Speed \( V \) using the following formula:

$$
V = \sqrt{\frac{2 \cdot (P_t - P_s)}{\rho}}
$$

where:
- \( V \) is the airspeed,
- \( P_t \) is the total pressure, (randomly generated input)
- \( P_s \) is the static pressure, (randomly generated input)
-  $\rho$  is the air density.
   
4. Calculate lift \( L \) using the following formula:

$$
L = 0.5 \cdot \rho \cdot V^2 \cdot A_{\text{wing}} \cdot C_L
$$

where:
- \( L \) is the lift force,
-  $\rho$ is the air density,
- \( V \) is the airspeed,
- \( $A_{\text{wing}}$ \) is the wing area, (randomly generated input)
- \( C_L \) is the lift coefficient. (randomly generated input)


### Randomly Generated Input Variables

1. **Temperature \( T_c \)**:
   - **Distribution**: Normal distribution
   - **Mean**: \( T_c \) follows a normal distribution with a mean of 25 degrees Celsius.
   - **Standard Deviation**: 5
   - **Values in C Program**: `Tc_mean = 25; Tc_stddev = 5;`

2. **Static Pressure \( P_s \)**:
   - **Distribution**: Normal distribution
   - **Mean**: \( P_s \) follows a normal distribution with a mean of 1013.25 hPa.
   - **Standard Deviation**: 10
   - **Values in C Program**: `Ps_mean = 1013.25; Ps_stddev = 10;`

3. **Total Pressure \( P_t \)**:
   - **Distribution**: Normal distribution
   - **Mean**: \( P_t \) follows a normal distribution with a mean of 1050.00 hPa.
   - **Standard Deviation**: 10
   - **Values in C Program**: `Pt_mean = 1050.00; Pt_stddev = 10;`

4. **Relative Humidity \( RH \)**:
   - **Distribution**: Normal distribution
   - **Mean**: \( RH \) follows a normal distribution with a mean of 50 percent.
   - **Standard Deviation**: 10
   - **Values in C Program**: `RH_mean = 50; RH_stddev = 10;`

5. **Wing Area \( $A_{\text{wing}}$ \)**:
   - **Distribution**: Normal distribution
   - **Mean**: \( A_{\text{wing}} \) follows a normal distribution with a mean of 1.0 m\(^2\).
   - **Standard Deviation**: 0.1
   - **Values in C Program**: `Area_mean = 1.0; Area_stddev = 0.1;`

6. **Lift Coefficient \( C_L \)**:
   - **Distribution**: Normal distribution
   - **Mean**: \( C_L \) follows a normal distribution with a mean of 1.2.
   - **Standard Deviation**: 0.05
   - **Values in C Program**: `CL_mean = 1.2; CL_stddev = 0.05;`
### References
1. https://aviex.goflexair.com/blog/density-of-air-air-density
2. https://en.wikipedia.org/wiki/Vapour_pressure_of_water#:~:text=The%20saturation%20vapor%20pressure%20is,it%20would%20evaporate%20or%20sublimate
3. https://www.grc.nasa.gov/www/k-12/VirtualAero/BottleRocket/airplane/pitot.html
## Usage

1. **Clone the repository**:
   ```bash
   git clone https://github.com/mailjavvad/lift-simulation.git
   cd lift-simulation
