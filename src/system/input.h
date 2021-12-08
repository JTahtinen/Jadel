#pragma once

namespace jadel
{
    
#define NUM_INPUT_KEYS 256

    enum Key
    {
        KEY_A = 0,
        KEY_B,
        KEY_C,
        KEY_D,
        KEY_E,
        KEY_F,
        KEY_G,
        KEY_H,
        KEY_I,
        KEY_J,
        KEY_K,
        KEY_L,
        KEY_M,
        KEY_N,
        KEY_O,
        KEY_P,
        KEY_Q,
        KEY_R,
        KEY_S,
        KEY_T,
        KEY_U,
        KEY_V,
        KEY_W,
        KEY_X,
        KEY_Y,
        KEY_Z,
        KEY_UP,
        KEY_DOWN,
        KEY_LEFT,
        KEY_RIGHT,
        KEY_SPACE,
        KEY_ENTER,
        KEY_ESCAPE,
        KEY_LCTRL,
        KEY_RCTRL,
        KEY_LALT,
        KEY_RALT,
        KEY_0,
        KEY_1,
        KEY_2,
        KEY_3,
        KEY_4,
        KEY_5,
        KEY_6,
        KEY_7,
        KEY_8,
        KEY_9,
        KEY_LSHIFT,
        KEY_RSHIFT,
        KEY_F1,
        KEY_F2,
        KEY_F3,
        KEY_F4,
        KEY_F5,
        KEY_F6,
        KEY_F7,
        KEY_F8,
        KEY_F9,
        KEY_AMOUNT,
        KEY_NULL
    };



    extern bool keysPressed[KEY_AMOUNT];
    extern bool keysTyped[KEY_AMOUNT];
    extern bool keysReleased[KEY_AMOUNT];

    extern int mouseX;
    extern int mouseY;
    extern int mouseDeltaX;
    extern int mouseDeltaY;

    extern bool mouseLeftClicked;
    extern bool mouseRightClicked;
    extern bool mouseLeftHeld;
    extern bool mouseRightHeld;
    extern bool mouseLeftReleased;
    extern bool mouseRightReleased;

    extern bool mouseWheelUp;
    extern bool mouseWheelDown;

    void initInput();
    void updateInput();
    bool isKeyPressed(unsigned int key);
    bool isKeyTyped(unsigned int key);
    bool isKeyReleased(unsigned int key);

}
