//! @file
#ifndef FSENSOR_H
#define FSENSOR_H

#include <inttypes.h>


//! minimum meassured chunk length in steps
extern int16_t fsensor_chunk_len;
// enable/disable flag
extern bool fsensor_enabled;
// not responding flag
extern bool fsensor_not_responding;
//enable/disable quality meassurement
extern bool fsensor_oq_meassure_enabled;


//! @name save restore printing
//! @{
extern void fsensor_stop_and_save_print(void);
extern void fsensor_restore_print_and_continue(void);
//! @}

//! initialize
extern void fsensor_init(void);

//! @name enable/disable
//! @{
extern bool fsensor_enable(void);
extern void fsensor_disable(void);
//! @}

//autoload feature enabled
extern bool fsensor_autoload_enabled;
extern void fsensor_autoload_set(bool State);

extern void fsensor_update(void);
#ifdef PAT9125
//! setup pin-change interrupt
extern void fsensor_setup_interrupt(void);

//! @name autoload support
//! @{

extern void fsensor_autoload_check_start(void);
extern void fsensor_autoload_check_stop(void);
#endif //PAT9125
extern bool fsensor_check_autoload(void);
//! @}

//! @name optical quality measurement support
//! @{
extern void fsensor_oq_meassure_set(bool State);
extern void fsensor_oq_meassure_start(uint8_t skip);
extern void fsensor_oq_meassure_stop(void);
extern bool fsensor_oq_result(void);
//! @}

//! @name callbacks from stepper
//! @{
extern void fsensor_st_block_chunk(int cnt);

// There's really nothing to do in block_begin: the stepper ISR likely has
// called us already at the end of the last block, making this integration
// redundant. LA1.5 might not always do that during a coasting move, so attempt
// to drain fsensor_st_cnt anyway at the beginning of the new block.
#define fsensor_st_block_begin(rev) fsensor_st_block_chunk(0)
//! @}

#endif //FSENSOR_H
