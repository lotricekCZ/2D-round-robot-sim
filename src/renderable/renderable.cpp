/**
 * @author Jakub Ramašeuski (xramas01); 2024
 */
#include "renderable.hpp"

uint32_t renderable::ID_incrementor = 0x020202;

renderable::renderable(/* args */)
{
    ID = ID_incrementor++;
}

renderable::~renderable()
{
}
