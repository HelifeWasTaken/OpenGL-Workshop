#ifndef EAB1973B_3615_4C8C_8FD9_3C2F43EE7FCC
#define EAB1973B_3615_4C8C_8FD9_3C2F43EE7FCC

typedef int(init_cb_t)();
typedef void(update_cb_t)(double);
typedef void(render_cb_t)();
typedef void(cleanup_cb_t)();

void workshop_on_init(init_cb_t*);
void workshop_on_update(update_cb_t*);
void workshop_on_render(render_cb_t*);
void workshop_on_cleanup(cleanup_cb_t*);
int workshop_start(const char *title, int width, int height);

#endif /* EAB1973B_3615_4C8C_8FD9_3C2F43EE7FCC */
