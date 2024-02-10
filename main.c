#include "raylib.h"
#include <time.h>
#include <stdlib.h>

#define RARITY_GRAY 1
#define RARITY_GREEN 2
#define RARITY_BLUE 3
#define RARITY_PURPLE 4
#define RARITY_GOLD 5
#define RARITY_HERO 6

#define CAST_GHOST 1
#define CAST_KNIGHT 2
#define CAST_ORK 3
#define CAST_WIZARD 4
#define CAST_HERO 5

//------------------------------------------------------------------------------------------
// Types and Structures Definition
//------------------------------------------------------------------------------------------
typedef enum GameScreen { LOGO = 0, TITLE, GAMEPLAY, ENDING } GameScreen;
typedef enum Map {CASTLE, CAVE, HELL, SWAMP} Map;

typedef struct Card {
    Texture texture;
    Rectangle source;
    Rectangle outline;
    Vector2 origin;
    bool played;
    int rarity;
    int cast;
    int strength;
    int fire;
    int magic;
    int defence;
    int fire_defence;
    int magic_defence;
} Card;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

const int screenWidth = 1920;
const int screenHeight = 1080;
const float heightOfCards = 214.0f;
const float widthOfCards = 131.0f;
Card cardCollection[21]; // This variable contains all cards

void initializeCards(Card *, Card *, int, Card *);
void setCastProperties();
void randomSelectDeckCards(Card *, Card *, int);
void resetCardPositionAndSize(Card *, int);
int drawPlayerHand(Card *, int, bool *); // Maybe use variable names here to make the code different?
bool drawHoverOverCards(Card, float, bool *);
void reorganizeCardsInHand(Card *, int);
void drawPlayedCards(Card *, int);
void displayCardProperties(Card);
void displayComputersCards(Card *, int);
int computerMoves(Card *, int, bool *);
void compareScores(int *, int *, Card *, Card *, int);

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic screen manager");
    ToggleFullscreen();
    InitAudioDevice();

    // Initializing the rand function
    srand(time(NULL));

    GameScreen currentScreen = LOGO;
    Map map;
    bool playerRound = false;
    // Generate a random number for the map selection 
    int randomNumber = rand() % 4 + 1;
    Texture2D mapTexture;
    // Select the map according to the random number generated
    switch (randomNumber)
    {
    case 1:
        map = CASTLE;
        mapTexture = LoadTexture("images/background_map/desk_castle.png");
        break;

    case 2:
        map = CAVE;
        mapTexture = LoadTexture("images/background_map/desk_cave.png");
        break;

    case 3:
        map = HELL;
        mapTexture = LoadTexture("images/background_map/desk_hell.png");
        break;

    case 4:
        map = SWAMP;
        mapTexture = LoadTexture("images/background_map/desk_swamp.png");
        break;
    
    default:
        break;
    }

    // TODO: Initialize all required variables and load all required data here!

    int framesCounter = 0;          // Useful to count frames

    const int numberOfCards = 8;
    int numberOfCardsInPlayerHand = 8;
    // These variables will be compared for the final result
    int scoreOfPlayer = 0, scoreOfComputer = 0;
    
    // Rarity 1: gray, 2: green, 3: blue, 4: purple, 5: gold, 6: hero
    // Casts: 1: ghost, 2: knight, 3: ork, 4: wizard, 5: hero
    Texture2D logoScreenTexture = LoadTexture("images/misc/loading_screen.png");
    Texture2D menuTexture = LoadTexture("images/background_map/menu.png");
    // Setting up variables for the background
    Texture2D backgroundTexture = LoadTexture("images/background_map/background.png");
    Rectangle backgroundSrcRec = (Rectangle){
        .height = backgroundTexture.height,
        .width = backgroundTexture.width,
        .x = 0,
        .y = 0
    };
    Rectangle backgroundDestRec = (Rectangle){
        .height = 1080.0f,
        .width = 1920.0f,
        .x = 0.0f,
        .y = 0.0f
    };
    Vector2 backgroundOrigin = (Vector2){
        .x = 0.0f,
        .y = 0.0f
    };

    // Setting up background music
    Music music = LoadMusicStream("audio/background_music.mp3");

    Card cardsOfPlayer[numberOfCards], cardsOfComputer[numberOfCards];
    Card playedCardsOfPlayer[2*numberOfCards];
    int numberOfPlayedCards = -1;

    initializeCards(cardsOfPlayer, cardsOfComputer, numberOfCards, playedCardsOfPlayer);
    randomSelectDeckCards(cardsOfPlayer, cardsOfComputer, numberOfCards);

    SetTargetFPS(60);               // Set desired framerate (frames-per-second)
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateMusicStream(music);   // Update music buffer with new stream data. WITHOUT THIS THE MUSIC WON'T START!
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
                PlayMusicStream(music);
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
                    DrawTexture(logoScreenTexture, 0, 0, WHITE);

                } break;
                case TITLE:
                {
                    // TODO: Draw TITLE screen here!
                    DrawTexturePro(menuTexture, backgroundSrcRec, backgroundDestRec, backgroundOrigin, 0.0f, WHITE);

                } break;
                case GAMEPLAY:
                {
                    // TODO: Draw the hand of the player with this function
                    DrawTexturePro(backgroundTexture, backgroundSrcRec, backgroundDestRec, backgroundOrigin, 0.0f, WHITE);
                    DrawTexturePro(mapTexture, backgroundSrcRec, backgroundDestRec, backgroundOrigin, 0.0f, WHITE);
                    displayComputersCards(cardsOfComputer, numberOfCards); // DEBUG PURPOSES
                    // The computer selects a card (index)
                    int selected_card_computer = computerMoves(cardsOfComputer, numberOfCards, &playerRound);
                    if(selected_card_computer > -1){
                        // Move that card to the played card pile
                        numberOfPlayedCards++;
                        playedCardsOfPlayer[numberOfPlayedCards] = cardsOfComputer[selected_card_computer];
                        playerRound = true;
                    }
                    int selected_card = drawPlayerHand(cardsOfPlayer, numberOfCardsInPlayerHand, &playerRound);
                    if(selected_card > -1){
                        // If the selected cards was clicked, decrease the value of the number of cards in the player's hand
                        numberOfCardsInPlayerHand--;
                        // Move the played card to the played card array
                        numberOfPlayedCards++;
                        playedCardsOfPlayer[numberOfPlayedCards] = cardsOfPlayer[selected_card];
                        // Reorganize cards in player's hand
                        reorganizeCardsInHand(cardsOfPlayer, numberOfCards);
                    }
                    drawPlayedCards(playedCardsOfPlayer, numberOfPlayedCards);
                    compareScores(&scoreOfPlayer, &scoreOfComputer, cardsOfPlayer, cardsOfComputer, numberOfCards);
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
        UnloadTexture(playedCardsOfPlayer[i].texture);
    }
    for(int i = 0; i < 21; i++){
        UnloadTexture(cardCollection[i].texture);
    }
    UnloadTexture(logoScreenTexture);
    UnloadTexture(mapTexture);
    UnloadTexture(backgroundTexture);
    
    UnloadMusicStream(music);          // Unload music stream buffers from RAM
    CloseAudioDevice();     // Close audio device (music streaming is automatically stopped)
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

