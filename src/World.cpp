#include <World.hpp>
#include <stdlib.h>

World::World()
{
    //ctor
}

World::~World()
{
    //dtor
}

World* World::get_world(){
    if(world == NULL){
        world = new World();
    }
    return world;
}

World* World::world = NULL;
