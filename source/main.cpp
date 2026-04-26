#ifndef NDEBUG
#include <vld.h>
#endif

#include "raylib.h"
#include <box2d.h>
#include <vector>

#include "Juego.h"

int main() {

    InitWindow(1000, 600, "MAVII - Entrega Guía Unidad 1 - Mavix despierta - Benitez Agustina");

    SetTargetFPS(60);

    Juego miJuego;

    while (!WindowShouldClose()) {

        miJuego.Actualizar();
        miJuego.Renderizar();

    }

    CloseWindow();

    return 0;

}