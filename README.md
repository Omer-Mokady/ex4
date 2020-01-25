## Ex4 - Advanced Programming 1 Course - Generic Problem solver.
__Authors__
* Gal Seidner
* Omer Mokady

#
__Coding Style__

[google coding style](https://google.github.io/styleguide/cppguide.html)
#

__Our Mission__

We created a generic problem solver using c++ language, keep on the Solid programming principle during the project.

We are using cache manager that we built for saving problems that we already solved along the problem, so we would be able to load them in O(1). 

We are supporing single and multi threading in the server side that receiving the problems from the clients.

We used Cloning to prevent clashes of the same objects while working with miltiple threads.

We used the Adapter and the bridge design patterns.
#
__Goals__

- [X] Create serial and parallel servers side for getting problems need to be sloved by us, using sockets over TCP/IP protocol. 

- [X] Create generic problem solver.

- [X] Create representation for a problem as a matrix - supporting non simetric matrices.

- [X] Implememt [Breadth First Search](https://en.wikipedia.org/wiki/Breadth-first_search) Algorithm for a generic problem.

- [X] Implememt [Depth First Search](https://en.wikipedia.org/wiki/Depth-first_search) Algorithm for a generic problem.

- [X] Implememt [Best First Search](https://en.wikipedia.org/wiki/Best-first_search) Algorithm for a generic problem.

- [X] Implememt [A Star Search Algorithm](https://en.wikipedia.org/wiki/A*_search_algorithm) for a generic problem.
#
__How It Works?__

When running the program you'll need to copile it from the terminal with the following line:

"g++ -std=c++14 *.cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o a.out -pthread"

run it with the command: "./a.out potrNumber"

when port number is the port you want the server to listen on. the default code in case you forgot to insert one is 5600.

now you can connect as client to this port and send it the problem you want it to slove.

if we have the solution in out cache or disk - you'll get it in O(1).

otherwise - we will solve it and then return you the solution.

__Running Example__

given the following input from a client: 1,2,1\n1,0,0\n1,2,1\n0,0\n2,2\nend

we will build aproblem represent by 3x3 matrix with statr point of (0,0) and goal destanation of (2,2):

1 2 1

1 0 1

1 2 1

we will calculate the best way to go from 0,0 to 2,2 using one of four search algorithm (the one that will be the most efficient of them), and in this case we will return the following answer:

down (1), right(1), right(2), down(1) - which will represent the steps need to be done + the total cost of the path. 
