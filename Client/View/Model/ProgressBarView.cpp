//
// Created by juampi on 11/21/17.
//

#include "ProgressBarView.h"
#include "../../../Common/Lock.h"

ProgressBarView::ProgressBarView(Renderer &r, SDL_Texture *t,
                                 int srcW, int srcH,
                                 int dstW, int dstH) :
        renderer(r), bar(t, r),
        srcW(srcW), srcH(srcH),
        dstW(dstW), dstH(dstH),
        total(1), part(0) {
    bar.setSourceRect(0, 0, srcW, srcH);
    bar.setDestRect(0, 0, dstW, dstH);
}


void ProgressBarView::setDestXY(int x, int y) {
    bar.setDestXY(x, y);
}

void ProgressBarView::setTotal(Uint32 t) {
    Lock(this->m);
    if (total == 0) return;
    total = t;
}

void ProgressBarView::setPart(Uint32 p) {
    Lock(this->m);
    part = p;
}

void ProgressBarView::draw() {
    Lock(this->m);
    if (part >= total) {
        bar.setSourceW(srcW);
        bar.setDestW(dstW);
    } else {
        bar.setSourceW((part * srcW) / total);
        bar.setDestW((part * dstW) / total);
    }

    bar.drawEuclidian();
}

bool ProgressBarView::isFull() {
    Lock(this->m);
    return part >= total;
}

void ProgressBarView::addPart(Uint32 p) {
    Lock(this->m);
    part += p;
}