void initializeCards(Card *cardsOfPlayer, Card *cardsOfComputer, int numberOfCards, Card *playedCardsOfPlayer){
    int index = 0;
    // Loading the textures of the cards
    for(int rarity = 1; rarity <= 5; rarity++){
        for(int cast = 1; cast <= 4; cast++){
            cardCollection[index].texture = LoadTexture(TextFormat("images/cards/card_%d_%d.png", rarity, cast));
            cardCollection[index].rarity = rarity;
            cardCollection[index].cast = cast;
            //cardCollection[index].texture = LoadTexture("images/cards/image_card0.png");
            index++;
        }
    }
    
    // The index at this point should be 20. This is a safety check
    if(index != 20) exit(1);

    // Loading the texture of the hero card
    cardCollection[index].texture = LoadTexture("images/cards/card_6_5.png");

    for(int i = 0; i < 21; i++){
        // The size and position of the texture in the file
        cardCollection[i].source = (Rectangle){
            .height = (float)cardCollection[i].texture.height,
            .width = (float)cardCollection[i].texture.width,
            .x = 0.0f,
            .y = 0.0f
        };

        // The outlines of the size and position of the cards (the texture will be scaled according of this rectangle's size)
        cardCollection[i].outline = (Rectangle){
            .height = heightOfCards,
            .width = widthOfCards,
            .x = 0.0f,
            .y = (float)(screenHeight - heightOfCards)
        };

        // TODO: Found out what is this for
        cardCollection[i].origin = (Vector2){
            .x = 0.0f,
            .y = 0.0f
        };

        cardCollection[i].played = false;

    }
    // Initializing cards in hand and on the board
    for (int i = 0; i < numberOfCards; i++)
    {
        // Initializing every card as unplayed (just in case)
        cardsOfPlayer[i].played = false;
        cardsOfComputer[i].played = false;
        playedCardsOfPlayer[i].played = false;
    }
    setCastProperties(numberOfCards);
}

