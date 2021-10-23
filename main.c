#include "stdio.h"
#include "stdlib.h"
#include "SDL.h"
#include "SDL2_gfxPrimitives.h"
#include <sys/time.h>

#include "formulas.h"
#include "wall.h"
#include "robot.h"

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
    int front_left_sensor = 0, front_right_sensor= 0, right_sensor = 0, left_sensor = 0;
    struct timeval start_time, end_time;
    gettimeofday(&start_time, 0);
    unsigned long msec;

    // SETUP MAZE
    // You can create your own maze here. line of code is adding a wall.
    // You describe position of top left corner of wall (x, y), then width and height going down/to right
    // Relative positions are used (OVERALL_WINDOW_WIDTH and OVERALL_WINDOW_HEIGHT)
    // But you can use absolute positions. 10 is used as the width, but you can change this.
    
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

    /*
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
                robotAutoMotorMove(&robot, front_left_sensor, front_right_sensor, left_sensor, right_sensor);
            robotMotorMove(&robot);
         }

        //Check if robot reaches endpoint. and check sensor values
        if (checkRobotReachedEnd(&robot, OVERALL_WINDOW_WIDTH, OVERALL_WINDOW_HEIGHT/2+100, 10, 100)){
            gettimeofday(&end_time, 0);
            msec = ((end_time.tv_sec - start_time.tv_sec)*1000)+(end_time.tv_usec - start_time.tv_usec)/1000;
            robotSuccess(&robot, msec);
        }
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
