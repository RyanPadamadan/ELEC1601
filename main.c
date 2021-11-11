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

    insertAndSetFirstWall(&head, 1, 0, 0, 10, OVERALL_WINDOW_HEIGHT);
        insertAndSetFirstWall(&head, 2, OVERALL_WINDOW_WIDTH - 10, 0, 10, OVERALL_WINDOW_HEIGHT);
        insertAndSetFirstWall(&head, 3, 0, 0, OVERALL_WINDOW_WIDTH, 10);
        insertAndSetFirstWall(&head, 4, 0, OVERALL_WINDOW_HEIGHT - 10,OVERALL_WINDOW_WIDTH/2 + 60, 10);
        insertAndSetFirstWall(&head, 5, OVERALL_WINDOW_WIDTH/2 + 105, OVERALL_WINDOW_HEIGHT - 10,OVERALL_WINDOW_WIDTH/2 + 60, 10);
        //square l,r,d,t
        insertAndSetFirstWall(&head, 5, 55, 0.7*OVERALL_WINDOW_HEIGHT - 10, 10, 90);
        insertAndSetFirstWall(&head, 6, 135, 0.7*OVERALL_WINDOW_HEIGHT - 10, 10, 90);
        insertAndSetFirstWall(&head, 7, 55, OVERALL_WINDOW_HEIGHT - 65, 90, 10);
        insertAndSetFirstWall(&head, 8, 55, OVERALL_WINDOW_HEIGHT - 155, 90, 10);
        //horizontal above base
        insertAndSetFirstWall(&head, 9, 195, OVERALL_WINDOW_HEIGHT - 65, 180, 10);
        //vertical parallel near bottom mid
        insertAndSetFirstWall(&head, 10,  OVERALL_WINDOW_WIDTH/2 - 40, OVERALL_WINDOW_HEIGHT/2 - 80, 10, OVERALL_WINDOW_HEIGHT/2 + 20);
        insertAndSetFirstWall(&head, 11, OVERALL_WINDOW_WIDTH/2 + 50, OVERALL_WINDOW_HEIGHT - 65, 10, 55);
        insertAndSetFirstWall(&head, 12,  195, OVERALL_WINDOW_HEIGHT/2 + 55, 10, OVERALL_WINDOW_HEIGHT/2 - 120);
        //3 horizontal parallel (left)
        insertAndSetFirstWall(&head, 13,  85, OVERALL_WINDOW_HEIGHT/4 - 40, OVERALL_WINDOW_WIDTH/2 - 200, 10);
        insertAndSetFirstWall(&head, 13,  37, OVERALL_WINDOW_HEIGHT/2 , OVERALL_WINDOW_WIDTH/2 - 70, 10);
        insertAndSetFirstWall(&head, 13,  37, OVERALL_WINDOW_HEIGHT/2 - 80, OVERALL_WINDOW_WIDTH/2 - 50, 10);
        
        insertAndSetFirstWall(&head, 13,  150, 0,10, OVERALL_WINDOW_HEIGHT/4 - 40);
        insertAndSetFirstWall(&head, 10,  OVERALL_WINDOW_WIDTH/2 - 60, 40, 10, OVERALL_WINDOW_HEIGHT/4 + 10);
        insertAndSetFirstWall(&head, 10,  OVERALL_WINDOW_WIDTH/2 - 20, 40, 10, OVERALL_WINDOW_HEIGHT/4 + 10);
        insertAndSetFirstWall(&head, 10,  OVERALL_WINDOW_WIDTH/2 - 20 + 42, 40, 10, OVERALL_WINDOW_HEIGHT/4 + 10);
        
        insertAndSetFirstWall(&head, 13,  OVERALL_WINDOW_WIDTH/2 + 22, OVERALL_WINDOW_HEIGHT/2 - 80, OVERALL_WINDOW_WIDTH/2 - 30, 10);
        insertAndSetFirstWall(&head, 13,  OVERALL_WINDOW_WIDTH/2 - 40, OVERALL_WINDOW_HEIGHT/2 - 40, OVERALL_WINDOW_WIDTH/2 - 5, 10);
        insertAndSetFirstWall(&head, 13,  OVERALL_WINDOW_WIDTH/2 + 5, OVERALL_WINDOW_HEIGHT/2, OVERALL_WINDOW_WIDTH/2 - 10, 10);
        insertAndSetFirstWall(&head, 13,  OVERALL_WINDOW_WIDTH/2 - 40, OVERALL_WINDOW_HEIGHT/2 + 40, OVERALL_WINDOW_WIDTH/2 - 5, 10);
        insertAndSetFirstWall(&head, 13,  OVERALL_WINDOW_WIDTH/2 + 5, OVERALL_WINDOW_HEIGHT/2 + 80, OVERALL_WINDOW_WIDTH/2 - 10, 10);
        insertAndSetFirstWall(&head, 13,  OVERALL_WINDOW_WIDTH/2 - 40, OVERALL_WINDOW_HEIGHT/2 + 120, OVERALL_WINDOW_WIDTH/2 - 5, 10);
       
        insertAndSetFirstWall(&head, 11, OVERALL_WINDOW_WIDTH/2 + 105, OVERALL_WINDOW_HEIGHT - 78, 10, 105);
        
        
        setup_robot(&robot);
        updateAllWalls(head, renderer);
    
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
        if (checkRobotReachedEnd(&robot, OVERALL_WINDOW_WIDTH/2 + 82 , 0, 10, 100)){
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
