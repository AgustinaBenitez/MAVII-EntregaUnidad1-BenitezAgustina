#include "Juego.h"

Juego::Juego() : anguloPreconfigurado(0.0f) {

    // Inicializo mundo con gravedad
    mundo = new b2World({ 0.0f, 9.8f });

    // Creo el suelo inicial (Cuerpo Estático)
    objetos.push_back(new Caja(mundo, { 500, 580 }, 0, 1000, 40, b2_staticBody, DARKGRAY));

}

void Juego::Actualizar() {

    // Avanzo la simulación física
    mundo->Step(1.0f / 60.0f, 8, 3);

    // Ajusto orientación antes de crear (con flechas)
    if (IsKeyDown(KEY_LEFT)) {
        anguloPreconfigurado -= 0.05f;
    }

    if (IsKeyDown(KEY_RIGHT)) {
        anguloPreconfigurado += 0.05f;
    }

    // Creo nueva caja dinámica al presionar ESPACIO
    if (IsKeyPressed(KEY_SPACE)) {

        // Se crea en la parte superior con el ángulo configurado 
        objetos.push_back(new Caja(mundo, { 500, 50 }, anguloPreconfigurado, 50, 50, b2_dynamicBody, SKYBLUE));

    }

}

void Juego::Renderizar() {

    BeginDrawing();

        ClearBackground(RAYWHITE);

        for (auto obj : objetos) obj->Dibujar();

        DrawText("Flechas: Rotar angulo inicial | ESPACIO: Crear caja", 10, 10, 20, DARKBLUE);
        DrawText(TextFormat("Angulo de creacion: %.2f rad", anguloPreconfigurado), 10, 40, 20, GRAY);

    EndDrawing();

}

Juego::~Juego() {

    for (auto obj : objetos) delete obj;
    delete mundo;

}