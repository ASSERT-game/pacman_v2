# PacMan v2

Having created [this version](https://github.com/ASSERT-game/pacman), I knew the overall scope
of the game I wanted to make.

In this version I further develop a library that interacts with SDL that makes
some things easier. These things include working with textures, Xbox controller input,
frame rate and RenderQueues.

As such this version of pacman supports Xbox controllers, I am using [this](https://github.com/360Controller/360Controller/releases)
to get a Xbox controller working on my MacOs Environment (High Sierra 10.13.6), plugged through USB. (rumbles when you collect pellets!)
This version also supports animations!

The only library it uses is SDL, up to the extent of using SDL's standard libc implemented functions like SDL_Log and SDL_calloc.
The purpose of using SDL was to not have to write code for driver and OS type calls that poll I/O devices or handles GPU/CPU rendering.
The only exception is a call to srand(3) and rand(3) for I did not find a SDL random number generator.

The code is linked to Dynamic SDL Libraries so in theory all you would need to do is find your OS versions and recompile.

The code is even more cleaner than the previous version, I took some liberties with indentations and it made the code
pleasing to read. I could add more small things but I imagine I would get up getting diminishing returns. The game
is already plenty of fun, and I spent a few too many hours playing it. You can press the start button on the Xbox controller
or R key on keyboard to reset the level, so you don't have to close and rerun the app btw.

Input is WASD, arrow keys, Xbox DPAD, Xbox Right Axis or Left (I made it easy to edit/add input so I did just that, add the reasonable input people would use)


<br>
<img height="700" src="https://github.com/ASSERT-game/pacman_v2/blob/main/resources/cookie.gif" />
<br>

You can play this game today right now, at no extra charge! Visit https://mrcolour.github.io//#/pacman
