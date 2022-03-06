/*
    C'est un programme d'un jeu : le bouncing ball qui va se joue a deux. Chaque
    jouur va controler son camps et empecher que l'advaire marque tout en essayant de marque

    Auteur: Omar DIASSE

    Debut: 12/06/2021
    Fin: 

    compilation : gcc src/*.c -o bin/pong -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

    Pour la prochaine fois: 
        Trouver une solution pour la player2 qui move bco trop vite par rapport au player1
*/

#include "game.h"

int main(int argc, char **argv)
{  
    // Declaration
    SDL_Window *win = NULL;
    SDL_Renderer *render = NULL;
    SDL_Rect player1;
    SDL_Rect player2;
    SDL_Rect ball;
    SDL_Rect topHorizontalBar;
    SDL_Rect botHorizontalBar;
    SDL_Rect middleLine;
    SDL_Event e;
    SDL_bool launch = SDL_TRUE;
    //------------

    // Initiliation
    init();
    //------------

    // Create window
    win = SDL_CreateWindow("Ma fênetre" ,SDL_WINDOWPOS_UNDEFINED ,SDL_WINDOWPOS_UNDEFINED ,800 ,600 ,0);
    if(win == NULL)
    {
        printf("Erreur creation fenetre : %s\n" ,SDL_GetError());
        quit(NULL, NULL);
        exit(EXIT_FAILURE);
    }
    //--------------

    // Create a renderer
    render = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if(render == NULL)
    {
        printf("Erreur creation fenetre : %s\n" ,SDL_GetError());
        quit(win, NULL);
        exit(EXIT_FAILURE);
    }
    //------------------

    // Middle line
    middleLine.x = 399;
    middleLine.y = 20;
    middleLine.w = 2;
    middleLine.h = 560;
    //-----------

    clear(render);

    // Velocity
    int y_vel1 = 10, y_vel2 = 10, ball_vel_x = 5, ball_vel_y = -5; // The value of ball_vels nust mulitiple of 5 or 2
    //---------

    // The horintal bars
    topHorizontalBar.x = 0;
    topHorizontalBar.y = 0;
    topHorizontalBar.w = 800;
    topHorizontalBar.h = 20;

    botHorizontalBar.x = 0;
    botHorizontalBar.y = 580;
    botHorizontalBar.w = 800;
    botHorizontalBar.h = 20;
    //-----------------

    // Draw player 1
    player1.x = 20;
    player1.y = 20;
    player1.w = 20;
    player1.h = 100;
    //--------------

    // Draw player 2
    player2.x = 760;
    player2.y = 20;
    player2.w = 20;
    player2.h = 100;
    //--------------

    // The ball
    ball.x = (800) / 2;
    ball.y = (600) / 2;
    ball.w = 20;
    ball.h = 20;
    //---------

    // Score
    int scorePlayer1 = 0, scorePlayer2 = 0;
    printf("Score: %d - %d\n", scorePlayer1, scorePlayer2);
    //-----

    // Game loop
    while(launch)
    {
        SDL_PollEvent(&e);

        // Ball mouvenent
    
        if((ball.y >= player1.y - 20) && (ball.y <= player1.y + player1.h + 20) && (ball.x == 40))
        {
            if(ball.x <= player1.x + 20)
            {
                ball.x = player1.x + 20;
                ball_vel_x = -ball_vel_x;
            }
        }
    
        if((ball.y >= player2.y - 20) && (ball.y <= player2.y + player2.h + 20) && (ball.x == 740))
        {
            if(ball.x >= player2.x - 20)
            {
                ball.x = player2.x - 20;
                ball_vel_x = -ball_vel_x;
            }
        }
        
        
        if(ball.y >= 560)
        {
            ball.y = 560;
            ball_vel_y = -ball_vel_y;
        }
        if(ball.y <= 20)
        {
            ball.y == 20;
            ball_vel_y = -ball_vel_y;
        }
            // Draw a ball instead of rect

        //----------------

        // Goal test
        if(ball.x + ball.w  < 0)
        {
            scorePlayer2++;
            printf("Score: %d - %d\n", scorePlayer1, scorePlayer2);
            SDL_Delay(2000);
            ball.x = 800 / 2;
            ball.y = 600 / 2;
        }
        if(ball.x > 800)
        {
            scorePlayer1++;
            printf("Score: %d - %d\n", scorePlayer1, scorePlayer2);
            SDL_Delay(2000);
            ball.x = 800 / 2;
            ball.y = 600 / 2;
        }
        //----------

        ball.x += ball_vel_x;
        ball.y += ball_vel_y;

        switch(e.type)
        {
            case SDL_QUIT:
                launch = SDL_FALSE;
                break;

            case SDL_KEYDOWN:
                switch (e.key.keysym.sym)
                {
                    case SDLK_q:
                        y_vel1 -= 30;
                        if(player1.y <= 20)
                        {
                            y_vel1 = 0;
                        }
                        break;

                    case SDLK_a:
                        y_vel1 += 30;
                        if(player1.y + 20 >= 500)
                        {
                            y_vel1 = 0;
                        }
                        break;

                    case SDLK_o:
                        y_vel2 -= 30;
                        if(player2.y <= 20)
                        {
                            y_vel2 = 0;
                        }
                        break;

                    case SDLK_l:
                        y_vel2 += 30;
                        if(player2.y + 20 >= 500)
                        {
                            y_vel2 = 0;
                        }
                        break;
                    
                    default:
                        break;
                }
        }
        player1.y += y_vel1;
        player2.y += y_vel2;
        y_vel1 = 0;
        y_vel2 = 0;

        clear(render);

        if(SDL_SetRenderDrawColor(render ,0 ,180 ,180 ,0) != 0)
        {
            printf("Erreur creation rendu : %s\n" ,SDL_GetError());
            exit(EXIT_FAILURE);
        }
        SDL_RenderFillRect(render, &player1);
        
        if(SDL_SetRenderDrawColor(render ,180 ,40 ,40 ,0) != 0)
        {
            printf("Erreur creation rendu : %s\n" ,SDL_GetError());
            exit(EXIT_FAILURE);
        }
        SDL_RenderFillRect(render, &player2);

        if(SDL_SetRenderDrawColor(render ,220 ,220 ,220 ,0) != 0)
        {
            printf("Erreur creation rendu : %s\n" ,SDL_GetError());
            exit(EXIT_FAILURE);
        }
        SDL_RenderFillRect(render, &topHorizontalBar);
        SDL_RenderFillRect(render, &botHorizontalBar);
        SDL_RenderFillRect(render, &ball);
        SDL_RenderFillRect(render, &middleLine);

        SDL_RenderPresent(render);

        // Mimike framerates
        SDL_Delay(1000/60);
    }
    //----------

    // Free ressources
    quit(win ,render);
    //----------------

    return EXIT_SUCCESS;
}