#include "simpleSDLfunctions.h"

//################################## FUN��ES DE ATALHO ##################################OO
//Fun��es para facilitar a aplica��o de outras fun��es, otimizando suas utiliza��es,
//em termos de organiza��o e linhas de c�digo

//---------------------------------- CARREGAR IMAGEM ------------------------------------//
//Fun��o de carregamento de imagem
SDL_Surface *load_image (std::string nome_do_arquivo)
{
    //Ponteiro de armazenamento de imagem
    SDL_Surface *imagemAux = NULL;
    SDL_Surface *imagem = NULL;

    //Carregar imagem
    imagemAux = IMG_Load (nome_do_arquivo.c_str ());
    //Se a imagem tiver sido carregada corretamente
    if (imagemAux != NULL)
    {
        //Otimizar a imagem
        imagem = SDL_DisplayFormat(imagemAux);
        SDL_FreeSurface(imagemAux);

        //Definir cor chave
        Uint32 corchave = SDL_MapRGB(imagem->format, 0xFF, 0, 0xFF);

        //Tornar a cor chave transparente
        SDL_SetColorKey(imagem, SDL_SRCCOLORKEY, corchave);
    }

    //Retorna a imagem otimizada
    return imagem;
}
//---------------------------------------------------------------------------------------//

//--------------------------------- CRIAR SUPERFICIE --------------------------/
// Fun��o que cria uma superf�cie vazia
SDL_Surface *create_surface (int width, int height) {
	return SDL_CreateRGBSurface (SDL_SWSURFACE, width, height, 32,
			RMASK, GMASK, BMASK, AMASK);
}
//

//--------------------------------- APLICAR SUPERFICIE ----------------------------------//
//Aplica uma superf�cie recebendo tamb�m suas coordenadas como par�metros
void apply_surface(int x, int y, SDL_Surface* fonte, SDL_Surface* destino, SDL_Rect* corte, float empurrar)
{
    //Especifica as coordenadas x e y da superf�cie
    SDL_Rect coordenada;
    coordenada.x = x;
    coordenada.y = y;

    coordenada.x -= fonte->w*empurrar;

    //Transferir superf�cie para seu destino
    SDL_BlitSurface(fonte, corte, destino, &coordenada);
}

Uint32 getRGBAMap (SDL_Surface *target, SDL_Color cor, Uint8 alpha) {
	return SDL_MapRGBA (target->format, cor.r, cor.g, cor.b, alpha);
}

// Preenche o fundo de uma superf�cie: padr�o = preto
void fill_surface (SDL_Surface *target, SDL_Color cor, SDL_Rect *dstrect) {
	SDL_FillRect (target, dstrect, getRGBAMap (target, cor));
}
//---------------------------------------------------------------------------------------//

//--------------------------------- ESCREVER TEXTO --------------------------------//
//Escreve um texto na tela, na posi��o desejada
void write_text(int x, int y, SDL_Surface *destino, std::string texto, SDL_Color cor, float alinhamento)
{
	TTF_Font *fonte = TTF_OpenFont ("DejaVuSansMono.ttf", DEFAULT_FONT_SIZE);
	SDL_Surface *mensagem = TTF_RenderUTF8_Solid (fonte, texto.c_str (), cor);

	apply_surface (x, y, mensagem, destino, NULL, alinhamento);

	SDL_FreeSurface (mensagem);
	TTF_CloseFont (fonte);
}
//---------------------------------------------------------------------------------------//
