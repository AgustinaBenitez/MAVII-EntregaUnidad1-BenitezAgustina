#include "Juego.h"

Juego::Juego() : anguloPreconfigurado(0.0f) {

    // Inicializo gravedad
    b2Vec2 gravedad(0.0f, 9.8f);

    // Inicializo mundo físico
    mundo = std::make_unique<b2World>(gravedad);

    // Creo el suelo inicial (Cuerpo Estático)
    objetos.emplace_back(std::make_unique<Caja>(mundo.get(), b2Vec2{ 500, 580 }, 0.0f, 1000.0f, 40.0f, b2_staticBody, DARKGRAY));

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
        objetos.emplace_back(std::make_unique<Caja>(mundo.get(), b2Vec2{ 500, 50 }, anguloPreconfigurado, 50.0f, 50.0f, b2_dynamicBody, SKYBLUE));

    }

}

void Juego::Renderizar() {

    BeginDrawing();

        ClearBackground(RAYWHITE);

        // Box2D calcula, Raylib dibuja el resultado visual
        for (const auto& obj : objetos) {
            obj->Dibujar();
        }

        DrawText("Flechas: Rotar angulo inicial | ESPACIO: Crear caja", 10, 10, 20, DARKBLUE);
        DrawText(TextFormat("Angulo de creacion: %.2f rad", anguloPreconfigurado), 10, 40, 20, GRAY);

    EndDrawing();

}

//Juego::~Juego() {}