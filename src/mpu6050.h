#ifndef MPU_6050
#define MPU_6050

#include "Wire.h"

#define MPU6050_ADDRESS (0x68)
#define MASK_CLKSEL   (0b11111000)
#define POS_CLKSEL    (0)
#define MASK_TEMP_DIS (0b11110111)
#define POS_TEMP_DIS  (3)
#define MASK_FS_SEL   (0b11100111)
#define POS_FS_SEL    (3)
#define MASK_AFS_SEL  (0b11100111)
#define POS_AFS_SEL   (3)
#define MASK_DLPF_CFG (0b11111000)
#define POS_DLPF_CFG  (0)

typedef enum
{
    SELF_TEST_X  = 0x0D,
    SELF_TEST_Y  = 0x0E,
    SELF_TEST_Z  = 0x0F,
    SELF_TEST_A  = 0x10,
    SMPLRT_DIV   = 0x19,
    CONFIG       = 0x1A,
    GYRO_CONFIG  = 0x1B,
    ACCEL_CONFIG = 0x1C,
    MOT_THR      = 0x1F,
    FIFO_EN      = 0x23,
    I2C_MST_CTRL = 0x24,
    INT_PIN_CFG  = 0x37,
    INT_ENABLE   = 0x38,
    INT_STATUS   = 0x3A,
    ACCEL_XOUT_H = 0x3B,
    ACCEL_XOUT_L = 0x3C,
    ACCEL_YOUT_H = 0x3D,
    ACCEL_YOUT_L = 0x3E,
    ACCEL_ZOUT_H = 0x3F,
    ACCEL_ZOUT_L = 0x40,
    TEMP_OUT_H   = 0x41,
    TEMP_OUT_L   = 0x42,
    GYRO_XOUT_H  = 0x43,
    GYRO_XOUT_L  = 0x44,
    GYRO_YOUT_H  = 0x45,
    GYRO_YOUT_L  = 0x46,
    GYRO_ZOUT_H  = 0x47,
    GYRO_ZOUT_L  = 0x48,
    PWR_MGMT_1   = 0x6B,
    PWR_MGMT_2   = 0x6C,
    WHO_AM_I     = 0x75 
} MPURegister;

typedef enum
{
    INTERNAL_8MHZ   = 0,
    PLL_XGYRO       = 1,
    PLL_YGYRO       = 2,
    PLL_ZGYRO       = 3,
    EXTERNAL_32KHZ  = 4,
    EXTERNAL_19MHZ  = 5,
    KEEP_RESET      = 7
} MPUClockSource;

typedef enum
{
    FS_SEL_250  = 0,
    FS_SEL_500  = 1,
    FS_SEL_1000 = 2,
    FS_SEL_2000 = 3
} MPUGyroRange;

typedef enum
{
    AFS_SEL_2g  = 0,
    AFS_SEL_4g  = 1,
    AFS_SEL_8g  = 2,
    AFS_SEL_16g = 3,
} MPUAccelRange;

typedef enum
{
    DLPF_ACCEL260Hz_GYRO256Hz = 0,
    DLPF_ACCEL184Hz_GYRO188Hz = 1,
    DLPF_ACCEL94Hz_GYRO98Hz   = 2,
    DLPF_ACCEL44Hz_GYRO42Hz   = 3,
    DLPF_ACCEL21Hz_GYRO20Hz   = 4,
    DLPF_ACCEL10Hz_GYRO10Hz   = 5,
    DLPF_ACCEL5Hz_GYRO5Hz     = 6
} MPULowPassFilter;


class MPU6050
{
    private:
    float gyro_scale_factor;
    float accel_scale_factor;
    float temp_scale_factor;
    public:
    float accel_x, accel_y, accel_z;
    float gyro_x, gyro_y, gyro_z, temp;

    MPU6050();
    void init(MPUGyroRange gyro_range, MPUAccelRange accel_range);
    bool status();

    void setClockSource(MPUClockSource source);
    MPUClockSource getClockSource();
    void setTemperatureSensorStatus(bool enable);
    bool getTemperatureSensorStatus();
    void setAccelRange(MPUAccelRange range);
    MPUAccelRange getAccelRange();
    void setGyroRange(MPUGyroRange range);
    MPUGyroRange getGyroRange();
    void setLowPassFilter(MPULowPassFilter filter);
    MPULowPassFilter getLowPassFilter();

    uint8_t readRegister(MPURegister register);
    uint8_t readRegister(MPURegister register, uint8_t mask, uint8_t pos);
    void writeRegister(MPURegister register, uint8_t value);
    void writeRegister(MPURegister register, uint8_t value, uint8_t mask, uint8_t pos);

    void update();
};

#endif