#include "Juego.h"

Juego::Juego() : anguloPreconfigurado(0.0f), anchoPre(80.0f), altoPre(50.0f) {

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

    // Ajusto orientación antes de crear caja (con flechas)
    if (IsKeyDown(KEY_LEFT)) {
        anguloPreconfigurado -= 0.05f;
    }

    if (IsKeyDown(KEY_RIGHT)) {
        anguloPreconfigurado += 0.05f;
    }

    // Creo nueva caja dinámica al presionar ESPACIO
    if (IsKeyPressed(KEY_SPACE)) {

        // Se crea en la parte superior con el ángulo configurado 
        objetos.emplace_back(std::make_unique<Caja>(mundo.get(), b2Vec2{ 500, 50 }, anguloPreconfigurado, anchoPre, altoPre, b2_dynamicBody, SKYBLUE));

    }

}

void Juego::Renderizar() {

    BeginDrawing();

        ClearBackground(RAYWHITE);

        // Box2D calcula, Raylib dibuja el resultado visual
        for (const auto& obj : objetos) {
            obj->Dibujar();
        }

        // Creo una "Caja Fantasma" a modo de preview
        Vector2 posPre = { 500.0f, 50.0f };
        Rectangle recPre = { posPre.x, posPre.y, anchoPre, altoPre };
        Vector2 origenPre = { anchoPre / 2.0f, altoPre / 2.0f };

        // Convierto el ángulo de radianes a grados para Raylib
        float gradosPre = anguloPreconfigurado * RAD2DEG;

        // Dibujo la caja fantasma
        DrawRectanglePro(recPre, origenPre, gradosPre, Fade(SKYBLUE, 0.5f));        

        // Muestro instrucciones
        DrawText("Flechas: Rotar angulo inicial | Barra de espacio: Crear caja", 10, 10, 20, DARKBLUE);
        DrawText(TextFormat("Angulo de creacion: %.2f rad", anguloPreconfigurado), 10, 40, 20, GRAY);

    EndDrawing();

}
