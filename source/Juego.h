#pragma once
#include <vector>
#include <memory> // Para usar los Smart Pointers
#include "Caja.h"

class Juego {

private:

    std::unique_ptr<b2World> mundo;                     // El mundo físico que va a ser el contenedor principal
    std::vector<std::unique_ptr<ObjetoFisico>> objetos; // Lista de objetos que se actualizan y dibujan

    float anguloPreconfigurado;                         // El ángulo que Mavix ajusta antes de crear la caja

public:

    Juego();
    ~Juego() = default;

    void Actualizar(); // Maneja Step() e Input
    void Renderizar(); // Dibuja la escena

};

