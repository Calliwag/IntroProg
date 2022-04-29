bffffffff#include <iostream>
#include "graphics.h"

using namespace std;
using namespace mssm;

#pragma GCC diagnostic ignored "-Wsign-compare"

int main()
{
    Graphics g("Test", 1600, 900);

    while (g.draw()) {

        for (const Event& e : g.events()) {

            switch (e.evtType) {
            case EvtType::KeyPress:
                break;
            case EvtType::KeyRelease:
                break;
            case EvtType::MouseMove:
                break;
            case EvtType::MousePress:
                break;
            case EvtType::MouseRelease:
                break;
            default:
                break;
            }
        }
    }

    return 0;
}


