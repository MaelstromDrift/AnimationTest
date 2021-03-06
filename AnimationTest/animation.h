#pragma once
#include <SDL.h>
#include <string>
#include <tinyxml2.h>
#include "texture.h"

class Animation {
public:
    Animation() {};
    ~Animation() {};
    int getFrameCount() { return frameCount; }
    std::string getName() { return title; }
    SDL_Rect getFrame(int frameNumber) { return frameList[frameNumber]; }
    Texture getTexture() { return spriteSheet; }
    int  getFrameDelay() { return frameDelay; }
    bool parseFile(std::string path, SDL_Renderer* renderer) {
        tinyxml2::XMLDocument doc;
        doc.LoadFile(path.c_str());
        tinyxml2::XMLElement* animStart = doc.FirstChildElement("animation");
        title = animStart->FirstChildElement("name")->GetText();
        spriteSheet.loadFromPath(animStart->FirstChildElement("image")->GetText(), renderer);
        animStart->FirstChildElement("framecount")->QueryIntText(&frameCount);

        animStart->FirstChildElement("framedelay")->QueryIntText(&frameDelay);
       
        tinyxml2::XMLElement* frameNode = animStart->FirstChildElement("frames");
        
        tinyxml2::XMLElement* frameElement = frameNode->FirstChildElement("frame");
        frameList = new SDL_Rect[frameCount];
        for (int i = 0; i < frameCount; i++) {
            frameList[i].x = frameElement->IntAttribute("x");
            frameList[i].y = frameElement->IntAttribute("y");
            frameList[i].w = frameElement->IntAttribute("width");
            frameList[i].h = frameElement->IntAttribute("height");
        
            frameElement = frameElement->NextSiblingElement("frame");
        }
        return true;
    }
private:
    Texture spriteSheet;
    SDL_Rect *frameList;
    int frameDelay = 66;
    std::string title;
    int frameCount;
};

