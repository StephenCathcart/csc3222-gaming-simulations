##CSC3222 Gaming Simulations

###Overview
Multiple spheres inside a bounding box. Broadphase and narrowphase collision detection in place. On detection the penetration distance is fixed and an impulse is given to the sphere. Small global drag applied to all spheres.

###Notes
The framework is based on a custom component entity system design using a messaging system to transfer data (collision data in this case). 

All the code relevant to this coursework (Gaming simulations) can be found in:

- Game.h - Creation of cube and spheres
- CollisionSystem.h - Collision detection functions and transmits response data
- PhysicsSystem.h -	Handles the collision such as penetration correction and applys impulse. Also uses a simple euler algorithm in update function.
- CollisionData.h - Stores all collision reponse data used by systems 
- MovementComponent.h - Stores all information with regards to spheres (position, velocity etc.)

###Video
![enter image description here](https://www.youtube.com/watch?v=XXr7A0xqccw)
