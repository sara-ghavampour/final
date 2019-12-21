#include <stdio.h>
#include "beep.h"
//sudo apt install pulseaudio
//sudo apt install alsa-utils
//before runing run this command : pulseaudio -k && sudo alsa force-reload
//compile with : gcc test.c beep.o sintable.o -lasound
int main () {
beep(1000,1000);
}
