//
//  maingame.h
//  gametest
//
//  Created by MBA on 12/2/14.
//  Copyright (c) 2014 MBA. All rights reserved.
//

#ifndef gametest_maingame_h
#define gametest_maingame_h

void maingame(){
    //The event structure
    SDL_Event event;
    
    /*if( init() == false ) {
        return 1;
    }*/
    
    
    
    
    Car_A myCar = Car_A("carGreen.png" );
    Car_B BCar = Car_B("carRed.png" );
    Track mytrack = Track();
    Timer fps;
    int col_flag = 0;
    
    
    circle A_c = myCar.get_circle();
    circle B_c = BCar.get_circle();
    
    
    ///////race start////////
    //car Timer
    Timer TimerA;
    Timer TimerB;
    
    
    TimerA.start();
    TimerB.start();
    
    
    
    
    
    std::stringstream time;
    
    
    //Convert the timer's time to a string
    
    
    //Render the time surface
    
    
    
    
    
    
    /////////////////////////////
    
    
    mytrack.init(screen);
    
    printf("%d",inputlap);
    
    
    while( quit == false and win == false ){
        
        //printf("Time %d \n",TimerA.get_ticks());
        
        fps.start();
        
        while( SDL_PollEvent( &event ) ){
            if( event.type == SDL_KEYDOWN )
            {
                
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    //pause Timer
                    TimerA.pause();
                    pausescreen();
                    TimerA.unpause();
                }
            }
            
            
            
            
            
            
            myCar.handle_input( &event );
            BCar.handle_input( &event );
            if( event.type == SDL_QUIT ){
                quit = true;
            }
        }
        myCar.move();
        BCar.move();
        
        
        
        handle_collision(myCar, BCar, mytrack);
        if(col_flag == 0){
            car_collision(myCar, BCar);
            col_flag = 1;
        }
        A_c = myCar.get_circle();
        B_c = BCar.get_circle();
        
        if(!circle_overlap(A_c, B_c)){
            col_flag = 0;
        }
    
        //SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
        mytrack.show( screen );
        myCar.show( screen );
        BCar.show(screen);
        
        
        
        
        //Apply the messages
        apply_surface( 0, 0, startStop, screen );
        //apply_surface( ( SCREEN_WIDTH - pauseMessage->w ) / 2, 250, pauseMessage, screen );
        
        //The timer's time as a string
        std::stringstream laptimea;
        std::stringstream laptimeb;
        
        //time box
        laptimea <<playername<< "-> LapTime: " << TimerA.get_ticks() / 1000 << ":" << TimerA.get_ticks() % 1000;
        laptimea <<" Lap"<<lapcountA;
        laptimeb<< "CarB-> "<<"LapTime: " << TimerB.get_ticks() / 1000 << ":" << TimerA.get_ticks() % 1000;
        laptimeb <<" Lap"<<lapcountB;
        
        //Render the time surface
        secondsA = TTF_RenderText_Solid( TTF_OpenFont( "lazy.ttf", 24 ), laptimea.str().c_str(), {255, 255, 255 });
        secondsB = TTF_RenderText_Solid( TTF_OpenFont( "lazy.ttf", 24 ), laptimeb.str().c_str(), {255, 255, 255 });
        
        
        //Apply the time surface
        apply_surface(0, 0, secondsA, screen );
        apply_surface(0, 50, secondsB, screen );
        
        
        //Free the time surface
        SDL_FreeSurface( secondsA );
        SDL_FreeSurface( secondsB );
        
        //Update the screen
        SDL_Flip( screen );
        
        
        if(myCar.checklap()==true){
            lapcountA++;
            TimerA.stop();
            TimerA.start();
        }
        
        if(BCar.checklap()==true){
            lapcountB++;
            TimerB.stop();
            TimerB.start();
        }
        
        //Cap the frame rate
        if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND ){
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }
        
        if (lapcountA > inputlap) {
            win=true;
            winscreen(0);
            return;
        }
        
        if (lapcountB > inputlap) {
            win=true;
            winscreen(1);
            return;
        }
        
        
    }
    
    
    
    
   

}


#endif
