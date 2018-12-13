#ifndef __SENSOR_DHT12_H__
#define __SENSOR_DHT12_H__

#include <string>
using std::string;

#include "driver.h"
#include "device.h"
#include "i2c-dev.h"

#define SENSOR_DHT12_POLLING_MS 1000

#define SENSOR_DHT12_I2C_ADDRESS 0x5C

//* ////////////////////////////////////
//* Register map
#define REG_GOGOBRIGHT_ID 0

class SENSOR_DHT12 : public Device
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

	I2CDev *i2c;
	float temperature;
	float humidity;
	uint8_t raw_data[5];

	bool wireWriteDataByte(uint8_t cmd, uint8_t param1);
	bool wireWriteDataByte(uint8_t cmd, uint8_t param1, uint8_t param2);
	bool wireWriteDataByte(uint8_t cmd, uint8_t param1, uint8_t param2, uint8_t param3);

  public:
	// constructor
	SENSOR_DHT12();
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
	float readTemp(void);
	float readHumi(void);
};

#endif
