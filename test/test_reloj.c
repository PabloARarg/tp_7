/* === Headers files inclusions =============================================================== */
#include "reloj.h"
#include "unity.h"
#include <stdint.h>

/* === Macros definitions ====================================================================== */
#ifndef TICK_POR_SEC
#define TICK_POR_SEC 5
#endif

#ifndef TIME_OUT
#define TIME_OUT 5
#endif
/* === Private data type declarations ========================================================== */

/* === Private variable declarations =========================================================== */

/* === Private function implementation (complementarias)======================================== */

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */
// Al inicializar el reloj está en 00:00 y con hora invalida.
void test_reloj_arranca_con_hora_invalida(void) {

    static const uint8_t ESPERADO[] = {0, 0, 0, 0, 0, 0}; // crea un vector que se toma como referencia para comparar
    uint8_t hora[6] = {0xff};                             // variable para almacenar la hora auxiliar
    clock_t reloj = ClockCreate(TICK_POR_SEC); // cuando lo creo un objeto reloj le digo cuanto pulso(ticks) por segundo

    TEST_ASSERT_FALSE(ClockGetTime(reloj, hora, 6));  // pasa el test si la hora->valida es FALSE o 0
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, 6); // pasa el test si la ESPERADO es igual hora=reloj->hora_actual
}

// Al ajustar la hora el reloj queda en hora y es válida.
void test_ajustar_hora(void) {

    static const uint8_t ESPERADO[] = {1, 2, 3, 4, 0, 0};
    uint8_t hora[6];
    clock_t reloj = ClockCreate(TICK_POR_SEC);

    TEST_ASSERT_TRUE(ClockSetTime(reloj, ESPERADO, 4)); // comprueba que la hora que pasamos es valida
    TEST_ASSERT_TRUE(ClockGetTime(reloj, hora, 6));     // comprueba que la hora que debuelve es valida
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, 6); // compara la hora consultada con la hora que deberia ser correcta
}

// Después de n ciclos de reloj la hora avanza un segundo
void test_unidad_segundos_aumenta(void) {

    static const uint8_t ESPERADO[] = {0, 0, 0, 0, 0, 1};
    uint8_t hora[6];
    clock_t reloj = ClockCreate(TICK_POR_SEC);

    SetTicks(reloj);              // coloca al contador de ticks del reloj 1 por debajo del necesario
    AumentarTick(reloj);          // aumenta 1 tick al contador
    ActualizarHora(reloj);        // actualiza la hora del reloj
    ClockGetTime(reloj, hora, 6); // toma el valor del reloj actual a hora
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, 6); // compara si la hora es la correcta
}
// despues 10 segundos
void test_decena_segundos_aumenta(void) {

    static const uint8_t ESPERADO[] = {0, 0, 0, 0, 1, 0};
    uint8_t hora[6] = {0, 0, 0, 0, 0, 9}; // a 1 seg de cambiar la hora
    clock_t reloj = ClockCreate(TICK_POR_SEC);

    ClockSetTime(reloj, hora, 6); // establece la hora a 1 segundo del cambio a la decena
    SetTicks(reloj);              // coloca al contador de ticks del reloj 1 por debajo del necesario
    AumentarTick(reloj);          // aumenta 1 tick al contador
    ActualizarHora(reloj);        // actualiza la hora del reloj
    ClockGetTime(reloj, hora, 6); // toma el valor del reloj actual a hora
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, 6); // compara si la hora es la correcta
}

// Después de n ciclos de reloj la hora avanza 1 minutos
void test_unidad_minuto_aumenta(void) {

    static const uint8_t ESPERADO[] = {0, 0, 0, 1, 0, 0};
    uint8_t hora[6] = {0, 0, 0, 0, 5, 9}; // a 1 seg de cambiar la hora
    clock_t reloj = ClockCreate(TICK_POR_SEC);

    ClockSetTime(reloj, hora, 6);
    SetTicks(reloj);              // coloca al contador de ticks del reloj 1 por debajo del necesario
    AumentarTick(reloj);          // aumenta 1 tick al contador
    ActualizarHora(reloj);        // actualiza la hora del reloj
    ClockGetTime(reloj, hora, 6); // toma el valor del reloj actual a hora
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, 6); // compara si la hora es la correcta
}

