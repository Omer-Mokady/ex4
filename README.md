## Ex4 - Advanced Programming 1 Course - Generic Problem solver.
__Authors__
* Gal Seidner
* Omer Mokady

#
__Coding Style__

[google coding style](https://google.github.io/styleguide/cppguide.html)
#

__Our Mission__

We got a task of creting a generic problem solver, keep on Solid principle.

We are using cache manager that we built for saving problems, and we are supporing multi threading as a server that receiving the problems from the clients.

We used in Cloning to prevent clashes of the same objects while working with miltiple threads.

We used the following patten designs: Adapter (for Object Adapter), bridge to.
#
__Goals__

- [X] Create serial and parallel servers side for getting problems need to be sloved by us, using sockets over TCP/IP protocol. 

- [X] Create generic problem solver.

- [X] Create representation for a problem as a matrix - supporting non simetric matrices.

- [X] Implememt Breadth First Search Algorithm for a generic problem.

- [X] Implememt Depth First Search Algorithm for a generic problem.

- [X] Implememt Best First Search Algorithm for a generic problem.

- [X] Implememt A Star Search Algorithm for a generic problem.
