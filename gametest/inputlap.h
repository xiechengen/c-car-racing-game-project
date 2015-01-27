//
//  inputlap.h
//  gametest
//
//  Created by MBA on 12/2/14.
//  Copyright (c) 2014 MBA. All rights reserved.
//

#ifndef gametest_inputlap_h
#define gametest_inputlap_h



void enterName(){
    quitscreen = false;
    
    //player name
    StringInput name;
    
    
    //Keep track if whether or not the user has entered their name
    bool nameEntered = false;
    
    
    
    SDL_Surface *message = NULL;
    inputScreen = load_image("opening.png");
    
    //Set the message
    message = TTF_RenderText_Solid(TTF_OpenFont( "lazy.ttf", 24 ), "Enter your name:", textColor );
    
    //While the user hasn't quit
    while( quitscreen == false )
    {
        //While there's events to handle
        while( SDL_PollEvent( &event ) )
        {
            //If the user hasn't entered their name yet
            if( nameEntered == false )
            {
                //Get user input
                name.handle_input();
                
                
                //If the enter key was pressed
                if( ( event.type == SDL_KEYDOWN ) && ( event.key.keysym.sym == SDLK_RETURN ) )
                {
                    //Change the flag
                    nameEntered = true;
                    quitscreen = true;
                    
                    //Free the old message surface
                    //SDL_FreeSurface( message );
                    
                    
                    //Change the message
                    
                    
                }
            }
            
            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }
        }
        
        //Apply the background
        apply_surface( 0, 0, inputScreen, screen );
        
        //Show the message
        apply_surface( ( SCREEN_WIDTH - message->w ) / 2, ( ( SCREEN_HEIGHT / 2 ) - message->h ) / 2, message, screen );
        
        //Show the name on the screen
        
        playername = name.getstring();
        name.show_centered();
        //Update the screen
        SDL_Flip( screen );
        
    }
    
    //free(inputScreen);
}


void enterLap(){
    quitscreen = false;
    
    //player name
    StringInput laps;
    
     //printf("hiii!");
    //Keep track if whether or not the user has entered their name
    bool nameEntered = false;
    
    
    
    SDL_Surface *message = NULL;
    inputScreen = IMG_Load("opening.png");
    
    //Set the message
    message = TTF_RenderText_Solid(TTF_OpenFont( "lazy.ttf", 24 ), "Enter the laps(1-5)", textColor );
    
    //While the user hasn't quit
    while( quitscreen == false )
    {
        //While there's events to handle
        while( SDL_PollEvent( &event ) )
        {
            //If the user hasn't entered their name yet
            if( nameEntered == false )
            {
                //Get user input
                laps.handle_input();
                
                
                //If the enter key was pressed
                if( ( event.type == SDL_KEYDOWN ) && ( event.key.keysym.sym == SDLK_RETURN ) )
                {
                    //Change the flag
                    nameEntered = true;
                    quitscreen = true;
                    
                    //Free the old message surface
                    //SDL_FreeSurface( message );
                    
                    
                    //Change the message
                    
                    
                }
            }
            
            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }
        }
        
       
        
        //Apply the background
        apply_surface( 0, 0, inputScreen, screen );
        
        //Show the message
        apply_surface( ( SCREEN_WIDTH - message->w ) / 2, ( ( SCREEN_HEIGHT / 2 ) - message->h ) / 2, message, screen );
        
        //Show the name on the screen
        
        std::istringstream (laps.getstring()) >> inputlap;
        //inputlap = std::stoi (laps.getstring());
        
        laps.show_centered();
        //Update the screen
        SDL_Flip( screen );
        
    }
}



#endif
