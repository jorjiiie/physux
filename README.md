# physux
Physics Simulator + Renderer in OpenGL

# Features
* Simulates charged particles in 3d space
* Support for a global constant magnetic field
* Attachable logger for individual particles that logs force, position, and velocity
* Tick-based system that simulates motion in arbitrary units of 1 time unit, can be changed to 500x and half speed with keybinds (2 and 0 + .)
* (I think) Super cool sphere generator using triangles 🤓



# If I wasn't lazy I would do this (also known as future plans)
* Separate RenderWindow -> Actual RenderWindow and a PhysicsWindow
* Give it a UI so you're not guessing all the keys
* Clean up the key register mechanics so editing the state isn't going on in multiple places -> this should just be in a single inputprocess function
* Support for circuits & implement an integrator (monte carlo) to support electromagnetism 
* Render things other than spheres

