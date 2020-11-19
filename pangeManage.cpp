//
// Created by vmuser on 11/19/20.
//

#include "pangeManage.h"

page * pangeManage::creatPage() {
    page *p;
    if(pageLists::instance()->empty())
    {
        p=new page(lvglBase::instance()->getScr());
    }
    else
    {
        p =new page(pageLists::instance()->back()->getWin());
    }
    printf("push back \n");
//    pageLists::instance()->push_back(p);
    return p;
}

void pangeManage::delPage() {
    page *p;
    if(false==pageLists::instance()->empty())
    {
        printf("delPage \n");
        p=pageLists::instance()->back();
        p->close();
        pageLists::instance()->pop_back();
        if(false==pageLists::instance()->empty())
        {
            printf("reopen \n");
            p=pageLists::instance()->back();
            p->open();
        }
    }

}
