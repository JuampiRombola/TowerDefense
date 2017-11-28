//
// Created by tino on 27/11/17.
//

#ifndef TOWERDEFENSE_FIXEDCONNECT_H
#define TOWERDEFENSE_FIXEDCONNECT_H


#include <gtkmm/builder.h>
#include <gtkmm/entry.h>
#include <gtkmm/button.h>
#include <gtkmm/fixed.h>

class FixedConnect {
    bool on_key_press(GdkEventKey* event);

public:
    FixedConnect();
    ~FixedConnect();
    Gtk::Fixed* fixed;
    Gtk::Button* button_connect;
    Gtk::Entry* entry_ip;
    Gtk::Entry* entry_port;

    void Set(const Glib::RefPtr<Gtk::Builder>& refBuilder);
};


#endif //TOWERDEFENSE_FIXEDCONNECT_H
