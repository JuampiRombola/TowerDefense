#include "DoNothingButton.h"

DoNothingButton::DoNothingButton(int id, int horda, SDL_Texture *texture,
                                 MousePosition &mousePosition,
                                 Renderer &renderer) : Button(id, 0,
                                                              200 + horda * 200,
                                                              100, 100, texture,
                                                              mousePosition,
                                                              renderer) {}

void DoNothingButton::click() {}
