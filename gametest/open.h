//
//  open.h
//  game2
//
//  Created by MBA on 11/26/14.
//  Copyright (c) 2014 MBA. All rights reserved.
//

#ifndef game2_open_h
#define game2_open_h

#include "global.h"
#include <stdbool.h>
//The button states in the sprite sheet
const int CLIP_MOUSEOVER = 0;
const int CLIP_MOUSEOUT = 1;
const int CLIP_MOUSEDOWN = 2;
const int CLIP_MOUSEUP = 3;



//The event structure



//The button
class Button
{
private:
    //The attributes of the button
    SDL_Rect box;
    
    //The part of the button sprite sheet that will be shown
    SDL_Rect* clip;
    
public:
    //Initialize the variables
    Button( int x, int y, int w, int h);
    
    //Handles events and set the button's sprite region
    void handle_events();
    
    //Shows the button on the screen
    void show();
    
    bool buttonclick = false;
    //The surfaces
    SDL_Surface *buttonSheet = NULL;
    
    //The clip regions of the sprite sheet
    SDL_Rect clips[ 4 ];


    bool load_files( const char * filename)
    {
        //Load the button sprite sheet
        buttonSheet = IMG_Load(filename);
        
        //If there was a problem in loading the button sprite sheet
        if( buttonSheet == NULL )
        {
            return false;
        }
        
        //If everything loaded fine
        return true;
    }
    
    void set_clips()
    {
        //Clip the sprite sheet
        clips[ CLIP_MOUSEOVER ].x = 0;
        clips[ CLIP_MOUSEOVER ].y = 0;
        clips[ CLIP_MOUSEOVER ].w = 180;
        clips[ CLIP_MOUSEOVER ].h = 50;
        
        clips[ CLIP_MOUSEOUT ].x = 180;
        clips[ CLIP_MOUSEOUT ].y = 0;
        clips[ CLIP_MOUSEOUT ].w = 180;
        clips[ CLIP_MOUSEOUT ].h = 50;
        
        clips[ CLIP_MOUSEDOWN ].x = 0;
        clips[ CLIP_MOUSEDOWN ].y = 50;
        clips[ CLIP_MOUSEDOWN ].w = 180;
        clips[ CLIP_MOUSEDOWN ].h = 50;
        
        clips[ CLIP_MOUSEUP ].x = 180;
        clips[ CLIP_MOUSEUP ].y = 50;
        clips[ CLIP_MOUSEUP ].w = 180;
        clips[ CLIP_MOUSEUP ].h = 50;
    }

};




Button::Button( int x, int y, int w, int h)
{
    //Set the button's attributes
    box.x = x;
    box.y = y;
    box.w = w;
    box.h = h;
    
    //Set the default sprite
    clip = &clips[ CLIP_MOUSEOUT ];
}

void Button::handle_events()
{
    //The mouse offsets
    int x = 0, y = 0;
    
    //If the mouse moved
    if( event.type == SDL_MOUSEMOTION )
    {
        //Get the mouse offsets
        x = event.motion.x;
        y = event.motion.y;
        
        //If the mouse is over the button
        if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) )
        {
            //Set the button sprite
            clip = &clips[ CLIP_MOUSEOVER ];
        }
        //If not
        else
        {
            //Set the button sprite
            clip = &clips[ CLIP_MOUSEOUT ];
        }
    }
    //If a mouse button was pressed
    if( event.type == SDL_MOUSEBUTTONDOWN )
    {
        //If the left mouse button was pressed
        if( event.button.button == SDL_BUTTON_LEFT )
        {
            //Get the mouse offsets
            x = event.button.x;
            y = event.button.y;
            
            //If the mouse is over the button
            if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) )
            {
                //Set* the button sprite
                clip = &clips[ CLIP_MOUSEDOWN ];
            }
        }
    }
    //If a mouse button was released
    if( event.type == SDL_MOUSEBUTTONUP )
    {
        //If the left mouse button was released
        if( event.button.button == SDL_BUTTON_LEFT )
        {
            //Get the mouse offsets
            x = event.button.x;
            y = event.button.y;
            
            
            //If the mouse is over the button
            if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) )
            {
                //Set the button sprite
                clip = &clips[ CLIP_MOUSEUP ];
                buttonclick = true;
            }
        }
    }
}

void Button::show()
{
    //Show the button
    
    apply_surface( box.x, box.y, buttonSheet, screen, clip );
    
    
}








#endif
