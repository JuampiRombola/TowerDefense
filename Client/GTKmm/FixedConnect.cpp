//
// Created by tino on 27/11/17.
//

#include "FixedConnect.h"
FixedConnect::FixedConnect() {

}

FixedConnect::~FixedConnect(){

}

void FixedConnect::Set(const Glib::RefPtr<Gtk::Builder> &refBuilder){
    refBuilder->get_widget("fixed_connect", fixed);
    refBuilder->get_widget("entry_ip", entry_ip);
    refBuilder->get_widget("entry_port", entry_port);
    refBuilder->get_widget("button_connect", button_connect);
    //entry_ip->signal_key_press_event().connect( sigc::mem_fun(this, &FixedConnect::on_key_press) );
    //entry_ip->add_events(Gdk::KEY_PRESS_MASK | Gdk::KEY_RELEASE_MASK);
}

bool FixedConnect::on_key_press(GdkEventKey* event)
{
    if (event->type == GDK_KEY_PRESS && event->keyval == GDK_KEY_ISO_Enter)
        button_connect->clicked();

    return true;
}