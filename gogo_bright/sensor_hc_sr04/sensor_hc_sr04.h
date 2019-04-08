#ifndef __SENSOR_HC_SR04_H__
#define __SENSOR_HC_SR04_H__

#include <string>
using std::string;

#include "driver.h"
#include "device.h"
#include "i2c-dev.h"

#define SENSOR_HC_SR04_POLLING_MS 200

#define SENSOR_HC_SR04_I2C_ADDRESS 0x42

//* ////////////////////////////////////
//* Register map
#define REG_GOGOBRIGHT_ID 0
#define REG_SPECIAL_PORT_VALUE 28

#define CMD_SPECIAL_ULTRASONIC 21

//* Commands I2C
#define CATEGORY_CMD 0

class SENSOR_HC_SR04 : public Device
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
	bool time_to_read_value = false;

	I2CDev *i2c;
	float distance;

	bool wireWriteDataByte(uint8_t cmd, uint8_t param1);
	bool wireWriteDataByte(uint8_t cmd, uint8_t param1, uint8_t param2);
	bool wireWriteDataByte(uint8_t cmd, uint8_t param1, uint8_t param2, uint8_t param3);

  public:
	// constructor
	SENSOR_HC_SR04();
	// override
	void init(void);
	void process(Driver *drv);
	int prop_count(void);
	bool prop_name(int index, char *name);
	bool prop_unit(int index, char *unit);
	bool prop_attr(int index, char *attr);
	bool prop_read(int index, char *value);
	bool prop_write(int index, char *value);

	//* ********************* I2C port functions *********************
	int startUltrasonic(int selectSensorType, int selectUnit);
	float readDistance();
};

#endif
