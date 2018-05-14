# Graphics_Exam_IMT2531_mathisti
Exam for Graphics programming in OpenGL 2018 NTNU

# Features:
### Camera:
Control camera orientation using mouse, and move the camera using the keys ‘i’ and ‘k’ for z axis, ‘j’ and ‘l’ for x axis, and ‘y’
and ‘h’ for y axis. You can zoom using the scroll wheel on the mouse.

Press '-' on the Norwegian keyboard will alow you to switch between a camera that follows the glider in the scene and a free-moving camera.

### Glider:
The Glider can be controlled using the WASD keys. W and S makes a pitch movement where 'W' is downward and 'S' is upward. 'A'and 'D' rolls left and right respectively.

Using ',' and '.' You can change the speed of the glider, where ',' makes the speed increase (positively) and '.' makes the speed decrease (negatively accelerate!) there is no maximum or minimum speed for the glider, so it can go backwards (it will go faster backwards if you keep pressing '.' when the speed is negative).

The camera that follows the glider does not follow properly, and is only oriented toward the original front of the plane.

### Other Features:
Using 'R' you can reset the glider to it's original position.

# Deployment:
To set up, clone the repo. Start cmake and navigate the source to the main folder of the repo and say it should build in path_to_folder/build. Hit "configure", then "generate".

After generating, move to the directory and enter the "build" folder. Run the solution file "Exam_Graphics_Programming_2018.sln".

When inside, right-click the solution in the solution explorer and select "properties". Change the "Single startup project" from "ALL_BUILD" to "Exam_Graphics_Programming_2018" and click "OK". Build and run the code and you are set to go.
