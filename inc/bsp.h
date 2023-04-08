/* 2023 - Carmela Colqui <carmela.colqui@gmail.com>
 */

#ifndef BSP_H
#define BSP_H

/** \brief Board hardware abstraction declarations
 **
 ** \addtogroup hal HAL
 ** \brief Hardware abstraction layer
 ** @{ */

/* === Headers files inclusions ================================================================ */

#include "digital.h"
#include <stdint.h>

/* === Cabecera C++ ============================================================================ */

#ifdef __cplusplus
extern "C"
{
#endif

    /* === Public macros definitions =============================================================== */

    /* === Public data type declarations =========================================================== */

    typedef struct board_s
    {
        digital_output_t led_azul;
        digital_output_t led_rojo;
        digital_output_t led_amarillo;
        digital_output_t led_verde;

        digital_input_t boton_prueba;
        digital_input_t boton_cambiar;
        digital_input_t boton_prender;
        digital_input_t boton_apagar;
    } *board_t;

    /* === Public variable declarations ============================================================ */

    /* === Public function declarations ============================================================ */

    board_t BoardCreate(void);

    void SisTick_Init(uint16_t ticks);

    /* === End of documentation ==================================================================== */

#ifdef __cplusplus
}
#endif

/** @} End of module definition for doxygen */

#endif /* BSP_H */