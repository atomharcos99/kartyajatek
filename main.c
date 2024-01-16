#include "raylib.h"

//------------------------------------------------------------------------------------------
// Types and Structures Definition
//------------------------------------------------------------------------------------------
typedef enum GameScreen { LOGO = 0, TITLE, GAMEPLAY, ENDING } GameScreen;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic screen manager");
    ToggleFullscreen();

    GameScreen currentScreen = LOGO;

    // TODO: Initialize all required variables and load all required data here!

    int framesCounter = 0;          // Useful to count frames

    int numberOfCards = 6;
    float heightOfCards = 350.0f;
    float widthOfCards = 250.0f;

    // TODO: MAKE A CARD STRUCT THAT HAS cardTextures, sourceRecsCard, destionationRecsCard (maybe even originCard?) AS MEMBERS

    // Loading the textures of the cards
    Texture cardTextures[numberOfCards];
    for(int i = 0; i < numberOfCards; i++){
        cardTextures[i] = LoadTexture(TextFormat("images/image_card%d.png", i));
    }

    // The size and position of the texture in the file. Since all the card textures are the same size, we don't need an array of these.
    Rectangle sourceRecCard = {
        .height = (float)cardTextures[0].height,
        .width = (float)cardTextures[0].width,
        .x = 0.0f,
        .y = 0.0f
    };

    // The outlines of the size and position of the cards (the texture will be scaled according of this rectangle's size)
    Rectangle destinationRecsCard[numberOfCards];
    for(int i = 0; i < numberOfCards; i++){
        destinationRecsCard[i] = (Rectangle){
            .height = heightOfCards,
            .width = widthOfCards,
            .x = 0.0f + i * widthOfCards,
            .y = 0.0f
        };
    }

    // TODO: Found out what is this for
    Vector2 originCard = {
        .x = 0.0f,
        .y = 0.0f
    };

    SetTargetFPS(60);               // Set desired framerate (frames-per-second)
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        switch(currentScreen)
        {
            case LOGO:
            {
                // TODO: Update LOGO screen variables here!

                framesCounter++;    // Count frames

                // Wait for 2 seconds (120 frames) before jumping to TITLE screen
                if (framesCounter > 120)
                {
                    currentScreen = TITLE;
                }
            } break;
            case TITLE:
            {
                // TODO: Update TITLE screen variables here!

                // Press enter to change to GAMEPLAY screen
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                    currentScreen = GAMEPLAY;
                }
            } break;
            case GAMEPLAY:
            {
                // TODO: Update GAMEPLAY screen variables here!

                // Press enter to change to ENDING screen
                // if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                // {
                //     currentScreen = ENDING;
                // }
            } break;
            case ENDING:
            {
                // TODO: Update ENDING screen variables here!

                // Press enter to return to TITLE screen
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                    currentScreen = TITLE;
                }
            } break;
            default: break;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            switch(currentScreen)
            {
                case LOGO:
                {
                    //  TODO: Draw LOGO screen here!
                    DrawText("LOGO SCREEN", 20, 20, 40, LIGHTGRAY);
                    DrawText("WAIT for 2 SECONDS...", 290, 220, 20, GRAY);

                } break;
                case TITLE:
                {
                    // TODO: Draw TITLE screen here!
                    DrawRectangle(0, 0, screenWidth, screenHeight, GREEN);
                    DrawText("TITLE SCREEN", 20, 20, 40, DARKGREEN);
                    DrawText("PRESS ENTER or TAP to JUMP to GAMEPLAY SCREEN", 120, 220, 20, DARKGREEN);

                } break;
                case GAMEPLAY:
                {
                    for(int i = 0; i < numberOfCards; i++) {
                        DrawTexturePro(cardTextures[i], sourceRecCard, destinationRecsCard[i], originCard, 0.0f, WHITE);
                    }
                } break;
                case ENDING:
                {
                    // TODO: Draw ENDING screen here!
                    DrawRectangle(0, 0, screenWidth, screenHeight, BLUE);
                    DrawText("ENDING SCREEN", 20, 20, 40, DARKBLUE);
                    DrawText("PRESS ENTER or TAP to RETURN to TITLE SCREEN", 120, 220, 20, DARKBLUE);

                } break;
                default: break;
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    // TODO: Unload all loaded data (textures, fonts, audio) here!

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}