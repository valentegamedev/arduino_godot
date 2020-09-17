#ifndef GDSERIAL_H
#define GDSERIAL_H
#define PLATFORM_LINUX 1

#include <Godot.hpp>
#include <Sprite.hpp>

namespace godot {

class GDSerial : public Sprite {
    GODOT_CLASS(GDSerial, Sprite)

private:
    float time_passed;

#if PLATFORM_LINUX || PLATFORM_MAC
	int serial_port;
#endif

public:
    static void _register_methods();

    GDSerial();
    ~GDSerial();

    void _init(); // our initializer called by Godot

    bool open_port(String port, int baud_rate);
    void close_port();
    void write_text(String text);
    String read_text();
};

}

#endif