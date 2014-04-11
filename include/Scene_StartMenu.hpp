#ifndef SCENE_STARTMENU_H
#define SCENE_STARTMENU_H

#include "Scene.hpp"

class Scene_StartMenu : public Scene
{
    public:
        Scene_StartMenu();
        virtual ~Scene_StartMenu();

        virtual void draw(SDL_Surface *screen);

        virtual void update();

    protected:
        virtual void escape();
        virtual void handle_scene_input(int input);

    private:
        SDL_Surface *title;
};

#endif // SCENE_STARTMENU_H
