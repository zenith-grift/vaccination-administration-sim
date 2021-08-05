# Project 2

## Responsibilities

### VaccinationCenter

The `VaccinationCenter` is the main engine that manages the various
actors in the program. The `VaccinationCenter` is responsible for 

### VaccinationStation

### Customer
 
### Distribution
    `Distribution` is a *pure* virtual class that acts as an inteface and
    allows for polymorphism on pulling samples from arbitrary distributions
    via the `pullSample()` method.

#### ExponentialDistribution
    `ExponentialDistribution` inherits from `Distribution` and provides a
    `pullSample()` method that returns a sample based on an initialized rate.

#### UniformDistribution
    `UniformDistribution` inherits from `Distribution` and provides a
    `pullSample()` method that returns a sample based on a range supplied by
    the constructor.
