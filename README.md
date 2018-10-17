# fracture

## About
This is by far my favorite project. The idea behind fracture is that I would keep coding until I had a working 3D game engine, but I completely ran out of time and it unfortunately died. While it never became a proper game engine, it was an incredible learning experience and my sandbox project for computer graphics.

It's most notable feature is a fully featured realtime [PBR renderer](https://learnopengl.com/PBR/Theory) with full support to image lighting and quite a few material formats written in C++ and OpenGL. However it includes a lot of utility and game engine stuff like an input system, interactive camera, skybox rendering, HDRi parsing and (quite a) few other bits and pieces.

fracture is not my first try at a computer graphics project, but it's the most successful one. It all started with the now long dead quad engine, a project that worked with the same general guidelines fracture used despite having started with 2D stuff, later evolving to a simple [Phong renderer](https://en.wikipedia.org/wiki/Phong_shading). After fracture I got started with Vulkan and DirectX 12, but those projects never got past the "textured quad step" as it would take a lot of time I didn't have. You can see the post mortem of my work with both quad and fracture in a [compilation of screenshots](https://drive.google.com/open?id=1XOsMyruCvqrSk1IU5NmDcmGa469j4wg6) I managed  to organize. I regret not doing proper dev logs, but such is life.

![Imgur](https://i.imgur.com/KfNVOMD.jpg)

## Notes
I didn't know how to use git properly and didn't want to make this open source at the time, so while I probably had a private repository somewhere, I don't really know what happened to it (I deleted a lot of stuff I shouldn't in my early days). That's why I'm just creating a new repo and pushing it all at once. Unfortunately  this is a dead project, so when I do try working on a game engine again (AND I SURE WILL!) it will be on a new and hopefully properly versioned project.

Another thing to keep in mind is that this features learning code. It's not optimized and not commented at all, but as I said it's my favorite project, I really love result and want to show it off.

## Running
The dependencies are in the repository (I wasn't very good at structuring projects at the time and don't feel like fixing it now) so there should be no problems building and running it using Visual Studio. Do keep in mind that the current demo scene uses a few resources that are not in the repository (it's a lot of big images), but you can get them [here](https://drive.google.com/file/d/1aiTnfZPEiXw-vUuIITkP5BoFH9aY-BMF/view?usp=sharing). Extract it to the core folder and you should be ready to go.