#ifndef __DOOR_H__
#define __DOOR_H__

#define DOOR_ID             "6612c42ee056da36ad21269f"
#define DOOR_GPIO           4

typedef enum {
    DOOR_STATE_CLOSE = 0,
    DOOR_STATE_OPEN = 1
} Door_State;

void doorInit(); // (Ngoc)
void doorSetState(Door_State state); // (Tung | Nguyen)
void doorEventHandler(char *query); // (Ngoc)

#endif