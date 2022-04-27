#include "snake.h"
Snake::Snake(int coordx, int coordy)
{
    position_t initCoord = {
        .x = coordx,
        .y = coordy
    };
    this->body = (position_t *) malloc(sizeof(position_t));
    this->body[0] = initCoord;
}

void Snake::eat(){
    position_t lastCoord = this->body[length-1];
    run();
    this->length ++;
    this->body = (position_t *)realloc(this->body,length*sizeof(position_t));
    this->body[length-1] = lastCoord;
}

void Snake::run(){
    if(this->length>1){
        for (int i=(length-1); i > 0; i--){
                this->body[i].x = this->body[i-1].x;
                this->body[i].y = this->body[i-1].y;
            }
    }
    
    this->body[0].x += velocity[0];
    this->body[0].y += velocity[1];
}
void Snake::setVelocity(int x, int y){
    this->velocity[0]=x;
    this->velocity[1]=y;
}
void Snake::printer(){
    for(int i=0; i<length; i++){
        cout << "("<<this->body[i].x << "," << this->body[i].y <<")"<< endl;
    }
}
int Snake::getSteps(){
    return this->steps;
}
position_t* Snake::getBody(){
    return this->body;
}
unsigned int Snake::getLength(){
    return this->length;
}
void Snake::setSteps(int steps){
    this->steps = steps;
}

