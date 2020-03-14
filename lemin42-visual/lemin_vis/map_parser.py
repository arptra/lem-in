import itertools
from dataclasses import dataclass
from collections import namedtuple
from enum import Enum
from io import StringIO

Coords = namedtuple("Coords", "x y")
RoomType = Enum("RoomType", "start end")


@dataclass(frozen=True)  # forzen makes class hashable
class Room:
    name: str
    coords: Coords
    type: RoomType


@dataclass
class Link:
    from_: Room  # 'from' is a keyword in python
    to_: Room    # underscore for consistency

    # impement __hash__ & __eq__ to make Link hashable to store in set
    def __hash__(self):
        return id(self.from_) ^ id(self.to_)

    # straight and reverse links are equal
    def __eq__(self, other):
        return id(self.from_) == id(other.from_) and id(self.to_) == id(other.to_) or \
            id(self.from_) == id(other.to_) and id(self.to_) == id(other.to_)


class Map:
    def __init__(self):
        self.number_of_ants: int = 0
        self.rooms: dict = {}
        self.links: list = []
        self.start_room: Room = None
        self.end_room: Room = None
        self.error: str = None


def parse_map_str(map_str):
    map_buf = StringIO(map_str)
    map = Map()

    # read 1st line: number of ants
    map.number_of_ants = int(map_buf.readline())

    # read "room" lines until first "link" line is encountered
    map_file_iter = iter(map_buf)
    room_type = None

    for room_line in map_file_iter:
        # eliminate trailing "\n"
        room_line = room_line.strip()

        # ignore empty line
        if len(room_line) == 0:
            continue

        # ignore comment lines
        if is_comment_line(room_line):
            continue

        # first "link" line read -> put it back and proceed to reading "link" rooms
        if is_link_line(room_line):
            # "put link line back to iterator"
            map_file_iter = itertools.chain((room_line,), map_file_iter)
            break

        # ##start or ##end room
        if is_command_line(room_line):
            room_type = parse_command_line(room_line)
            continue

        # create room and add to collection
        room = parse_room_line(room_line, room_type)
        map.rooms[room.name] = room

        # store start and end rooms
        if room_type == RoomType.start:
            map.start_room = room
        if room_type == RoomType.end:
            map.end_room = room

        room_type = None

    # read link lines
    for link_line in map_file_iter:
        # eliminate trailing "\n"
        link_line = link_line.strip()

        # ignore empty line
        if len(link_line) == 0:
            continue

        # ignore comment lines
        if is_comment_line(link_line):
            continue

        # create link and add to set collection
        link = parse_link_line(link_line, map.rooms)
        map.links.append(link)

    return map


def is_comment_line(line):
    if line[0] == '#':
        if len(line) == 1:  # line with only comment symbol
            return True
        else:
            if line[1] != '#':  # not command line
                return True

    return False


def is_link_line(line):
    return True if ' ' not in line and '-' in line else False


def is_command_line(line):
    return True if line.startswith('##') else False


def parse_command_line(line):
    type_str = line[2:]
    if type_str == 'start':
        return RoomType.start
    elif type_str == 'end':
        return RoomType.end

    return None


def parse_room_line(line, room_type):
    data = line.split(' ')
    room_name = str(data[0])
    x = int(data[1])
    y = int(data[2])

    return Room(room_name, Coords(x, y), room_type)


def parse_link_line(line, rooms):
    data = line.split('-')
    from_room_name = str(data[0])
    to_room_name = str(data[1])

    return Link(rooms[from_room_name], rooms[to_room_name])
