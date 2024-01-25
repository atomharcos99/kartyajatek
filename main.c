#include "raylib.h"

//------------------------------------------------------------------------------------------
// Types and Structures Definition
//------------------------------------------------------------------------------------------
typedef enum GameScreen { LOGO = 0, TITLE, GAMEPLAY, ENDING } GameScreen;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

typedef struct Card {
    Texture texture;
    Rectangle source;
    Rectangle outline;
    Vector2 origin;
} Card;

void drawPlayerHand(Card *, int);

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

    int numberOfCards = 8;
    float heightOfCards = 214.0f;
    float widthOfCards = 131.0f;

    Card cardsOfPlayer[numberOfCards];

    // Initializing the cards
    for(int i = 0; i < numberOfCards; i++){
        // Loading the textures of the cards
        cardsOfPlayer[i].texture = LoadTexture(TextFormat("images/image_card%d.png", i));

        // The size and position of the texture in the file
        cardsOfPlayer[i].source = (Rectangle){
            .height = (float)cardsOfPlayer[i].texture.height,
            .width = (float)cardsOfPlayer[i].texture.width,
            .x = 0.0f,
            .y = 0.0f
        };

        // This makes the cards to be drawned out with overlap
        float shiftOfCardsInDeck = 0.8f;
        // The outlines of the size and position of the cards (the texture will be scaled according of this rectangle's size)
        cardsOfPlayer[i].outline = (Rectangle){
            .height = heightOfCards,
            .width = widthOfCards,
            .x = (float) ((screenWidth - numberOfCards * (widthOfCards * shiftOfCardsInDeck))/2 + i * (widthOfCards * shiftOfCardsInDeck)),
            .y = (float)(screenHeight - heightOfCards)
        };

        // Shift the height of cards to match the pattern of holding cards in hand
        int shiftUp = 5.0f;
        int counter = 0;
        for(int i = 0; i < numberOfCards; i++){
            if(i < numberOfCards/2){
                cardsOfPlayer[i].outline.y = cardsOfPlayer[i].outline.y - counter * shiftUp;
                counter++;
            } else if(i > numberOfCards/2) {
                cardsOfPlayer[i].outline.y = cardsOfPlayer[i].outline.y - counter * shiftUp;
                counter--;
            } else {
                cardsOfPlayer[i].outline.y = cardsOfPlayer[i].outline.y - counter * shiftUp;
            }
        }

        // TODO: Found out what is this for
        cardsOfPlayer[i].origin = (Vector2){
            .x = 0.0f,
            .y = 0.0f
        };
    }

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
                    // TODO: Draw the hand of the player with this function
                    drawPlayerHand(cardsOfPlayer, numberOfCards);
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

    for (int i = 0; i < numberOfCards; i++)
    {
        UnloadTexture(cardsOfPlayer[i].texture);
    }
    

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

void drawPlayerHand(Card *cardsOfPlayer, int numberOfCards){
    float rotation = 0.0f;
    for(int i = 0; i < numberOfCards; i++){
        //cardsOfPlayer[i].outline.
        DrawTexturePro(cardsOfPlayer[i].texture, cardsOfPlayer[i].source, cardsOfPlayer[i].outline, cardsOfPlayer[i].origin, rotation, WHITE);
    }
}
