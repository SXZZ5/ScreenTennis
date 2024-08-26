- struct motion: to define speeds of the shooter-platform and the striker goti. Speeds in pixels hai ye. Problem ye hai ki 1 pixel per frame bhi visually bahut high speed hoti hai. So, what I have currently done for the workaround is to update or "do-movements" once for every 1000 frames only. The right way to deal with this problem would be to learn about timers in SDL, but I AM LAZY.

*abhi dikkat ye hai na ki aise karne pe, 1000frames aane me kitna time lagega, wo koi fix to hai nahi. Kabhi CPU idle hai to 1000frames jaldi aagye, kabhi thodi der se aaye. Iss kaaran se mere animation me achaanak se speed bumps dikhti hain.*

- init(): Initialisation of SDL_Subsystems.
- shutdown(): Free resources and quit SDL; 
- openWindow(): opens up a window, with a title and size and stuff.
- openRenderer(): gets a rendering context for the window's backbuffer.

- createTargetRect(): Defines the position and dimensions of the target object to be hit. Currently at centre of window.
- createShooterRect(): Defines the position of the shooter-platform from which my striker will detach and go.
- createStrikerRect(): Defines the initial position of the striker on top of the shooter platform. 

*Note that: Abhi mai createStrikerRect() ko repeatedly call karta hoon har frame me, shooter platform ko move karne ke baad. Yaani striker, move-nahi kar raha hai, bas chipka rakha hai shooter-platform pe.*

- createXaxis(): Guidelines ki x-axis.
- createYaxis(): Guidelines ki y-axis.

- moveShooter(): Shooter-platform ko move karane ka logic.

- loadStriker(): Striker ko image se load karke Texture me convert karta hai.

