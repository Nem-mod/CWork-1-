#include "Unit.h"
#include "Utils.h"
#include <glut.h>
void Unit::draw()
{
    glMaterialfv(GL_FRONT, GL_AMBIENT, getAmbiColor());
    glMaterialfv(GL_FRONT, GL_DIFFUSE, getDiffColor());
    glMaterialfv(GL_FRONT, GL_SPECULAR, getSpecColor());

    glPushMatrix();
    glTranslatef(getXCenter(), getYCenter(), getZCenter());
    parallelepiped(getXSize(), getYSize(), getZSize());
    glPopMatrix();
}