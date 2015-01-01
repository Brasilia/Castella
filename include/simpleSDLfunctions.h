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

#define DEFAULT_FONT_SIZE 26

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

/* Cores b�sicas, em SDL_Color */
#define PRETO		{0, 0, 0}
#define BRANCO		{255, 255, 255}
#define VERMELHO	{255, 0, 0}
#define VERDE		{0, 255, 0}
#define AZUL		{0, 0, 255}
#define AMARELO		{255, 255, 0}
#define MAGENTA		{255, 0, 255}
#define CIANO		{0, 255, 255}


//############################# FUN��ES DE ATALHO ##############################
// Fun��es para facilitar a aplica��o de outras fun��es, otimizando suas
// utiliza��es, em termos de organiza��o e linhas de c�digo

//------------------------------ CARREGAR IMAGEM -----------------------------//
//Fun��o de carregamento de imagem
SDL_Surface *load_image (std::string nome_do_arquivo);
//----------------------------------------------------------------------------//

//--------------------------------- CRIAR SUPERFICIE -------------------------//
// Fun��o que cria uma superf�cie vazia
SDL_Surface *create_surface (int width, int height);
//----------------------------------------------------------------------------//

//---------------------------- APLICAR SUPERFICIE ----------------------------//
//Aplica uma superf�cie recebendo tamb�m suas coordenadas como par�metros
void apply_surface(int x, int y, SDL_Surface* fonte, SDL_Surface* destino,
		SDL_Rect* corte = NULL, float empurrar = 0);
/// Transforma um SDL_Color em Uint32, pras fun��es que o precisam
Uint32 getRGBAMap (SDL_Surface *target, SDL_Color cor, Uint8 alpha = 0xff);
/** @brief Preenche o fundo de uma superf�cie
 *
 * @param[in] target Superf�cie a ser 'pintada'
 * @param[in] cor Cor de fundo; padr�o = preto
 * @param[in] dstrect Ret�ngulo a ser preenchido; padr�o = em toda a superf�cie
 */
void fill_surface (SDL_Surface *target, SDL_Color cor = PRETO,
		SDL_Rect *dstrect = NULL);
//----------------------------------------------------------------------------//

//-------------------------------- ESCREVER TEXTO ----------------------------//
//Escreve um texto na tela, na posi��o desejada
// cor pelo SDL_Color: padr�o = preto
void write_text (int x, int y, SDL_Surface *destino, std::string texto,
		SDL_Color cor = PRETO, float alinhamento = 0);
//----------------------------------------------------------------------------//
#endif // SIMPLESDLFUNCTIONS_H_INCLUDED

