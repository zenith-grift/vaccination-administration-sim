# Project 2

## Responsibilities

### VaccinationCenter

The `VaccinationCenter` is the main engine that manages the various
actors in the program. The `VaccinationCenter` is responsible for 

### Clerk

The `Clerk` is not aware of time, the `Clerk` is just sent requests from
the `VaccinationCenter` and the `VaccinationStation` and handles them as
fast as possible

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


## Logging

Logging should take place at all customer transitions.
1. Customer arrival?? (Logged by `VaccinationCenter`)
2. Check-in/Enqueue time (Logged by `Clerk`)
3. Transferred to a VaccinationStation (Logged by `Clerk`)
4. Finished vaccination (Logged by `VaccinationStation`)
