//
// Created by vmuser on 11/19/20.
//

#include "page.h"


page::page(lv_obj_t* parent) {
    if(parent== nullptr)
    {
        parent=lvglBase::instance()->getScr();
    }
    win = lv_cont_create(parent,NULL);
    lv_obj_set_size(win,lvglBase::instance()->getLvHor(),lvglBase::instance()->getLvVer());
    lvglBase::instance()->clearGroup();
}

page::~page() {
    close();
}

void page::close() {
    if(win!= nullptr)
    {
        lv_obj_del_async(win);
    }
    win=nullptr;
}

lv_obj_t *page::getWin() const {
    return win;
}

void page::open(void) {
    lvglBase::instance()->clearGroup();
    for(auto ch:objGroup)
    {
        lvglBase::instance()->addGroup(ch);
    }
//    lv_group_focus_prev(lvglBase::instance()->getG());
}




