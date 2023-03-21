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
- Include one extra projection (**Parallel**)
- Zoom in and out.
- Translate your model.
- Rotate your model.
- Add one more bonus of your choice - **Anti-Aliasing**

### **Example input:**
```
$>cat test.fdf
0 0 1 2 3 4 5 6 7 8 9
0 0 0 1 2 3 4 5 6 7 8
0 0 0 0 1 2 3 4 5 6 7
0 0 0 0 0 1 2 3 4 5 6
0 0 0 0 0 0 1 2 3 4 5
0 0 0 0 0 0 0 1 2 3 4
0 0 0 0 0 0 0 0 1 2 3
0 0 0 0 0 0 0 0 0 1 2
0 0 0 0 0 0 0 0 0 0 1
$>
```
**Produces the following output:**

![screenshot](https://user-images.githubusercontent.com/108353744/226677024-10c8a229-8c5e-46ab-abb0-9da35c72c9b3.png)

## **Usage:**
*This program was compiled and tested on Linux.*

```shell
# Clone the repository:
$> git clone --recursive https://github.com/fv99/fdf.git

# Compile:
$> make

# Run with valid map as parameter:
$> ./fdf map.fdf
```
