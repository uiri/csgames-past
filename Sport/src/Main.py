import pygame
import socket
import select
from enum import Enum
import math
import datetime
import time
from collections import deque
import sys
import json

"""
Tilemap:
BIG_DOT = 0
BLANK = 1
DOT = 2
DOWN_DOWBLE_WALL = 3
DL_ANGLED_CORNER = 4
DL_SMOOTH_CORNER = 5
DR_ANGLED_CORNER = 6
DR_SMOOTH_CORNER = 7
DOWN_SIMPLE_WALL = 8
GHOST_BARRIER = 9
LEFT_DOUBLE_WALL = 10
LEFT_SIMPLE_WALL = 11
RIGHT_DOUBLE_WALL = 12
RIGHT_SIMPLE_WALL = 13
UP_DOUBLE_WALL = 14
UL_ANGLED_CORNER = 15
UL_SMOOTH_CORNER = 16
UR_ANGLED_CORNER = 17
UR_SMOOTH_CORNER = 18
UP_SIMPLE_WALL = 19
FULL_WALL = 20
"""
Terrain_tiles = [pygame.image.load("assets/terrain/big_dot_sprite.png"), pygame.image.load("assets/terrain/blank_tile.png"), pygame.image.load("assets/terrain/dot_sprite.png"), pygame.image.load("assets/terrain/down_double_wall.png"), pygame.image.load("assets/terrain/down_left_angled_corner.png"), pygame.image.load("assets/terrain/down_left_smooth_corner.png"), pygame.image.load("assets/terrain/down_right_angled_corner.png"), pygame.image.load("assets/terrain/down_right_smooth_corner.png"), pygame.image.load("assets/terrain/down_simple_wall.png"), pygame.image.load("assets/terrain/ghost_spawn_barrier.png"), pygame.image.load("assets/terrain/left_double_wall.png"), pygame.image.load("assets/terrain/left_simple_wall.png"), pygame.image.load("assets/terrain/right_double_wall.png"), pygame.image.load("assets/terrain/right_simple_wall.png"), pygame.image.load("assets/terrain/up_double_wall.png"), pygame.image.load("assets/terrain/up_left_angled_corner.png"), pygame.image.load("assets/terrain/up_left_smooth_corner.png"), pygame.image.load("assets/terrain/up_right_angled_corner.png"), pygame.image.load("assets/terrain/up_right_smooth_corner.png"), pygame.image.load("assets/terrain/up_simple_wall.png"), pygame.image.load("assets/terrain/full_wall.png")]

GHOST_MAX_SPEED = 120
PACMAN_MAX_SPEED = 160

DEFAULT_X = 1280.0
DEFAULT_Y = 800.0
SPEED_MULTIPLIER = 1.0

BASE_SPEED_INCREASE = 20
BASE_SPEED_DECREASE = -2.5
SPEED_INCREASE = 20
SPEED_DECREASE = -2.5

class Direction(Enum):
    UP = 0
    RIGHT = 1
    DOWN = 2
    LEFT = 3
    NONE = 4

