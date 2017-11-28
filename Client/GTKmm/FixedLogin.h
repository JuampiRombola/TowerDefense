//
// Created by tino on 27/11/17.
//

#ifndef TOWERDEFENSE_FIXEDLOGIN_H
#define TOWERDEFENSE_FIXEDLOGIN_H


#include <gtkmm/fixed.h>
#include <gtkmm/builder.h>
#include <gtkmm/entry.h>
#include <gtkmm/button.h>

class FixedLogin {
public:
    FixedLogin();
    ~FixedLogin();

    Gtk::Fixed *fixed;
    Gtk::Entry *entry_name;
    Gtk::Button *button_login;

    void Set(const Glib::RefPtr<Gtk::Builder>& refBuilder);
};


#endif //TOWERDEFENSE_FIXEDLOGIN_H
