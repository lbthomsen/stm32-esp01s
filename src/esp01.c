/**
 ******************************************************************************
 * @file           : esp01.c
 * @brief          : ESP01 Library Source
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

#include "main.h"
#include <stdio.h>
#include <string.h>
#include "esp01.h"

esp01_result_t esp01_init(esp01_handler_t *esp01, UART_HandleTypeDef *uart) {
    esp01_result_t res = ESP01_OK;

    esp01->uart = uart;

    char txbuf[32];

    sprintf(txbuf, "ATE1\r\n");

    if (HAL_UART_Transmit(esp01->uart, (uint8_t *)&txbuf, strlen(txbuf), 100) != HAL_OK) {
        printf("HAL Transmit Error\n");
        return ESP01_Error;
    }
    //HAL_Delay(100);

//    sprintf(txbuf, "AT+GMR\r\n");
//    HAL_UART_Transmit(esp01->uart, (uint8_t *)&txbuf, strlen(txbuf), 100);

    return res;
}

void esp01_receive(char ch) {

    static char str[256] = "";

    switch (ch) {
    case '\r':
        printf("Got string: %s\n", str);
        str[0] = 0;
        break;
    case '\n':
        break;
    default:
        strncat(str, &ch, 1);
    }

}
