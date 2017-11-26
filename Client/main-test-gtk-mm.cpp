#include <gtkmm.h>
#include <iostream>

int main(int argc, char** argv) {
    auto app = Gtk::Application::create(argc, argv);
    auto refBuilder = Gtk::Builder::create();
    refBuilder->add_from_file("../Client/Launchermm.glade");

    Gtk::Window* w;
    refBuilder->get_widget("window_global", w);
    if (w){
        w->set_default_size(960, 540);
        w->show_all();
        return app->run(*w);
    }
    return -1;
}