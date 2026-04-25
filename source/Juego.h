#pragma once
#include <vector>
#include "Caja.h"

class Juego {

private:
    b2World* mundo; // El contenedor principal
    std::vector<ObjetoFisico*> objetos;
    float anguloPreconfigurado; // El ángulo que Mavix ajusta antes de crear la caja

public:
    Juego();
    ~Juego();
    void Actualizar(); // Maneja Step() e Input
    void Renderizar(); // Dibuja la escena

};

