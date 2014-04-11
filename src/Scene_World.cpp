#include "Scene_World.hpp"

Scene_World::Scene_World()
{
    SceneControl::set_cur(SceneControl::SCENE_WORLD);
    windows.push_back(new Window("newgame"));
}

Scene_World::~Scene_World()
{
    //dtor
}

void Scene_World::update(){Scene::update();}

void Scene_World::draw(SDL_Surface *screen){Scene::draw(screen);}

void Scene_World::mouseclick(int x, int y){Scene::mouseclick(x, y);}

void Scene_World::escape(){
    SceneControl::set_next(SceneControl::SCENE_START_MENU);
}

void Scene_World::handle_scene_input(int input){}
