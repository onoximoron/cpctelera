//-----------------------------LICENSE NOTICE------------------------------------
//  This file is part of CPCtelera: An Amstrad CPC Game Engine
//  Copyright (C) 2015 ronaldo / Fremos / Cheesetea / ByteRealms (@FranGallegoBR)
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//------------------------------------------------------------------------------

#include <cpctelera.h>
#include "mazes/mazes.h"
#include "sprites/sprites.h"

//////////////////////////////////////////////////////////////////////////////////////////
// STRUCTURES
//

// Entity statuses
typedef enum {
   ST_WALKLEFT  = 0, // Walking to the left
   ST_WALKRIGHT,     // Walking to the right
   ST_WALKUP   ,     // Walking up
   ST_WALKDOWN ,     // Walking down
   ST_HITLEFT  ,     // Hitting left
   ST_HITRIGHT ,     // Hitting right
   ST_HITUP    ,     // Hitting up
   ST_HITDOWN  ,     // Hitting down
   ST_DEAD,          // Being dead
   ST_NUMSTATUSES    // Total actions
} EEntityStatus;

// Entity information (Location, status and sprites)
typedef struct {
   u8 maze;              // Maze where the entity is located
   u8 tx, ty;            // Upper-left tile of the entity over the tilemap
   EEntityStatus status; // Status of the entity
   u8 **sprite_set;      // Set of sprites for different actions of the entity
} TEntity;

// We always draw over the backbuffer
u8* const g_backBuffer = (u8*)0x8000;

//////////////////////////////////////////////////////////////
// Switch Front and Back Screen Buffers
//   Backbuffer is shown on screen,
//   Frontbuffer is removed from screen and treated as new backbuffer
//
void switchScreenBuffers() {
   u8** backbuf = (u8**)(&g_backBuffer);

   // Check which is present backbuffer and then switch
   if (g_backBuffer == (u8*)0x8000) {
      *backbuf = (u8*)0xC000;
      cpct_setVideoMemoryPage(cpct_page80);
   } else {
      *backbuf = (u8*)0x8000;
      cpct_setVideoMemoryPage(cpct_pageC0);
   }
}

//u8* const g_entities[10];


void application(){
   maze_initialize(0);
   maze_draw(g_backBuffer);
   switchScreenBuffers();

   // Loop forever
   while (1);   
}

void main(void) {
   cpct_setStackLocation((u8*)0x8000);
   cpct_disableFirmware();
   cpct_setVideoMode(0);
   application();
}