

#include <stdint.h>
#include <xbasic_types.h>
#include <stdio.h>
#include <xil_types.h>
#include "xparameters.h"
#include "xbram.h"
#include "logging.h"
#include "crc_0x43.h"

/* Defines */
#define STERING_WHEEL_POSITION_INCREMENTAL_ADDR 0u
#define STERING_WHEEL_FFB_MAGNITUDE_ADDR        4u
#define STERING_WHEEL_FFB_SIGN_ADDR             8u
#define DATA_0_ADDR                             12u
#define DATA_1_ADDR                             16u
#define STERING_WHEEL_POSITION_BISSC_ADDR       20u
#define STERING_WHEEL_ROTATION_ADDR             24u

/* Local variables */
XBram Bram_0; /* The Instance of the BRAM Driver */
XBram Bram_1; /* The Instance of the BRAM Driver */

/* Fordward declaration */
int initBram();
void _initializeECC(XBram_Config *ConfigPtr, u32 EffectiveAddr);
int32_t readPosition();

/* Public methods */

int initBramModules(XBram* bram, UINTPTR base_addr, Xboolean selfTest)
{
	int Status;
	XBram_Config *ConfigPtr;

    #ifdef SDT
        LOG("XBram %u LookupConfig SDT DEFINED\n\r", base_addr);
    #endif

    ConfigPtr = XBram_LookupConfig(base_addr);
    if (ConfigPtr == (XBram_Config *) NULL) {
        LOG("XBram %u LookupConfig FAILED\n\r", base_addr);
        return XST_FAILURE;
    }

    Status = XBram_CfgInitialize(bram, ConfigPtr, ConfigPtr->CtrlBaseAddress);
    if (Status != XST_SUCCESS) {
        return XST_FAILURE;
    }

    _initializeECC(ConfigPtr, ConfigPtr->CtrlBaseAddress);

    if (selfTest == TRUE) {
        Status = XBram_SelfTest(bram, 0);
        if (Status != XST_SUCCESS) {
            LOG("XBram %u tested FAILED\n\r", base_addr);
            return XST_FAILURE;
        }
        else {
            LOG("XBram %u tested\n\r", base_addr);
        }
    }

    LOG("XBram %u initialised\n\r", base_addr);
    return XST_SUCCESS;
}

int temp()
{
    int Status;
    XBram_Config *ConfigPtr_0;
    XBram_Config *ConfigPtr_1;


    ConfigPtr_0 = XBram_LookupConfig(XPAR_XBRAM_0_BASEADDR);
    if (ConfigPtr_0 == (XBram_Config *) NULL) {
        return XST_FAILURE;
    }
    Status = XBram_CfgInitialize(&Bram_0, ConfigPtr_0, ConfigPtr_0->CtrlBaseAddress);
    if (Status != XST_SUCCESS) {
        return XST_FAILURE;
    }
    _initializeECC(ConfigPtr_0, ConfigPtr_0->CtrlBaseAddress);
    Status = XBram_SelfTest(&Bram_0, 0);
    if (Status != XST_SUCCESS) {
        return XST_FAILURE;
    }

/*
    ConfigPtr_1 = XBram_LookupConfig(XPAR_XBRAM_1_BASEADDR);
    if (ConfigPtr_1 == (XBram_Config *) NULL) {
        return XST_FAILURE;
    }
    Status = XBram_CfgInitialize(&Bram_1, ConfigPtr_1, ConfigPtr_1->CtrlBaseAddress);
    if (Status != XST_SUCCESS) {
        return XST_FAILURE;
    }
    _initializeECC(ConfigPtr_1, ConfigPtr_1->CtrlBaseAddress);
    Status = XBram_SelfTest(&Bram_1, 0);
    if (Status != XST_SUCCESS) {
        return XST_FAILURE;
    }
*/
}

int initBram(Xboolean selfTest){
    /*
    if (initBramModules(&Bram_0, XPAR_XBRAM_0_BASEADDR, selfTest) != XST_SUCCESS) {
        return XST_FAILURE;
    }
    if (initBramModules(&Bram_1, XPAR_XBRAM_1_BASEADDR, selfTest) != XST_SUCCESS) {
        return XST_FAILURE;
    }
    */
    temp();
    return XST_SUCCESS;
}

