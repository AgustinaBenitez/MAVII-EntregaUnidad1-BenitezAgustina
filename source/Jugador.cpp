#include "Jugador.h"
#include "Juego.h"

Jugador::Jugador() {

	// Inicializo textura en cero para evitar warnings
	texturaJugador = { 0 };

}

Jugador::~Jugador() {

	UnloadTexture(texturaJugador);

}

void Jugador::Iniciar() {

	// Propiedades
	escalaJugador = 0.15f;
	posicionJugador = { 70, 365 };

	// Cargo textura
	texturaJugador = LoadTexture("assets/chellArriba.png");
	SetTextureFilter(texturaJugador, TEXTURE_FILTER_BILINEAR);

}

void Jugador::Dibujar() {

	DrawTextureEx(texturaJugador, posicionJugador, 0.0f, escalaJugador, WHITE);

}