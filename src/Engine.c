#include "Engine.h"
void startloop(struct game_loop *loop, float *delta_time){
    loop->begin_play();
    while(loop->is_ticking > 0){
        loop->tick(delta_time);
    }
    loop->end_tick();
}