void setCastProperties(){
    // Initializing the properties of the cards
    // Gray ghost
    cardCollection[0].strength = 0;
    cardCollection[0].fire = 6;
    cardCollection[0].magic = 3;
    cardCollection[0].defence = 0;
    cardCollection[0].fire_defence = 6;
    cardCollection[0].magic_defence = 1;
    // Gray knight
    cardCollection[1].strength = 6;
    cardCollection[1].fire = 1;
    cardCollection[1].magic = 0;
    cardCollection[1].defence = 6;
    cardCollection[1].fire_defence = 1;
    cardCollection[1].magic_defence = 0;
    // Gray orc
    cardCollection[2].strength = 4;
    cardCollection[2].fire = 2;
    cardCollection[2].magic = 1;
    cardCollection[2].defence = 4;
    cardCollection[2].fire_defence = 0;
    cardCollection[2].magic_defence = 1;
    // Gray wizard
    cardCollection[3].strength = 0;
    cardCollection[3].fire = 3;
    cardCollection[3].magic = 6;
    cardCollection[3].defence = 0;
    cardCollection[3].fire_defence = 1;
    cardCollection[3].magic_defence = 6;

    // Green ghost
    cardCollection[4].strength = 0;
    cardCollection[4].fire = 7;
    cardCollection[4].magic = 4;
    cardCollection[4].defence = 0;
    cardCollection[4].fire_defence = 7;
    cardCollection[4].magic_defence = 2;
    // Green knight
    cardCollection[5].strength = 7;
    cardCollection[5].fire = 1;
    cardCollection[5].magic = 0;
    cardCollection[5].defence = 7;
    cardCollection[5].fire_defence = 1;
    cardCollection[5].magic_defence = 0;
    // Green orc
    cardCollection[6].strength = 5;
    cardCollection[6].fire = 3;
    cardCollection[6].magic = 2;
    cardCollection[6].defence = 5;
    cardCollection[6].fire_defence = 0;
    cardCollection[6].magic_defence = 2;
    // Green wizard
    cardCollection[7].strength = 0;
    cardCollection[7].fire = 4;
    cardCollection[7].magic = 7;
    cardCollection[7].defence = 0;
    cardCollection[7].fire_defence = 2;
    cardCollection[7].magic_defence = 7;

    // Blue ghost
    cardCollection[8].strength = 0;
    cardCollection[8].fire = 8;
    cardCollection[8].magic = 5;
    cardCollection[8].defence = 0;
    cardCollection[8].fire_defence = 8;
    cardCollection[8].magic_defence = 2;
    // Blue knight
    cardCollection[9].strength = 8;
    cardCollection[9].fire = 1;
    cardCollection[9].magic = 0;
    cardCollection[9].defence = 8;
    cardCollection[9].fire_defence = 1;
    cardCollection[9].magic_defence = 0;
    // Blue orc
    cardCollection[10].strength = 6;
    cardCollection[10].fire = 4;
    cardCollection[10].magic = 3;
    cardCollection[10].defence = 6;
    cardCollection[10].fire_defence = 0;
    cardCollection[10].magic_defence = 3;
    // Blue wizard
    cardCollection[11].strength = 0;
    cardCollection[11].fire = 5;
    cardCollection[11].magic = 8;
    cardCollection[11].defence = 0;
    cardCollection[11].fire_defence = 2;
    cardCollection[11].magic_defence = 8;

    // Purple ghost
    cardCollection[12].strength = 0;
    cardCollection[12].fire = 9;
    cardCollection[12].magic = 6;
    cardCollection[12].defence = 0;
    cardCollection[12].fire_defence = 9;
    cardCollection[12].magic_defence = 3;
    // Purple knight
    cardCollection[13].strength = 9;
    cardCollection[13].fire = 2;
    cardCollection[13].magic = 0;
    cardCollection[13].defence = 9;
    cardCollection[13].fire_defence = 2;
    cardCollection[13].magic_defence = 1;
    // Purple orc
    cardCollection[14].strength = 7;
    cardCollection[14].fire = 5;
    cardCollection[14].magic = 4;
    cardCollection[14].defence = 7;
    cardCollection[14].fire_defence = 1;
    cardCollection[14].magic_defence = 4;
    // Purple wizard
    cardCollection[15].strength = 0;
    cardCollection[15].fire = 6;
    cardCollection[15].magic = 9;
    cardCollection[15].defence = 0;
    cardCollection[15].fire_defence = 3;
    cardCollection[15].magic_defence = 9;

    // Gold ghost
    cardCollection[16].strength = 0;
    cardCollection[16].fire = 10;
    cardCollection[16].magic = 7;
    cardCollection[16].defence = 0;
    cardCollection[16].fire_defence = 10;
    cardCollection[16].magic_defence = 3;
    // Gold knight
    cardCollection[17].strength = 10;
    cardCollection[17].fire = 2;
    cardCollection[17].magic = 1;
    cardCollection[17].defence = 10;
    cardCollection[17].fire_defence = 2;
    cardCollection[17].magic_defence = 2;
    // Gold orc
    cardCollection[18].strength = 8;
    cardCollection[18].fire = 6;
    cardCollection[18].magic = 5;
    cardCollection[18].defence = 8;
    cardCollection[18].fire_defence = 2;
    cardCollection[18].magic_defence = 5;
    // Gold wizard
    cardCollection[19].strength = 0;
    cardCollection[19].fire = 7;
    cardCollection[19].magic = 10;
    cardCollection[19].defence = 0;
    cardCollection[19].fire_defence = 3;
    cardCollection[19].magic_defence = 10;

    // Hero
    cardCollection[20].strength = 10;
    cardCollection[20].fire = 10;
    cardCollection[20].magic = 10;
    cardCollection[20].defence = 10;
    cardCollection[20].fire_defence = 10;
    cardCollection[20].magic_defence = 10;
}

