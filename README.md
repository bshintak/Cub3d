# Cub3d

### search_player
function that searches for the player in a map represented as a 2D array of characters.

### search_direction
function that sets the direction vector of the player based on the character representing their initial direction.
- Direção Norte: dir_x = 0, dir_y = -1
- Direção Sul: dir_x = 0, dir_y = 1
- Direção Oeste: dir_x = -1, dir_y = 0
- Direção Leste: dir_x = 1, dir_y = 0

### search_plane
function that defines the player's camera plane vector based on their direction. 
(The plane vector is used to calculate the camera's position in three-dimensional space)

### raycasting_loop
the function iterates over each column of the screen and calculates the information for a single ray for each column.

### calc_delta_dist
used to determine the distance from the player to the next vertical or horizontal wall.

### calc_side_dist
the side distance is the distance from the player to the next grid line in the map for each direction.

### hit_wall
this function determines whether the ray hit a wall in the map or not and calculates the perpendicular distance of the collision from the side distance.

### put_color
this function puts color to a given pixel in the image. The code sets different shades, creating a 3D wall effect.

### raycasting_key
a function to handle key press events

### move_w || move_s
the function checks if the next position of the player in the x-axis and y-axis are empty spaces on the map. If both x-axis and y-axis next positions
are empty spaces, then the player's x and y position are updated to their next positions, moving the player forward in the direction of the current angle.

### rotate_right
rotates the player's direction and camera plane in the clockwise direction

### rotate_left
rotates the player's direction and camera plane in the counterclockwise direction
