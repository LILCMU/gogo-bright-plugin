#include <stdio.h>
#include <math.h>
#include <locale>
#include "esp_system.h"
#include "kidbright32.h"
#include "sensor_hc_sr04.h"

SENSOR_HC_SR04::SENSOR_HC_SR04()
{
	channel = 0; //bus_ch;
	address = SENSOR_HC_SR04_I2C_ADDRESS;
	polling_ms = SENSOR_HC_SR04_POLLING_MS;
}

void SENSOR_HC_SR04::init(void)
{
	first_read = true;
	distance = 0;
	state = s_detect;
}

int SENSOR_HC_SR04::prop_count(void)
{
	return 0;
}

bool SENSOR_HC_SR04::prop_name(int index, char *name)
{
	if (index == 0)
	{
		snprintf(name, DEVICE_PROP_NAME_LEN_MAX, "%s", "Distance value");
		return true;
	}
	// not supported
	return false;
}

bool SENSOR_HC_SR04::prop_unit(int index, char *unit)
{
	if (index == 0)
	{
		snprintf(unit, DEVICE_PROP_UNIT_LEN_MAX, "%s", "Centimeters"); //? default unit
		return true;
	}

	// not supported
	return false;
}

bool SENSOR_HC_SR04::prop_attr(int index, char *attr)
{
	if (index == 0)
	{
		get_attr_str(attr, PROP_ATTR_READ_FLAG | PROP_ATTR_TYPE_NUMBER_FLAG); // read only, number
		return true;
	}

	// not supported
	return false;
}

bool SENSOR_HC_SR04::prop_read(int index, char *value)
{
	if (index == 0)
	{
		snprintf(value, DEVICE_PROP_VALUE_LEN_MAX, "%d", distance);
		return true;
	}

	return false;
}

bool SENSOR_HC_SR04::prop_write(int index, char *value)
{
	// not supported
	return false;
}

void SENSOR_HC_SR04::process(Driver *drv)
{
	// I2CDev *i2c = (I2CDev *)drv;
	i2c = (I2CDev *)drv;
	uint8_t byte, data[2];

	switch (state)
	{
	case s_detect:
		// stamp polling tickcnt
		polling_tickcnt = get_tickcnt();

		// detect i2c device
		if (i2c->detect(channel, address) == ESP_OK)
		{

			initialized = true;
			// clear error flag
			error = false;
			// get current tickcnt
			tickcnt = get_tickcnt();
			state = s_get_sensor;
		}
		else //* try on other i2c bus
		{
			state = s_error;
		}
		break;
	case s_get_sensor:
		if (is_tickcnt_elapsed(tickcnt, 50))
		{
			byte = REG_SPECIAL_PORT_VALUE;
			i2c->read(channel, address, &byte, 1, &data[0], 1);

			byte = REG_SPECIAL_PORT_VALUE + 1;
			i2c->read(channel, address, &byte, 1, &data[1], 1);

			distance = (data[0] << 8) + data[1];
			
			initialized = true;
			tickcnt = polling_tickcnt;
			state = s_wait;
		}
		break;
	case s_error:
		// set error flag
		error = true;
		// clear initialized flag
		initialized = false;
		// set first read flag
		first_read = true;
		// get current tickcnt
		tickcnt = get_tickcnt();
		// goto wait and retry with detect state
		state = s_wait;
		// set flag to switch to comm on other i2c bus
		i2c_bus_flag = !i2c_bus_flag;
		break;

	case s_wait:
		// wait polling_ms timeout
		if (is_tickcnt_elapsed(tickcnt, polling_ms))
		{
			state = s_detect;
		}
		break;
	}
}

//* ************* Input port functions *************

int SENSOR_HC_SR04::readDistance(int selectUnit)
{
	uint8_t byte, data[2];

	if (selectUnit < 0 || selectUnit > 1)
		return 0;

	if (!wireWriteDataByte(CMD_SPECIAL_ULTRASONIC, selectUnit))
	{
		return 0;
	}

	// time_to_read_value = true;
	// vTaskDelay(100 / portTICK_PERIOD_MS); //? wait 100ms for ultasonic to read value

	return distance;
}

//* ************* I2C functions *************

bool SENSOR_HC_SR04::wireWriteDataByte(uint8_t cmd, uint8_t param1)
{
	uint8_t data[3];

	if (!initialized)
	{
		return false;
	}

	data[0] = CATEGORY_CMD;
	data[1] = cmd;
	data[2] = param1;

	return (i2c->write(channel, address, data, 3) == ESP_OK);
}

bool SENSOR_HC_SR04::wireWriteDataByte(uint8_t cmd, uint8_t param1, uint8_t param2)
{
	uint8_t data[4];

	if (!initialized)
	{
		return false;
	}

	data[0] = CATEGORY_CMD;
	data[1] = cmd;
	data[2] = param1;
	data[3] = param2;

	return (i2c->write(channel, address, data, 4) == ESP_OK);
}

bool SENSOR_HC_SR04::wireWriteDataByte(uint8_t cmd, uint8_t param1, uint8_t param2, uint8_t param3)
{
	uint8_t data[5];

	if (!initialized)
	{
		return false;
	}

	data[0] = CATEGORY_CMD;
	data[1] = cmd;
	data[2] = param1;
	data[3] = param2;
	data[4] = param3;

	return (i2c->write(channel, address, data, 5) == ESP_OK);
}