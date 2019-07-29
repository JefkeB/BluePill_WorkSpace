#ifndef INC_TOUCH_H_
#define INC_TOUCH_H_


//
//
//
extern void touchInit();
extern void touchProc();
extern void touchInput_sync();
extern uint8_t *touchPtr_Get();
extern uint8_t *touchQualityKeyPtr_Get();

#endif
