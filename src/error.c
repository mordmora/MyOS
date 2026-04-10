#include "error.h"
#include "printf.h"

void print_cow(const char *error_msg) {
    kprintf("                 (      )\n");
    kprintf("                 ~(^^^^)~\n");
    kprintf("                  ) @@ \\~_          |\\\n");
    kprintf("                 /     | \\        \\~ /\n");
    kprintf("                ( 0  0  ) \\        | |       Hey\n");
    kprintf("                 ---___/~  \\       | |           Hiya\n");
    kprintf("                  /'__/ |   ~-_____/ |                Doin?\n");
    kprintf("   o          _   ~----~      ___---~\n");
    kprintf("     O       //     |         |\n");
    kprintf("            ((~\\  _|         -|\n");
    kprintf("      o  O //-_ \\/ |        ~  |      Oops! %s\n", error_msg);
    kprintf("           ^   \\_ /         ~  |\n");
    kprintf("                  |          ~ |          I mean MOOOOOOO\n");
    kprintf("                  |     /     ~ |\n");
    kprintf("                  |     (       |\n");
    kprintf("                   \\     \\      /\\\n");
    kprintf("                  / -_____-\\   \\ ~~-*\n");
    kprintf("                  |  /       \\  \\       .==.\n");
    kprintf("                  / /         / /       |  |\n");
    kprintf("                /~  |      //~  |       |__|\n");
    kprintf("                ~~~~        ~~~~\n");
}
