/* 2023 - Carmela Colqui <carmela.colqui@gmail.com>
 *
 *
 */

/** @file EITI_TPN° 8
 **
 ** @brief TPN° 8  - FreeRTOS
 **
 ** Ejemplo de un led parpadeando utilizando la capa de abstraccion de
 ** hardware y con sistema operativo FreeRTOS.
 **
 **
 ** @defgroup ejemplos Proyectos de ejemplo
 ** @brief Proyectos de ejemplo de la Especialización en Sistemas Embebidos
 ** @{
 */

/* === Inclusiones de cabeceras ============================================ */
#include "FreeRTOS.h"
#include "bsp.h"
#include "task.h"
#include <stdbool.h>

/* === Definicion y Macros ================================================= */

/* === Declaraciones de tipos de datos internos ============================ */

typedef struct parametros_s
{
    digital_output_t led;
    uint16_t periodo;
    digital_input_t tecla;
} *parametros_t;

/* === Declaraciones de funciones internas ================================= */

/* === Definiciones de variables internas ================================== */

static board_t board;

/* === Definiciones de variables externas ================================== */

/* === Definiciones de funciones internas ================================== */

void Blinking(void *parameters)
{

    parametros_t parametros = (parametros_t)parameters;

    while (true)
    {
        DigitalOutputToggle(parametros->led);
        vTaskDelay(pdMS_TO_TICKS(parametros->periodo));
    }
}

void BlinkingAmarillo(void *parameters)
{

    parametros_t parametros = (parametros_t)parameters;

    TickType_t ultimo_valor;

    ultimo_valor = xTaskGetTickCount();

    while (true)
    {

        DigitalOutputToggle(parametros->led);
        vTaskDelayUntil(&ultimo_valor, pdMS_TO_TICKS(parametros->periodo));
    }
}

void Teclado(void *parameters)
{

    parametros_t parametros = (parametros_t)parameters;
    TaskHandle_t tarea;
    eTaskState estado;

    tarea = xTaskGetHandle("Rojo");
    estado = eTaskGetState(tarea); /*Returns as an enumerated type the state in which a task existed at the time eTaskGetState() was executed.*/

    while (true)
    {
        if (parametros->tecla == board->boton_prueba)
        {

            if (DigitalInputHasActivated(parametros->tecla))
            {
                DigitalOutputToggle(parametros->led);
            }
        }
        if (parametros->tecla == board->boton_prender)
        {

            if (DigitalInputHasActivated(parametros->tecla) && estado == eSuspended)
            {
                vTaskResume(tarea);
            }
            else if (DigitalInputHasActivated(parametros->tecla) && estado == eReady)
            {
                vTaskSuspend(tarea);
            }
        }
        vTaskDelay(pdMS_TO_TICKS(parametros->periodo)); // eliminamos rebote del teclado
    }
}
/* === Definiciones de funciones externas ================================== */

/** @brief Función principal del programa
 **
 ** @returns 0 La función nunca debería termina
 **
 ** @remarks En un sistema embebido la función main() nunca debe terminar.
 **          El valor de retorno 0 es para evitar un error en el compilador.
 */
int main(void)
{

    static struct parametros_s parametros[4];
    /* Inicializaciones y configuraciones de dispositivos */
    board = BoardCreate();

    parametros[0].led = board->led_rojo;
    parametros[0].periodo = 500;

    parametros[1].led = board->led_verde;
    parametros[1].periodo = 750;

    parametros[2].led = board->led_amarillo;
    parametros[2].periodo = 250;

    parametros[3].led = board->led_azul;
    parametros[3].periodo = 250;
    parametros[3].tecla = board->boton_prueba;

    parametros[4].tecla = board->boton_prender;
    parametros[4].periodo = 250;

    /* Creación de las tareas */
    xTaskCreate(Blinking, "Rojo", configMINIMAL_STACK_SIZE, &parametros[0], tskIDLE_PRIORITY + 1, NULL);
    xTaskCreate(Blinking, "Verde", configMINIMAL_STACK_SIZE, &parametros[1], tskIDLE_PRIORITY + 2, NULL);
    xTaskCreate(BlinkingAmarillo, "Amarillo", configMINIMAL_STACK_SIZE, &parametros[2], tskIDLE_PRIORITY + 3, NULL);
    xTaskCreate(Teclado, "Azul", configMINIMAL_STACK_SIZE, &parametros[3], tskIDLE_PRIORITY + 4, NULL);
    xTaskCreate(Teclado, "Teclado", configMINIMAL_STACK_SIZE, &parametros[4], tskIDLE_PRIORITY + 4, NULL);

    /* Arranque del sistema operativo */
    vTaskStartScheduler();

    /* vTaskStartScheduler solo retorna si se detiene el sistema operativo */
    while (1)
    {
    };

    /* El valor de retorno es solo para evitar errores en el compilador*/
    return 0;
}
/* === Ciere de documentacion ============================================== */
/** @} Final de la definición del modulo para doxygen */