void displayCardProperties(Card cardToDisplay){
    // This function is to display the given card's properties for debug purposes
    DrawText(TextFormat("Strength: %d", cardToDisplay.strength), 0, 0, 30, RED);
    DrawText(TextFormat("Fire: %d", cardToDisplay.fire), 0, 30, 30, RED);
    DrawText(TextFormat("Magic: %d", cardToDisplay.magic), 0, 60, 30, RED);
    DrawText(TextFormat("Defence: %d", cardToDisplay.defence), 0, 90, 30, RED);
    DrawText(TextFormat("Fire defence: %d", cardToDisplay.fire_defence), 0, 120, 30, RED);
    DrawText(TextFormat("Magic defence: %d", cardToDisplay.magic_defence), 0, 150, 30, RED);
}

void displayComputersCards(Card *cardsOfComputer, int numberOfCards){
    // FOR DEBUG PURPOSES
    // Draw the computer's cards
    for(int i = 0; i < numberOfCards; i++){
        // Skip played cards
        if(cardsOfComputer[i].played) continue;
        
        cardsOfComputer[i].outline.y = 0.0f + cardsOfComputer[i].outline.height;
        cardsOfComputer[i].outline.x = (float) i * widthOfCards;
        DrawTexturePro(cardsOfComputer[i].texture, cardsOfComputer[i].source, cardsOfComputer[i].outline, cardsOfComputer[i].origin, 0.0f, WHITE);
    }
}

