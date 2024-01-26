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

const int screenWidth = 1920;
const int screenHeight = 1080;
const float heightOfCards = 214.0f;
const float widthOfCards = 131.0f;

void resetCardPositionAndSize(Card *, int);
void drawPlayerHand(Card *, int); // Maybe use variable names here to make the code different?
void drawHoverOverCards(Card, float);

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic screen manager");
    // ToggleFullscreen();

    GameScreen currentScreen = LOGO;

    // TODO: Initialize all required variables and load all required data here!

    int framesCounter = 0;          // Useful to count frames

    int numberOfCards = 8;

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

        // The outlines of the size and position of the cards (the texture will be scaled according of this rectangle's size)
        cardsOfPlayer[i].outline = (Rectangle){
            .height = heightOfCards,
            .width = widthOfCards,
            .x = 0.0f,
            .y = (float)(screenHeight - heightOfCards)
        };

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

void resetCardPositionAndSize(Card *cardsOfPlayer, int numberOfCards){
    for(int i = 0; i < numberOfCards; i++){
        cardsOfPlayer[i].outline.x = 0.0f;
        cardsOfPlayer[i].outline.y = (float)(screenHeight - heightOfCards);
        cardsOfPlayer[i].outline.width = widthOfCards;
        cardsOfPlayer[i].outline.height = heightOfCards;
    }
}

void drawPlayerHand(Card *cardsOfPlayer, int numberOfCards){
    float shiftOfCardsInDeck = 0.7f; // percentage
    float rotation = 0.0f, shiftToCorrect = 0.0f; // this variable needed to correctly arrange the right-top corner of the cards on the right side
    int shiftUp = 20.0f;
    int counter = 0;
    int markedCardIndex = -1;
    float markedCardRotation;

    resetCardPositionAndSize(cardsOfPlayer, numberOfCards);
    
    for(int i = 0; i < numberOfCards; i++){
        // This makes the cards to be drawned out with overlap
        cardsOfPlayer[i].outline.x = (float)((screenWidth - numberOfCards * (cardsOfPlayer[i].outline.width * shiftOfCardsInDeck))/2 + i * (cardsOfPlayer[i].outline.width * shiftOfCardsInDeck));
        // This reset is need for the cards in the middle
        rotation = 0.0f;

        // We try to align the edges of the cards from the left of the center card with this variable
        shiftToCorrect = 40.0f;

        // Shift the height of cards to match the pattern of holding cards in hand
        if (i < numberOfCards / 2) {
            rotation = (30.0f - counter * 5.0f) * -1; // -1 need for the cards to lean counter-clockwise
            //shiftToCorrect = 100.0f - counter * 10.0f;
            // Increase counter before the half-way point
            counter++;
        } else if(i > numberOfCards / 2){
            rotation = 30.0f - counter * 5.0f;
            shiftToCorrect = 0.0f;
            // Start decreasing counter after the half-way point
            counter--;
        } else {
            shiftToCorrect = 15.0f;
        }

        // (screenHeight - cardsOfPlayer[i].outline.height) = place the card on the bottom of the screen - (the shift of the card in the column)
        cardsOfPlayer[i].outline.y = (float)(screenHeight - cardsOfPlayer[i].outline.height) - counter * shiftUp + shiftToCorrect;

        if(!CheckCollisionPointRec(GetMousePosition(), cardsOfPlayer[i].outline)){
            // Simply draw the card if it is not selected
            DrawTexturePro(cardsOfPlayer[i].texture, cardsOfPlayer[i].source, cardsOfPlayer[i].outline, cardsOfPlayer[i].origin, rotation, WHITE);
        } else {
            // Save the info of the card the cursor is on to draw the selected card AFTER the for loop, so the selected card will be on top
            markedCardIndex = i;
            markedCardRotation = rotation;
        }
    }
    // Drawing the selected (hovered) card
    if(markedCardIndex > -1) {
        drawHoverOverCards(cardsOfPlayer[markedCardIndex], markedCardRotation);
        // Resetting flags
        markedCardIndex = -1;
    }
}

void drawHoverOverCards(Card cardToDraw, float rotation){
    cardToDraw.outline.x -= 15.0f;
    cardToDraw.outline.y -= 30.0f;
    cardToDraw.outline.width = 1.4f * widthOfCards;
    cardToDraw.outline.height = 1.4f * heightOfCards;
    DrawTexturePro(cardToDraw.texture, cardToDraw.source, cardToDraw.outline, cardToDraw.origin, rotation, WHITE);
}
