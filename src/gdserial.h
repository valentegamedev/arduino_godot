#ifndef GDSERIAL_H
#define GDSERIAL_H
//#define PLATFORM_LINUX 1
//#define PLATFORM_MAC 1
//#define DEBUG_LOG 1
#include <Godot.hpp>

namespace godot {

class GDSerial : public Reference {
    GODOT_CLASS(GDSerial, Reference)

#if PLATFORM_LINUX || PLATFORM_MAC
	int serial_port;
#else
	void * handler;
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