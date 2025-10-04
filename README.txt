1. Description
Terminal Clock is a linux utillity that allows you to check the current time of the day
by displaying ascii art of an analog clock that defines three hands with different lengths:
short, medium and long corresponding to the actual hour, minute and second respectively.

2. How it works
Actually, this utillity is a good example of how simple things can be used to build complex
ones. Clock is drawn using small built-in library that provides a pretty good graphical
emulation of cartesian plane using ascii letters. Such plane's data point is defined to be
two characters sticking together horizontally - this makes each of DPs more square-like.
The rest is just a drawing algorithm for outer circle and hands which I really do not want
to elaborate on here, because it is well documented in source.

3. Usage
First it needs to be built. Ensure the 'make' tool is installed, then just run it to build
a linux executable. Afterwards you can use it like a linux command, just pass the '--help'
switch within it to learn more about the capabilities of the util.
