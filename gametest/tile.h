#include "SDL/SDL.h"
#include "SDL_image/SDL_image.h"
#include "SDL_rotozoom.h"
#include <string>
#include "global.h"
#include <math.h>


class Tile{
 protected:
  axis base;
  SDL_Surface *tile;
  int direction;
 public:
  Tile(){}
  Tile(std::string filename, axis base, int direction);
  void show(SDL_Surface * track);
  virtual int surface_check(axis cor){ return 2;}

};

class Straight : public Tile{
 public:
  Straight(){}
 Straight(std::string filename, axis base, int direction):  Tile(filename,  base, direction){}
  virtual int surface_check(axis cor);
};

class Corner : public Tile{
 public:
  Corner(){}
 Corner(std::string filename, axis base, int direction):  Tile(filename,  base, direction){}
  virtual int surface_check(axis cor);
};



Tile::Tile(std::string filename, axis _base,int _direction){
  direction = _direction;
  base = _base;
  tile = load_image(filename);
  tile = rotozoomSurface(tile, direction, 1, 0);
}

void Tile::show(SDL_Surface * track){
  if(direction == 90)
    apply_surface(base.x, base.y-1, tile, track);
  else if(direction == 180)
    apply_surface(base.x-2, base.y-2, tile, track);
  else if(direction == 270)
    apply_surface(base.x-2, base.y-2, tile, track);
  apply_surface(base.x, base.y, tile, track);
}


int Straight::surface_check( axis cor){
  int t = 0;
  if(direction%180 == 0)
    t = cor.x - base.x;
  else if(direction % 180 == 90)
    t = cor.y - base.y;
  
  if( t> 30 && t< 130)
    return 2; //ontrack
  else if( t> 20 && t< 140)
    return 1; //on grass
  else 
    return 0; //hit wall 
  
}
int Corner::surface_check( axis cor){
  axis apex;
  apex.x = base.x;
  apex.y = base.y;
  if(direction == 0){
    apex.x += 160;
    apex.y += 160;
  } 
  else if(direction == 90){
    apex.x += 160;
  }
  else if(direction == 270){
    apex.y += 160;
  }

  double t;
  t = sqrt((cor.x-apex.x)*(cor.x-apex.x)+(cor.y-apex.y)*(cor.y-apex.y));
  if( t> 30 && t< 130)
    return 2; //ontrack
  else if( t> 20 && t< 145)
    return 1; //on grass
  else
    return 0; //hit wall      
}