// Después de n ciclos 10 minutos
void test_decena_minuto_aumenta(void) {

    static const uint8_t ESPERADO[] = {0, 0, 1, 0, 0, 0};
    uint8_t hora[6] = {0, 0, 0, 9, 5, 9}; // a 1 seg de cambiar la hora
    clock_t reloj = ClockCreate(TICK_POR_SEC);

    ClockSetTime(reloj, hora, 6);
    SetTicks(reloj);              // coloca al contador de ticks del reloj 1 por debajo del necesario
    AumentarTick(reloj);          // aumenta 1 tick al contador
    ActualizarHora(reloj);        // actualiza la hora del reloj
    ClockGetTime(reloj, hora, 6); // toma el valor del reloj actual a hora
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, 6); // compara si la hora es la correcta
}

// Después de n ciclos de reloj la hora avanza 1 hora
void test_unidad_hora_aumenta(void) {

    static const uint8_t ESPERADO[] = {0, 1, 0, 0, 0, 0};
    uint8_t hora[6] = {0, 0, 5, 9, 5, 9}; // a 1 seg de cambiar la hora
    clock_t reloj = ClockCreate(TICK_POR_SEC);

    ClockSetTime(reloj, hora, 6);
    SetTicks(reloj);              // coloca al contador de ticks del reloj 1 por debajo del necesario
    AumentarTick(reloj);          // aumenta 1 tick al contador
    ActualizarHora(reloj);        // actualiza la hora del reloj
    ClockGetTime(reloj, hora, 6); // toma el valor del reloj actual a hora
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, 6); // compara si la hora es la correcta
}

// Después de n ciclos de reloj la hora avanza 10 horas y despues 1 día.
void test_decena_hora_aumenta(void) {

    static const uint8_t ESPERADO[] = {1, 0, 0, 0, 0, 0};
    uint8_t hora[6] = {0, 9, 5, 9, 5, 9}; // a 1 seg de cambiar la hora
    clock_t reloj = ClockCreate(TICK_POR_SEC);

    ClockSetTime(reloj, hora, 6);
    SetTicks(reloj);              // coloca al contador de ticks del reloj 1 por debajo del necesario
    AumentarTick(reloj);          // aumenta 1 tick al contador
    ActualizarHora(reloj);        // actualiza la hora del reloj
    ClockGetTime(reloj, hora, 6); // toma el valor del reloj actual a hora
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, 6); // compara si la hora es la correcta
}

// Después de n ciclos de reloj la hora avanza 1 día.
void test_cambia_dia(void) {

    static const uint8_t ESPERADO[] = {0, 0, 0, 0, 0, 0};
    uint8_t hora[6] = {2, 3, 5, 9, 5, 9}; // a 1 seg de cambiar la hora
    clock_t reloj = ClockCreate(TICK_POR_SEC);

    ClockSetTime(reloj, hora, 6);
    SetTicks(reloj);              // coloca al contador de ticks del reloj 1 por debajo del necesario
    AumentarTick(reloj);          // aumenta 1 tick al contador
    ActualizarHora(reloj);        // actualiza la hora del reloj
    ClockGetTime(reloj, hora, 6); // toma el valor del reloj actual a hora
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, 6); // compara si la hora es la correcta
}

// ‣ Fijar la hora de la alarma y consultarla.
void test_establecer_alarma(void) {

    static const uint8_t ESPERADO[] = {1, 2, 3, 4, 0, 0};
    uint8_t hora[6];
    clock_t reloj = ClockCreate(TICK_POR_SEC);

    TEST_ASSERT_TRUE(ClockSetAlarm(reloj, ESPERADO, 4)); // comprueba que la hora que pasamos es valida
    TEST_ASSERT_TRUE(ClockGetAlarm(reloj, hora, 6));     // comprueba que la hora que debuelve es valida
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, 6); // compara la hora consultada con la hora que deberia ser correcta
}

