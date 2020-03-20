# lem-in
Elementary algorithmic project

for test: ./lem-in maps/test2.map

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
$ make && cp lem-in checker && cd checker && bash checker_lem-in.sh -abcdef
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
