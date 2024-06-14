#include "FrameRate.h"
#include <iostream>

FrameRate::FrameRate() : timer(0) {

}
FrameRate::~FrameRate() {

}
void FrameRate::Initialize() {

}
void FrameRate::Load() {
    if(font.loadFromFile("assets/Fonts/arial.ttf")) {
        std::cout << "Arial.ttf font has been loaded successfully" << std::endl;
        frameRateText.setFont(font);
    }else{
        std::cout << "Failed to load Arial.ttf font" << std::endl;
    }
}
void FrameRate::Update(double deltaTime) {
    timer += deltaTime; // 16.66667 ms 60 fps

    if (timer >= 100.0) {
        float fps = 1000.0 / deltaTime;
        frameRateText.setString("FPS: " + std::to_string((int)fps) + " frameTime: " + std::to_string((int)deltaTime));
        timer = 0;
    }
}
void FrameRate::Draw(sf::RenderWindow &window) {
    window.draw(frameRateText);
}