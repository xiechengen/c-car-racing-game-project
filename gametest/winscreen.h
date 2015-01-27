//
//  winscreen.h
//  gametest
//
//  Created by MBA on 12/2/14.
//  Copyright (c) 2014 MBA. All rights reserved.
//

#ifndef gametest_winscreen_h
#define gametest_winscreen_h

void winscreen(int n){
    SDL_Surface *winner = NULL;
    winner = IMG_Load("winner.png");
    apply_surface(0, 0, winner, screen);
    
    
    SDL_Surface *message = NULL;
    
    
   
    std::stringstream string;
    
    //time box
    if (n==0) {
        string <<"The winner is" << playername<< "!";
    }
    
    if(n==1){
        string <<"The winner is" << "CarB"<< "!";
    }
    
     message = TTF_RenderText_Solid(TTF_OpenFont( "lazy.ttf", 24 ), string.str().c_str(), textColor );
    
    apply_surface(20, 240, message, screen);
    
    
    Button start( 70, 380, 180, 50 );
    
    
    
    
    start.load_files("startbut.png");
    
    start.set_clips();
    
    start.show();
    
    
    
    bool resume = false;
    
    while( resume == false )
    {
        
        //If there's events to handle
        if( SDL_PollEvent( &event ) )
        {
            //Handle button events
            start.handle_events();
            
            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit=true;
                resume = true;
            }
            
            if (start.buttonclick == true) {
                resume = true;
            }
            
            start.show();
            SDL_Flip( screen );
            
        }
        
    
        
        
    }
    
  
    
    SDL_free(winner);
    
    
    
}

#endif
