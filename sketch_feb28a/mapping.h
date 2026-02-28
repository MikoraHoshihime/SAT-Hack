void mapping() {
    // 1. Get distance and convert angle to radians
    double d = get_distance();
    double theta = sat_dir * (M_PI / 180.0);

    // 2. Calculate the wall coordinate (endpoint)
    double wall_x = sat_pos[0] + d * std::sin(theta);
    double wall_y = sat_pos[1] + d * std::cos(theta);

    // 3. Supercover Algorithm: Mark the path as EMPTY
    double x1 = sat_pos[0], y1 = sat_pos[1];
    double x2 = wall_x, y2 = wall_y;

    double dx = std::abs(x2 - x1);
    double dy = std::abs(y2 - y1);
    int x = std::floor(x1);
    int y = std::floor(y1);

    int n = 1;
    int x_step = (x2 > x1) ? 1 : -1;
    int y_step = (y2 > y1) ? 1 : -1;
    double error;

    // Boundary initialization for the line algorithm
    if (dx == 0) { x_step = 0; error = 1e10; }
    else { n += std::abs(int(std::floor(x2)) - x); error = (std::floor(x1) + (x2 > x1 ? 1 : 0) - x1) * dy; }

    if (dy == 0) { y_step = 0; error -= 1e10; }
    else { n += std::abs(int(std::floor(y2)) - y); error -= (std::floor(y1) + (y2 > y1 ? 1 : 0) - y1) * dx; }

    // Trace the line through the grid
    for (; n > 0; --n) {
        if (x >= 0 && x < 400 && y >= 0 && y < 700) {
            grid[x][y] = EMPTY;
        }
        if (error > 0) { y += y_step; error -= dx; }
        else if (error < 0) { x += x_step; error += dy; }
        else {
            x += x_step; y += y_step; error += dy - dx;
            if (x >= 0 && x < 400 && y >= 0 && y < 700) grid[x][y] = EMPTY;
            n--;
        }
    }

    // 4. Proximity Logic: Mark the 4 cells around the wall_coord as WALL
    // This replicates your Python proximity() function logic
    int x_floor = (int)std::floor(wall_x);
    int x_ceil  = (int)std::ceil(wall_x);
    int y_floor = (int)std::floor(wall_y);
    int y_ceil  = (int)std::ceil(wall_y);

    int px[2] = {x_floor, x_ceil};
    int py[2] = {y_floor, y_ceil};

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (px[i] >= 0 && px[i] < 400 && py[j] >= 0 && py[j] < 700) {
                grid[px[i]][py[j]] = WALL;
            }
        }
    }
}