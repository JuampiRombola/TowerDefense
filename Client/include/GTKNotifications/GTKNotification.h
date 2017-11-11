//
// Created by tino on 11/11/17.
//

#ifndef TOWERDEFENSE_GTKNOTIFICATION_H_H
#define TOWERDEFENSE_GTKNOTIFICATION_H_H

class GTKRunner;

class GTKNotification {
public:
    GTKNotification();
    virtual ~GTKNotification() = 0;
    virtual void Execute(GTKRunner& runner) = 0;
};



#endif //TOWERDEFENSE_GTKNOTIFICATION_H