void randomSelectDeckCards(Card *cardsOfPlayer, Card *cardsOfComputer, int numberOfCards){
    int sumOfPlayerCards = 0, sumOfComputerCards = 0;
    // Select cards for the player
    for(int i = 0; i < numberOfCards; i++){
        // The rarest card it can draw is blue
        int randomIndex = rand() % 12;
        cardsOfPlayer[i] = cardCollection[randomIndex];
        // We calculate the sum of the rarity of the player's deck so the AI could have a deck with the same weight
        sumOfPlayerCards += cardsOfPlayer[i].rarity;
    }

    // Select cards with equal sum for the AI
    while(sumOfComputerCards != sumOfPlayerCards){
        sumOfComputerCards = 0;
        for(int i = 0; i < numberOfCards; i++){
            // The rarest card it can draw is blue
            int randomIndex = rand() % 12;
            cardsOfComputer[i] = cardCollection[randomIndex];
            sumOfComputerCards += cardsOfComputer[i].rarity;
        }
    }
}

void resetCardPositionAndSize(Card *cardsOfPlayer, int numberOfCards){
    for(int i = 0; i < numberOfCards; i++){
        cardsOfPlayer[i].outline.x = 0.0f;
        cardsOfPlayer[i].outline.y = (float)(screenHeight - heightOfCards);
        cardsOfPlayer[i].outline.width = widthOfCards;
        cardsOfPlayer[i].outline.height = heightOfCards;
    }
}

