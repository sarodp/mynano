
#ifndef DATA_CPP
#define DATA_CPP

#include <WProgram.h>
#include <avr/pgmspace.h>
#include "Data.h"

#if !defined(ARRAY_SIZE)
  #define ARRAY_SIZE(x) (sizeof((x)) / sizeof((x)[0]))
#endif

/* all our feaky fucking position data */

static const prog_uint16_t PGMScene01[] PROGMEM = 
{ ................................ data is nomally here but it was to much for this post................ 
};

static const prog_uint16_t PGMScene02[] PROGMEM = 
{ ................................ data is nomally here but it was to much for this post................ 
};

static const prog_uint16_t PGMScene03[] PROGMEM = 
{ ................................ data is nomally here but it was to much for this post................ 
}; 




const prog_uint16_t* PGMScenes[] = 
{ PGMScene01, PGMScene02, PGMScene03, PGMScene04, PGMScene05, PGMScene06, PGMScene07,
PGMScene08, PGMScene09, PGMScene10, PGMScene11, PGMScene12, PGMScene13, PGMScene14, PGMScene15, PGMScene16 };

const unsigned int PGMFrameLengths[] = 
{ 972, 895, 559, 1413, 660, 746, 688, 334, 572, 294, 549, 484, 3079, 948, 531, 1697 };

Data data;

void Data::setup() {  
 verbose           = true;
 
 interpolating     = false;
 scene_count       = ARRAY_SIZE(PGMScenes);
 frame_count       = 0; 
 scene_pos         = -1;
 frame_pos         = -1;
 point[0] = point[1] = point[2] = 0; // _x _y _z
 frame[0] = frame[1] = frame[2] = frame[3] = frame[4] = 0; //_scene _frame _x _y _z
 frames_in_between = 44; //leere frames zwischen zwei scenen
 frames_at_start   = 70; //leere frames am anfang des filmes   

 lscene_lframe[0] = lscene_lframe[1] = lscene_lframe[2] = 0; 
 tscene_fframe[0] = tscene_fframe[1] = tscene_fframe[2] = 0; 
 tframe[0] = tframe[1] = tframe[2] = 0;    
 
 if (verbose) {
   Serial.begin(115200);
 }
}

/* triggers the next scene 
* at the beginning of a scene go first in transition mode by substracting 
* frames_in_between or frames_at_start from the frame_pos
*/

int Data::nextScene() {
 if(scene_count - 1 > scene_pos) {
   scene_pos++;
   last_frame_pos = frame_pos;
   frame_pos = (scene_pos == 0) ? -frames_at_start-1 : -frames_in_between-1;
   frame_count = PGMFrameLengths[scene_pos];
   if (verbose) {
     Serial.print("Scene: "); Serial.println(scene_pos);
     Serial.print("Frame: "); Serial.println(frame_pos);
     Serial.print("Framecount: "); Serial.println(frame_count);
     Serial.print("Scenecount: "); Serial.println(scene_count);
   }
 }
 return scene_pos;
}

