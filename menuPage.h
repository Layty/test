#ifndef LVGL_MENUPAGE_H
#define LVGL_MENUPAGE_H
#include "page.h"
#include "pangeManage.h"


typedef struct
{
    std::string name;
    lv_event_cb_t cb;
}menuItem_t;

class menuPage:page {
    std::vector<menuItem_t> menuList;
public:
    menuPage(page* parent ,const std::vector<menuItem_t> &menuList);


    void setMenuList(std::vector<menuItem_t> &menuList);
    virtual void open() override;
};


#endif //LVGL_MENUPAGE_H
