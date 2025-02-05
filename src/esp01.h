/**
 ******************************************************************************
 * @file           : esp01.h
 * @brief          : ESP01 Library Header
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 Lars Boegild Thomsen <lbthomsen@gmail.com>
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#ifndef ESP01_H_
#define ESP01_H_

typedef struct {
    UART_HandleTypeDef *uart;
} esp01_handler_t;

typedef enum {
    ESP01_OK,
    ESP01_Error
} esp01_result_t;

esp01_result_t esp01_init(esp01_handler_t *esp01, UART_HandleTypeDef *uart);

void esp01_receive(char ch);

#endif /* ESP01_H_ */