/* triggers the next frame and fills the position array 
*/
int Data::nextFrame() {
 if(frame_pos < frame_count - 1 ) {
   frame_pos++;
   //Serial.print("Frame Pos: "); Serial.println(frame_pos);
   if(frame_pos >= 0) { // only if we'r not in the scene transition mode
     if(scene_pos != 12) {
       tframe[0] = pgm_read_word_far( PGMScenes[scene_pos] + (frame_pos * 3) + 0 );
       tframe[1] = pgm_read_word_far( PGMScenes[scene_pos] + (frame_pos * 3) + 1 );
       tframe[2] = pgm_read_word_far( PGMScenes[scene_pos] + (frame_pos * 3) + 2 );
     }else{
       tframe[0] = pgm_read_word_far( PGMScene13 + (frame_pos * 3) + 0 );
       tframe[1] = pgm_read_word_far( PGMScene13 + (frame_pos * 3) + 1 );
       tframe[2] = pgm_read_word_far( PGMScene13 + (frame_pos * 3) + 2 );
     }
     interpolating = false;      
   } else if(scene_pos != 0 && scene_pos != -1) { // here we'r in transition mode
     /* get the last frame from last scene (lscene_lframe) and the first frame from this 
      * scene (tscene_fframe) for transition 
      */
     //int frame_count_last_scene =  (PGMFrameLengths[scene_pos - 1]) - 1;
     int frame_count_last_scene = last_frame_pos; // get the framepos from last scene before jumping into interpolation mode
      if(scene_pos - 12 != 1 ) {
       lscene_lframe[0] = pgm_read_word_far( PGMScenes[scene_pos-1] + (frame_count_last_scene * 3 + 0) );
       lscene_lframe[1] = pgm_read_word_far( PGMScenes[scene_pos-1] + (frame_count_last_scene * 3 + 1) );
       lscene_lframe[2] = pgm_read_word_far( PGMScenes[scene_pos-1] + (frame_count_last_scene * 3 + 2) );
     } else {
       lscene_lframe[0] = pgm_read_word_far( PGMScene13 + (frame_count_last_scene * 3 + 0) );
       lscene_lframe[1] = pgm_read_word_far( PGMScene13 + (frame_count_last_scene * 3 + 1) );
       lscene_lframe[2] = pgm_read_word_far( PGMScene13 + (frame_count_last_scene * 3 + 2) );
     }
     if(scene_pos != 12) {
       tscene_fframe[0] = pgm_read_word_far( PGMScenes[scene_pos] + 0 );
       tscene_fframe[1] = pgm_read_word_far( PGMScenes[scene_pos] + 1 );
       tscene_fframe[2] = pgm_read_word_far( PGMScenes[scene_pos] + 2 );
     } else {
       tscene_fframe[0] = pgm_read_word_far( PGMScene13 + 0 );
       tscene_fframe[1] = pgm_read_word_far( PGMScene13 + 1 );
       tscene_fframe[2] = pgm_read_word_far( PGMScene13 + 2 );
     }
     /* interpolate between these two points */
     
     interpolate(lscene_lframe, tscene_fframe, tframe, frames_in_between + frame_pos);
     interpolating = true;

   } else { // here we'r at the beginning of the film - send 70. times zero 
     tframe[0] = 0; tframe[1] = 0; tframe[2] = 0; 
     interpolating = true;
   }
   /* fill the frame and position aka point arrays */
   point[0] = tframe[0]; point[1] = tframe[1];  point[2] = tframe[2];
   frame[0] = scene_pos;  frame[1] = frame_pos; frame[2] = tframe[0]; frame[3] = tframe[1]; frame[4] = tframe[2];      
 }
 return frame_pos;
}

/* returns count of scenes */
int Data::getSceneCount() {
 return scene_count;
}

/* returns count of frames of actual active scene */
int Data::getFrameCount() {
 return frame_count;
}

/* returns frameposition in actual scene */
int Data::getFramePos() {
 return frame_pos;
}

/* returns the camera position of the actual frame as Array() */
long* Data::getPosition() {
 return point;
}

/* returns the actual frame (_scene_pos, _frame_pos, _x, _y, _z) 
* --> simmilar to getPosition();
*/
long* Data::getFrame() {
 return frame;
}

/* resets everything including scene_pos and frame_pos -> back to the start */
void Data::reset() {
 scene_pos   = -1;
 frame_pos   = -1;
 frame_count = 0;
 point[0] = point[1] = point[2] = 0;
 frame[0] = frame[1] = frame[2] = frame[3] = frame[4] = 0;
}

/* returns if the mashine is interpolating right now */
bool Data::isInterpolating() {
 return interpolating;
}

int Data::availableMemory() 
{
 int size = 1024;
 byte *buf;
 while ((buf = (byte *) malloc(--size)) == NULL);
 free(buf);
 return size;
}

/* private stuff */
void Data::interpolate(long from[3], long to[3], long dst[3], int in_stack) 
{ 
 float mu = ( float(in_stack) / float(frames_in_between) );

 int tx = round(CosineInterpolate(float(from[0]), float(to[0]), mu));
 int ty = round(CosineInterpolate(float(from[1]), float(to[1]), mu));
 int tz = round(CosineInterpolate(float(from[2]), float(to[2]), mu));
 
 dst[0] = tx; dst[1] = ty; dst[2] = tz;
}

float Data::CosineInterpolate(float y1, float y2, float mu) {
 float mu2;
 mu2 = (1.0-cos(mu*PI))/2.0;
 return(y1*(1.0-mu2)+y2*mu2);
}

#endif
