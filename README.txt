### Midterm Project - COMP 308
=====
Author: Iury Roger Painelli
Student ID: 300333846

=====
## How to run:

==>Stage 1 (Splines)
make clean
make
Run: ./mproj assets/priman.asf
OR
Run: ./mproj assets/priman.asf assets/walking.con

==>Stage 2 
Run: ./mproj assets/priman.asf
Press 'q' to switch to editor mode

Tu run walking keyframe animation  ./mproj assets/priman.asf assets/walking.con
To run my animation file --Last item of stage 2--, just run:  ./mproj assets/priman.asf assets/poses.con

==>Stage 3 (Camera control)
Rotation: SHIFT + LEFT BUTTON
Pan: SHIFT + RIGHT BUTTON
Zoom: SHIFT + SCROLL UP or DOWN

==>Advanced Stage
It's all there =)

=====
IMPORTANT: There is a menu attached with the middle-button click to control different parts of the assignment.

=====
## Controls:

==>Stage 2 mode (Editor mode)
Select Bone: CTRL + LEFT BUTTON
Move Bone: RIGHT BUTTON
Switch Axis: 'x' or Option in the menu
Save Keyframe: 's' or Option in the menu

'p' next Keyframe
Keyframe Animation
'f' is Rewind
'g' is Play
'h' is Stop
'j' is Pause
'k' is Fast Forward

=====
## What I did (a lot)
==>Stage 1 (Splines or Animation Mode)
		I created three viewports: Trajectory, Speed and Render.
		Catmull-Rom spline to create the splines with chord length table to maintain the same interpolation speed.
==>Stage 2 (Editor Mode)
		The application reads the .asf file and creates one keyframe.
		The user can select, move, and save current pose in a file. I used the same structure as .amc files to save the pose.
		The application reads .con files to load saved keyframes. The .con file describes the file for the keyframes.
		I created two .con files: walking.con and poses.con
		NOTE: the application does not save .con file, I created them by hand
==>Stage 3 
		I used shoemaker's code to control the camera.
		To pan I used translation and to zoom I used scale
		
==>Advanced Stage
		I put everything together in the main viewport, and created the menu to control everything.
That's it! Thank you for reading the file. :)

