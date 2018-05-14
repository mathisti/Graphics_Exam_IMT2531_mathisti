# Graphics_Exam_IMT2531_mathisti
Exam for Graphics programming in OpenGL 2018 NTNU

# Features:
### Camera:
Control camera orientation using mouse, and move the camera using the keys ‘I’ and ‘K’ for z axis, ‘J’ and ‘L’ for x axis, and ‘Y’
and ‘H’ for y axis. You can zoom using the scroll wheel on the mouse (not the 'N' and 'M' buttons!). Controls for the camera is not optimal, and it will move once, pause, and start moving again.

Press '-' on the Norwegian keyboard will alow you to switch between a camera that follows the glider in the scene and a free-moving camera.

### Glider:
The Glider can be controlled using the WASD keys. W and S makes a pitch movement where 'W' is downward and 'S' is upward. 'A'and 'D' rolls left and right respectively.

Using ',' and '.' You can change the speed of the glider, where ',' makes the speed increase (positively) and '.' makes the speed decrease (negatively accelerate!) there is no maximum or minimum speed for the glider, so it can go backwards (it will go faster backwards if you keep pressing '.' when the speed is negative). At high speeds, the camera gets a little choppy.

The camera that follows the glider does not follow properly, and is only oriented toward the original front of the plane.

### Other Features:
Using 'R' you can reset the glider to it's original position.
If you press 'F' you will move your plane to a random position. Does not check whether you actually end up inside the map or not!

Source for generating random floats for the random move: https://stackoverflow.com/a/686373 (last accessed 14.05.2018)

# Deployment:
**NOTE: cmake is only made and tested for windows, probably won't work on other operating systems!**

To set up, clone the repo. Start cmake and navigate the source to the main folder of the repo and say it should build in path_to_folder/build. Hit "configure", then "generate".

After generating, move to the directory and enter the "build" folder. Run the solution file "Exam_Graphics_Programming_2018.sln".

When inside, right-click the solution in the solution explorer and select "properties". Change the "Single startup project" from "ALL_BUILD" to "Exam_Graphics_Programming_2018" and click "OK". Build and run the code and you are set to go.


# Notes from the development process:
### Framework
Framework can be found here: https://github.com/Avokadoen/learnOpenGLCode (last accessed 14.05.2018) Version used was taken 11.05.2018.
Entire framework is not in the delivery as the entire framework was not needed for what i accomplished.

### Glider:
Glider was turned from a .blender file into an .obj file using blender.

### Heightmap:
Heightmap was made using blender rather than code.

For the process of doing so, there is a very handy guide here: http://johnflower.org/tutorial/make-mountains-blender-height-maps (last accessed 14.05.2018).

In case the site is down or you are otherwise unable to access it, i'll walk you through the proccess here:

#### Turning a greyscale image file into a heightmap with blender:
start by making sure "*import images as planes*" is enabled. You can do this easily by going to file -> import -> and see if the option appears there. If it does not, open the "Blender User Preferences", which can be easily done by pressing *ctrl + alt + u*. Press on *Add-ons*, *import-export*, and scroll down untill you find "*import images as planes*". Tick the checkbox, and you should be good to go.

Remove the cube in the center by right-clicking on it, and pressing x, enter, and import your image as a plane.

Press tab to enter edit mode, and press W to bring up the *specials menu*. In there find *subdivide*. Turn *number of cuts up*, I used 100 for my heightmap.

Now go back to Object mode using tab or but navigating through the menu close to the bottom.

Find the *properties* menu and click on the *wrench (modifier icon)*. Click add modifier and select "*Displace*". Click on the *texture icon (looks like a checkerboard)* and select the texture from the image you loaded.

Change the "*Texture Coordinates*" modifier from "*Local*" to "*UV*", and For *UV map* select "*UVmap*". Choose "*Smooth*" *shading* on the left side of the screen, and change the *strength* of the modifier on the right side of the screen untill you're happy with the look of the map (the strength is likely too high, i ended up with 0.200 for mine). When done Click *apply* for the modifier, save the .blender file if you want, and export the file to .obj by going File -> Export -> Wavefront(.obj) and you are done!
