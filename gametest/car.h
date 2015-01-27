
#include "SDL_rotozoom.h"
#include <string>

#include <math.h>
#include "global.h"


class Car{
protected:
  circle c;
//  double x, y;
  //The velocity of the dot
  double Vel;
  //the direction of the dot;
  int direction;
  //the acceleration of the dot;
  int acc;
  //the turning action
  int turn;
  //top speed and acc
  double topspeed;
  int topacc;
  double x_shift, y_shift;
  //surface for car image
   
    int Car_covered[4][3]={0};

    bool lap = false;
   
    

  SDL_Surface *car;
 
public:
  //Initializes the variables
  Car(const char* filename );
  //Takes key presses and adjusts the dot's velocity
  //void handle_input( SDL_Event * event );
  //Moves the dot
  void move();
  //Shows the dot on the screen
  void show( SDL_Surface * screen);
  circle get_circle();
  void setTopSpeed(int ts);
  void move_back();
  int get_direction();
  double get_vel();
  void set_direction(int dir);
  void set_vel(int vel);
    
    bool checklap();
};

class Car_A : public Car{
 public:  
 Car_A(const char* filename ) : Car(filename ){}
  void handle_input( SDL_Event * event );
};

class Car_B : public Car{
 public:  
 Car_B(const char* filename ) : Car(filename ){
    c.cor.x = 130;
  }
  void handle_input( SDL_Event * event );
};


int Car::get_direction(){
  return direction;
}
double Car::get_vel(){
  return Vel;
}
void Car::set_direction(int dir){
  direction = dir;
}
void Car::set_vel(int vel){
  Vel = vel;
}

void Car::setTopSpeed(int ts){
  topspeed = ts;
}
Car::Car( const char* filename){
  //Initialize the offsets
  c.cor.x = 100;
  c.cor.y = 100;
  c.radius = 14;
  //Initialize the velocity
  Vel = 0;
  topspeed = 10;
  topacc = 5;

//Initialize the direction
  direction = 0;
  acc= 0;
  turn = 0;
  
  //load file to this class
  car = IMG_Load(filename);
  //if(car == NULL)
  // printf("error loading car.bmp");
}

void Car_A::handle_input(SDL_Event  * event ){
  //If a key was pressed
  if( event->type == SDL_KEYDOWN ){
    //printf("pressed\n");
    //Adjust the velocity
    switch( event->key.keysym.sym ){
    case SDLK_LEFT: turn -= 5; break;
    case SDLK_RIGHT: turn += 5; break;
    case SDLK_UP: acc = acc + 1; break;
    case SDLK_DOWN: acc = acc - 1; break;
    default: break;
    }
  }
  //If a key was released
  else if( event->type == SDL_KEYUP ){
    //printf("unpressed\n");
    //Adjust the velocity
    switch( event->key.keysym.sym ){
    case SDLK_UP: acc = 0; break;
    case SDLK_DOWN: acc = 0; break;
    case SDLK_LEFT: turn = 0; break;
    case SDLK_RIGHT: turn = 0; break;
    default: break;
    }
  }
}

void Car_B::handle_input(SDL_Event  * event ){
  //If a key was pressed
  if( event->type == SDL_KEYDOWN ){
    printf("pressed\n");
    //Adjust the velocity
    switch( event->key.keysym.sym ){
    case SDLK_a: turn -= 5; break;
    case SDLK_d: turn += 5; break;
    case SDLK_w: acc = acc + 1; break;
    case SDLK_s: acc = acc - 1; break;
    default: break;
    }
  }
  //If a key was released
  else if( event->type == SDL_KEYUP ){
    printf("unpressed\n");
    //Adjust the velocity
    switch( event->key.keysym.sym ){
    case SDLK_w: acc = 0; break;
    case SDLK_s: acc = 0; break;
    case SDLK_a: turn = 0; break;
    case SDLK_d: turn = 0; break;
    default: break;
    }
  }
}


void Car::move(){

  //Move the dot left or right
  if(acc >= topacc)
    acc = topacc;
  else if(acc <= -5)
    acc = -5;
  if(turn > 45)
    turn = 45;
  else if(turn < -45)
    turn = -45;

  //  printf("direction is %d, acc is %d, Vel is %f\n",direction, acc, Vel);
  direction = direction + turn;
  direction += 360;
  direction = direction % 360;
  Vel = Vel + acc;
  //top speed;
  if(Vel > topspeed)
    Vel = topspeed;
  else if(Vel < -3)
    Vel = -3;
  
  x_shift = Vel*sin(direction*3.14/180);
  y_shift = Vel*cos(direction*3.14/180);
  
  //when backward

  c.cor.x -= x_shift;
  //If the dot went too far to the left or right
  if( ( c.cor.x < 0 ) || ( c.cor.x + DOT_WIDTH > SCREEN_WIDTH ) ){
    //move back
    c.cor.x += x_shift;
    Vel = 0;
  }

  //Move the dot up or down
  c.cor.y += y_shift;
  
  //If the dot went too far up or down
  if( ( c.cor.y < 0 ) || ( c.cor.y + DOT_HEIGHT > SCREEN_HEIGHT ) ){
    //move back
    c.cor.y -= y_shift;
    Vel = 0;
  }
}
void Car::move_back(){
  c.cor.y -= y_shift;
  c.cor.x += x_shift;
    Vel = 0;
}

void Car::show( SDL_Surface *screen){
  SDL_Surface *rotate_car= NULL;
  double offset = 20*(sin((direction%90)*3.14/180)+cos((direction%90)*3.14/180));
  //printf("cor is (%d, %d)\n", int(c.cor.x),int(c.cor.y));
  rotate_car = rotozoomSurface(car,-direction, 1,1);
  apply_surface( int(c.cor.x - offset/2 ), int(c.cor.y - offset/2), rotate_car, screen );
  SDL_FreeSurface(rotate_car);
}

circle Car::get_circle(){
  return c;
}


bool Car::checklap(){
    
    int a = get_circle().cor.x / 160;
    int b = get_circle().cor.y / 160;
    
   //track visit
    if(Car_covered[a][b]==0){
        Car_covered[a][b]=1;
    }
    
    
    
    //printf("%d\n",Car_covered[a][b]);
  
    int allcover = 0;
    
    //count visited track
    for(int i = 0; i<4; i++){
        for(int j = 0; j<3; j++){
            if (Car_covered[i][j]>=1)
                allcover++;
            
        }
    }
    
    //printf("allcover %d\n",allcover);
    
    if (allcover==12 and a ==0 and b==0)
        lap=true;
    
    
    if (lap == true) {
        //reset visted track
        for(int i = 0; i<4; i++){
            for(int j = 0; j<3; j++){
                Car_covered[i][j]=0;
                
                
            }
        }
        
        lap = false;
        return true;
    }
    
    return false;
    
}
