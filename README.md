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


## Using Threads

Should maybe have a separate thread for each component that can sleep.
For example, each vaccination station should run on a separate thread because
they are not dependent on each other. Also the customer arrival should run 
in a separate thread because customers can arrive while vaccinations are taking
place.

This would require me to make the queues thread safe unless the clerk is the
only one allowed to modify the queues.

The logger will need to lock the file when writing in order to prevent data
races.


The other option is to pre-populate queues and vectors with samples
and then coordinate those based on a global "clock"... 


## Timing
In order to simulate the timing I decided to actually sleep/block during
a phase where a time sample is taken. Since I don't want to wait five days
for the simulation to finish, I ran the simulation where 1 hour = 1 second.
This allows for a 5 day simulation to not even take a couple of minutes.