// ‣ Fijar la alarma y avanzar el reloj para que suene.
void test_alarm_match(void) {

    static const uint8_t ESPERADO[] = {1, 0, 1, 0, 0, 0};
    uint8_t hora[6] = {1, 0, 0, 9, 5, 9}; // a 1 seg de cambiar la hora
    clock_t reloj = ClockCreate(TICK_POR_SEC);

    ClockSetTime(reloj, hora, 6);      // estabelce la hora
    ClockSetAlarm(reloj, ESPERADO, 6); // establece la alarma

    SetTicks(reloj);     // coloca al contador de ticks del reloj 1 por debajo del necesario
    AumentarTick(reloj); // aumenta 1 tick al contador

    ActualizarHora(reloj); // actualiza la hora del reloj
    TEST_ASSERT_TRUE(AlarmaActivar(reloj));
}
// ‣ Fijar la alarma, deshabilitarla y avanzar el reloj para no suene.
void test_alarm_match_no_sound(void) {

    static const uint8_t ESPERADO[] = {1, 0, 1, 0, 0, 0};
    uint8_t hora[6] = {1, 0, 0, 9, 5, 9}; // a 1 seg de cambiar la hora
    clock_t reloj = ClockCreate(TICK_POR_SEC);

    ClockSetTime(reloj, hora, 6);      // estabelce la hora
    ClockSetAlarm(reloj, ESPERADO, 6); // establece la alarma

    SetTicks(reloj);     // coloca al contador de ticks del reloj 1 por debajo del necesario
    AumentarTick(reloj); // aumenta 1 tick al contador

    ActualizarHora(reloj); // actualiza la hora del reloj
    TEST_ASSERT_FALSE(AlarmaOnOf(reloj, false));
}

// ‣ Hacer sonar la alarma y posponerla.
void test_alarm_standby(void) {

    static const uint8_t ESPERADO[] = {1, 0, 1, 0, 0, 0};
    uint8_t hora[6] = {1, 0, 0, 9, 5, 9}; // a 1 seg de cambiar la hora
    clock_t reloj = ClockCreate(TICK_POR_SEC);

    ClockSetTime(reloj, hora, 6);      // estabelce la hora
    ClockSetAlarm(reloj, ESPERADO, 6); // establece la alarma

    SetTicks(reloj);     // coloca al contador de ticks del reloj 1 por debajo del necesario
    AumentarTick(reloj); // aumenta 1 tick al contador

    ActualizarHora(reloj); // actualiza la hora del reloj
    TEST_ASSERT_TRUE(AlarmaActivar(reloj));
    TEST_ASSERT_TRUE(AlarmaRest(reloj, TIME_OUT));
    TEST_ASSERT_FALSE(AlarmaActivar(reloj));
}

// ‣ Hacer sonar la alarma y cancelarla hasta el otro dia..
void test_alarm_pospone(void) {

    static const uint8_t ESPERADO[] = {1, 0, 1, 0, 0, 0};
    uint8_t hora[6] = {1, 0, 0, 9, 5, 9}; // a 1 seg de cambiar la hora
    clock_t reloj = ClockCreate(TICK_POR_SEC);

    ClockSetTime(reloj, hora, 6);      // estabelce la hora
    ClockSetAlarm(reloj, ESPERADO, 6); // establece la alarma

    SetTicks(reloj);     // coloca al contador de ticks del reloj 1 por debajo del necesario
    AumentarTick(reloj); // aumenta 1 tick al contador

    ActualizarHora(reloj);                    // actualiza la hora del reloj
    TEST_ASSERT_TRUE(AlarmaActivar(reloj));   // comprueba que la alarma suena
    TEST_ASSERT_FALSE(AlarmaPosponer(reloj)); // pospone la alarma

    SetTicks(reloj);     // coloca al contador de ticks del reloj 1 por debajo del necesario
    AumentarTick(reloj); // aumenta 1 tick al contador

    ActualizarHora(reloj);                   // actualiza la hora y avanza 1 segundo
    TEST_ASSERT_FALSE(AlarmaActivar(reloj)); // comprueba si la alarma sigue sonando

    // establece nuevamente la hora a 1 seg de que suene la alarma
    ClockSetTime(reloj, hora, 6); // estabelce la hora

    SetTicks(reloj);     // coloca al contador de ticks del reloj 1 por debajo del necesario
    AumentarTick(reloj); // aumenta 1 tick al contador

    ActualizarHora(reloj); // actualiza la hora del reloj

    ClockGetTime(reloj, hora, 6);                     // toma el valor del reloj actual a hora
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, 6); // compara la hora de la alarma con la hora del reloj
    TEST_ASSERT_TRUE(AlarmaActivar(reloj));           // comprueba que la alarma suena
}
// Probar horas invalidas y verifica que las rechaza...
void test_hora_invalida(void) {

    uint8_t hora[6] = {4, 0, 0, 9, 5, 9}; // a 1 seg de cambiar la hora
    clock_t reloj = ClockCreate(TICK_POR_SEC);

    TEST_ASSERT_FALSE(ClockSetTime(reloj, hora, 6));
}

/* === Public function implementation ========================================================= */
