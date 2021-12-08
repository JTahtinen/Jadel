#pragma once


namespace jadel
{
#define MAX_EVENTS 50

    extern void* inputEvents;
    extern void* windowEvents;
    extern int numInputEvents;
    extern int numWindowEvents;

    void updateEvents();
    void initEvents();
}
