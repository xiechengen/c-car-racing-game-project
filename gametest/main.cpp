#include "SDL/SDL.h"
#include "SDL_image/SDL_image.h"
#include "SDL_ttf/SDL_ttf.h"

#include <string>
#include <sstream>
#include "global.h"

#include "car.h"
#include "timer.h"
#include "track.h"



#include "open.h"
#include "pause.h"
#include "stringinput.h"
#include "collision.h"
#include "winscreen.h"
#include "maingame.h"
#include "inputlap.h"



int main( int argc, char* args[] ) {
    
    
    /////OPENING SCREEN-----/////////////////
    
    
    
    //Initialize
    if( init() == false )
    {
        return 1;
    }
    
    //Load the files
    
    
    //Clip the sprite sheet
    
    //Make the button
    Button start( 70, 380, 180, 50 );
    Button quitgame( 400, 380, 180, 50 );
    //Button quit(
    
    
    if( (start.load_files("startbut.png") == false) or (quitgame.load_files("quitbut.png")==false))
    {
        return 1;
    }
    
    start.set_clips();
    quitgame.set_clips();
    
    SDL_Surface *background = load_image("opening.png");
    apply_surface( 0, 0, background, screen );
    
    
    
    //While the user hasn't quit
    while( quit == false )
    {
        
        //If there's events to handle
        if( SDL_PollEvent( &event ) )
        {
            //Handle button events
            start.handle_events();
            quitgame.handle_events();
            
            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }
        }
        
    
        
        
        
        
        start.show();
        quitgame.show();
        
        //Update the screen
        if( SDL_Flip( screen ) == -1 )
        {
            return 1;
        }
        
        
        if(start.buttonclick == true){
            quit = true;
        }
        
        //quit game
        if (quitgame.buttonclick == true) {
            clean_up();
            return 0;
        }
        
    }
    
    SDL_free(background);
    
    
    ///////enterlap screen;
    enterName();
    enterLap();
    
    /////////////////////
    
    
    
    
    
    printf("%d\n",inputlap);
    
    /*if (quit==true) {
        clean_up();
        return 0;
    }*/
    
    ///////////////////sdalfjslkdajflsadjflksjdlfksldjf///////////////////
    
    quit = false;
    
    
    while (quit==false) {
        maingame();
        lapcountA=0;
        lapcountB=0;
        win = false;
        SDL_FreeSurface( screen );
        //printf("quitgame3");
        
    }
   
    
    
    
    
    clean_up();
    return 0;
}
