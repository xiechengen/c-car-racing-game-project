
//#include "car.h"
//#include "timer.h"
//#include "track.h"
#include "global.h"


void track_collision(Car& myCar, Track& mytrack){
  circle c = myCar.get_circle();
  int collision_flag = mytrack.surface_check(c.cor);
  if(collision_flag == 1)
    myCar.setTopSpeed(5);
  else if(collision_flag == 2)
    myCar.setTopSpeed(10);
  else if(collision_flag == 0)
    myCar.move_back();
  //printf("collision condition %d\n", collision_flag); 
}

int circle_overlap(circle &A, circle &B){
  double d = sqrt((A.cor.x - B.cor.x)*(A.cor.x - B.cor.x) + (A.cor.y - B.cor.y)*(A.cor.y - B.cor.y));
  if(d<(A.radius + B.radius))
    return 1;
  return 0;
}



void car_collision( Car & ACar, Car & BCar){
  circle A_c = ACar.get_circle();
  circle B_c = BCar.get_circle();
  int angle = 0;
  double vel_after_col_A, vel_after_col_B;
  double vel_A_sin, vel_A_cos;
  double vel_B_sin, vel_B_cos;
  double angle_A_delta;
  double angle_B_delta;
  double A_vel, B_vel;
  
  if(circle_overlap(A_c, B_c)){
    //    printf("collision deteced\n");
    angle = abs(ACar.get_direction() - BCar.get_direction())/2;

    vel_A_sin = ACar.get_vel() * sin(angle *3.14/180);
    vel_B_sin = BCar.get_vel() * sin(angle *3.14/180);
    vel_A_cos = ACar.get_vel() * cos(angle *3.14/180);
    vel_B_cos = BCar.get_vel() * cos(angle *3.14/180);

    //vel_after_col = (vel_A_cos + vel_B_cos) /2;
    if(vel_A_cos > vel_B_cos){
      vel_after_col_A = vel_B_cos;
      vel_after_col_B = vel_A_cos;
    }

    if(vel_A_cos < vel_B_cos){
      vel_after_col_B = vel_A_cos;
      vel_after_col_A = vel_B_cos;
    }

    A_vel = sqrt(vel_A_sin*vel_A_sin + vel_after_col_A*vel_after_col_A);
    B_vel = sqrt(vel_B_sin*vel_B_sin + vel_after_col_B*vel_after_col_B);
    //A_vel = vel_A_sin + vel_after_col;
    //B_vel = vel_B_sin + vel_after_col;
    if(A_vel > 15)
      A_vel = 15;
    if(B_vel > 15)
      B_vel = 15;

    
    // if((A_vel > B_vel) && (A_vel < (B_vel+1))){
    //   A_vel = A_vel + 1;
    // }
    // else if((A_vel < B_vel) && (B_vel < (A_vel+1))){
    //    B_vel = B_vel + 1;
    // }
    
    ACar.set_vel(A_vel);
    BCar.set_vel(B_vel);
    
    angle_A_delta = atan(vel_A_sin / vel_after_col_A) - atan(vel_A_sin / vel_A_cos);    
    angle_A_delta = int(angle_A_delta) % 360;
    angle_B_delta = atan(vel_B_sin / vel_after_col_B) - atan(vel_B_sin / vel_B_cos);
    angle_B_delta = int(angle_B_delta) % 360;

    // angle_A_delta = ACar.get_direction();
    // angle_B_delta = BCar.get_direction();
   

    if(A_vel < 1 ){
      ACar.move_back();
    }
    else{
      //      ACar.set_direction(angle_B_delta);
      ACar.set_direction(ACar.get_direction() - angle_A_delta);
    }
    if(B_vel < 1){
      BCar.move_back();
    }
    else{
      //      BCar.set_direction(angle_A_delta);
            BCar.set_direction(BCar.get_direction() - angle_B_delta);
    }
  } 
}

void handle_collision(Car& ACar, Car& BCar, Track& mytrack){
  track_collision(ACar, mytrack);
  track_collision(BCar, mytrack);
  //  if(!(ACar.get_vel() == 0 && BCar.get_vel() == 0))
    
}
