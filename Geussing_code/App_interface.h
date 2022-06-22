/*
 * File Name  : Guessing Game
 * Version    : 1.00
 * Description: this game generate random number and the player guess what the number
 *             using switch and number of presses represent the number
 *
 * Author     : Alaa Abdelrahman
 */

#ifndef APP_INTERFACE_H_
#define APP_INTERFACE_H_

#define LOWER_LIMIT   1

#define UPPER_LIMIT   15




void App_Init();

void App_GenerateRandom();

void App_SetTimeOut();

void App_GetNumber();

void App_Display();

void App_Update();

#endif
