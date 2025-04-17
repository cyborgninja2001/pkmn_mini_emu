#include "emulator.h"

void emu_cycle(Emulator *emulator, int n) {
    for (int i = 0; i < n; i++) {
        // avanzar todos los componentes del sistema 1 ciclo
        //timer_tick();     // avanzas timers
        //sound_tick();     // si usas audio
        //lcd_tick();       // si emulas pantalla
        //irq_check();      // verificar interrupciones
        emulator->emu_ticks++;      // contas los ciclos
    }
}

/*
void timer_tick() {
    // por ejemplo, cada 64 ciclos aumenta un contador
    if (++timer_counter == 64) {
        timer_counter = 0;
        timer++;
    }
}
*/