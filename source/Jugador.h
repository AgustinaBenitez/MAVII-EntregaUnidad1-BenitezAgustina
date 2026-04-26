#pragma once
#include "raylib.h"

class Jugador {

private:

	// Textura para el personaje del jugador
	Texture2D texturaJugador;

	////// Propiedades

	Vector2 posicionJugador;
	float escalaJugador;

public:

	Jugador();
	~Jugador();

	void Iniciar();
	void Dibujar();

};

