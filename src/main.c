#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Function to generate normally distributed random numbers using the Marsaglia polar method
double normrnd(double mean, double stddev) {
    static int haveSpare = 0;
    static double spare;
    if (haveSpare) {
        haveSpare = 0;
        return mean + stddev * spare;
    }

    double u, v, s;
    do {
        u = 2.0 * rand() / RAND_MAX - 1.0;
        v = 2.0 * rand() / RAND_MAX - 1.0;
        s = u * u + v * v;
    } while (s >= 1.0 || s == 0.0);

    s = sqrt(-2.0 * log(s) / s);
    spare = v * s;
    haveSpare = 1;

    return mean + stddev * (u * s);
}

// Function to calculate air density
double calculate_air_density(double T, double P, double RH, double Rd, double Rv) {
    double E = 6.1078 * pow(10, (7.5 * T / (T + 237.3))) * 100; // Saturation vapor pressure in Pa
    double e = RH * E; // Actual vapor pressure in Pa
    double Pd = P - e; // Partial pressure of dry air in Pa
    double Tk = T + 273.15; // Temperature in Kelvin
    double rho = Pd / (Rd * Tk) + e / (Rv * Tk); // Air density in kg/m^3
    return rho;
}

// Function to calculate airspeed from Pitot tube measurements
double calculate_air_speed(double Pt, double Ps, double rho) {
    return sqrt(2 * (Pt - Ps) / rho); // Airspeed in m/s
}

// Function to calculate lift
double calculate_lift(double Tc, double Ps, double Pt, double RH, double Area, double CL) {
    // Define constants
    const double Rd = 287.05; // Specific gas constant for dry air (J/(kg·K))
    const double Rv = 461.5; // Specific gas constant for water vapor (J/(kg·K))
    
    // Calculate air density
    double density = calculate_air_density(Tc, Ps, RH, Rd, Rv);
    
    // Calculate airspeed
    double V = calculate_air_speed(Pt, Ps, density);
    
    // Calculate lift
    return 0.5 * density * pow(V, 2) * Area * CL;
}

int main() {
    // Seed the random number generator
    srand(time(NULL));

    // Define constants
    const int NUM_SIMULATIONS = 1000;
    const double Rd = 287.05; // Specific gas constant for dry air (J/(kg·K))
    const double Rv = 461.5; // Specific gas constant for water vapor (J/(kg·K))

    // Mean and standard deviations of input parameters
    const double Tc_mean = 25; // Mean temperature in Celsius
    const double Ps_mean = 1013.25; // Mean static pressure in hPa
    const double Pt_mean = 1050.00; // Mean total pressure in hPa
    const double RH_mean = 50; // Mean relative humidity in percentage
    const double Area_mean = 1.0; // Wing area in m^2
    const double CL_mean = 1.2; // Lift coefficient

    const double Tc_stddev = 2; // Standard deviation of temperature
    const double Ps_stddev = 5; // Standard deviation of static pressure
    const double Pt_stddev = 5; // Standard deviation of total pressure
    const double RH_stddev = 5; // Standard deviation of relative humidity
    const double Area_stddev = 0.1; // Standard deviation of wing area
    const double CL_stddev = 0.05; // Standard deviation of lift coefficient

    // Initialize array to store lift values
    double lifts[NUM_SIMULATIONS];

    // Simulation loop
    for (int i = 0; i < NUM_SIMULATIONS; ++i) {
        // Generate random inputs
        double Tc = normrnd(Tc_mean, Tc_stddev);
        double Ps = normrnd(Ps_mean, Ps_stddev) * 100; // Convert to Pa
        double Pt = normrnd(Pt_mean, Pt_stddev) * 100; // Convert to Pa
        double RH = normrnd(RH_mean, RH_stddev) / 100; // Convert to decimal
        double Area = normrnd(Area_mean, Area_stddev);
        double CL = normrnd(CL_mean, CL_stddev);

        // Ensure RH is within 0 to 1
        if (RH < 0) RH = 0;
        if (RH > 1) RH = 1;

        // Calculate lift
        double L = calculate_lift(Tc, Ps, Pt, RH, Area, CL);

        // Store lift value
        lifts[i] = L;
    }

    // Calculate the mean and standard deviation of the lift distribution
    double sum_lift = 0.0, sum_sq_lift = 0.0;
    for (int i = 0; i < NUM_SIMULATIONS; ++i) {
        sum_lift += lifts[i];
        sum_sq_lift += lifts[i] * lifts[i];
    }
    double mean_lift = sum_lift / NUM_SIMULATIONS;
    double stddev_lift = sqrt((sum_sq_lift / NUM_SIMULATIONS) - (mean_lift * mean_lift));

    // Output the result
    printf("Mean lift is %f N\n", mean_lift);
    printf("Standard deviation of lift is %f N\n", stddev_lift);

    return 0;
}
