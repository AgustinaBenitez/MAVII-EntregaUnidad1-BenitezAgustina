#pragma once
#include "raylib.h"
#include <box2d.h>

class ObjetoFisico {

protected:
    b2Body* cuerpo; // El cuerpo que Box2D simula
    Color color;

public:
    ObjetoFisico(b2World* mundo, b2Vec2 posicion, float angulo, b2BodyType tipo, Color col) {

        color = col;

        b2BodyDef defCuerpo;
        defCuerpo.type = tipo; // Puede ser estático o dinámico
        defCuerpo.position = posicion;
        defCuerpo.angle = angulo; // Rotación inicial

        cuerpo = mundo->CreateBody(&defCuerpo);

    }

    virtual ~ObjetoFisico() {
        cuerpo->GetWorld()->DestroyBody(cuerpo); // Limpieza de memoria física
    }

    virtual void Dibujar() = 0; // Método abstracto para que Raylib dibuje el resultado

};