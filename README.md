**VERY EARLY DEVELOPMENT**
# fragFrame 0.01
*A quick way to experiment with frag shaders*

fragFrame is a quick way to create interesting patterns with frag shaders. It is currently in very early stages of development.

![screenshot](screenshot.png)

## Requirements
* GNU/Linux
* make
* gcc
* libglfw3
* libglfw3-dev
* libglew2.0
* libglew-dev
* entr

## How to use
Install dependencies

`sudo apt-get install libglfw3 libglfw3-dev libglew2.0 libglew-dev entr`

Make fragframe

`make`

Run fragframe

`./fragframe_run.sh`

Edit `shader.frag` and your frame will automatically update once you save

## Uniforms
A number of useful uniform variables are provided in fragframe, these are as follows:
* `u_time` (float) - The amount of time in seconds the shader has been running for
* `u_mouse` (vec2) - The x and y position of the cursor
* `u_resolution` (vec2) - The resolution of the frame window

## Notes
* If you are using vim and want syntax highlighting, add the following to your vimrc:

`au BufReadPost *.frag set syntax=c`

* Currently only GLSL version 130 is supported

* A green screen indicates a bad shader
