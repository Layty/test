
#include "topMenuPage.h"


void topMenuPage::open() {
    static   const std::vector<menuItem_t> menuTop={
        {
                .name="Home",
                .cb=&lvglBase::defaultPrintEv
        },
        {
                .name="Setting",
                .cb=openSetting
        },
        {
                .name="Test",
                .cb=&lvglBase::defaultPrintEv
        }
    };

    page* p=pangeManage::instance()->creatPage();
    menuPage* m=new menuPage(p,menuTop);
    pageLists::instance()->push_back((page*)m);
    m->open();
}

