#include "Caja.h"

Caja::Caja(b2World* mundo, b2Vec2 pos, float ang, float w, float h, b2BodyType tipo, Color col)
    : ObjetoFisico(mundo, pos, ang, tipo, col), ancho(w), alto(h) {

    // Defino la forma rectangular
    b2PolygonShape forma;
    forma.SetAsBox(w / 2.0f, h / 2.0f); // Box2D usa semi-lados

    // Defino las propiedades físicas
    b2FixtureDef defFixture;
    defFixture.shape = &forma;
    defFixture.density = 1.0f;      // Influye en la masa
    defFixture.friction = 0.3f;     // Resistencia al deslizamiento
    defFixture.restitution = 0.4f;  // Nivel de rebote

    cuerpo->CreateFixture(&defFixture);

}

void Caja::Dibujar() {

    b2Vec2 pos = cuerpo->GetPosition();
    float anguloGrados = cuerpo->GetAngle() * RAD2DEG; // Conversión para Raylib

    Rectangle rec = { pos.x, pos.y, ancho, alto };
    Vector2 origen = { ancho / 2.0f, alto / 2.0f };

    // Raylib utiliza la info de Box2D para representar el objeto
    DrawRectanglePro(rec, origen, anguloGrados, color);

}