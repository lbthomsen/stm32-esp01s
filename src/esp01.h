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

#define ESP01_WIFI_MODE_STA 1
#define ESP01_WIFI_MODE_AP 2
#define ESP01_WIFI_MODE_APSTA 3

#define ESP01_SNTP_DISABLED 0
#define ESP01_SNTP_ENABLED 1

typedef struct {
    UART_HandleTypeDef *uart;
} esp01_handler_t;

typedef enum {
    ESP01_OK,
    ESP01_Error
} esp01_result_t;

esp01_result_t esp01_init(esp01_handler_t *esp01, UART_HandleTypeDef *uart);
esp01_result_t esp01_reset(esp01_handler_t *esp01);
esp01_result_t esp01_set_wifi_mode(esp01_handler_t *esp01, uint8_t mode);
esp01_result_t esp01_wifi_connect(esp01_handler_t *esp01, char *ssid, char *pwd);
esp01_result_t esp01_set_ntp(esp01_handler_t *esp01, uint8_t config, uint8_t timezone, char *ntp);
esp01_result_t esp01_get_ntp_time(esp01_handler_t *esp01);

void esp01_receive(esp01_handler_t *esp01, char ch);

#endif /* ESP01_H_ */
