# GDArduino
git clone --recursive https://github.com/GodotNativeTools/godot-cpp

cd godot-cpp

scons platform=PLATFORM generate_bindings=yes -j4

cd ..

scons platform=PLATFORM

Windows:

Change the flags MD and MDd to MT and MTd in both SConstructs while compiling godot-cpp and the lib as release.