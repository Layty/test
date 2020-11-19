#include "menuPage.h"

void menuPage::setMenuList(std::vector<menuItem_t> &menuListNew) {
    menuList = menuListNew;
}

void menuPage::open() {
    printf("menu open\n");
    lv_obj_t *listMenu = lv_list_create(getWin(), NULL);
    addGroup(listMenu);
    for(auto ch : menuList)
    {
        lv_obj_t* btn=lv_list_add_btn(listMenu,NULL,ch.name.c_str());//设置事件回调函数,用于关闭窗体
        lv_obj_set_event_cb(btn, ch.cb);
        addGroup(btn);
        printf("i\n");
    }
    page::open();
}

menuPage::menuPage(page *parent, const std::vector<menuItem_t> &menuList) : page(parent->getWin()), menuList(menuList)
{

}

