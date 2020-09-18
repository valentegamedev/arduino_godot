# GDArduino
git clone --recursive https://github.com/GodotNativeTools/godot-cpp

cd godot-cpp

scons platform=PLATFORM generate_bindings=yes -j4

cd ..

scons platform=PLATFORM