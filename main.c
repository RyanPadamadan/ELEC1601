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
    
    setup_robot(&robot);
    updateAllWalls(head, renderer);

    SDL_Event event;
    while(!done){
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
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
        if (checkRobotReachedEnd(&robot, 120, 480, 100, 10)){ //Maze 6
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
