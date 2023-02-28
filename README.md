# FdF

First graphical project at 42 Prague, using the [minilibx](https://github.com/42Paris/minilibx-linux) graphics library.

>This project is a simple wireframe model representation of a 3D landscape by linking various points (x, y, z) thanks to line segments (edges). The coordinates of the landscape are stored in a .fdf file passed as a parameter to the program.

## **About:**
**Mandatory part:**
- Your program has to display the image in a window.
- The management of your window must remain smooth (changing to another window, minimizing, and so forth).
- Pressing ESC must close the window and quit the program in a clean way.
- Clicking on the cross on the window’s frame must close the window and quit the program in a clean way.
- The use of the images of the MiniLibX is mandatory

**Bonus part:**
- Include one extra projection (such as parallel or conic)
- Zoom in and out.
- Translate your model.
- Rotate your model.
- Add one more bonus of your choice

### Example input:
```
$>cat 40.fdf
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 4 4 0 0 4 4 0 0 0 4 4 4 4 4 0 0 0
0 0 4 4 0 0 4 4 0 0 0 0 0 0 0 4 4 0 0
0 0 4 4 0 0 4 4 0 0 0 0 0 0 0 4 4 0 0
0 0 4 4 4 4 4 4 0 0 0 0 4 4 4 4 0 0 0
0 0 0 4 4 4 4 4 0 0 0 4 4 0 0 0 0 0 0
0 0 0 0 0 0 4 4 0 0 0 4 4 0 0 0 0 0 0
0 0 0 0 0 0 4 4 0 0 0 4 4 4 4 4 4 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
$>
```
Each number represents a point in space:
- The horizontal position corresponds to its axis.
- The vertical position corresponds to its ordinate.
- The value corresponds to its altitude.

## **Usage:**
*This program was compiled and tested on Linux. If you have problems on other platforms, just install Gentoo*

```shell
# Clone the repository:
$> git clone --recursive https://github.com/fv99/fdf.git

# Compile:
$> make

# Run with valid map as parameter:
$> ./fdf map.fdf
```

## **Controls:**

*To be added*