void num_a_binario(uint32_t num, char* buffer, size_t size) {
    // Verifica que el buffer tenga suficiente espacio (32 bits + terminador nulo).
    if (size < 33) {
        return;  // O bien puedes manejar el error de otra forma.
    }
    
    for (int i = 31; i >= 0; i--) {
        uint32_t mask = 1U << i;
        buffer[31 - i] = (num & mask) ? '1' : '0';
    }
    buffer[32] = '\0';
}

void print_binary(uint32_t num) {
    for (int i = 31; i >= 0; i--) {
        uint32_t mask = 1U << i;
        xil_printf("%d", (num & mask) ? 1 : 0);

        // Opcional: agregar un espacio cada 8 bits para mejorar la legibilidad
        if (i % 8 == 0 && i != 0)
            xil_printf(" ");
    }
    xil_printf("\n");
}

#define WINDOW_SIZE 1000  // 1000 ms = 1 segundo
uint8_t crc_buffer_0[WINDOW_SIZE] = {0};
int current_index_0 = 0;
int fail_count_0 = 0;
uint32_t fail_count_abs_0 = 0;
uint8_t crc_buffer_1[WINDOW_SIZE] = {0};
int current_index_1 = 0;
int fail_count_1 = 0;
uint32_t fail_count_abs_1 = 0;
uint8_t crc_buffer_2[WINDOW_SIZE] = {0};
int current_index_2 = 0;
int fail_count_2 = 0;
uint32_t fail_count_abs_2 = 0;

void readWheelPositionFromBram(int32_t* position_incremental_enc, int32_t* position_bissc_enc){
    (*position_incremental_enc) = XBram_ReadReg(XPAR_XBRAM_0_BASEADDR, STERING_WHEEL_POSITION_INCREMENTAL_ADDR);
    (*position_bissc_enc) = XBram_ReadReg(XPAR_XBRAM_0_BASEADDR, STERING_WHEEL_POSITION_BISSC_ADDR);

    int32_t data0 = XBram_ReadReg(XPAR_XBRAM_0_BASEADDR, DATA_0_ADDR);
    int32_t data1 = XBram_ReadReg(XPAR_XBRAM_0_BASEADDR, DATA_1_ADDR);
    int32_t data2 = (*position_bissc_enc);
    //print_binary(data0);
#if 0    
    char binario[33] = {};
    char binario_1[33] = {};
    char binario_2[33] = {};
    char polinomio[] = "1000011";
    char input[25] = {};
    char crc_leido[7] = {};
    char crc_computado[7] = {};


    int crc_fail_0 = 0;
    int crc_fail_1 = 0;
    int crc_fail_2 = 0;
    {
        num_a_binario(data0, binario, sizeof(binario));
        strncpy(input, binario + 2, 24);
        strncpy(crc_leido, binario + 26, 6);
        char *crc_raw = pstrCRCGEN(input, polinomio);
        int  i = 0;
        unsigned long long crc_len = strlen(polinomio) - 2;
        for (i = crc_len; i >= 0; i--) {
            if (crc_raw[i] == '1')
                crc_computado[crc_len - i] = '0';
            else if (crc_raw[i] == '0')
                crc_computado[crc_len - i] = '1';
            //printf ("%c", crc_raw[i]);
        }
        free(crc_raw);

        crc_fail_0 = (strcmp(crc_leido, crc_computado) != 0);

        // Resta el valor que se sobrescribirá (el de hace más de 1 segundo)
        fail_count_0 -= crc_buffer_0[current_index_0];

        // Almacena el nuevo resultado (1: fallo, 0: éxito)
        crc_buffer_0[current_index_0] = crc_fail_0;

        // Actualiza el contador global de fallos
        fail_count_0 += crc_fail_0;
        fail_count_abs_0 += crc_fail_0;

        // Avanza el índice de forma circular
        current_index_0 = (current_index_0 + 1) % WINDOW_SIZE;
    }
    {
        num_a_binario(data1, binario_1, sizeof(binario_1));
        strncpy(input, binario_1 + 2, 24);
        strncpy(crc_leido, binario_1 + 26, 6);
        char *crc_raw = pstrCRCGEN(input, polinomio);
        int  i = 0;
        unsigned long long crc_len = strlen(polinomio) - 2;
        for (i = crc_len; i >= 0; i--) {
            if (crc_raw[i] == '1')
                crc_computado[crc_len - i] = '0';
            else if (crc_raw[i] == '0')
                crc_computado[crc_len - i] = '1';
            //printf ("%c", crc_raw[i]);
        }
        free(crc_raw);

        crc_fail_1 = (strcmp(crc_leido, crc_computado) != 0);

        // Resta el valor que se sobrescribirá (el de hace más de 1 segundo)
        fail_count_1 -= crc_buffer_1[current_index_1];

        // Almacena el nuevo resultado (1: fallo, 0: éxito)
        crc_buffer_1[current_index_1] = crc_fail_1;

        // Actualiza el contador global de fallos
        fail_count_1 += crc_fail_1;
        fail_count_abs_1 += crc_fail_1;

        // Avanza el índice de forma circular
        current_index_1 = (current_index_1 + 1) % WINDOW_SIZE;
    }
    
    {
        num_a_binario(data2, binario_2, sizeof(binario_2));
        strncpy(input, binario_2 + 2, 24);
        strncpy(crc_leido, binario_2 + 26, 6);
        char *crc_raw = pstrCRCGEN(input, polinomio);
        int  i = 0;
        unsigned long long crc_len = strlen(polinomio) - 2;
        for (i = crc_len; i >= 0; i--) {
            if (crc_raw[i] == '1')
                crc_computado[crc_len - i] = '0';
            else if (crc_raw[i] == '0')
                crc_computado[crc_len - i] = '1';
            //printf ("%c", crc_raw[i]);
        }
        free(crc_raw);

        crc_fail_2 = (strcmp(crc_leido, crc_computado) != 0);

        // Resta el valor que se sobrescribirá (el de hace más de 1 segundo)
        fail_count_2 -= crc_buffer_2[current_index_2];

        // Almacena el nuevo resultado (1: fallo, 0: éxito)
        crc_buffer_2[current_index_2] = crc_fail_2;

        // Actualiza el contador global de fallos
        fail_count_2 += crc_fail_2;
        fail_count_abs_2 += crc_fail_2;

        // Avanza el índice de forma circular
        current_index_2 = (current_index_2 + 1) % WINDOW_SIZE;
    }

    double fail_percentage_0 = (fail_count_0 * 100.0) / WINDOW_SIZE;
    double fail_percentage_1 = (fail_count_1 * 100.0) / WINDOW_SIZE;
    double fail_percentage_2 = (fail_count_2 * 100.0) / WINDOW_SIZE;

    if (crc_fail_0||crc_fail_1||crc_fail_2) {
        printf ("RAW %s %u %4.1f%% %8u CRCv0 %s %u %4.1f%% %8u CRCv1 %s %u %4.1f%% %8u \n",
            binario,
            crc_fail_0,
            fail_percentage_0,
            fail_count_abs_0,
            binario_1,
            crc_fail_1,
            fail_percentage_1,
            fail_count_abs_1,
            binario_2,
            crc_fail_2,
            fail_percentage_2,
            fail_count_abs_2);
    }
#endif
}