int drawPlayerHand(Card *cardsOfPlayer, int numberOfCardsInPlayerHand, bool *playerRound){
    float shiftOfCardsInDeck = 0.7f; // percentage
    float rotation = 0.0f, shiftToCorrect = 0.0f; // this variable needed to correctly arrange the right-top corner of the cards on the right side
    int shiftUp = 20.0f;
    int counter = 0;
    int markedCardIndex = -1;
    float markedCardRotation;

    resetCardPositionAndSize(cardsOfPlayer, numberOfCardsInPlayerHand);
    
    for(int i = 0; i < numberOfCardsInPlayerHand; i++){
        // If the card was played, do not change the properties of the card, skip it
        if(cardsOfPlayer[i].played) continue;

        // This makes the cards to be drawned out with overlap
        cardsOfPlayer[i].outline.x = (float)((screenWidth - numberOfCardsInPlayerHand * (cardsOfPlayer[i].outline.width * shiftOfCardsInDeck))/2 + i * (cardsOfPlayer[i].outline.width * shiftOfCardsInDeck));
        // This reset is need for the cards in the middle
        rotation = 0.0f;

        // We try to align the edges of the cards from the left of the center card with this variable
        shiftToCorrect = 40.0f;

        // Shift the height of cards to match the pattern of holding cards in hand
        if (i < numberOfCardsInPlayerHand / 2) {
            rotation = (30.0f - counter * 5.0f) * -1; // -1 need for the cards to lean counter-clockwise
            //shiftToCorrect = 100.0f - counter * 10.0f;
            // Increase counter before the half-way point
            counter++;
        } else if(i > numberOfCardsInPlayerHand / 2){
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
        if(drawHoverOverCards(cardsOfPlayer[markedCardIndex], markedCardRotation, playerRound)){
            // Saving the index to return later (since the markedCardIndex variable will be reseted before returning a value)
            int indexToReturn = markedCardIndex;
            // If the selected card was clicked on, set the flag 
            cardsOfPlayer[markedCardIndex].played = true;
            // Resetting flags
            markedCardIndex = -1;
            return indexToReturn;
        }
    }
    return -1;
}

bool drawHoverOverCards(Card cardToDraw, float rotation, bool *playerRound){
    cardToDraw.outline.x -= 15.0f;
    cardToDraw.outline.y -= 100.0f;
    cardToDraw.outline.width = 1.4f * widthOfCards;
    cardToDraw.outline.height = 1.4f * heightOfCards;
    DrawTexturePro(cardToDraw.texture, cardToDraw.source, cardToDraw.outline, cardToDraw.origin, rotation, WHITE);
    // THIS IS ONLY NEEDED FOR DEBUG PURPOSES
    displayCardProperties(cardToDraw);
    // If the player presses the left mouse button while the card is selected and it's the player's round, the card is played
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && *playerRound) {
        *playerRound = false;
        return true;
    }
    return false;
}

void reorganizeCardsInHand(Card *cardsOfPlayer, int numberOfCards){
    // Start searching for a played card
    for(int i = 0; i < numberOfCards-1; i++){
        if(cardsOfPlayer[i].played){
            // If found a played card, push each card from the index of the played card to one index to the left (so decrease their index by one)
            for(int j = i; j < numberOfCards-1; j++){
                cardsOfPlayer[j] = cardsOfPlayer[j+1];
            }
        }
    }
}

void drawPlayedCards(Card *playedCardsOfPlayer, int numberOfPlayedCards){
    int shift = 0;
    // Check if the player has played any card
    if(numberOfPlayedCards > -1){
        // Draw the first card (shift it to the right by the size of three cards to arrange the pile in the middle)
        playedCardsOfPlayer[0].outline.x = (3 * playedCardsOfPlayer[0].outline.width);
        playedCardsOfPlayer[0].outline.y = (screenHeight / 2) - (heightOfCards / 2);
        DrawTexturePro(playedCardsOfPlayer[0].texture, playedCardsOfPlayer[0].source, playedCardsOfPlayer[0].outline, playedCardsOfPlayer[0]. origin, 0.0f, WHITE);

        // If the number is not greater than 0 -> return (so the index won't be -1 below)
        if(numberOfPlayedCards == 0) return;

        // Draw the cards up until the third card from the last position with a little overlap
        for(int i = 1; i <= numberOfPlayedCards - 2; i++){
            playedCardsOfPlayer[i].outline.x = playedCardsOfPlayer[i-1].outline.x + 50.0f;
            playedCardsOfPlayer[i].outline.y = (screenHeight / 2) - (heightOfCards / 2);
            DrawTexturePro(playedCardsOfPlayer[i].texture, playedCardsOfPlayer[i].source, playedCardsOfPlayer[i].outline, playedCardsOfPlayer[i]. origin, 0.0f, WHITE);
        }

        // Draw the last x number of cards without overlap
        for(int i = numberOfPlayedCards - 1; i <= numberOfPlayedCards; i++){
            // This statement prevents the drawing of the first card twice
            if(i == 0) continue;
            playedCardsOfPlayer[i].outline.x = playedCardsOfPlayer[i-1].outline.x + widthOfCards;
            playedCardsOfPlayer[i].outline.y = (screenHeight / 2) - (heightOfCards / 2);
            DrawTexturePro(playedCardsOfPlayer[i].texture, playedCardsOfPlayer[i].source, playedCardsOfPlayer[i].outline, playedCardsOfPlayer[i]. origin, 0.0f, WHITE);
        }
    }
}

