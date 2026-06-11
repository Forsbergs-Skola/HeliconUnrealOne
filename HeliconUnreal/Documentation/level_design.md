# Level Design Documentation #
## Overview ##

### Seamless Unreal Engine Map ###
The game does not seperate into multiple maps. There is one map called Map_Game that uses seamless portals to move the player around the map creating an illusion of multiple levels loading instantly. 

### Asset Target Quality ###
The game has a target quality of low-mid polygon count. We utilize multiple optimization techniques to increase performance:
Impostor baked trees, simplified static meshes in modelling mode, carefully adjusted fields in expensive areas like volumetric clouds, shader complexity debugging and handpicking good assets. 