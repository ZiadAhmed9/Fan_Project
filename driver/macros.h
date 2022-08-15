/*
 * macros.h
 *
 *  Created on: Aug 15, 2022
 *      Author: Ismailia laptop
 */

#ifndef MACROS_H_
#define MACROS_H_
#define SET_BIT(REG,BIT_NUM) (REG|=(1<<BIT_NUM))
#define CLEAR_BIT(REG,BIT_NUM) (REG&=(~(1<<BIT_NUM)))
#define TOGGLE_BIT(REG,BIT_NUM) (REG^=(1<<BIT_NUM)))
#define CHECK_IF_SET(REG,BIT_NUM) (REG&(1<<BIT_NUM))
#define CHECK_IF_CLEAR(REG,BIT_NUM) (!(REG&(1<<bit_num))




#endif /* MACROS_H_ */
