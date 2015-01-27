#include "SDL/SDL.h"
#include "SDL_image/SDL_image.h"
//#include "SDL/SDL_rotozoom.h"
#include <string>
#include "global.h"
#include "tile.h"
//#include "car.h"

class Track{
 private:  
  SDL_Surface *track;
  Tile* st[4][3];
  
  int ACar_covered[4][3];
  int BCar_covered[4][3];
  int ACar_lap;
  int BCar_lap;

 public:
  Track();
  void init( SDL_Surface *screen);
  void show( SDL_Surface *screen);
  int surface_check( axis cor);
  int check_win(Car & ACar, Car & BCar);
};


Track::Track(){
  
}



void Track::init(SDL_Surface * screen){
  axis b[4][3];
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 3; j++){
      b[i][j].x = i*160;
      b[i][j].y = j*160;
      ACar_covered[i][j] = 0;
      BCar_covered[i][j] = 0;
    }
  }
  ACar_lap = 0;
  BCar_lap = 0;

  st[0][0] = new Corner("ctrack.png", b[0][0], 0); 
  st[0][1] = new Straight("strack.png", b[0][1], 0);
  st[0][2] = new Corner("ctrack.png", b[0][2], 90);
  st[1][0] = new Corner("ctrack.png", b[1][0], 270);
  st[1][1] = new Corner("ctrack.png", b[1][1], 90);
  st[1][2] = new Straight("strack.png", b[1][2], 90);
  st[2][0] = new Corner("ctrack.png", b[2][0], 0);
  st[2][1] = new Corner("ctrack.png", b[2][1], 180);
  st[2][2] = new Straight("strack.png", b[2][2], 90);
  st[3][0] = new Corner("ctrack.png", b[3][0], 270);
  st[3][1] = new Straight("strack.png", b[3][1], 180);
  st[3][2] = new Corner("ctrack.png", b[3][2], 180);

  
  track = screen;
}

void Track::show( SDL_Surface *screen){
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 3; j++){
      st[i][j]->show(track);
    }
  }
  apply_surface(0, 0, track, screen );
}


int Track::surface_check( axis cor){
  return st[int(cor.x/160)][int(cor.y/160)]->surface_check(cor);
}
