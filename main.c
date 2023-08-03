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
#include <sys/time.h>

#include "linux_timer.h"

/**
 * @brief  获取当前毫秒时间
 * @param  msec: 输出参数, 获取到的毫秒时间
 * @return true : 成功
 * @return false: 失败
 */
bool get_current_msec(uint64_t *msec)
{
    struct timeval tv = {0};
    // 获取到的秒
    uint64_t sec = 0;
    // 获取到的微秒
    uint64_t usec = 0;

    if (!msec)
    {
        return false;
    }

    if (0 != gettimeofday(&tv, NULL))
    {
        return false;
    }

    sec = tv.tv_sec;
    usec = tv.tv_usec;

    *msec = ((sec * 1000) + (usec / 1000));

    return true;
}

static void test_timer1_cb(const linux_timer_t *linux_timer)
{
    uint64_t current_msec = 0;
    get_current_msec(&current_msec);

    printf("[%ld] this is %s, user_data: %d\n", current_msec, __FUNCTION__, *(uint8_t *)linux_timer->user_data);
}

static void test_timer2_cb(const linux_timer_t *linux_timer)
{
    uint64_t current_msec = 0;
    get_current_msec(&current_msec);

    printf("[%ld] this is %s\n", current_msec, __FUNCTION__);
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

    uint64_t current_msec = 0;
    get_current_msec(&current_msec);
    printf("[%ld] create timer1\n", current_msec);
    linux_timer_create(&test_timer1, test_timer1_cb, 1000, &user_data);
    linux_timer_ready(&test_timer1);
    linux_timer_set_repeat_count(&test_timer1, 5);

    linux_timer_t test_timer2 = {0};
    linux_timer_create(&test_timer2, test_timer2_cb, 1000, NULL);

    sleep(3);
    get_current_msec(&current_msec);
    printf("[%ld] pause timer1\n", current_msec);
    linux_timer_pause(&test_timer2);

    sleep(3);
    get_current_msec(&current_msec);
    printf("[%ld] resume timer1\n", current_msec);
    linux_timer_resume(&test_timer2);

    while (true)
    {
        sleep(1);
    }

    return 0;
}
