#pragma once
#include "GameObject.h"
#include <iostream>

class Platform : public GameObject
{
    float win_w, win_h;
    sf::RectangleShape shape;

public:
    Platform(size_t w, size_t h, float x, float y, float w_w, float w_h, float v, sf::Color color = sf::Color::Yellow)
    {
        win_w = w_w;
        win_h = w_h;
        shape.setPosition(x, y);
        shape.setSize(sf::Vector2f(w, h));
        shape.setFillColor(color);
        shape.setOrigin(w / 2, h / 2);
        set_velocity(v);
    }
    virtual void init_object() override {}
    virtual float get_velocity() override { return 0; }
    virtual sf::Shape& get_shape() override
    {
        return shape;
    }
    virtual void update() override
    {
        sf::FloatRect tmp_rect = shape.getGlobalBounds();
        if ((tmp_rect.left <= 0) && (v.x < 0)) return; 
        if ((tmp_rect.left + tmp_rect.width >= win_w) && (v.x > 0)) return;
        shape.move(v);
    }
    void stop()
    {
        v.x = 0;
    }
    void move_left()
    {
        v.x = -velocity;
    }
    void move_right()
    {
        v.x = velocity;
    }

private:
    float velocity = 0;
    virtual void set_velocity(float dr) override
    {
        velocity = dr;
    };
};
