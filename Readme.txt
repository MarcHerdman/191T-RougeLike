Marc Herdman
I started by converting the Scene class into a pure virtual function. Then I made all menus and levels child classes of Scene. That allowed for a stack to be created in main and all calls in main to Scene call the top of the stack instead. Now when a menu is pushed to the stack in the game or main menu it will render that scene automatically and when it's done, it pops off the stack and the original scene is automatically rendered again. I made a button system with onMouseOver style highlighting to navigate the various menus of the game. Next I converted the texture class to allow for sprite sheets, scale, and pivot points. In addition, when rendering any sprite, flags can be set for flip and mirror. I used a recursive backtracking algorithm to build a random maze for each level and incorporated Dijkstra's algorithm to generate a path and manhattan distance to the player from every cell of the maze. That allowed the monster and exit to always start a reasonable distance from the player. It also allows the monster to hunt down the player.

Christian Vaughn
I programmed the visual effect used in our game. I started with a Stencil mask around the player, I enabled the stencil buffer in main.cpp and drew a mask which was a triangle fan to make a circle, and a triangle to act as a flashlight beam. Stencil buffers lacking alpha made it look very bad because most of the map was all black. I ended up using a shader that generates a gradient noise instead. This plus a timer in the code makes a semi-realistic fog effect that moves through the play screen. I had to go online and read many articles to figure out how to generate noise with an algorithm because my first approach of using a noise map texture for fog didn't look appealing. my quad with the shader somehow ended up being slightly larger than our game area, so I used the stencil mask I had set up to hide the fog that would float outside the game screen. I also programmed the sound and added button click, and footstep sound effects and level music. I had to add a function to properly pause and unpause the music in the game so it would start and stop at the same spot. The last thing I did was make a death screen and win screen by modifying the pause menu popups












