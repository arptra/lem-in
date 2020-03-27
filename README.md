# lem-in
Elementary algorithmic project

The goal of the project is to find the maximum number of disjoint paths for moving ants from point A to point B in the least number of moves, provided that in one move the ants can only go to the neighboring vertex. Ants cannot move several pieces along the same edge, nor can they be at the same vertex at the same time, except for the start and finish.
```
for test: ./lem-in < maps/test2.map
```
# lemin visualization

visualization is implemented in __python 3__
using [pyside2](https://pypi.org/project/PySide2/) - Qt framework port for python - for graphics


# installing dependencies
```
$ pip3 install pyside2
```

# running visualization

```
$ ./lem-in maps/theta_unequal_4.map | python3 lemin42-visual/lemin_visual.py
```
# test lem-in

```
$ make && cp lem-in checker && cd checker && bash check_lem-in.sh -abcdef
```
```
$ -h    show options with brief descriptions
$ -a    check errors management
$ -b    check leak with invalid map
$ -c    check output is right format
$ -d    check leak with valid map
$ -e    check time complexity
$ -f    check accuracy
```
