#include "bullet.h"
#include "renderer.h"

Bullet::Bullet(){

}

void Bullet::draw(Renderer &p, Bullet b){
    p.drawBullet(b.x, b.y, b.size);
}