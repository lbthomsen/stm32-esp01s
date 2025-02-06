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

#define MAX_DELAY 1000 // in ms - so 1 s
#define MAX_STR 128

char last_str[MAX_STR];
char txbuf[MAX_STR];

// Private functions
esp01_result_t wait_for_string(char *str, uint32_t timeout) {
    uint32_t end_time = uwTick + timeout;
    while (uwTick <= end_time) {
        if (strcmp(str, last_str) == 0) return ESP01_OK;
    }
    return ESP01_Error;
}

// Public functions

esp01_result_t esp01_reset(esp01_handler_t *esp01) {
    esp01_result_t res = ESP01_OK;

    sprintf(txbuf, "AT+RST\r\n");

    if (HAL_UART_Transmit(esp01->uart, (uint8_t *)&txbuf, strlen(txbuf), 100) != HAL_OK) {
        printf("HAL Transmit Error\n");
        return ESP01_Error;
    }

    if (wait_for_string("OK", 5000) != ESP01_OK) return ESP01_Error;

    return res;
}

esp01_result_t esp01_init(esp01_handler_t *esp01, UART_HandleTypeDef *uart) {
    esp01_result_t res = ESP01_OK;

    esp01->uart = uart;

    sprintf(txbuf, "AT\r\n");

    if (HAL_UART_Transmit(esp01->uart, (uint8_t *)&txbuf, strlen(txbuf), 100) != HAL_OK) {
        printf("HAL Transmit Error\n");
        return ESP01_Error;
    }

    if (wait_for_string("OK", 1000) != ESP01_OK) return ESP01_Error;

    sprintf(txbuf, "AT+GMR\r\n");
    HAL_UART_Transmit(esp01->uart, (uint8_t *)&txbuf, strlen(txbuf), 100);

    if (wait_for_string("OK", 1000) != ESP01_OK) return ESP01_Error;

    return res;
}

void esp01_receive(char ch) {

    static char str[256] = "";

    switch (ch) {
    case '\r':
        printf("Got string: %s\n", str);
        strncpy(last_str, str, MAX_STR - 1);
        str[0] = 0;
        break;
    case '\n':
        break;
    default:
        strncat(str, &ch, 1);
    }

}


