#ifndef GLOBAL_H
#define GLOBAL_H



SDL_Surface * screen = NULL;
bool quit = false;
bool win = false;
bool pause = false;
bool quitscreen = false;

SDL_Surface *secondsA = NULL;
SDL_Surface *secondsB = NULL;
SDL_Surface *startStop = NULL;
SDL_Event event;


SDL_Surface *inputScreen;

//TTF_Font *font = TTF_OpenFont( "lazy.ttf", 24 );



//The color of the font
SDL_Color textColor = {255,255,255};;


int inputlap = 1;
int lapcountA = 1;
int lapcountB = 1;

std::string playername;

//The screen attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

//The frame rate
const int FRAMES_PER_SECOND = 20;

//The dimensions of the dot
const int DOT_WIDTH = 20;
const int DOT_HEIGHT = 20;

struct axis{
    double x;
    double y;
};

struct circle{
    axis cor;
    int radius;
};

SDL_Surface *load_image( std::string filename )
{
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;
    
    //The optimized surface that will be used
    SDL_Surface* optimizedImage = NULL;
    
    //Load the image
    loadedImage = IMG_Load( filename.c_str() );
    
    //If the image loaded
    if( loadedImage != NULL )
    {
        //Create an optimized surface
        optimizedImage = SDL_DisplayFormat( loadedImage );
        
        //Free the old surface
        SDL_FreeSurface( loadedImage );
        
        //If the surface was optimized
        if( optimizedImage != NULL )
        {
            //Color key surface
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
        }
    }
    
    //Return the optimized surface
    return optimizedImage;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    //Holds offsets
    SDL_Rect offset;
    
    //Get offsets
    offset.x = x;
    offset.y = y;
    
    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}



bool init(){
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ){
        return false;
    }
    //Set up the screen
    
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
    //If there was an error in setting up the screen
    if( screen == NULL ){
        return false;
    }
    //Set the window caption
    if( TTF_Init() == -1 )
    {
        return false;
    }
    
    
    SDL_WM_SetCaption( "Car Racing", NULL );
    //If everything initialized fine
    return true;
}


void clean_up(){
    //Free the surface
    SDL_FreeSurface( screen );
    //Quit SDL
    SDL_Quit();
}


#endif
