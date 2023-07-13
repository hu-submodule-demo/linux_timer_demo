/**
 * @file      : main.c
 * @brief     : 程序入口文件
 * @author    : huenrong (huenrong1028@outlook.com)
 * @date      : 2023-07-13 21:35:42
 *
 * @copyright : Copyright (c) 2023 huenrong
 *
 * @history   : date        author          description
 *              2023-07-13  huenrong        创建文件
 *
 */

#include <stdio.h>
#include <unistd.h>

#include "linux_timer.h"

static void test_timer1_cb(linux_timer_t *linux_timer)
{
    printf("this is %s, user_data: %d\n", __FUNCTION__, *(uint8_t *)linux_timer->user_data);
}

static void test_timer2_cb(linux_timer_t *linux_timer)
{
    printf("this is %s\n", __FUNCTION__);
}

/**
 * @brief  : 程序入口
 * @param  : argc: 输入参数, 参数个数
 * @param  : argv: 输入参数, 参数列表
 * @return : 成功: 0
 *           失败: 其它
 */
int main(int argc, char *argv[])
{
    uint8_t user_data = 10;

    linux_timer_t test_timer1 = {0};
    linux_timer_create(&test_timer1, test_timer1_cb, 1000, &user_data);
    linux_timer_set_repeat_count(&test_timer1, 5);

    linux_timer_t test_timer2 = {0};
    linux_timer_create(&test_timer2, test_timer2_cb, 1000, NULL);

    while (true)
    {
        sleep(1);
    }

    return 0;
}