class Board:
    """Simple Pacman board"""

    def __init__(self, path):
        with open(path, 'r') as tilemap:
            content = tilemap.read()
            self.tiles = parse_tilemap(content)

        self.vulnerability_timer = 0
        self.screen=pygame.display.set_mode((0,0), (pygame.FULLSCREEN | pygame.HWSURFACE))
        #pygame.display.toggle_fullscreen()
        display_info = pygame.display.Info()
        # Assume Width > Height
        self.tile_height = int(display_info.current_h / 30)
        self.tile_width = self.tile_height

        self.start_x = (display_info.current_w - (28 * self.tile_width)) / 2

        global SPEED_MULTIPLIER
        SPEED_MULTIPLIER = float(display_info.current_h) / DEFAULT_Y

        print("Speed multiplier = %s" % (SPEED_MULTIPLIER))

        #print("Screen info: width = %s, height = %s" % (display_info.current_w, display_info.current_h))
        #print("Tile width = %s, tile height = %s, start x = %s" %(self.tile_width, self.tile_height, self.start_x))

        for curr_x in range(0, 28):
            for curr_y in range(0, 30):
                self.blit_tile(self.tiles[curr_x][curr_y], curr_x, curr_y)

    def blit_tile(self, sprite, x, y):
        tile_surface = pygame.transform.scale(sprite, (self.tile_width, self.tile_height))
        self.screen.blit(tile_surface, (x * self.tile_width + self.start_x , self.tile_height * y))

    def blit_score(self):
        self.screen.blit(SCORE, (30, 30))
        self.screen.blit(SCORE_SURF, (SCORE.get_width() + 30, 30))

    def blit_lives(self):
        self.screen.blit(LIVES, (30, 60))
        self.screen.blit(LIVE_SURF, (LIVES.get_width() + 30, 60))

    def blit_surroundings(self, sprite):
        tile_pos = sprite.get_curr_tile(self)
        x = tile_pos[0]
        y = tile_pos[1]
        self.blit_tile(self.tiles[x][y], x, y)
        self.blit_tile(self.tiles[x - 1][y], x - 1, y)
        self.blit_tile(self.tiles[x + 1][y], x + 1, y)
        self.blit_tile(self.tiles[x][y - 1], x, y - 1)
        self.blit_tile(self.tiles[x][y + 1], x, y + 1)
        self.blit_tile(self.tiles[x - 1][y - 1], x - 1, y - 1)
        self.blit_tile(self.tiles[x + 1][y - 1], x + 1, y - 1)
        self.blit_tile(self.tiles[x - 1][y + 1], x - 1, y + 1)
        self.blit_tile(self.tiles[x + 1][y + 1], x + 1, y + 1)
        spdir = sprite.direction
        if(spdir == Direction.UP and y + 2 < len(self.tiles[x])):
            self.blit_tile(self.tiles[x][y + 2], x, y + 2)
        elif(spdir == Direction.DOWN and y - 2 >= 0):
            self.blit_tile(self.tiles[x][y - 2], x, y - 2)
        elif(spdir == Direction.LEFT and x + 2 < len(self.tiles)):
            self.blit_tile(self.tiles[x + 2][y], x + 2, y)
        elif(spdir == Direction.RIGHT and x - 2 >= 0):
            self.blit_tile(self.tiles[x - 2][y], x - 2, y)

    def blit(self, sprite):
        sprite_surface = pygame.transform.scale(sprite.current_sprite(), (self.tile_width, self.tile_height))
        self.screen.blit(sprite_surface, (sprite.x, sprite.y))

    def is_wall(self, x, y):
        tile = self.tiles[x][y]
        return tile != Terrain_tiles[0] and tile != Terrain_tiles[1] and tile != Terrain_tiles[2]

    def tile_at(self, fl_x, fl_y):
        x = int(fl_x)
        y = int(fl_y)
        x_tile = int((x - self.start_x) // self.tile_width)
        y_tile = int(y // self.tile_height)
        return (x_tile, y_tile)

    def grid_to_abs(self, x, y):
        nx = x * self.tile_width + self.start_x
        ny = y * self.tile_height
        return (nx, ny)

class PlayableSprite:
    direction = Direction.NONE

    base_image = None
    none_sprite = None
    up_sprite = None
    right_sprite = None
    down_sprite = None
    left_sprite = None

    # Logic position
    real_x = 0
    real_y = 0

    # Position in surface
    x = 0
    y = 0

    lastinput = datetime.datetime.now()

    def __init__(self):
        self.event_queue = deque([])
        self.speed = 20

    def current_sprite(self):
        if(self.direction == Direction.NONE):
            return self.none_sprite
        elif(self.direction == Direction.UP):
            return self.up_sprite
        elif(self.direction == Direction.DOWN):
            return self.down_sprite
        elif(self.direction == Direction.LEFT):
            return self.left_sprite
        elif(self.direction == Direction.RIGHT):
            return self.right_sprite

    def spawn(self, board, x, y):
        board.blit_tile(self.none_sprite, x, y)
        self.x = board.start_x + x * board.tile_width
        self.y = y * board.tile_height
        self.real_x = self.x
        self.real_y = self.y
        self.board = board

    def get_curr_tile(self, board):
        x_tile = int((self.x - board.start_x) // board.tile_width)
        y_tile = int(self.y // board.tile_height)
        return (x_tile, y_tile)

    def decrease_speed(self):
        self.speed += SPEED_DECREASE
        print("Decreasing speed by %s" % SPEED_DECREASE)
        if(self.speed < 0):
            self.speed = 0

    def increase_speed(self):
        self.speed += SPEED_INCREASE
        print("Increasing speed by %s" % SPEED_INCREASE)
        if(self.speed > self.max_speed):
            self.speed = self.max_speed

    def queue_event(self, event):
        #print("Queuing event %s" % event)
        self.event_queue.append((event, 7))

    def update(self, board):
        if(isinstance(self, Ghost)):
            if(not self.alive):
                for i in range(0, len(self.event_queue)):
                    evt = self.event_queue.popleft()
                    continue
                objective = board.grid_to_abs(13, 13)
                xdiff = self.real_x - objective[0]
                ydiff = self.real_y - objective[1]
                #print("Dead ghost update, distance to destination = (%s, %s)" % (xdiff, ydiff))
                self.real_y -= ydiff / self.travel_time
                self.real_x -= xdiff / self.travel_time
                self.x = int(self.real_x // 1)
                self.y = int(self.real_y // 1)
                self.travel_time -= 1.0
                if(self.travel_time <= 0.0):
                    self.alive = True
                    self.travel_time = 0.0
                return
        curr_x_pos = self.real_x
        curr_y_pos = self.real_y
        dist = 0.0
        if(isinstance(self, Ghost)):
            if(self.is_vulnerable):
                old_speed = self.speed
                self.speed /= 2
        if(self.direction == Direction.UP):
            self.real_y -= self.speed / 60.0
            self.x = int(self.real_x)
            self.y = int(self.real_y)
            new_tile = self.get_curr_tile(board)
            if(board.is_wall(new_tile[0], new_tile[1])):
                coords = board.grid_to_abs(new_tile[0], new_tile[1] + 1)
                self.real_y = coords[1]
        elif(self.direction == Direction.RIGHT):
            self.real_x += self.speed / 60.0
            self.x = int(self.real_x)
            self.y = int(self.real_y)
            new_tile = self.get_curr_tile(board)
            if(board.is_wall(new_tile[0] + 1, new_tile[1])):
                coords = board.grid_to_abs(new_tile[0], new_tile[1])
                self.real_x = coords[0]
        elif(self.direction == Direction.DOWN):
            self.real_y += self.speed / 60.0
            self.x = int(self.real_x)
            self.y = int(self.real_y)
            new_tile = self.get_curr_tile(board)
            if(board.is_wall(new_tile[0], new_tile[1] + 1)):
                coords = board.grid_to_abs(new_tile[0], new_tile[1])
                self.real_y = coords[1]
        elif(self.direction == Direction.LEFT):
            self.real_x -= self.speed / 60.0
            self.x = int(self.real_x)
            self.y = int(self.real_y)
            new_tile = self.get_curr_tile(board)
            if(board.is_wall(new_tile[0], new_tile[1])):
                coords = board.grid_to_abs(new_tile[0] + 1, new_tile[1])
                self.real_x = coords[0]
        if(curr_x_pos != self.real_x):
            dist = self.real_x - curr_x_pos
        elif(curr_y_pos != self.real_y):
            dist = self.real_y - curr_y_pos
        self.x = int(self.real_x)
        self.y = int(self.real_y)
        old_coords = self.rollback(dist)
        old_tile = board.tile_at(old_coords[0], old_coords[1])
        for i in range(0, len(self.event_queue)):
            evt = self.event_queue.popleft()
            #print("Event %s" % (evt, ))
            tm = evt[1]
            direction = evt[0]
            if(direction == UP):
                if(self.direction == Direction.UP):
                    continue
                if(self.can_go_up(board, old_tile)):
                    self.direction = Direction.UP
            elif(direction == DOWN):
                if(self.direction == Direction.DOWN):
                    continue
                if(self.can_go_down(board, old_tile)):
                    self.direction = Direction.DOWN
            elif(direction == LEFT):
                if(self.direction == Direction.LEFT):
                    continue
                if(self.can_go_left(board, old_tile)):
                    self.direction = Direction.LEFT
            elif(direction == RIGHT):
                if(self.direction == Direction.RIGHT):
                    continue
                if(self.can_go_right(board, old_tile)):
                    self.direction = Direction.RIGHT
            evt = (evt[0], tm - 1)
            if(evt[1] == 0):
                continue
            self.event_queue.append(evt)
        if(isinstance(self, Ghost)):
            if(self.is_vulnerable):
                self.speed = old_speed
        self.x = int(self.real_x // 1)
        self.y = int(self.real_y // 1)

    def rollback(self, dist):
        old_x = self.real_x
        old_y = self.real_y
        if(self.direction == Direction.UP or self.direction == Direction.DOWN):
            old_y -= dist
        elif(self.direction == Direction.LEFT or self.direction == Direction.RIGHT):
            old_x -= dist
        return (old_x, old_y)

    def can_go_up(self, board, old_tile):
        curr_tile = self.get_curr_tile(board)
        tilepos = board.grid_to_abs(curr_tile[0], curr_tile[1])
        if(old_tile != curr_tile):
            if(self.direction == Direction.LEFT):
                if(old_tile != curr_tile):
                    if(board.is_wall(old_tile[0], old_tile[1] - 1)):
                        return False
                    coords = board.grid_to_abs(old_tile[0], old_tile[1])
                    self.real_x = coords[0]
                    self.real_y = coords[1]
                    return True
            elif(self.direction == Direction.RIGHT):
                if(old_tile != curr_tile):
                    if(board.is_wall(curr_tile[0], curr_tile[1] - 1)):
                        return False
                    self.real_x = tilepos[0]
                    self.real_y = tilepos[1]
                    return True
        if(board.is_wall(curr_tile[0], curr_tile[1] - 1)):
            return False
        if(self.real_x == tilepos[0]):
            return True
        return False

    def can_go_left(self, board, old_tile):
        curr_tile = self.get_curr_tile(board)
        tilepos = board.grid_to_abs(curr_tile[0], curr_tile[1])
        if(old_tile != curr_tile):
            if(self.direction == Direction.UP):
                if(old_tile != curr_tile):
                    if(board.is_wall(old_tile[0] - 1, old_tile[1])):
                        return False
                    coords = board.grid_to_abs(old_tile[0], old_tile[1])
                    self.real_x = coords[0]
                    self.real_y = coords[1]
                    return True
            elif(self.direction == Direction.DOWN):
                if(old_tile != curr_tile):
                    if(board.is_wall(curr_tile[0] - 1, curr_tile[1])):
                        return False
                    self.real_x = tilepos[0]
                    self.real_y = tilepos[1]
                    return True
        if(board.is_wall(curr_tile[0] - 1, curr_tile[1])):
            return False
        if(self.real_y == tilepos[1]):
            return True
        return False

    def can_go_right(self, board, old_tile):
        curr_tile = self.get_curr_tile(board)
        tilepos = board.grid_to_abs(curr_tile[0], curr_tile[1])
        if(old_tile != curr_tile):
            if(self.direction == Direction.UP):
                if(board.is_wall(old_tile[0] + 1, old_tile[1])):
                    return False
                coords = board.grid_to_abs(old_tile[0], old_tile[1])
                self.real_x = coords[0]
                self.real_y = coords[1]
                return True
            elif(self.direction == Direction.DOWN):
                if(board.is_wall(curr_tile[0] + 1, curr_tile[1])):
                    return False
                self.real_x = tilepos[0]
                self.real_y = tilepos[1]
                return True
        if(board.is_wall(curr_tile[0] + 1, curr_tile[1])):
            return False
        if(self.real_y == tilepos[1]):
            return True
        return False

    def can_go_down(self, board, old_tile):
        curr_tile = self.get_curr_tile(board)
        tilepos = board.grid_to_abs(curr_tile[0], curr_tile[1])
        if(old_tile != curr_tile):
            if(self.direction == Direction.RIGHT):
                if(board.is_wall(curr_tile[0], curr_tile[1] + 1)):
                    return False
                self.real_x = tilepos[0]
                self.real_y = tilepos[1]
                return True
            elif(self.direction == Direction.LEFT):
                if(board.is_wall(old_tile[0], old_tile[1] + 1)):
                    return False
                coords = board.grid_to_abs(old_tile[0], old_tile[1])
                self.real_x = coords[0]
                self.real_y = coords[1]
                return True
        if(board.is_wall(curr_tile[0], curr_tile[1] + 1)):
            return False
        if(self.real_x == tilepos[0]):
            return True
        return False

class Ghost(PlayableSprite):
    """Ghost base class"""
    is_vulnerable = False
    vulnerable_sprite = [pygame.image.load("assets/vulnerable_ghost.png"), pygame.image.load("assets/vulnerable_ghost_inverted.png")]

    ghost_eyes = pygame.image.load("assets/ghost_eyes.png")

    def reset(self):
        self.score = 0
        self.speed = 0

    def __init__(self, path):
        self.alive = True
        self.speed = 0
        self.event_queue = deque([])
        self.base_image = pygame.image.load(path)
        self.vulnerability_counter = 0
        self.vulnerable_sprite_id = 0
        sprite_surface = (self.base_image.get_width() // 2, self.base_image.get_height() // 2)
        self.max_speed = GHOST_MAX_SPEED

        sprite_base = pygame.Rect((0, 0), sprite_surface)
        self.up_sprite = self.base_image.subsurface(sprite_base)

        sprite_base = pygame.Rect((self.base_image.get_width() // 2, 0), sprite_surface)
        self.right_sprite = self.base_image.subsurface(sprite_base)

        sprite_base = pygame.Rect((0, self.base_image.get_height() // 2), sprite_surface)
        self.down_sprite = self.base_image.subsurface(sprite_base)

        sprite_base = pygame.Rect((self.base_image.get_width() // 2, self.base_image.get_height() // 2), sprite_surface)
        self.left_sprite = self.base_image.subsurface(sprite_base)

        self.none_sprite = self.up_sprite

    def update_speed(self):
        self.max_speed = int(float(GHOST_MAX_SPEED) * SPEED_MULTIPLIER)
        print("Ghost max speed = %s" % self.max_speed)

    def current_sprite(self):
        if(not self.alive):
            return self.ghost_eyes
        elif(self.is_vulnerable):
            self.vulnerability_counter += 1
            if(self.vulnerability_counter == 30):
                self.vulnerable_sprite_id = self.vulnerable_sprite_id ^ 1
                self.vulnerability_counter = 0
            return self.vulnerable_sprite[self.vulnerable_sprite_id]
        elif(self.direction == Direction.NONE):
            return self.none_sprite
        elif(self.direction == Direction.UP):
            return self.up_sprite
        elif(self.direction == Direction.DOWN):
            return self.down_sprite
        elif(self.direction == Direction.LEFT):
            return self.left_sprite
        elif(self.direction == Direction.RIGHT):
            return self.right_sprite

class Pacman(PlayableSprite):
    """Pacman object"""
    
    animation_frame = 0
    remaining_time_frame = 10

    def reset(self):
        self.lives = 3
        self.score = 0
        self.speed = 0

    def __init__(self, path, none_path):
        self.alive = True
        self.score = 0
        self.up_anim = []
        self.right_anim = []
        self.down_anim = []
        self.left_anim = []
        self.speed = 0
        self.event_queue = deque([])
        self.base_image = pygame.image.load(path)
        width = self.base_image.get_width() // 2
        height = self.base_image.get_height() // 4
        sprite_surface = (width, height)
        self.max_speed = PACMAN_MAX_SPEED
        self.lives = 3

        sprite_base = pygame.Rect((0, 0), sprite_surface)
        self.left_anim.append(self.base_image.subsurface(sprite_base))
        sprite_base = pygame.Rect((width, 0), sprite_surface)
        self.left_anim.append(self.base_image.subsurface(sprite_base))

        sprite_base = pygame.Rect((0, height), sprite_surface)
        self.up_anim.append(self.base_image.subsurface(sprite_base))
        sprite_base = pygame.Rect((width, height), sprite_surface)
        self.up_anim.append(self.base_image.subsurface(sprite_base))

        sprite_base = pygame.Rect((0, height * 2), sprite_surface)
        self.right_anim.append(self.base_image.subsurface(sprite_base))
        sprite_base = pygame.Rect((width, height * 2), sprite_surface)
        self.right_anim.append(self.base_image.subsurface(sprite_base))

        sprite_base = pygame.Rect((0, height * 3), sprite_surface)
        self.down_anim.append(self.base_image.subsurface(sprite_base))
        sprite_base = pygame.Rect((width, height * 3), sprite_surface)
        self.down_anim.append(self.base_image.subsurface(sprite_base))

        self.none_sprite = pygame.image.load(none_path)

        death_image = pygame.image.load("assets/pacman_death.png")
        self.death_animation = []
        for i in range(0, 11):
            self.death_animation.append(death_image.subsurface(pygame.Rect((26 * i, 0), sprite_surface)))

    def update_speed(self):
        self.max_speed = int(float(PACMAN_MAX_SPEED) * SPEED_MULTIPLIER)
        print("Pacman max speed = %s" % self.max_speed)

    def blit(self, board):
        self.remaining_time_frame -= 1
        if(self.remaining_time_frame == 0):
            self.animation_frame ^= 1
            self.remaining_time_frame = 10
        board.blit(self)

    def current_sprite(self):
        if(self.direction == Direction.NONE):
            return self.none_sprite
        elif(self.direction == Direction.UP):
            return self.up_anim[self.animation_frame]
        elif(self.direction == Direction.DOWN):
            return self.down_anim[self.animation_frame]
        elif(self.direction == Direction.LEFT):
            return self.left_anim[self.animation_frame]
        elif(self.direction == Direction.RIGHT):
            return self.right_anim[self.animation_frame]

    def eat_puck(self, board):
        currtile = self.get_curr_tile(board)
        #print("Pacman is at coordinates %s" % (currtile,))
        tile_object = board.tiles[currtile[0]][currtile[1]]
        midtile_x = currtile[0] * board.tile_width + board.start_x + (board.tile_width // 2)
        midtile_y = currtile[1] * board.tile_height + (board.tile_height // 2)
        global SCORE_SURF
        if(tile_object == Terrain_tiles[2] or tile_object == Terrain_tiles[0]):
            if(self.direction == Direction.UP):
                if(self.y <= midtile_y):
                    board.tiles[currtile[0]][currtile[1]] = Terrain_tiles[1]
                    self.score += 10
                    SCORE_SURF = font.render(str(self.score), True, (255,255,255), (0,0,0))
                    sounds[NOM].play()
                    if(tile_object == Terrain_tiles[0]):
                        for i in ghosts:
                            i.is_vulnerable = True
                        board.vulnerability_timer = 600
            elif(self.direction == Direction.LEFT):
                #print("Going left, midtile_x = %s, currx = %s" % (midtile_x, self.x))
                if(self.x <= midtile_x):
                    board.tiles[currtile[0]][currtile[1]] = Terrain_tiles[1]
                    self.score += 10
                    SCORE_SURF = font.render(str(self.score), True, (255,255,255), (0,0,0))
                    sounds[NOM].play()
                    if(tile_object == Terrain_tiles[0]):
                        for i in ghosts:
                            i.is_vulnerable = True
                        board.vulnerability_timer = 600
        if(self.direction == Direction.DOWN):
            tile_object = board.tiles[currtile[0]][currtile[1] + 1]
            if(tile_object == Terrain_tiles[2] or tile_object == Terrain_tiles[0]):
                if(self.y >= midtile_y):
                    board.tiles[currtile[0]][currtile[1] + 1] = Terrain_tiles[1]
                    self.score += 10
                    SCORE_SURF = font.render(str(self.score), True, (255,255,255), (0,0,0))
                    sounds[NOM].play()
                    if(tile_object == Terrain_tiles[0]):
                        for i in ghosts:
                            i.is_vulnerable = True
                        board.vulnerability_timer = 600
        if(self.direction == Direction.RIGHT):
            tile_object = board.tiles[currtile[0] + 1][currtile[1]]
            if(tile_object == Terrain_tiles[2] or tile_object == Terrain_tiles[0]):
                if(self.x >= midtile_x):
                    board.tiles[currtile[0] + 1][currtile[1]] = Terrain_tiles[1]
                    self.score += 10
                    SCORE_SURF = font.render(str(self.score), True, (255,255,255), (0,0,0))
                    sounds[NOM].play()
                    if(tile_object == Terrain_tiles[0]):
                        for i in ghosts:
                            i.is_vulnerable = True
                        board.vulnerability_timer = 600

    def collision(self, board):
        for ghost in ghosts:
            if(abs(self.real_x - ghost.real_x) < board.tile_width and abs(self.real_y - ghost.real_y) < board.tile_height):
                if(ghost.is_vulnerable and ghost.alive):
                    sounds[PHANTOM_NOM].play()
                    ghost.alive = False
                    ghost.travel_time = 120.0
                    self.score += 100
                    global SCORE_SURF
                    SCORE_SURF = font.render(str(self.score), True, (255,255,255), (0,0,0))
                else:
                    if not ghost.is_vulnerable and ghost.alive and self.alive:
                        self.alive = False
                        self.lives -= 1
                        global LIVE_SURF
                        LIVE_SURF = font.render(str(self.lives), True, (255,255,255), (0,0,0))
                        time.sleep(1.3)

    def play_death_animation(self, board):
        sounds[PACMAN_DEATH].play()
        for i in self.death_animation:
            for j in range(0, 10):
                tick = datetime.datetime.now()
                board.blit_surroundings(self)
                sprite_surface = pygame.transform.scale(i, (board.tile_width, board.tile_height))
                board.screen.blit(sprite_surface, (self.x, self.y))
                ntick = datetime.datetime.now()
                tckdiff = ntick - tick
                tick = ntick
                rendr_time = tckdiff.microseconds // 1000
                #print("Frame computed in %s milliseconds" % rendr_time)
                wait = (tick_rate - rendr_time) / 1000
                pygame.display.flip()
                if(wait > 0):
                    time.sleep(wait)
        board.blit_surroundings(self)
        pacman.alive = True

def parse_tilemap(content):
    tilemap = []
    for i in range(0, 28):
        tilemap.append([])
    lines = str.split(content, '\n')
    for ln in lines:
        x = 0
        if len(ln.strip()) != 0:
            els = str.split(ln, ',')
            for tl in els:
                tlidx = int(tl.strip())
                #print("Terrain tile (%s,%s) = %s" %(x, len(tilemap[x]), Terrain_tiles[tlidx]))
                tilemap[x].append(Terrain_tiles[tlidx])
                x += 1
    return tilemap

def player_setup(player_id, board):
    locfont = pygame.font.SysFont("Arial", 40)
    player_spr = locfont.render("PRESS KEY FOR PLAYER ", True, (255,255,255), (0,0,0))
    player_id_surf = locfont.render(str(player_id), True, (255,255,255), (0,0,0))
    board.screen.blit(player_spr, (0,0))
    board.screen.blit(player_id_surf, (player_spr.get_width() + 10,0))
    pygame.display.flip()
    while True:
        for event in pygame.event.get():
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_q:
                    sys.exit(0)
            if event.type == pygame.JOYBUTTONDOWN:
                evt = event.joy
                for e in pygame.event.get():
                    pass
                return evt
        time.sleep(0.1)

def setup_input_for_joystick(player_id, board, joystick_id):
    directions = ["UP......", "RIGHT", "DOWN.....", "LEFT......"]
    retdirs = []
    locfont = pygame.font.SysFont("Arial", 40)
    keysetup = locfont.render("KEY SETUP - PLAYER ", True, (255,255,255), (0,0,0))
    pid_surface = locfont.render(str(player_id), True, (255,255,255), (0,0,0))
    press_the = locfont.render("PRESS BUTTON ", True, (255,255,255), (0,0,0))
    i = 0
    btn_surf = locfont.render(directions[i], True, (255, 255, 255), (0,0,0))
    board.screen.blit(keysetup, (0, 0))
    board.screen.blit(pid_surface, (keysetup.get_width() + 10, 0))
    board.screen.blit(press_the, (0, keysetup.get_height() + 10))
    board.screen.blit(btn_surf, (press_the.get_width() + 10, keysetup.get_height() + 10))
    pygame.display.flip()
    last_read = -1
    while i < len(directions):
        for event in pygame.event.get():
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_q:
                    sys.exit(0)
            if event.type == pygame.JOYBUTTONDOWN:
                print event
                if event.joy != joystick_id:
                    continue
                if event.button == last_read:
                    continue
                last_read = event.button
                retdirs.append(event.button)
                i += 1
                if i >= len(directions):
                    break
                btn_surf = locfont.render(directions[i], True, (255, 255, 255), (0,0,0))
                board.screen.blit(btn_surf, (press_the.get_width() + 10, keysetup.get_height() + 10))
                pygame.display.flip()
        time.sleep(0.1)
    for e in pygame.event.get():
        pass
    return retdirs

def respawn(board):
    global spawn_timers
    spawn_timers = [0, 300, 600, 900]
    board.vulnerability_timer = 0
    akabe.spawn(board, 13, 10)
    pinky.spawn(board, 11, 13)
    aosuke.spawn(board, 13, 13)
    guzuta.spawn(board, 15, 13)
    pacman.spawn(board, 13, 22)

def main():
    global SCORE_SURF
    SCORE_SURF = font.render("0", True, (255,255,255), (0,0,0))
    global LIVE_SURF
    LIVE_SURF = font.render("3", True, (255,255,255), (0,0,0))

    global SPEED_INCREASE
    global SPEED_DECREASE
    global SPEED_MULTIPLIER
    SPEED_INCREASE = int(float(BASE_SPEED_INCREASE) * SPEED_MULTIPLIER)
    SPEED_DECREASE = BASE_SPEED_DECREASE * SPEED_MULTIPLIER
    print("Speed increase = %s, speed decrease = %s" % (SPEED_INCREASE, SPEED_DECREASE))

    #global NEED_INPUTS
    global joy_map
    global joy2play
    global clients

    print joy2play
    print joy_map

    board = Board("tilemap.pacman")

    respawn(board)
    vulnerability_timer = 0
    init_player_entities = [pacman, akabe, pinky, aosuke, guzuta]
    player_entities = []
    for i in range(5 - ROTATE, 5):
        player_entities.append(init_player_entities[i])
    for i in range(0, 5 - ROTATE):
        player_entities.append(init_player_entities[i])

    for i in player_entities:
        i.reset()
        i.update_speed()
    player_mappings = [
            [pygame.K_UP, pygame.K_RIGHT, pygame.K_DOWN, pygame.K_LEFT],
            [pygame.K_w, pygame.K_d, pygame.K_s, pygame.K_a],
            [pygame.K_t, pygame.K_h, pygame.K_g, pygame.K_f],
            [pygame.K_i, pygame.K_l, pygame.K_k, pygame.K_j],
            [pygame.K_c, pygame.K_v, pygame.K_b, pygame.K_n]
            ]

    pygame.display.flip()

    sounds[INTRO].play()
    time.sleep(5.0)
    for event in pygame.event.get():
        if(event.type == pygame.KEYDOWN and event.key == pygame.K_q):
            return 1
        continue

    while True:
        if pacman.lives == 0:
            fnt = pygame.font.SysFont("Arial", 60)
            game_over = fnt.render("GAME OVER", True, (255, 255, 255))
            continue_msg = fnt.render("PRESS A KEY TO CONTINUE", True, (255, 255, 255))
            board.screen.blit(game_over, (board.screen.get_width() // 2 - 200, board.screen.get_height() // 2 - 80))
            board.screen.blit(continue_msg, (board.screen.get_width() // 2 - 400, board.screen.get_height() // 2))
            pygame.display.flip()
            while True:
                for event in pygame.event.get():
                    if event.type == pygame.KEYDOWN:
                        return 0
                time.sleep(0.01666)
        tick = datetime.datetime.now()
        for i in range(0, 4):
            if(spawn_timers[i] == 0):
                continue
            spawn_timers[i] -= 1
            if(spawn_timers[i] == 0):
                board.blit_surroundings(ghosts[i])
                ghosts[i].spawn(board, 13, 10)
        if(board.vulnerability_timer > 0):
            board.vulnerability_timer -= 1
            if(board.vulnerability_timer == 0):
                for i in ghosts:
                    i.is_vulnerable = False
        rsocks, _, _ = select.select(clients, [], [], 0)
        #rsocks = []
        for i in rsocks:
            idx = clients.index(i)
            msg = clients[idx].recv(1024)
            while len(msg) != 0:
                cmd = msg[:1]
                msg = msg[1:]
                idx = int(cmd)
                player_entities[idx].increase_speed()
        for event in pygame.event.get():
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_q:
                    return 1
                for i in range(0, 5):
                    for j in range(0, 4):
                        if event.key == player_mappings[i][j]:
                            if(player_entities[i].alive):
                                #player_entities[i].increase_speed()
                                player_entities[i].queue_event(j)
            if event.type == pygame.JOYBUTTONDOWN:
                player = joy2play[event.joy]
                btn = event.button
                print("Player %s, event.joy = %s, event.button = %s" % (player, event.joy, event.button))
                direction = -1
                for i in range(0, 4):
                    if btn == joy_map[event.joy][i]:
                        direction = i
                        break
                if direction == -1:
                    print "Unknown"
                    continue
                #player_entities[player].#increase_speed()
                print("Queuing direction %s for player %s" % (direction, player))
                player_entities[player].queue_event(direction)
        check_alive = []
        for i in range(0, 4):
            if not ghosts[i].alive:
                check_alive.append(i)
        for i in range(0, 5):
            player_entities[i].decrease_speed()
            player_entities[i].update(board)
        for i in check_alive:
            if ghosts[i].alive:
                spawn_timers[i] = 150
        for i in range(0, 5):
            board.blit_surroundings(player_entities[i])
        for i in range(0, 4):
            board.blit(ghosts[i])
        pacman.collision(board)
        pacman.eat_puck(board)
        pacman.blit(board)
        board.blit_score()
        board.blit_lives()
        pygame.display.flip()
        ntick = datetime.datetime.now()
        tckdiff = ntick - tick
        tick = ntick
        rendr_time = tckdiff.microseconds // 1000
        #print("Frame computed in %s milliseconds" % rendr_time)
        wait = (tick_rate - rendr_time) / 1000
        if(wait > 0):
            time.sleep(wait)
        if(not pacman.alive):
            pacman.play_death_animation(board)
            respawn(board)

args = sys.argv
rd_inputs = False
if len(args) > 1:
    with open(args[1], 'r') as inputs:
        str_json = inputs.read()
        data = json.loads(str_json)
        joy2play = data['joy2play']
        joy_map = data['joy_map']
    rd_inputs = True
    print joy2play
    print joy_map

tick_rate = 16.667

UP = 0
RIGHT = 1
DOWN = 2
LEFT = 3

INTRO = 0
NOM = 1
PHANTOM_NOM = 2
PACMAN_DEATH = 3

pygame.init();
pygame.font.init()
pygame.joystick.init()
font = pygame.font.SysFont("Arial", 20)
SCORE = font.render("SCORE = ", True, (255,255,0))
LIVES = font.render("LIVES = ", True, (255,255,0))

pygame.mixer.init()
sounds = [pygame.mixer.Sound("assets/sfx/intro.wav"), pygame.mixer.Sound("assets/sfx/nom.wav"), pygame.mixer.Sound("assets/sfx/phantom_nom.wav"), pygame.mixer.Sound("assets/sfx/pacman_death.wav")]

akabe = Ghost("assets/akabe.png")
pinky = Ghost("assets/pinky.png")
aosuke = Ghost("assets/aosuke.png")
guzuta = Ghost("assets/guzuta.png")
pacman = Pacman("assets/pacman.png", "assets/pacman_none.png")

SCORE_SURF = font.render("0", True, (255,255,255), (0,0,0))

ghosts = [akabe, pinky, aosuke, guzuta]
spawn_timers = [0, 300, 600, 900]

# Just for first blit
board = Board("tilemap.pacman");

if not rd_inputs:
    joy_map = [-1, -1, -1, -1, -1]
    joy2play = [0, 0, 0, 0, 0]

    joysticks = [pygame.joystick.Joystick(x) for x in range(pygame.joystick.get_count())]
    for i in joysticks:
        i.init()
    player = 0
    for i in joysticks:
        joy_id = player_setup(player, board)
        print("Player %s is joystick %s" % (player, joy_id))
        joy2play[joy_id] = player
        joy_map[joy_id] = setup_input_for_joystick(player, board, joy_id)
        player += 1

    with open("inputs.json", 'w') as out_fl:
        out_fl.write("{\"joy2play\":")
        out_fl.write(str(joy2play))
        out_fl.write(",\"joy_map\":")
        out_fl.write(str(joy_map))
        out_fl.write("}")

server = socket.socket()
server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
server.bind(('0.0.0.0', 4444))
server.listen(1)
clients = []
for i in range(0, 1):
    clients.append(server.accept()[0])
server.close()

NEED_INPUTS = False

ROTATE = 0

while main() == 0:
    ROTATE += 1
    ROTATE %= 5
    continue
