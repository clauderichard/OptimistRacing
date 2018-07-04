# OptimistRacing
A video game where you try to keep your head up, literally!

# Setup
Unfortunately, it might be a pain to set up to actually run on your computer, since the project is a bit old with several dependencies.
The dependencies I can think of off the top of my head are: Allegro 5, libpng, Lua.
If you try to run this you might get an error about a missing DLL or something.

# The basic idea
It's a video game where you try to balance a reverse pendulum in 3D while making it move on a coloured track.
The colours matter: the pendulum's colour and the floor's colour must match according to a special formula (see "Electric Colours" in the documentation), otherwise you just fall through!
If I remember correctly, there are objects you can touch that change the pendulum's colour, which helps you go on other floors.
The object of the game is to reach the finish zone without letting the pendulum hit the floor.

# The physics model
The thing you control consists of 2 parts: The bottom part is attached to the floor,
as long as the bottom part's colour has a non-empty intersection with the colour of the floor.

## Bottom part
The bottom part is free to rotate around the vertical axis, and has a mass and moment of inertia.

## Top part
The top part is attached by a massless rigid rod to the bottom part.
At the non-stable equilibrium position, the top is directly above the bottom part.
But the rod-top-part can tilt around the model's z-axis.
So if you're looking from behind the model i.e. the camera is along the z-axis of the model,
then you can see the top part of the pendulum (and the rod with it) tilting left or right about the bottom part,
but it can't tilt forward or backward.

## Controls
In the game, using the arrow keys applies a corresponding force to the bottom (in the model's x or z direction).
In addition, the left and right arrow keys also apply a torque (around the vertical axis) to the bottom part,
so this adds another level of control you need to keep track of when playing lest you spin out of control
(the faster you spin, the faster the pendulum will fall!)
The up and down arrows don't apply any torque.
