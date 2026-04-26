#pragma once
#include "ObjetoFisico.h"

class Caja : public ObjetoFisico {

private:

    float ancho, alto;    

public:

    Caja(b2World* mundo, b2Vec2 pos, float ang, float w, float h, b2BodyType tipo, Color col);
    void Dibujar() override; // Recomendado por Gemini siempre que esté heredando

};