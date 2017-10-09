# FlockingSimulaion
Flocking simulation based on Daniel Shiffman's implementation in ["The Nature of Code"](http://natureofcode.com/book/)

##### External Libraries
   - [SFML](https://www.sfml-dev.org/)

##### Project Description
The idea is for every boid to traverse the "pack" and update its position according to three rules:
   - align
   - cohese
   - separate
  
By implementing all behaviour rules in single run, using method *swarm*, constant factor in algorithm complexity may be reduced by three times.

For further performance improvement, multithreading implementation is considered as **std::vector**'s read-thread-safety allows to split the pack on thread-groups.

![Snapshot](https://user-images.githubusercontent.com/31808526/31323066-a153dcde-acaa-11e7-9bc8-fe8e33caf7be.png)
