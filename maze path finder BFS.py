maze = [[-1, -1, -1, -1, -1, -1, -1, -1, -1],
        [-1,  0, -1,  0,  0,  0, -1,  0, -1],
        [-1,  0, -1,  0, -1,  0, -1,  0, -1],
        [-1,  0,  0,  0, -1,  0, -1,  0, -1],
        [-1, -1, -1, -1, -1,  0, -1,  0, -1],
        [-1,  0,  0,  0,  0,  0,  0,  0, -1],
        [-1, -1, -1, -1, -1, -1, -1, -1, -1]]
start = (1, 1)
maze[1][1] = 1
end = (1, 7)
size = (9, 7)
path = []
queue = []

def mark_distance(x, y):
    offsets = ((1, 0), (-1, 0), (0, -1), (0, 1))
    for offset in offsets:
        temp_x = x + offset[0]
        temp_y = y + offset[1]
        if maze[temp_x][temp_y] == 0:
            maze[temp_x][temp_y] = maze[x][y] + 1
            queue.append((temp_x, temp_y))
        if (temp_x, temp_y) == end:
            get_path(maze[x][y] + 1, end[0], end[1])
            return
    unexplored = queue.pop(0)
    mark_distance(unexplored[0], unexplored[1])

def get_path(distance, x, y):
    offsets = ((1, 0), (-1, 0), (0, -1), (0, 1))
    for offset in offsets:
        temp_x = x + offset[0]
        temp_y = y + offset[1]
        if (temp_x, temp_y) == start:
            return
        elif maze[temp_x][temp_y] == distance - 1:
            path.insert(0, (temp_x, temp_y))
            get_path(distance - 1, temp_x, temp_y)

def show_maze(): # show the maze in output
    for i in range(len(maze)):
        for j in range(len(maze[i])):
            if maze[i][j] < 0 or maze[i][j] >= 10:
                print(maze[i][j], end= ' ')
            else:
                print(' ', maze[i][j], sep= '', end= ' ')
        print()

# main loop
mark_distance(1, 1)
show_maze()
print(path)