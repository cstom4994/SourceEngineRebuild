#include <vgui/VGUI.h>

namespace vgui {
    class Panel;
}

class IHTMLMainMenu {
public:
    virtual void Create(vgui::VPANEL parent) = 0;

    virtual void Destroy(void) = 0;
};

extern IHTMLMainMenu *HTMLMainMenu;