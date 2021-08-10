# Project 2

## Overview

The program is a multi-thread simulation tool for vaccination distribution.

## Responsibilities

### VaccinationCenter

The `VaccinationCenter` is the main engine that manages the various
actors in the program. The `VaccinationCenter` is responsible for for 
running the main simulation and joining all threads that were spawned.

The main *run* consists of the following:
1. sleeps for a sampled customer *arrival time* (*separate thread*)
2. pass `Customer` to a `Clerk`
3. the `Clerk` samples a *check-in time* and sleeps
4. the `Clerk` places `Custoemr` into appropriate queue
5. `VaccinationStations` notify when they are available
6. `Clerk` takes `Customer`s from queues and distributes to `VacciationStations`
7. `VacciationStations` sample a *vaccination time* and sleep (*separate thread*)
8. `Customer` has been vaccinated

### Clerk

As can be seen in the run description of the `VaccinationCenter`, the `Clerk`
is responsible for managing where the `Customer`s go. The `Clerk` receives
a `Customer` from the `VaccinationCenter`, puts it in an appropriate queue,
and then passes the customer to a `VaccinationStation` when one is available.

### VaccinationStation

The `VacciationStation`'s main objectives, is to consume a `Custoemr` as well
as sleep. This is done in the `VacciationStation`'s `vaccinate` method. This
method is intended to run asynchronously. One thread should be running for
each `VaccinationStation` the simulation is using. This will better simulate
the real world, where multiple vaccination stations will be doing concurrent
work.

### Customer

The `Customer` is a container that is passed around and keeps track of 
various times throughout the process. 
 
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


### Logger
The logger facilities a simple means to log events throughout the simulation.
The intent of the logger is to write all events to a file that can be used
post simulation for analysis.

Logging occurs at the following stages:
1. Customer arrival absolute time (Logged by `VaccinationCenter`)
2. Check-in/Enqueue time length (Logged by `Clerk`)
3. Vaccination start time (Logged by `VacciationStation`)
4. Vaccination end time length (Logged by `VaccinationStation`)

### SynchronizationQueue

In order to provide thread safety, the queues that are used to store the
`Customer`s and the `VaccinationStation`s need to be thread safe. The
`SynchronizationQueue` is a wrapper around a `queue` with some guards in
place to prevent double access to the same queue. 

### StatsHelper

The `StatsHelper` class is used in post simulation. It is used to analyze
the log files and provide any desired statistic about the simulation.
