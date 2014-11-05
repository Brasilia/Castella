/** @file simpleSDLfunctions.h
 * header do model/simpleSDLfunctions.cpp
 */

#ifndef SIMPLESDLFUNCTIONS_H_INCLUDED
#define SIMPLESDLFUNCTIONS_H_INCLUDED

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_gfxPrimitives.h>

#include <string>

/* M�scara de bits pra cria��o de superf�cie, dica do SDL */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
#	define RMASK 0xff000000
#	define GMASK 0x00ff0000
#	define BMASK 0x0000ff00
#	define AMASK 0x000000ff
#else
#	define RMASK 0x000000ff
#	define GMASK 0x0000ff00
#	define BMASK 0x00ff0000
#	define AMASK 0xff000000
#endif

//################################## FUN��ES DE ATALHO ##################################OO
//Fun��es para facilitar a aplica��o de outras fun��es, otimizando suas utiliza��es,
//em termos de organiza��o e linhas de c�digo

//---------------------------------- CARREGAR IMAGEM ------------------------------------//
//Fun��o de carregamento de imagem
SDL_Surface *load_image (std::string nome_do_arquivo);
//----------------------------------------------------------------------------//

//--------------------------------- CRIAR SUPERFICIE -------------------------//
// Fun��o que cria uma superf�cie vazia
SDL_Surface *create_surface (int width, int height);
//----------------------------------------------------------------------------//

//---------------------------- APLICAR SUPERFICIE ----------------------------//
//Aplica uma superf�cie recebendo tamb�m suas coordenadas como par�metros
void apply_surface(int x, int y, SDL_Surface* fonte, SDL_Surface* destino, SDL_Rect* corte = NULL, float empurrar = 0);
// Preenche o fundo de uma superf�cie: padr�o = preto, em toda a superf�cie
void fill_surface (SDL_Surface *target, SDL_Rect *dstrect = NULL,
		SDL_Color cor = {0, 0, 0});
//----------------------------------------------------------------------------//

//-------------------------------- ESCREVER TEXTO ----------------------------//
//Escreve um texto na tela, na posi��o desejada
// cor por RGB: padr�o = preto
void write_text(int x, int y, SDL_Surface *destino, std::string texto, unsigned char R = 0, unsigned char G = 0, unsigned char B = 0);
// cor direto pelo SDL_Color
void write_text(int x, int y, SDL_Surface *destino, std::string texto, SDL_Color cor);
//----------------------------------------------------------------------------//
#endif // SIMPLESDLFUNCTIONS_H_INCLUDED

