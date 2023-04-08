/* 2023 - Carmela Colqui <carmela.colqui@gmail.com>
 *
 */

#ifndef DIGITAL_H
#define DIGITAL_H

/** \brief Digital inputs/outputs declarations
 **
 ** \addtogroup hal HAL
 ** \brief Hardware abstraction layer
 ** @{ */

/* === Headers files inclusions ================================================================ */

#include <stdbool.h>
#include <stdint.h>

/* === Cabecera C++ ============================================================================ */

#ifdef __cplusplus
extern "C"
{
#endif

    /* === Public macros definitions =============================================================== */

    //! Referencia a un descriptor para gestionar una entrada digital
    typedef struct digital_input_s *digital_input_t;

    //! Referencia a un descriptor para gestionar una salida digital
    typedef struct digital_output_s *digital_output_t;

    /* === Public data type declarations =========================================================== */

    /* === Public variable declarations ============================================================ */

    /* === Public function declarations ============================================================ */

    /**
     * @brief Metodo para crear una entrada digital
     *
     * @param   port        Puerto GPIO que contine a la salida
     * @param   pin         Numero de terminal del puerto GPIO asignado a la salida
     * @param   inverted    Badera que indica que la entrada trabaja con logica invertida
     * @return  digital_output_t    Puntero al descriptor de la salida creada
     */
    digital_input_t DigitalInputCreate(uint8_t port, uint8_t pin, bool inverted);

    /**
     * @brief Metodo para consultar el estado de una entrada digital
     *
     * @param   input   Puntero al descriptor de la entrada
     * @return  true    La entrada esta activa
     * @return  false   La entrada esta inactiva
     */
    bool DigitalInputGetState(digital_input_t input);

    /**
     * @brief Metodo para consultar cambios en el estado de una entrada digital
     *
     * @param   input   Puntero al descriptor de la entrada
     * @return  true    La entrada tuvo cambios desde la ultima llamada
     * @return  false   La entrada no tuvo cambios desde la ultima llamada
     */
    bool DigitalInputHasChanged(digital_input_t input);

    /**
     * @brief Metodo para consultar activaciones en una entrada digital
     *
     * @param   input   Puntero al descriptor de la entrada
     * @return  true    La entrada tuvo activaciones desde la ultima llamada
     * @return  false   La entrada no tuvo activaciones desde la ultima llamada
     */
    bool DigitalInputHasActivated(digital_input_t input);

    /**
     * @brief Metodo para consultar descativaciones en una entrada digital
     *
     * @param   input   Puntero al descriptor de la entrada
     * @return  true    La entrada tuvo descativaciones desde la ultima llamada
     * @return  false   La entrada no tuvo descativaciones desde la ultima llamada
     */
    bool DigitalInputHasDeactivated(digital_input_t input);

    /**
     * @brief Metodo para crear una salida digital
     *
     * @param   port    Puerto GPIO que contine a la salida
     * @param   pin     Numero de terminal del puerto GPIO asignado a la salida
     * @return  digital_output_t    Puntero al descriptor de la salida creada
     */
    digital_output_t DigitalOutputCreate(uint8_t port, uint8_t pin);

    /**
     * @brief Metodo para prender una salida digital
     *
     * @param   output  Puntero al descriptor de la salida
     */
    void DigitalOutputActivate(digital_output_t output);

    /**
     * @brief Metodo para apagar una salida digital
     *
     * @param   output  Puntero al descriptor de la salida
     */
    void DigitalOutputDeactivate(digital_output_t output);

    /**
     * @brief Metodo para invertir el estado de una salida digital
     *
     * @param   output  Puntero al descriptor de la salida
     */
    void DigitalOutputToggle(digital_output_t output);

    /* === End of documentation ==================================================================== */

#ifdef __cplusplus
}
#endif

/** @} End of module definition for doxygen */

#endif /* DIGITAL_H */