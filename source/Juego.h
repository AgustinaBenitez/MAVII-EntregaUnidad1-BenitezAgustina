#pragma once

#include <vector>
#include <memory> // Para usar los Smart Pointers
#include "Caja.h"
#include "Jugador.h"

// Declaro la clase acá para que después Juego la conozca --- Me ayudó Gemini porque no daba en el clavo con la implementación del sonido
class EscuchadorColisiones : public b2ContactListener {

private:

    Sound sonidoCaidaCaja;

public:

    EscuchadorColisiones(Sound s);
    void BeginContact(b2Contact* contacto) override;

};

class Juego {

private:

    std::unique_ptr<b2World> mundo;                     // El mundo físico que va a ser el contenedor principal
    std::vector<std::unique_ptr<ObjetoFisico>> objetos; // Lista de objetos que se actualizan y dibujan

    float anguloPreconfigurado; // El ángulo que el personaje ajusta antes de crear la caja
    float anchoPre;
    float altoPre;

    // Audio + escuchador
    Music musicaFondo;
    Sound sonidoGenerarCaja;
    Sound sonidoCaidaCaja;
    std::unique_ptr<EscuchadorColisiones> escuchador;

    // Objeto
    Jugador jugador;

public:

    Juego();
    ~Juego();

    void Iniciar();
    void Actualizar(); // Maneja Step() e Input
    void Renderizar(); // Dibuja la escena

};

