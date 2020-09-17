#include "gdserial.h"
#if PLATFORM_LINUX

#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>

#endif
using namespace godot;

void GDSerial::_register_methods() {
    register_method("open_port", &GDSerial::open_port);
    register_method("close_port", &GDSerial::close_port);
    register_method("write_text", &GDSerial::write_text);
    register_method("read_text", &GDSerial::read_text);
}

GDSerial::GDSerial() {
}

GDSerial::~GDSerial() {
    // add your cleanup here
}

void GDSerial::_init() {
    // initialize any variables here
    time_passed = 0.0;
}

bool GDSerial::open_port(String port, int baud_rate) {
    const char * port_c = port.utf8().get_data();
    printf("Port: %s\n", port_c);
    printf("BaudRate: %i\n", baud_rate);
    printf("----------------\n");

    printf("GDSerial: Trying to open: %s.\n", port_c);

#if PLATFORM_LINUX || PLATFORM_MAC

    serial_port = open(port_c, O_RDWR | O_NOCTTY | O_NDELAY);
    struct termios tty;
    struct termios tty_old;
    memset(&tty, 0, sizeof tty);
    if (tcgetattr(serial_port, &tty) != 0)
    {
        printf("GDSerial: Failed to get current serial parameters.\n");
        return false;
    }
    tty_old = tty;
    cfsetospeed(&tty, (speed_t)baud_rate);
    cfsetispeed(&tty, (speed_t)baud_rate);

    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag |= CS8;
    tty.c_cflag &= ~CRTSCTS;
    tty.c_cflag |= CREAD | CLOCAL;
    tty.c_lflag &= ~ICANON;
    tty.c_lflag &= ~ECHO;
    tty.c_lflag &= ~ECHOE;
    tty.c_lflag &= ~ECHONL;
    tty.c_lflag &= ~ISIG;
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);
    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL);
    tty.c_oflag &= ~OPOST;
    tty.c_oflag &= ~ONLCR;
    tty.c_cc[VTIME] = 0;
    tty.c_cc[VMIN] = 0;

    cfmakeraw(&tty);
    tcflush(serial_port, TCIFLUSH);

    if (tcsetattr(serial_port, TCSANOW, &tty) != 0)
    {
        printf("GDSerial: Could not set serial port parameters.\n");

        return false;
    }
    fcntl(serial_port, F_SETFL, FNDELAY);

#endif
    printf("GDSerial: %s opened.\n", port_c);
    return true;
}

void GDSerial::close_port() {

#if PLATFORM_LINUX || PLATFORM_MAC

    close(serial_port);
    serial_port = 0;
    
#endif
    printf("GDSerial: Serial port closed.\n");
}

void GDSerial::write_text(String text) {
    const char * text_c = text.utf8().get_data();
#if PLATFORM_LINUX || PLATFORM_MAC
    write(serial_port, text_c, text.length());
#endif

}

String GDSerial::read_text() {

#if PLATFORM_LINUX || PLATFORM_MAC
    String text = "";
    int bytes_avaiable = -1;
    ioctl(serial_port, FIONREAD, &bytes_avaiable);
    printf("Total available: %i", bytes_avaiable);
    /*
    unsigned char buf[4096];
    int n;
    n = read(serial_port, &buf, sizeof(buf));
    if (n > 0)
    {
        for (int x = 0; x < n; x++)
        {
            text+=buf[x];
        }
    }
    printf("GDSerial: %s.\n", text);
    */
    return text;
#endif
}