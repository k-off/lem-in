# lem-in
An Algo Project at Codam (42) - ant farm

### Thanks @sergeresko for the [verifier](https://github.com/sergeresko/lem_in).

An introduction to the grapth theory. Depth first search (DFS), breadth first search (BFS), maximum flow problem.

The goal is to send a given amount of ants from starting room to ending room using shortest possible amount of steps. A step is a line containing names of ants and names of rooms they should move to (format Lant1-room1 Lant2-room2 ...). The game has several restrictions: one room can contain one ant (excepting start-room and end-room), one ant can move only once per line.

A generator is provided to evaluate the project. It has 5 levels of difficulty: flow-one (one ant on the map), flow-ten (up to 20 ants, distinct paths, up to 1000 rooms), flow-thousand (up to 150 ants, distinct paths, up to 1500 rooms), big (up to 500 ants, crossing paths, 1000+ rooms), big-superposition (up to 500 ants, overlaying paths, 2000+ rooms). The generator outputs a map, containing amount of ants, room names, room connections.

The lem-in binary has to read the map on the standard output, find a shortest path or the best combination of paths, and print back the map with the answer.

A test is present in the repository. It checks the project for the internal 42 rules (tne Norme), for error handling, and for the standard defence cases.

## usage:
	cd project_path/test
	sh test.sh
