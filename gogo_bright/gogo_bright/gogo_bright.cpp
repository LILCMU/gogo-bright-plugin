#include <stdio.h>
#include <math.h>
#include <locale>
#include "esp_system.h"
#include "kidbright32.h"
#include "gogo_bright.h"

GOGO_BRIGHT::GOGO_BRIGHT()
{
	channel = 0; //bus_ch;
	address = GOGOBRIGHT_I2C_ADDRESS;
	polling_ms = GOGO_BRIGHT_POLLING_MS;
}

void GOGO_BRIGHT::init(void)
{
	first_read = true;
	// illuminance = 0;
	// sensor_values;
	state = s_detect;
}

int GOGO_BRIGHT::prop_count(void)
{
	return 1;
}

bool GOGO_BRIGHT::prop_name(int index, char *name)
{
	if (index == 0)
	{
		snprintf(name, DEVICE_PROP_NAME_LEN_MAX, "%s", "sensor values");
		return true;
	}

	// not supported
	return false;
}

bool GOGO_BRIGHT::prop_unit(int index, char *unit)
{
	if (index == 0)
	{
		snprintf(unit, DEVICE_PROP_UNIT_LEN_MAX, "%s", "analog");
		return true;
	}

	// not supported
	return false;
}

bool GOGO_BRIGHT::prop_attr(int index, char *attr)
{
	if (index == 0)
	{
		get_attr_str(attr, PROP_ATTR_READ_FLAG | PROP_ATTR_TYPE_NUMBER_FLAG); // read only, number
		return true;
	}

	// not supported
	return false;
}

bool GOGO_BRIGHT::prop_read(int index, char *value)
{
	if (index == 0)
	{
		snprintf(value, DEVICE_PROP_VALUE_LEN_MAX, "%d", sensor_values[0]);
		return true;
	}

	if (index > -1 && index < 4)
	{
		snprintf(value, DEVICE_PROP_VALUE_LEN_MAX, "%d", sensor_values[index]);
	}
	return false;
}

bool GOGO_BRIGHT::prop_write(int index, char *value)
{
	// not supported
	return false;
}

