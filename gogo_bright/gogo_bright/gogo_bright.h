#ifndef __GOGO_BRIGHT_H__
#define __GOGO_BRIGHT_H__

#include <string>
using std::string;

#include "driver.h"
#include "device.h"
#include "i2c-dev.h"

#define GOGO_BRIGHT_POLLING_MS 40

#define GOGOBRIGHT_I2C_ADDRESS 0x42
#define GOGOBRIGHT_ID_1 0x60
#define GOGOBRIGHT_ID_2 0x61

//* ////////////////////////////////////
//* Register map
#define REG_GOGOBRIGHT_ID 0
#define REG_INPUT_PORT_START 1
#define REG_SERVO_ACTIVE 9
#define REG_SERVO_ANGLE 10
#define REG_MOTOR_ACTIVE 14
#define REG_MOTOR_STATUS 15
#define REG_MOTOR_DIR 16
#define REG_MOTOR_PWR 17

//* ///////////////////////////////////
//* Commands I2C
#define CATEGORY_CMD 0
//* servo
#define CMD_SERVO_SETH 9
#define CMD_SERVO_ACTIVE 14
#define CMD_SERVO_CW 15
#define CMD_SERVO_CCW 16
#define CMD_SERVO_SET_ANGLE 17
//* motor
#define CMD_MOTOR_ACTIVE 7
#define CMD_MOTOR_ONOFF 2
// #define CMD_MOTOR_OFF 51
#define CMD_MOTOR_DIR 3
// #define CMD_MOTOR_CW 53
#define CMD_MOTOR_RD 4
#define CMD_MOTOR_PWR 6


class GOGO_BRIGHT : public Device
{
  private:
	enum
	{
		s_detect,
		s_get_sensor,
		s_error,
		s_wait
	} state;

	TickType_t tickcnt, polling_tickcnt;
	bool first_read;
	bool i2c_bus_flag = 0;
	// double illuminance;
	// double calc_lux(unsigned int ch0, unsigned int ch1);

	I2CDev *i2c;
	int sensor_values[4];

	bool wireWriteDataByte(uint8_t cmd, uint8_t param1);
	bool wireWriteDataByte(uint8_t cmd, uint8_t param1, uint8_t param2);
	bool wireWriteDataByte(uint8_t cmd, uint8_t param1, uint8_t param2, uint8_t param3);

  public:
	// constructor
	GOGO_BRIGHT();
	// override
	void init(void);
	void process(Driver *drv);
	int prop_count(void);
	bool prop_name(int index, char *name);
	bool prop_unit(int index, char *unit);
	bool prop_attr(int index, char *attr);
	bool prop_read(int index, char *value);
	bool prop_write(int index, char *value);
	// method
	double get_illuminance(void);

	//* ********************* Input port functions *********************
	//? get sensors value from input port 1-4
	int readInput(int port);

	//* ********************* Motor functions *********************
	//? set output to interact with ..
	bool talkToOutput(string output_port);
	// //? set output power
	bool setOutputPower(int power);
	// //? turn outputs on or off
	bool turnOutputON(void);
	bool turnOutputOFF(void);
	// //? turn outputs direction
	bool turnOutputCW(void);
	bool turnOutputCCw(void);
	bool reverseOutputDirection(void);

	//* ********************* Servo functions *********************
	//? set servos to interact with ..
	bool talkToServo(string servo_port);
	//? set servos head to input head_angle
	bool setServoAngle(int head_angle);
	//? turn servos clockwise by input angle
	bool turnServoCW(int cw_angle);
	//? turn servos counter-clockwise by input angle
	bool turnServoCCW(int ccw_angle);
};

#endif
