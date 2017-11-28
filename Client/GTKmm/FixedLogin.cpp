//
// Created by tino on 27/11/17.
//

#include "FixedLogin.h"

FixedLogin::FixedLogin() {

}

FixedLogin::~FixedLogin(){

}

void FixedLogin::Set(const Glib::RefPtr<Gtk::Builder> &refBuilder) {
    refBuilder->get_widget("fixed_login", fixed);
    refBuilder->get_widget("entry_name", entry_name);
    refBuilder->get_widget("button_login", button_login);
}