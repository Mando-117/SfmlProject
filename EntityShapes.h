//
// Created by Mx117 on 6/26/25.
//

#ifndef ENTITYSHAPES_H
#define ENTITYSHAPES_H
#include <string>
#include <fstream>
#include <iostream>

class EntityShapes
{
    std::string entityType;
    std::string entityName;
    int entityXPosition , entityYPosition, entityVeloX, entityVeloY,
        entityRValue, entityGValue, entityBValue, entityWidth, entityHeight;

    public:

    EntityShapes() {};

    EntityShapes(std::string eType, std::string eName, int eXPosition, int eYPosition, int eVeloX, int eVeloY,
                int eRValue, int eGValue, int eBValue, int eWidth, int eHeight)
                : entityType(eType),
                entityName(eName),
                entityXPosition(eXPosition),
                entityYPosition(eYPosition),
                entityVeloX(eVeloX),
                entityVeloY(eVeloY),
                entityRValue(eRValue),
                entityGValue(eGValue),
                entityBValue(eBValue),
                entityWidth(eWidth),
                entityHeight(eHeight)
    {
    }
    std::string getEntityType()
    {
        return entityType;
    }
    std::string getEntityName()
    {
        return entityName;
    }
    int getEntityXPosition()
    {
        return entityXPosition;
    }
    int getEntityYPosition()
    {
        return entityYPosition;
    }
    int getEntityVeloX()
    {
        return entityVeloX;
    }
    int getEntityVeloY()
    {
        return entityVeloY;
    }
    int getEntityRValue()
    {
        return entityRValue;
    }
    int getEntityGValue()
    {
        return entityGValue;
    }
    int getEntityBValue()
    {
        return entityBValue;
    }
    int getEntityWidth()
    {
        return entityWidth;
    }
    int getEntityHeight()
    {
        return entityHeight;
    }
    void loadFromFile(const std::string& fileName)
    {
        std::ifstream fileIN(fileName);
        std::string eName, eType;
        int eXPosition, eYPosition, eVeloX, eVeloY, eRValue, eGValue, eBValue, eWidth, eHeight;

        while (fileIN >> eName)
        {
            fileIN >> eType >> eXPosition >> eYPosition >> eVeloX >> eVeloY >> eRValue >> eGValue >> eBValue >> eWidth>> eHeight;
        }
    }
    void printEShapes()
    {
        std::cout << "Entity Type: " << entityType << std::endl;
    }

};


#endif //ENTITYSHAPES_H
