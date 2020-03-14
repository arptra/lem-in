#!/usr/bin/env python3

import fileinput
import sys
from itertools import tee, islice
import re

from lemin_vis.map_parser import parse_map_str, Map
from lemin_vis.solution_parser import parse_solution_str, Solution
import lemin_vis.view as view


def extract_map_and_solution(input_data):
    "separates map data string from solution data string when given single map-solution str as input"
    "return map string and solution strings as tuple"

    # find solution begin or ERROR msg in given input str
    solution_begin = re.search('^L', input_data, re.MULTILINE)

    if solution_begin is None:
        solution_begin = re.search('^ERROR', input_data, re.MULTILINE)

    i1, i2 = tee(input_data)

    # build two iterators
    # first from input str start to solution start in that input str
    # second from solution start til the end of input str
    i1 = islice(i1, solution_begin.start())
    i2 = islice(i2, solution_begin.start(), None)

    # build strings from iterators
    map_data = ''.join(i1)
    solution_data = ''.join(i2)

    return (map_data, solution_data)


# read map and solution from standard input
if len(sys.argv) < 2:
    input_data = sys.stdin.read()
else:
    # read map and solution from file specified as arg
    map_solution_filename = sys.argv[1]

    with open(map_solution_filename) as map_file:
        input_data = map_file.read()

try:
    map_data, solution_data = extract_map_and_solution(input_data)
except Exception as ex:
    print("ExtractionError: could not separate map data from solution data")
    sys.exit()

try:
    map = parse_map_str(map_data)
except Exception as ex:
    # if map parsing failed
    map = Map()
    map.error = f"MapParseError: {repr(ex)}"

try:
    solution = parse_solution_str(solution_data, map)
except Exception as ex:
    # if solution parsing failed
    solution = Solution()
    solution.error = f"SolutionParseError: {repr(ex)}"

view.init_and_run(map, solution)
