#include "hal_data.h"

#define PRCR        (*(volatile unsigned short *)0x4001E3FEUL)

#define HOCOCR      (*(volatile unsigned char  *)0x4001E036UL)
#define HOCOCR2     (*(volatile unsigned char  *)0x4001E037UL)
#define OSCSF       (*(volatile unsigned char  *)0x4001E03CUL)

#define SCKSCR      (*(volatile unsigned char  *)0x4001E026UL)
#define SCKDIVCR    (*(volatile unsigned long  *)0x4001E020UL)

#define MSTPCRE     (*(volatile unsigned long *)0x40084010UL)

#define PDR1        (*(volatile unsigned short *)0x40080022UL)
#define PODR1       (*(volatile unsigned short *)0x40080020UL)

#define LED_PIN     12U

#define GPT0_FLAG   (1UL << 6)

static void clock_init(void)
{
    PRCR = 0xA501U;
    HOCOCR2 &= (unsigned char)~0x03U;
    HOCOCR &= (unsigned char)~(1U << 0);
    while ((OSCSF & (1U << 0)) == 0U)
    {
        /* Wait */
    }
    SCKSCR &= (unsigned char)~0x07U;
    SCKDIVCR &= ~((0x7UL << 28) |
                  (0x7UL << 24) |
                  (0x7UL << 12) |
                  (0x7UL << 8)  |
                  (0x7UL << 4)  |
                  (0x7UL << 0));

    /* Lock clock-generation registers */
    PRCR = 0xA500U;
}

int main(void)
{
    unsigned int count = 0U;

    clock_init();
    PDR1 |= (unsigned short)(1U << LED_PIN);
    PODR1 &= (unsigned short)~(1U << LED_PIN);
    PRCR = 0xA501U;

    /* Enable GPT0 module */
    MSTPCRE &= ~(1UL << 31);

    /* Lock protected registers */
    PRCR = 0xA500U;

    R_GPT0->GTCR_b.CST = 0U;
    R_GPT0->GTCNT = 0UL;
    /*=======================================================
     * 6. SET GPT0 PERIOD
     *
     * PCLKD = 16 MHz
     *
     * Prescaler = /32
     *
     * GPT clock:
     *
     * 16,000,000 / 32
     * = 500,000 Hz
     *
     * One count:
     *
     * 1 / 500,000
     * = 2 us
     *
     * For 1 second:
     *
     * 1 second / 2 us
     * = 500,000 counts
     *
     * GTPR = 500,000 - 1
     *      = 499,999
     *=======================================================*/

    R_GPT0->GTPR = 499999UL;

    R_GPT0->GTCR =
            (5UL << R_GPT0_GTCR_TPCS_Pos) |
            (0UL << R_GPT0_GTCR_MD_Pos);


    R_GPT0->GTST &= ~GPT0_FLAG;

    R_GPT0->GTCR_b.CST = 1U;

    while (1)
    {

        if ((R_GPT0->GTST & GPT0_FLAG) != 0UL)
        {
            R_GPT0->GTST &= ~GPT0_FLAG;

            count++;

            if (count >= 60U)
            {
                count = 0U;

                PODR1 ^= (unsigned short)(1U << LED_PIN);
            }
        }
    }


    return 0;
}