#include "hal_data.h"
#include <stdint.h>

#define PRCR        (*(volatile uint16_t *)0x4001E3FEUL)
#define HOCOCR      (*(volatile uint8_t  *)0x4001E036UL)
#define HOCOCR2     (*(volatile uint8_t  *)0x4001E037UL)
#define OSCSF       (*(volatile uint8_t  *)0x4001E03CUL)
#define SCKSCR      (*(volatile uint8_t  *)0x4001E026UL)
#define SCKDIVCR    (*(volatile uint32_t *)0x4001E020UL)

#define PWPR        (*(volatile uint8_t  *)0x40080D03UL)

#define PFS103      (*(volatile uint32_t *)0x4008084CUL)
#define PFS104      (*(volatile uint32_t *)0x40080850UL)
#define PFS105      (*(volatile uint32_t *)0x40080854UL)
#define PODR1       (*(volatile uint16_t *)0x40080020UL)
#define PDR1        (*(volatile uint16_t *)0x40080022UL)
#define PIDR1       (*(volatile uint16_t *)0x40080026UL)


#define SW2_PIN     3U      /* P103 */
#define LED_PIN     4U      /* P104 */
#define SW1_PIN     5U      /* P105 */

static void clock_init(void)
{
    PRCR = 0xA501U;
    HOCOCR2 &= (uint8_t)~0x03U;
    HOCOCR &= (uint8_t)~(1U << 0);


    while ((OSCSF & (1U << 0)) == 0U)
    {
    }
    SCKSCR &= (uint8_t)~0x07U;
    SCKDIVCR &= ~((0x7UL << 28) |
                  (0x7UL << 24) |
                  (0x7UL << 12) |
                  (0x7UL << 8)  |
                  (0x7UL << 4)  |
                  (0x7UL << 0));

    /* Lock clock registers */
    PRCR = 0xA500U;
}

static void gpio_init(void)
{
    PWPR = 0x00U;
    PWPR = 0x40U;
    PFS103 = (1UL << 4);
    PFS104 = 0x00UL;
    PFS105 = (1UL << 4);
    PDR1 &= (uint16_t)~(1U << SW2_PIN);
    PDR1 |= (uint16_t)(1U << LED_PIN);
    PDR1 &= (uint16_t)~(1U << SW1_PIN);
    PODR1 &= (uint16_t)~(1U << LED_PIN);
    PWPR = 0x80U;
}

int main(void)
{
    clock_init();
    gpio_init();
    while (1)
    {
        uint8_t sw1;
        uint8_t sw2;
        uint8_t xor_result;
        sw1 = ((PIDR1 & (uint16_t)(1U << SW1_PIN)) == 0U)? 1U: 0U;
        sw2 = ((PIDR1 & (uint16_t)(1U << SW2_PIN)) == 0U)? 1U: 0U;
        xor_result = sw1 ^ sw2;
        if (xor_result != 0U)
        {
            PODR1 |= (uint16_t)(1U << LED_PIN);
        }
        else
        {
            PODR1 &= (uint16_t)~(1U << LED_PIN);
        }
    }

    return 0;
}