#include "raylib.h"

//------------------------------------------------------------------------------------------
// Types and Structures Definition
//------------------------------------------------------------------------------------------
typedef enum GameScreen { LOGO = 0, TITLE, GAMEPLAY, ENDING } GameScreen;

typedef struct Card {
    Texture texture;
    Rectangle source;
    Rectangle outline;
    Vector2 origin;
} Card;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

void drawPlayerHand(Card *, int);

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic screen manager");
    // ToggleFullscreen();

    GameScreen currentScreen = LOGO;

    // TODO: Initialize all required variables and load all required data here!

    int framesCounter = 0;          // Useful to count frames

    int numberOfCards = 8;
    float heightOfCards = 214.0f;
    float widthOfCards = 131.0f;

    Card cardsOfPlayer[numberOfCards];

    // Létrehozzuk a játékos kezeiben lévő kártyákat
    for(int i = 0; i < numberOfCards; i++){
        // Betöltsük a kártyák textúráit
        cardsOfPlayer[i].texture = LoadTexture(TextFormat("images/image_card%d.png", i));

        // Meghatározzuk a textúrán belüli kirajzolandó terület pozícióját és méretét
        cardsOfPlayer[i].source = (Rectangle){
            .height = (float)cardsOfPlayer[i].texture.height,
            .width = (float)cardsOfPlayer[i].texture.width,
            .x = 0.0f,
            .y = 0.0f
        };

        // Ezzel a változóval határozzuk meg, hogy mennyire legyenek közel egymáshoz a kártyák
        float shiftOfCardsInDeck = 0.8f;
        // Meghatározzuk a kirajzolandó kártya méretét és pozícióját (ebbe a négyszögbe lesz beleigazítva az előzőleg meghatározott textúra)
        cardsOfPlayer[i].outline = (Rectangle){
            .height = heightOfCards,
            .width = widthOfCards,
            .x = (float) ((screenWidth - numberOfCards * (widthOfCards * shiftOfCardsInDeck))/2 + i * (widthOfCards * shiftOfCardsInDeck)),
            .y = (float)(screenHeight - heightOfCards)
        };

        // Nem tudjuk ez mire van
        cardsOfPlayer[i].origin = (Vector2){
            .x = 0.0f,
            .y = 0.0f
        };
    }

    // Ezzel a változóval csúsztassuk magasabbra/alacsonyabbra a kártyákat, mintha a játékos a kezeiben tartaná
    int shiftUp = 20.0f;
    int counter = 0;
    for (int i = 0; i < numberOfCards; i++) {
        if (i < numberOfCards / 2) {
            // A kártyák feléig felfelé csúsztassuk a kártyák pozícióját
            counter++;
        } else if(i > numberOfCards / 2){
            // A kártyák felétől lefelé csúsztassuk a kártyák pozícióját
            counter--;
        }
        cardsOfPlayer[i].outline.y -= counter * shiftUp;
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

// A kártyákat úgy rajzolja ki, mintha a játékos a kezeiben tartaná
void drawPlayerHand(Card *cardsOfPlayer, int numberOfCards){
    float rotation = 0.0f;
    for(int i = 0; i < numberOfCards; i++){
        DrawTexturePro(cardsOfPlayer[i].texture, cardsOfPlayer[i].source, cardsOfPlayer[i].outline, cardsOfPlayer[i].origin, rotation, WHITE);
    }
}
