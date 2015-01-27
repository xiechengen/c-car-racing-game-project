
#ifndef game2_pause_h
#define game2_pause_h



void pausescreen(){
    SDL_Surface *pause = NULL;
    pause = IMG_Load("pause.png");
    apply_surface(0, 0, pause, screen);
    
    
    

    
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
        
        //Fill the screen white
        //SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
        
        
        //background
        
        
        
        //Show the button
        
        
        
        
    }
    
    
    SDL_free(pause);


    
}


#endif
