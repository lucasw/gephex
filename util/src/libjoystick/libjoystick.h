#ifndef INCLUDED_LIB_JOYSTICK_H
#define INCLUDED_LIB_JOYSTICK_H

/**
 * Simple Joystick lib.
 */
struct Joystick;


/**
 * Must be called before any joystick function is used.
 */
void joystick_init_core();

/**
 * Returns the number of joysticks.
 */
int joystick_get_num_devices();

struct Joystick* joystick_open(int id);
void joystick_close(struct Joystick* self);

const char* joystick_get_name(int id);

int joystick_get_num_axes(const struct Joystick* self);

int joystick_get_num_buttons(const struct Joystick* self);

/**
 * Polls the joystick driver for new data.
 * Must be called before get_axis or get_button.
 */
int joystick_poll(struct Joystick* self);

void joystick_recalibrate(struct Joystick* self);

/**
 * Returns a value between 0 and 1.
 * 0.5 is the center value.
 * If axis is >= get_num_axes(self), the return value is undefined
 */
double joystick_get_axis(const struct Joystick* self, int axis);

/**
 * Returns a value between 0 (not pressed) and 1 (pressed).
 * If button is >= get_num_buttons(self), the return value is undefined
 */
int joystick_get_button(const struct Joystick* self, int button);

#endif