void writeFfbMagnitudeToBram(int16_t magnitude)
{

    u32 value = abs(magnitude);
    u32 sign = 0;
    if (magnitude < 0)
    {
        sign = 1;
    }
    XBram_WriteReg(XPAR_XBRAM_0_BASEADDR, STERING_WHEEL_FFB_MAGNITUDE_ADDR, value);
    XBram_WriteReg(XPAR_XBRAM_0_BASEADDR, STERING_WHEEL_FFB_SIGN_ADDR, sign);
/*
    u32 var1 = XBram_ReadReg(XPAR_XBRAM_0_BASEADDR, STERING_WHEEL_FFB_MAGNITUDE_ADDR);
    u32 var2 = XBram_ReadReg(XPAR_XBRAM_0_BASEADDR, STERING_WHEEL_FFB_SIGN_ADDR);

    print_binary(var1);
    print_binary(var2);
*/
}

void writeRotationToBram(uint8_t rotation)
{
    XBram_WriteReg(XPAR_XBRAM_0_BASEADDR, STERING_WHEEL_ROTATION_ADDR, rotation);
}

/* Private methods */
void _initializeECC(XBram_Config *ConfigPtr, u32 EffectiveAddr)
{
    u32 Addr;
    volatile u32 Data;

    if (ConfigPtr->EccPresent &&
        ConfigPtr->EccOnOffRegister &&
        ConfigPtr->EccOnOffResetValue == 0 &&
        ConfigPtr->WriteAccess != 0) {
        for (Addr = ConfigPtr->MemBaseAddress;
            Addr < ConfigPtr->MemHighAddress; Addr+=4) {
            Data = XBram_In32(Addr);
            XBram_Out32(Addr, Data);
        }
        XBram_WriteReg(EffectiveAddr, XBRAM_ECC_ON_OFF_OFFSET, 1);
    }
}