# Day-6
import time
import concurrent.futures

with open('day-6/input.txt', 'r') as file:
    clean_grid = [list(line.strip()) for line in file]

orientation = [[-1, 0], [0, 1], [1, 0], [0, -1]]
path = set()

def print_grid(grid):
    for row in grid:
        print(''.join(row))


def increase_index(index):
    return index + 1 if index < 3 else 0


def find_start(grid):
    for row_index, row in enumerate(grid):
        if '^' in row:
            col_index = row.index('^')
            return row_index, col_index
    return None  # Return None if '^' is not found


def walk_until_wall(grid, start_index):
    row_index, col_index = start_index
    index = 0
    while 1 <= row_index < len(grid)-1 and 1 <= col_index < len(grid[0])-1:
        grid[row_index][col_index] = 'X'
        path.add((row_index, col_index))
        next_y, next_x = orientation[index][0], orientation[index][1]
        while grid[row_index+next_y][col_index+next_x] == '#' or grid[row_index+next_y][col_index+next_x] == 'O':
            index = increase_index(index)
            next_y, next_x = orientation[index][0], orientation[index][1]

        row_index += next_y
        col_index += next_x

    path.add((row_index, col_index))
    grid[row_index][col_index] = 'X' # Add the last 'X'


def walk_around(grid, start_index):
    pathed = set()
    row_index, col_index = start_index
    index = 0
    while 0 < row_index < len(grid)-1 and 0 < col_index < len(grid[0])-1:
        grid[row_index][col_index] = 'X'
        if (row_index, col_index, index) in pathed:
            return 1
        pathed.add((row_index, col_index, index))
        next_y, next_x = orientation[index][0], orientation[index][1]
        while grid[row_index+next_y][col_index+next_x] == '#' or grid[row_index+next_y][col_index+next_x] == 'O':
            index = increase_index(index)
            next_y, next_x = orientation[index][0], orientation[index][1]

        row_index += next_y
        col_index += next_x

    return 0


def walk_around_with_rudolf(coord):
    grid = [row.copy() for row in clean_grid]
    grid[coord[0]][coord[1]] = 'O'  # Add Rudolf
    result = walk_around(grid, start_index)
    # if result:
    #     print_grid(grid)
    #     print('    ')
    return result


# Part-1
grid = [row.copy() for row in clean_grid]
start_index = find_start(grid)
walk_until_wall(grid, start_index)
# print_grid(grid)
print("Count of Xs:", len(path))

# Part-2
start_time = time.time()

with concurrent.futures.ThreadPoolExecutor() as executor:
    results = list(executor.map(walk_around_with_rudolf, path))

loop_counter = sum(results)

end_time = time.time()
elapsed_time = end_time - start_time

print(len(results))
print("Loop Counter:", loop_counter)
print(f"Part-2 execution time: {elapsed_time:.2f} seconds")
 # 7.25 seconds on M1 Macbook Pro
 # 6.21 seconds on Ryzen 5 5600X
