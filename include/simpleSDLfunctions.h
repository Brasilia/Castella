#ifndef SIMPLESDLFUNCTIONS_H_INCLUDED
#define SIMPLESDLFUNCTIONS_H_INCLUDED

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_gfxPrimitives.h>

#include <iostream>
#include <memory>
#include <stdlib.h>

using namespace std;

//################################## FUN��ES DE ATALHO ##################################OO
//Fun��es para facilitar a aplica��o de outras fun��es, otimizando suas utiliza��es,
//em termos de organiza��o e linhas de c�digo

//---------------------------------- CARREGAR IMAGEM ------------------------------------//
//Fun��o de carregamento de imagem
SDL_Surface *load_image(const char *nome_do_arquivo);
//---------------------------------------------------------------------------------------//

//--------------------------------- APLICAR SUPERFICIE ----------------------------------//
//Aplica uma superf�cie recebendo tamb�m suas coordenadas como par�metros
void apply_surface(int x, int y, SDL_Surface* fonte, SDL_Surface* destino, SDL_Rect* corte = NULL, float empurrar = 0);
//---------------------------------------------------------------------------------------//

//--------------------------------- ESCREVER TEXTO --------------------------------------//
//Escreve um texto na tela, na posi��o desejada
// padr�o: cor preta
void write_text(int x, int y, SDL_Surface *destino, std::string texto);
// cor por RGB
void write_text(int x, int y, SDL_Surface *destino, std::string texto, unsigned char R, unsigned char G, unsigned char B);
// cor direto pelo SDL_Color
void write_text(int x, int y, SDL_Surface *destino, std::string texto, SDL_Color cor);
//---------------------------------------------------------------------------------------//
#endif // SIMPLESDLFUNCTIONS_H_INCLUDED

