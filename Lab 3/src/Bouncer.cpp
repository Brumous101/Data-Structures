//Name: Kyle Johnson
//Class: ETEC2101
//Section: 01
//Assignment: 3

#include <iostream>
#include <string>			// contains getline function (among other things)
#include <array_list.h>
#include <SFML/Graphics.hpp>
#include <Bouncer.h>

ssuds::Bouncer::Bouncer(float startPosX, float startPosY, float xVelocity, float yVelocity, float radius)://add radius as a parameter
{
    mVelocity.x = xVelocity;
    mVelocity.y = yVelocity;
    mSize = radius;
    mBounces = 0;
    setPosition(startPosX, startPosY);
}

ssuds::Bouncer::Bouncer()
{
    //Initialized to nothing, need this to set arrayList
}

void ssuds::Bouncer::move_me(float dt, int win_w, int win_h)
{
	position.x = old_position.x + mVelocity.x * dt;
    position.y = old_position.y + mVelocity.y * dt;

    //Flipping the vectors on bonks
    if (((this->getPosition().x) + (this->getRadius()) >= win_w) || (this->getPosition().x <= 0))// Right Side || Left side
    {
        (this->mVelocity.x) = ((this->mVelocity.x) * -1);
    }
    if (((this->getPosition().y) + (this->getRadius()) >= win_h) || (this->getPosition().y <= 0))// Bottom side || Top side
    {
        (this->mVelocity.y) = ((this->mVelocity.y) * -1);
    }
    (this->mPositionX.x) = (this->getPosition().x) + (this->mVelocity.x);
    (this->mPositionY.y) = (this->getPosition().y) + (this->mVelocity.y);
    
}

//Clear screen and update graphics with a different function
/*
Old Bouncer Blockhead code that I plan to recycle into this assignment.
Needs to be rewritten from SDL -> SFML but the logic should be sound
=========================================================================================================

void addBlockHeadToList(struct BLOCKHEAD_NODE ** blockhead_list)
{
    int blockSize=(10*rand()/(double)RAND_MAX)+ (10);
    long blockColor = (((rand()/(double)RAND_MAX))* 0xffffff);
    double xPosition = ((rand()/(double)RAND_MAX)*1000), yPosition = ((rand()/(double)RAND_MAX)*1000), xVector = (rand()/(double)RAND_MAX)*10, yVector = (rand()/(double)RAND_MAX)*10;

    //50% chance of each direction
    if((int)xVector % 2 == 0)
        xVector = xVector * (-1);
    if((int)yVector % 2 == 0)
        yVector = yVector * (-1);

    while((*blockhead_list)!=NULL)
    {
        blockhead_list=&((*blockhead_list)->next);
    }

    (*blockhead_list)=(BLOCK *)malloc(sizeof(BLOCK));
    (*blockhead_list)->x = xPosition;
    (*blockhead_list)->y = yPosition;
    (*blockhead_list)->dx = xVector;
    (*blockhead_list)->dy = yVector;
    (*blockhead_list)->color = blockColor;
    (*blockhead_list)->size = blockSize;
    (*blockhead_list)->next=NULL;
}

void addBlockHeadToListOnClick(struct BLOCKHEAD_NODE ** blockhead_list, int* x, int* y)
{
    int blockSize=(10*rand()/(double)RAND_MAX)+ (10);
    long blockColor = (((rand()/(double)RAND_MAX))* 0xffffff);
    double xVector = (rand()/(double)RAND_MAX)*10, yVector = (rand()/(double)RAND_MAX)*10;

    //50% chance of each direction
    if((int)xVector % 2 == 0)
        xVector = xVector * (-1);
    if((int)yVector % 2 == 0)
        yVector = yVector * (-1);

    while((*blockhead_list)!=NULL)
    {
        blockhead_list=&((*blockhead_list)->next);
    }

    (*blockhead_list)=(BLOCK *)malloc(sizeof(BLOCK));
    (*blockhead_list)->x = *x;
    (*blockhead_list)->y = *y;
    (*blockhead_list)->dx = xVector;
    (*blockhead_list)->dy = yVector;
    (*blockhead_list)->color = blockColor;
    (*blockhead_list)->size = blockSize;
    (*blockhead_list)->next=NULL;
}

void removeBlockHeadFromList( struct BLOCKHEAD_NODE ** blockhead_list, int index)
{
    int i=0;
    struct BLOCKHEAD_NODE * temp;

    while((*blockhead_list)!=NULL)
    {
        if((rand()/(double)RAND_MAX) <= 0.1)//10% chance
        {
            temp=(*blockhead_list);
            (*blockhead_list)=(*blockhead_list)->next;
            free(temp);
            return;
        }
        blockhead_list=&((*blockhead_list)->next);
        i++;
    }
}

void removeBlockHeadToListOnClick(struct BLOCKHEAD_NODE ** blockhead_list, int* x, int* y)
{
    int i=0;
    struct BLOCKHEAD_NODE * temp;

    while((*blockhead_list)!=NULL)
    {
        //if((*blockhead_list)->x == *x && (*blockhead_list)->y == *y)
        if(*x >= (*blockhead_list) -> x &&
           *x <= ((*blockhead_list) -> x + (*blockhead_list) -> size) &&
           *y >= (*blockhead_list) -> y &&
           *y <= ((*blockhead_list) ->y + (*blockhead_list) -> size) )
        {
            temp=(*blockhead_list);
            (*blockhead_list)=(*blockhead_list)->next;
            free(temp);
            return;
        }
        blockhead_list=&((*blockhead_list)->next);
        i++;
    }
}
void renderBlockHead(struct BLOCKHEAD_NODE * blockhead, SDL_Surface *screenSurface)
{
    SDL_Rect rect = {blockhead ->x, blockhead ->y, blockhead -> size, blockhead -> size};
    unsigned char B,G,R;
    B = (blockhead -> color) & 0xff;
    G = (blockhead -> color>>8) & 0xff;
    R = (blockhead -> color>>16) & 0xff;
    SDL_FillRect( screenSurface, &rect, SDL_MapRGB( screenSurface->format, R, G, B ) );
}

void renderBlockHeadList( struct BLOCKHEAD_NODE * blockhead_list, SDL_Surface *screenSurface)
{
    while(blockhead_list!=NULL)
    {
        renderBlockHead(blockhead_list, screenSurface);
        blockhead_list= blockhead_list->next;
    }
}

void moveBlockHead(struct BLOCKHEAD_NODE * blockhead)
{
        //Flipping the vectors on bonks
        if(((blockhead -> x) + (blockhead -> size) >= SCREEN_WIDTH) || (blockhead -> x <=0))// Right Side || Left side
        {
            (blockhead -> dx) = ((blockhead -> dx)*-1);
        }
        if(((blockhead -> y) + (blockhead -> size) >= SCREEN_HEIGHT) || (blockhead -> y <=0))// Bottom side || Top side
        {
            (blockhead -> dy) = ((blockhead -> dy)*-1);
        }
        (blockhead -> x) = (blockhead -> x) + (blockhead -> dx);
        (blockhead -> y) = (blockhead -> y) + (blockhead -> dy);
}

void moveBlockHeadList( struct BLOCKHEAD_NODE * blockhead_list)
{
    while(blockhead_list!=NULL)
    {
        moveBlockHead(blockhead_list);
        blockhead_list= blockhead_list->next;
    }
}
*/