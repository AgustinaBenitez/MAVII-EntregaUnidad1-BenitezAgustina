#include "Juego.h"

// Implementación del escuchador
EscuchadorColisiones::EscuchadorColisiones(Sound s) : sonidoCaidaCaja(s) {}

void EscuchadorColisiones::BeginContact(b2Contact* contacto) {
    PlaySound(sonidoCaidaCaja);
}

Juego::Juego() : anguloPreconfigurado(0.0f), anchoPre(80.0f), altoPre(50.0f) {

    // Inicializo gravedad
    b2Vec2 gravedad(0.0f, 9.8f);

    // Inicializo mundo físico
    mundo = std::make_unique<b2World>(gravedad);

}

void Juego::Iniciar() {

    InitWindow(1000, 600, "MAVII - Entrega Guía Unidad 1 - Benitez Agustina");

    InitAudioDevice();

    SetTargetFPS(60);

    // Cargo música de fondo
    musicaFondo = LoadMusicStream("assets/musicaFondo.mp3");
    musicaFondo.looping = true;     // Para que se repita infinitamente
    PlayMusicStream(musicaFondo);   // Le doy Play solo acá (una sola vez)

    // Cargo los sonidos
    sonidoGenerarCaja = LoadSound("assets/generarCaja.wav");
    sonidoCaidaCaja = LoadSound("assets/caidaCaja.wav");

    // Configuro el escuchador de colisiones
    escuchador = std::make_unique<EscuchadorColisiones>(sonidoCaidaCaja);
    mundo->SetContactListener(escuchador.get());

    // Creo el suelo inicial (Cuerpo Estático)
    objetos.emplace_back(std::make_unique<Caja>(mundo.get(), b2Vec2{ 500, 580 }, 0.0f, 1000.0f, 40.0f, b2_staticBody, DARKGRAY));

    // Cargo jugador
    jugador.Iniciar();

}

void Juego::Actualizar() {

    UpdateMusicStream(musicaFondo); // OBLIGATORIO para que suene la música

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

        PlaySound(sonidoGenerarCaja);

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

        //Dibujo al jugador
        jugador.Dibujar();

        // Creo una "Caja Fantasma" a modo de preview
        Vector2 posPre = { 500.0f, 50.0f };
        Rectangle recPre = { posPre.x, posPre.y, anchoPre, altoPre };
        Vector2 origenPre = { anchoPre / 2.0f, altoPre / 2.0f };

        // Convierto el ángulo de radianes a grados para Raylib
        float gradosPre = anguloPreconfigurado * RAD2DEG;

        // Dibujo la caja fantasma
        DrawRectanglePro(recPre, origenPre, gradosPre, Fade(SKYBLUE, 0.5f));        

        // Muestro cartel
        DrawText("Chell ha descubierto", 10, 10, 20, MAROON);
        DrawText("como crear cajas fisicas...", 10, 40, 20, MAROON);
        DrawText("Podra finalmente encontrar", 10, 70, 20, MAROON);
        DrawText("a su cubo de compania?", 10, 100, 20, MAROON);

        // Muestro instrucciones
        DrawText("Flechas: Rotar angulo inicial", 690, 10, 20, DARKBLUE);
        DrawText("Barra de espacio: Crear caja", 690, 40, 20, DARKBLUE);
        DrawText(TextFormat("Angulo de creacion: %.2f rad", anguloPreconfigurado), 690, 70, 20, GRAY);


    EndDrawing();

}

Juego::~Juego() {

    // Solución de Gemini al error que estaba teniendo de Dangling Pointer:
    // Le decimos al mundo que ya no use el escuchador.
    // Esto evita que intente acceder a memoria ya borrada.
    if (mundo) {
        mundo->SetContactListener(nullptr);
    }

    // Y limpiamos los objetos explícitamente AHORA.
    // Esto fuerza a que todos los DestroyBody se ejecuten mientras el mundo sigue vivo.
    objetos.clear();

    // Descargo los recursos de Raylib
    UnloadSound(sonidoGenerarCaja);
    UnloadSound(sonidoCaidaCaja);
    UnloadMusicStream(musicaFondo);

}
