/**
 * @author Jakub Ramašeuski (xramas01); 2024
*/

#include "ai.hpp"

ai::ai()
{
    patience = 255 + random() % 1024;
    steer();
}

ai::~ai()
{
}

void ai::steer()
{
    controls.dx = (float)(1+(-2 * (random() % 2))) * (float)(random() % 1500) / (100000.0);
    controls.dy = (random() % 3 != 0) * (float)(random() % 130 - 10) / (90.0);
    controls.next_change = std::chrono::steady_clock::now() + std::chrono::milliseconds(50 + random() % 1000);
}

void ai::attach(std::shared_ptr<renderable> &b){
    attached = b;
}