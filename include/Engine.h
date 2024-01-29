#ifndef ENGINE_H
#define ENGINE_H
struct game_loop
{
    void(*begin_play)();
    void(*tick)(float *delta_time);
    void(*end_tick)();
    int is_ticking;
    //void(*begin_play)(struct *game_loop);
    //void(*tick)(struct *game_loop, const float delta_time);
};

void startloop(struct game_loop *loop, float *delta_time);
#endif //ENGINE_H