void GOGO_BRIGHT::process(Driver *drv)
{
	// I2CDev *i2c = (I2CDev *)drv;
	i2c = (I2CDev *)drv;
	uint8_t byte, data[2], raw_data[8] = {0};

	switch (state)
	{
	case s_detect:
		// stamp polling tickcnt
		polling_tickcnt = get_tickcnt();

		// detect i2c device
		if (i2c->detect(channel, GOGOBRIGHT_I2C_ADDRESS) == ESP_OK)
		{

			byte = REG_GOGOBRIGHT_ID;
			i2c->read(channel, address, &byte, 1, &data[0], 1);

			if (data[0] == GOGOBRIGHT_ID_1 || data[0] == GOGOBRIGHT_ID_2)
			{
				initialized = true;
				// clear error flag
				error = false;
				// get current tickcnt
				tickcnt = get_tickcnt();
				state = s_get_sensor;
			}
			else
			{
				state = s_error;
			}
		}
		else //* try on other i2c bus
		{
			state = s_error;
		}
		break;
	case s_get_sensor:
		// read delay for 40ms
		if (is_tickcnt_elapsed(tickcnt, 40))
		{
			// int i = 4;
			// byte = REG_INPUT_PORT_START + i;
			// i2c->read(channel, address, &byte, 1, &raw_data[i], 1);

			// byte = REG_INPUT_PORT_START + i + 1;
			// i2c->read(channel, address, &byte, 1, &raw_data[i + 1], 1);

			// sensor_values[i/2] = ((uint16_t)raw_data[i] << 8) + raw_data[i+1];

			// Read 8 bytes for 4 analog sensors
			for (int i = 0; i < 8; i += 2)
			{
				byte = REG_INPUT_PORT_START + i;
				i2c->read(channel, address, &byte, 1, &raw_data[i], 1);

				byte = REG_INPUT_PORT_START + i + 1;
				i2c->read(channel, address, &byte, 1, &raw_data[i + 1], 1);

				sensor_values[i / 2] = ((uint16_t)raw_data[i] << 8) + raw_data[i + 1];
			}

			initialized = true;
			// load polling tickcnt
			tickcnt = polling_tickcnt;
			// goto wait and retry with detect state
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

int GOGO_BRIGHT::readInput(int port)
{
	if (port < 1 || port > 4)
		return 0;
	return sensor_values[port - 1];
}

//* ************* Motor functions *************

bool GOGO_BRIGHT::talkToOutput(string output_port)
{
	uint8_t motorBits = 0;
	// output_port.toLowerCase();

	if (output_port.length() < 1 || output_port.length() > 4)
		return false;

	for (int i = 0; i < 4; i++)
	{
		if (output_port[i] == 'a')
		{
			motorBits |= 1;
		}
		else if (output_port[i] == 'b')
		{
			motorBits |= 2;
		}
		else if (output_port[i] == 'c')
		{
			motorBits |= 4;
		}
		else if (output_port[i] == 'd')
		{
			motorBits |= 8;
		}
	}

	return wireWriteDataByte(CMD_MOTOR_ACTIVE, motorBits);
}

bool GOGO_BRIGHT::setOutputPower(int power)
{
	if (power < 0 || power > 100)
		return false;

	return wireWriteDataByte(CMD_MOTOR_PWR, 0, 0, power);
}

bool GOGO_BRIGHT::turnOutputON(void)
{
	return wireWriteDataByte(CMD_MOTOR_ONOFF, 0, 1);
}
bool GOGO_BRIGHT::turnOutputOFF(void)
{
	return wireWriteDataByte(CMD_MOTOR_ONOFF, 0, 0);
}

bool GOGO_BRIGHT::turnOutputCW(void)
{
	return wireWriteDataByte(CMD_MOTOR_DIR, 0, 1);
}

bool GOGO_BRIGHT::turnOutputCCw(void)
{
	return wireWriteDataByte(CMD_MOTOR_DIR, 0, 0);
}

bool GOGO_BRIGHT::reverseOutputDirection(void)
{
	return wireWriteDataByte(CMD_MOTOR_RD, 0); // currently active ports
}

//* ************* Servo functions *************

bool GOGO_BRIGHT::talkToServo(string servo_port)
{
	uint8_t servoBits = 0;

	if (servo_port.length() < 1 || servo_port.length() > 4)
		return false;

	for (int i = 0; i < 4; i++)
	{
		if (servo_port[i] == '1')
		{
			servoBits |= 1;
		}
		else if (servo_port[i] == '2')
		{
			servoBits |= 2;
		}
		else if (servo_port[i] == '3')
		{
			servoBits |= 4;
		}
		else if (servo_port[i] == '4')
		{
			servoBits |= 8;
		}
	}

	return wireWriteDataByte(CMD_SERVO_ACTIVE, servoBits);
}

bool GOGO_BRIGHT::setServoAngle(int head_angle)
{
	if (head_angle < 0 || head_angle > 180)
		return false;

	return wireWriteDataByte(CMD_SERVO_SET_ANGLE, 0, 0, head_angle);
}

bool GOGO_BRIGHT::turnServoCW(int cw_angle)
{
	if (cw_angle < 0 || cw_angle > 180)
		return false;

	return wireWriteDataByte(CMD_SERVO_CW, 0, 0, cw_angle);
}

bool GOGO_BRIGHT::turnServoCCW(int ccw_angle)
{
	if (ccw_angle < 0 || ccw_angle > 180)
		return false;

	return wireWriteDataByte(CMD_SERVO_CCW, 0, 0, ccw_angle);
}

//* ************* I2C functions *************

bool GOGO_BRIGHT::wireWriteDataByte(uint8_t cmd, uint8_t param1)
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

bool GOGO_BRIGHT::wireWriteDataByte(uint8_t cmd, uint8_t param1, uint8_t param2)
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

bool GOGO_BRIGHT::wireWriteDataByte(uint8_t cmd, uint8_t param1, uint8_t param2, uint8_t param3)
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
