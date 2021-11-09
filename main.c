#include "stdio.h"
#include "stdlib.h"
#include "SDL.h"
#include "SDL2_gfxPrimitives.h"
#include <sys/time.h>

#include "formulas.h"
#include "wall.h"
#include "robot.h"

#include "math.h"

int done = 0;


int main(int argc, char *argv[]) {
    SDL_Window *window;
    SDL_Renderer *renderer;

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        return 1;
    }

    window = SDL_CreateWindow("Robot Maze", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, OVERALL_WINDOW_WIDTH, OVERALL_WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    window = SDL_CreateWindow("Robot Maze", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, OVERALL_WINDOW_WIDTH, OVERALL_WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(window, -1, 0);

    struct Robot robot;
    struct Wall_collection *head = NULL;
    int front_left_sensor = 0, front_right_sensor= 0, right_sensor = 0, left_sensor = 0, leftest_sensor = 0;
    struct timeval start_time, end_time;
    gettimeofday(&start_time, 0);
    unsigned long msec;

    // SETUP MAZE
    // You can create your own maze here. line of code is adding a wall.
    // You describe position of top left corner of wall (x, y), then width and height going down/to right
    // Relative positions are used (OVERALL_WINDOW_WIDTH and OVERALL_WINDOW_HEIGHT)
    // But you can use absolute positions. 10 is used as the width, but you can change this.
    /*
    // Base Maze
    insertAndSetFirstWall(&head, 1,  OVERALL_WINDOW_WIDTH/2, OVERALL_WINDOW_HEIGHT/2, 10, OVERALL_WINDOW_HEIGHT/2);
    insertAndSetFirstWall(&head, 2,  OVERALL_WINDOW_WIDTH/2-100, OVERALL_WINDOW_HEIGHT/2+100, 10, OVERALL_WINDOW_HEIGHT/2-100);
    insertAndSetFirstWall(&head, 3,  OVERALL_WINDOW_WIDTH/2-250, OVERALL_WINDOW_HEIGHT/2+100, 150, 10);
    insertAndSetFirstWall(&head, 4,  OVERALL_WINDOW_WIDTH/2-150, OVERALL_WINDOW_HEIGHT/2, 150, 10);
    insertAndSetFirstWall(&head, 5,  OVERALL_WINDOW_WIDTH/2-250, OVERALL_WINDOW_HEIGHT/2-200, 10, 300);
    insertAndSetFirstWall(&head, 6,  OVERALL_WINDOW_WIDTH/2-150, OVERALL_WINDOW_HEIGHT/2-100, 10, 100);
    insertAndSetFirstWall(&head, 7,  OVERALL_WINDOW_WIDTH/2-250, OVERALL_WINDOW_HEIGHT/2-200, 450, 10);
    insertAndSetFirstWall(&head, 8,  OVERALL_WINDOW_WIDTH/2-150, OVERALL_WINDOW_HEIGHT/2-100, 250, 10);
    insertAndSetFirstWall(&head, 9,  OVERALL_WINDOW_WIDTH/2+200, OVERALL_WINDOW_HEIGHT/2-200, 10, 300);
    insertAndSetFirstWall(&head, 10,  OVERALL_WINDOW_WIDTH/2+100, OVERALL_WINDOW_HEIGHT/2-100, 10, 300);
    insertAndSetFirstWall(&head, 11,  OVERALL_WINDOW_WIDTH/2+100, OVERALL_WINDOW_HEIGHT/2+200, OVERALL_WINDOW_WIDTH/2-100, 10);
    insertAndSetFirstWall(&head, 12,  OVERALL_WINDOW_WIDTH/2+200, OVERALL_WINDOW_HEIGHT/2+100, OVERALL_WINDOW_WIDTH/2-100, 10);
    */
    

 int i;
    insertAndSetFirstWall(&head, 12,  120, 450, 10, 30);
    insertAndSetFirstWall(&head, 12,  220, 450, 10, 30);
    for (i = 0; i < 100; i++){
        insertAndSetFirstWall(&head, i,  20 + i , 350 + i, 10, 10); //1
        insertAndSetFirstWall(&head, i,  20 +100 + i , 350 + i, 10, 10); //1
    }
    insertAndSetFirstWall(&head, 12,  20, 280, 10, 70);
    insertAndSetFirstWall(&head, 12,  120, 280, 10, 70);
    for (i = 0; i < 180; i++){
        insertAndSetFirstWall(&head, i,  20 +190 - i/2 , 100 + i, 10, 10); //1
    }
    for (i = 0; i < 105; i++){
        insertAndSetFirstWall(&head, i,  20 +105/2 - i/2 , 175 + i, 10, 10); //1
    }
    insertAndSetFirstWall(&head, 2,  20, 175, 105/2, 10);
    insertAndSetFirstWall(&head, 2,  20, 20, 10, 155);
    insertAndSetFirstWall(&head, 2,  20, 20, 300, 10);
    insertAndSetFirstWall(&head, 2,  320, 20, 10, 60);
    insertAndSetFirstWall(&head, 2,  80, 100, 130, 10);
    insertAndSetFirstWall(&head, 2,  80, 80, 10, 20);
    insertAndSetFirstWall(&head, 2,  80, 80, 160, 10);

    double j;
    for (i = 0; i < 50; i++){
        j = i;
        insertAndSetFirstWall(&head, i+1,
                              // the most important bit is below.
                              // increase the 20 for a tighter bend
                              // descrease for a more meandering flow
                              320 + 30*sin(10*j * M_PI/180),
                              // increase the 5 for a spacier curve
                              (i * 5)+80,
                              10, 10);
    }
    for (i = 0; i < 75; i++){
        j = i;
        insertAndSetFirstWall(&head, i+1,
                              // the most important bit is below.
                              // increase the 20 for a tighter bend
                              // descrease for a more meandering flow
                              240 + 30*sin(10*j * M_PI/180),
                              // increase the 5 for a spacier curve
                              (i * 5)+80,
                              10, 10);
    }
    insertAndSetFirstWall(&head, 2,  345, 330, 105, 10);
    insertAndSetFirstWall(&head, 2,  450, 190, 10, 150);
    insertAndSetFirstWall(&head, 2,  380, 190, 70, 10);
    insertAndSetFirstWall(&head, 2,  380, 20, 10, 170);
    insertAndSetFirstWall(&head, 2,  380, 20, 260, 10);

    insertAndSetFirstWall(&head, 2,  255, 455, 345, 10);
    insertAndSetFirstWall(&head, 2,  600, 100, 10, 365);
    insertAndSetFirstWall(&head, 2,  530, 100, 70, 10);
    insertAndSetFirstWall(&head, 2,  530, 80, 10, 20);
    insertAndSetFirstWall(&head, 2,  530, 80, 110, 10);
    
    
    /*
    // Complex maze
    insertAndSetFirstWall(&head, 1,  0 + 15, 0 + 10, 610, 10);
    insertAndSetFirstWall(&head, 2,  0 + 15, 150 + 10, 310, 10);
    insertAndSetFirstWall(&head, 3,  0 + 15, 250 + 10, 60, 10);
    insertAndSetFirstWall(&head, 4,  0 + 15, 0 + 10, 10, 160);
    insertAndSetFirstWall(&head, 5,  0 + 15, 200 + 10, 10, 260);
    insertAndSetFirstWall(&head, 6,  50 + 15, 150 + 10, 10, 60);
    insertAndSetFirstWall(&head, 7,  50 + 15, 250 + 10, 10, 60);
    insertAndSetFirstWall(&head, 8,  100 + 15, 100 + 10, 10, 160);
    insertAndSetFirstWall(&head, 9,  50 + 15, 50 + 10, 10, 60);
    insertAndSetFirstWall(&head, 10,  50 + 15, 50 + 10, 60, 10);
    insertAndSetFirstWall(&head, 11,  100 + 15, 0 + 10, 10, 60);
    insertAndSetFirstWall(&head, 12,  0 + 15, 350 + 10, 110, 10);
    insertAndSetFirstWall(&head, 13,  100 + 15, 350 + 10, 10, 60);
    insertAndSetFirstWall(&head, 14,  100 + 15, 400 + 10, 60, 10);
    insertAndSetFirstWall(&head, 15,  150 + 15, 350 + 10, 10, 60);
    insertAndSetFirstWall(&head, 16,  50 + 15, 400 + 10, 10, 60);
    insertAndSetFirstWall(&head, 17,  150 + 15, 350 + 10, 210, 10);
    insertAndSetFirstWall(&head, 18,  250 + 15, 350 + 10, 10, 60);
    insertAndSetFirstWall(&head, 19,  350 + 15, 350 + 10, 10, 60);
    insertAndSetFirstWall(&head, 20,  350 + 15, 400 + 10, 160, 10);
    insertAndSetFirstWall(&head, 21,  500 + 15, 350 + 10, 10, 60);
    insertAndSetFirstWall(&head, 22,  200 + 15, 400 + 10, 10, 60);
    insertAndSetFirstWall(&head, 23,  300 + 15, 400 + 10, 10, 60);
    insertAndSetFirstWall(&head, 24,  100 + 15, 300 + 10, 210, 10);
    insertAndSetFirstWall(&head, 25,  150 + 15, 250 + 10, 10, 60);
    insertAndSetFirstWall(&head, 26,  250 + 15, 250 + 10, 10, 60);
    insertAndSetFirstWall(&head, 27,  300 + 15, 300 + 10, 10, 60);
    insertAndSetFirstWall(&head, 28,  150 + 15, 50 + 10, 110, 10);
    insertAndSetFirstWall(&head, 29,  150 + 15, 50 + 10, 10, 110);
    insertAndSetFirstWall(&head, 30,  200 + 15, 100 + 10, 160, 10);
    insertAndSetFirstWall(&head, 31,  300 + 15, 50 + 10, 10, 60);
    insertAndSetFirstWall(&head, 32,  350 + 15, 0 + 10, 10, 110);
    insertAndSetFirstWall(&head, 33,  400 + 15, 50 + 10, 10, 60);
    insertAndSetFirstWall(&head, 34,  400 + 15, 50 + 10, 60, 10);
    insertAndSetFirstWall(&head, 35,  450 + 15, 0 + 10, 10, 60);
    insertAndSetFirstWall(&head, 36,  150 + 15, 200 + 10, 210, 10);
    insertAndSetFirstWall(&head, 37,  200 + 15, 200 + 10, 10, 60);
    insertAndSetFirstWall(&head, 38,  300 + 15, 200 + 10, 10, 60);
    insertAndSetFirstWall(&head, 39,  300 + 15, 250 + 10, 60, 10);
    insertAndSetFirstWall(&head, 40,  350 + 15, 250 + 10, 10, 60);
    insertAndSetFirstWall(&head, 41,  350 + 15, 300 + 10, 60, 10);
    insertAndSetFirstWall(&head, 42,  400 + 15, 200 + 10, 10, 110);
    insertAndSetFirstWall(&head, 43,  400 + 15, 200 + 10, 60, 10);
    insertAndSetFirstWall(&head, 44,  450 + 15, 200 + 10, 10, 60);
    insertAndSetFirstWall(&head, 45,  450 + 15, 250 + 10, 60, 10);
    insertAndSetFirstWall(&head, 46,  350 + 15, 150 + 10, 10, 60);
    insertAndSetFirstWall(&head, 46,  350 + 15, 150 + 10, 210, 10);
    insertAndSetFirstWall(&head, 47,  450 + 15, 100 + 10, 10, 60);
    insertAndSetFirstWall(&head, 48,  500 + 15, 50 + 10, 60, 10);
    insertAndSetFirstWall(&head, 49,  500 + 15, 50 + 10, 10, 160);
    insertAndSetFirstWall(&head, 50,  500 + 15, 200 + 10, 110, 10);
    insertAndSetFirstWall(&head, 51,  550 + 15, 200 + 10, 10, 210);
    insertAndSetFirstWall(&head, 52,  400 + 15, 350 + 10, 60, 10);
    insertAndSetFirstWall(&head, 53,  450 + 15, 300 + 10, 10, 60);
    insertAndSetFirstWall(&head, 54,  450 + 15, 300 + 10, 110, 10);
    insertAndSetFirstWall(&head, 55,  550 + 15, 100 + 10, 60, 10);
    insertAndSetFirstWall(&head, 56,  600 + 15, 0 + 10, 10, 210);
    insertAndSetFirstWall(&head, 57,  600 + 15, 250 + 10, 10, 210);
    insertAndSetFirstWall(&head, 58,  0 + 15, 450 + 10, 610, 10);
    */
    /*
    // Complex Maze 2
    insertAndSetFirstWall(&head, 1, 0, 0, 5, OVERALL_WINDOW_HEIGHT);
        insertAndSetFirstWall(&head, 2, 0, 0, OVERALL_WINDOW_WIDTH, 5);
        insertAndSetFirstWall(&head, 3, 60, OVERALL_WINDOW_HEIGHT - 5, OVERALL_WINDOW_WIDTH - 60, 5);
        insertAndSetFirstWall(&head, 4, OVERALL_WINDOW_WIDTH - 5, 0, 5, OVERALL_WINDOW_HEIGHT - 60);
        insertAndSetFirstWall(&head, 5, 60, 64, 5, OVERALL_WINDOW_HEIGHT - 62);
        insertAndSetFirstWall(&head, 6, 64, 60, OVERALL_WINDOW_WIDTH - 128, 5);
        int l = 0;
        int b = 0;
        while (l < 60) {
            if (l <= 12) {
                insertAndSetFirstWall(&head, 7, OVERALL_WINDOW_WIDTH - 64 - l * 3, 60 + l * 5, 5, 5);
                b = OVERALL_WINDOW_WIDTH - 64 - l * 3;
            }
            if ((l >= 13 && l <= 25) || (l >= 39 && l <= 51)) {
                insertAndSetFirstWall(&head, 7, b + (l - 12) * 3, 60 + l * 5, 5, 5);
            }
            if (l >= 26 && l <= 38) {
                insertAndSetFirstWall(&head, 7, OVERALL_WINDOW_WIDTH - 64 - (l - 26) * 3, 60 + l * 5, 5, 5);
                b = OVERALL_WINDOW_WIDTH - 64 - l * 3;
            }
            if (l >= 52) {
                insertAndSetFirstWall(&head, 7, OVERALL_WINDOW_WIDTH - 64 - (l - 52) * 3, 60 + l * 5, 5, 5);
                b = OVERALL_WINDOW_WIDTH - 64 - l * 3;
            }
            l++;
        }
        insertAndSetFirstWall(&head, 8, OVERALL_WINDOW_WIDTH - 128, OVERALL_WINDOW_HEIGHT/2 + 120, 45, 5);
        insertAndSetFirstWall(&head, 9, 124, OVERALL_WINDOW_HEIGHT - 60, OVERALL_WINDOW_WIDTH - 128, 5);
        insertAndSetFirstWall(&head, 10, OVERALL_WINDOW_WIDTH - 128, OVERALL_WINDOW_HEIGHT/2 - 120, 5, OVERALL_WINDOW_HEIGHT - 240);
        insertAndSetFirstWall(&head, 11, 128, 120, OVERALL_WINDOW_WIDTH/2 + 64, 5);
        insertAndSetFirstWall(&head, 12, 128, 180, OVERALL_WINDOW_WIDTH/2, 5);
        insertAndSetFirstWall(&head, 13, 62, OVERALL_WINDOW_HEIGHT/2, 192, 5);
        insertAndSetFirstWall(&head, 14, OVERALL_WINDOW_WIDTH/2, OVERALL_WINDOW_HEIGHT/2, 64, 5);
        insertAndSetFirstWall(&head, 15, OVERALL_WINDOW_WIDTH/2, OVERALL_WINDOW_HEIGHT/2 + 60, 69, 5);
        insertAndSetFirstWall(&head, 16, OVERALL_WINDOW_WIDTH/2, OVERALL_WINDOW_HEIGHT/2, 5, 60);
        insertAndSetFirstWall(&head, 17, OVERALL_WINDOW_WIDTH/2 + 64, OVERALL_WINDOW_HEIGHT/2, 5, 60);
        insertAndSetFirstWall(&head, 18, OVERALL_WINDOW_WIDTH/2 + 128, OVERALL_WINDOW_HEIGHT/2 - 60, 5, OVERALL_WINDOW_HEIGHT/2 - 60);
        insertAndSetFirstWall(&head, 19, OVERALL_WINDOW_WIDTH/2 - 64, OVERALL_WINDOW_HEIGHT/2 + 120, OVERALL_WINDOW_WIDTH/2 - 128, 5);
        insertAndSetFirstWall(&head, 20, OVERALL_WINDOW_WIDTH/2 - 64, OVERALL_WINDOW_HEIGHT/2 + 60, 5, 60);
        insertAndSetFirstWall(&head, 21, 128, OVERALL_WINDOW_HEIGHT/2 + 60, 128, 5);
        insertAndSetFirstWall(&head, 22, 128, OVERALL_WINDOW_HEIGHT/2 + 60, 5, 60);
        insertAndSetFirstWall(&head, 23, 128, OVERALL_WINDOW_HEIGHT/2 + 120, 64, 5);
        insertAndSetFirstWall(&head, 24, OVERALL_WINDOW_WIDTH/2 - 128, OVERALL_WINDOW_HEIGHT/2 + 120, 5, 60);
        */
    
    
    /*
    // Circular maze
    int j=0; // Key value
    // Adding a circle with radius 50
    for (int i=-50; i<51; i+=1){
        // Leaving a gap
        if (-20>i || i>20) {
            insertAndSetFirstWall(&head, j,  OVERALL_WINDOW_WIDTH/2+i, OVERALL_WINDOW_HEIGHT/2+sqrt(2500-i*i), 5, 5);
            j+=1;
        }
        insertAndSetFirstWall(&head, j,  OVERALL_WINDOW_WIDTH/2+i, OVERALL_WINDOW_HEIGHT/2-sqrt(2500-i*i), 5, 5);
        j+=1;
    }
    // Adding a circle with radius 125
    for (int i=-125; i<126; i+=1){
        // Leaving a few gaps
        if ((70 > i || i > 100) && (-100 > i || i > -75)) {
            insertAndSetFirstWall(&head, j,  OVERALL_WINDOW_WIDTH/2+i, OVERALL_WINDOW_HEIGHT/2-sqrt(15625-i*i), 5, 5);
            j+=1;
        }
        // Leaving more gaps
        if ((-100 > i || i > -75) && (110 > i || i > 121)) {
            insertAndSetFirstWall(&head, j,  OVERALL_WINDOW_WIDTH/2+i, OVERALL_WINDOW_HEIGHT/2+sqrt(15625-i*i), 5, 5);
            j+=1;
        }
        // Creating a wall between the circles
        if (18<i && i<70) {
          insertAndSetFirstWall(&head, j,  OVERALL_WINDOW_WIDTH/2+19+i, OVERALL_WINDOW_HEIGHT/2+19+i, 5, 5);
          j+=1;
        }
        // Creating a wall between the circles
        if (20<i && i<85) {
          insertAndSetFirstWall(&head, j,  OVERALL_WINDOW_WIDTH/2+20+i, OVERALL_WINDOW_HEIGHT/2-15-i/1.5, 5, 5);
          j+=1;
        }
    }
    // Adding a circle with radius 200
    for (int i=-200; i<201; i+=1){
        // Leaving a gap
        if (198 > i) {
            insertAndSetFirstWall(&head, j,  OVERALL_WINDOW_WIDTH/2+i, OVERALL_WINDOW_HEIGHT/2+sqrt(40000-i*i), 5, 5);
            insertAndSetFirstWall(&head, j+1,  OVERALL_WINDOW_WIDTH/2+i, OVERALL_WINDOW_HEIGHT/2-sqrt(40000-i*i), 5, 5);
            j+=2;
        }
        // Creating two walls between the circles
        if (125<i && i<195) {
          insertAndSetFirstWall(&head, j,  OVERALL_WINDOW_WIDTH/2+i, (OVERALL_WINDOW_HEIGHT/2-2+(i/5)), 5, 5);
          j+=1;
        }
    }
    // Cleaining up the circles and adding the end corridoor
    insertAndSetFirstWall(&head, j,  OVERALL_WINDOW_WIDTH/2-200, OVERALL_WINDOW_HEIGHT/2-12.5, 5, 30);
    insertAndSetFirstWall(&head, j+1,  OVERALL_WINDOW_WIDTH/2-125, OVERALL_WINDOW_HEIGHT/2-10, 5, 25);
    insertAndSetFirstWall(&head, j+2,  OVERALL_WINDOW_WIDTH/2+125, OVERALL_WINDOW_HEIGHT/2-10, 5, 25);
    insertAndSetFirstWall(&head, j+3,  OVERALL_WINDOW_WIDTH/2+200, OVERALL_WINDOW_HEIGHT/2+35, 150, 5);
    insertAndSetFirstWall(&head, j+4,  OVERALL_WINDOW_WIDTH/2+200, OVERALL_WINDOW_HEIGHT/2-35, 150, 5);
    // Creating more walls between the circles
    insertAndSetFirstWall(&head, j+5,  OVERALL_WINDOW_WIDTH/2, OVERALL_WINDOW_HEIGHT/2-200, 5, 75);
    insertAndSetFirstWall(&head, j+6,  OVERALL_WINDOW_WIDTH/2-200, OVERALL_WINDOW_HEIGHT/2, 75, 5);
    */
    
    setup_robot(&robot);
    updateAllWalls(head, renderer);

    SDL_Event event;
    while(!done){
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
        SDL_RenderClear(renderer);

        //Move robot based on user input commands/auto commands
        if (!robot.crashed)
         {
            if (robot.auto_mode == 1)
                robotAutoMotorMove(&robot, front_left_sensor, front_right_sensor, left_sensor, right_sensor, leftest_sensor);
            robotMotorMove(&robot);
         }

        //Check if robot reaches endpoint. and check sensor values
        //Complex
        if (checkRobotReachedEnd(&robot, 640, 20, 10, 60)){ //Maze 5
            gettimeofday(&end_time, 0);
            msec = ((end_time.tv_sec - start_time.tv_sec)*1000)+(end_time.tv_usec - start_time.tv_usec)/1000;
            robotSuccess(&robot, msec);
        }
        
        // Circulr end point
        //Check if robot reaches endpoint. and check sensor values
 
        else if(checkRobotHitWalls(&robot, head))
            robotCrash(&robot);
        //Otherwise compute sensor information
        else {
            front_left_sensor = checkRobotSensorFrontLeftAllWalls(&robot, head);
            if (front_left_sensor>0)
                printf("Getting close on the front left. Score = %d\n", front_left_sensor);

            front_right_sensor = checkRobotSensorFrontRightAllWalls(&robot, head);
            if (front_right_sensor>0)
                printf("Getting close on the front right. Score = %d\n", front_right_sensor);
            
            right_sensor = checkRobotSensorRightAllWalls(&robot, head);
            if (right_sensor>0)
                printf("Getting close on the right. Score = %d\n", right_sensor);
            
            left_sensor = checkRobotSensorLeftAllWalls(&robot, head);
            if (left_sensor>0)
                printf("Getting close on the left. Score = %d\n", left_sensor);
            
            leftest_sensor = checkRobotSensorLeftestAllWalls(&robot, head);
            if (leftest_sensor>0)
                printf("Getting close on the leftest. Score = %d\n", leftest_sensor);
        }
        robotUpdate(renderer, &robot);
        updateAllWalls(head, renderer);
        
        // Manual Control
        // Check for user input
        SDL_RenderPresent(renderer);
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                done = 1;
            }
            const Uint8 *state = SDL_GetKeyboardState(NULL);
            if(state[SDL_SCANCODE_UP] && robot.direction != DOWN){
                robot.direction = UP;
            }
            if(state[SDL_SCANCODE_DOWN] && robot.direction != UP){
                robot.direction = DOWN;
            }
            if(state[SDL_SCANCODE_LEFT] && robot.direction != RIGHT){
                robot.direction = LEFT;
            }
            if(state[SDL_SCANCODE_RIGHT] && robot.direction != LEFT){
                robot.direction = RIGHT;
            }
            if(state[SDL_SCANCODE_SPACE]){
                setup_robot(&robot);
            }
            if(state[SDL_SCANCODE_RETURN]){
                robot.auto_mode = 1;
                gettimeofday(&start_time, 0);
            }
        }

        SDL_Delay(120);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    printf("DEAD\n");
}
