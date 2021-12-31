//
// Created by KaoruXun
//

#ifndef INVADEENGINE_IBROWSERPANEL_H
#define INVADEENGINE_IBROWSERPANEL_H

class IBrowserPanel {
public:
    virtual void Create(vgui::VPANEL parent) = 0;

    virtual void Destroy(void) = 0;

    virtual void Activate(void) = 0;
};

extern IBrowserPanel *BrowserPanel;

#endif //INVADEENGINE_IBROWSERPANEL_H