int computerMoves(Card *cardsOfComputer, int numberOfCards, bool *playerRound){
    // If's not the computer's round
    if(*playerRound) return -1;
    // Temporarily the computer just selects the first unplayed card
    for(int i = 0; i < numberOfCards; i++){
        if(!cardsOfComputer[i].played){
            cardsOfComputer[i].played = true;
            return i;
        }
    }
    return -1;
}

void compareScores(int *scoreOfPlayer, int *scoreOfComputer, Card *cardsOfPlayer, Card *cardsOfComputer, int numberOfCards){
    int playerStrength = 0, playerFire = 0, playerMagic = 0, playerDefence = 0, playerFireDefence = 0, playerMagicDefense = 0;
    int computerStrength = 0, computerFire = 0, computerMagic = 0, computerDefence = 0, computerFireDefence = 0, computerMagicDefense = 0;
 
    for(int i = 0; i < numberOfCards; i++){
        if(cardsOfPlayer[i].played){
            // Calculating player's stats
            playerStrength += cardsOfPlayer[i].strength;
            playerFire += cardsOfPlayer[i].fire;
            playerMagic += cardsOfPlayer[i].magic;
            playerDefence += cardsOfPlayer[i].defence;
            playerFireDefence += cardsOfPlayer[i].fire_defence;
            playerMagicDefense += cardsOfPlayer[i].magic_defence;
        }
        if(cardsOfComputer[i].played){
            // Calculating computer's stats
            computerStrength += cardsOfComputer[i].strength;
            computerFire += cardsOfComputer[i].fire;
            computerMagic += cardsOfComputer[i].magic;
            computerDefence += cardsOfComputer[i].defence;
            computerFireDefence += cardsOfComputer[i].fire_defence;
            computerMagicDefense += cardsOfComputer[i].magic_defence;
        }
    }

    playerStrength -= computerDefence;
    playerFire -= computerFireDefence;
    playerMagic -= computerMagicDefense;
    
    computerStrength -= playerDefence;
    computerFire -= playerFireDefence;
    computerMagic -= playerMagicDefense;

    *scoreOfPlayer = playerStrength + playerFire + playerMagic;
    *scoreOfComputer = computerStrength + computerFire + computerMagic;

    // FOR DEBUG PURPOSES
    DrawText(TextFormat("%d", playerStrength), 0, 500, 25, RED);
    DrawText(TextFormat("%d", playerFire), 0, 550, 25, RED);
    DrawText(TextFormat("%d", playerMagic), 0, 570, 25, RED);
    DrawText(TextFormat("%d", playerDefence), 0, 590, 25, RED);
    DrawText(TextFormat("%d", playerFireDefence), 0, 610, 25, RED);
    DrawText(TextFormat("%d", playerMagicDefense), 0, 630, 25, RED);

    DrawText(TextFormat("%d", computerStrength), 1900, 500, 25, RED);
    DrawText(TextFormat("%d", computerFire), 1900, 550, 25, RED);
    DrawText(TextFormat("%d", computerMagic), 1900, 570, 25, RED);
    DrawText(TextFormat("%d", computerDefence), 1900, 590, 25, RED);
    DrawText(TextFormat("%d", computerFireDefence), 1900, 610, 25, RED);
    DrawText(TextFormat("%d", computerMagicDefense), 1900, 630, 25, RED);

    DrawText(TextFormat("%d", *scoreOfPlayer), 570, 10, 50, YELLOW);
    DrawText(TextFormat("%d", *scoreOfComputer), 1020, 10, 50, YELLOW);
}
