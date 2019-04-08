// ********************* Sensor ********************* //

Blockly.Blocks["gogo_bright.input_sensor"] = {
	init: function () {

		var sensor_ports = [];
		for (var i = 1; i <= 4; i++) {
			sensor_ports.push([String(i), String(i)]);
		}
		this.appendDummyInput()
			.appendField(Blockly.Msg.SENSOR_SENSOR)
			.appendField(new Blockly.FieldDropdown(sensor_ports), 'SENSOR');

		this.setOutput(true, 'Number');
		this.setInputsInline(true);
		this.setPreviousStatement(false);
		this.setNextStatement(false);
		this.setColour(Blockly.Msg.COLOR_SENSOR)
		this.setHelpUrl('https://code.gogoboard.org/')
	}
};

Blockly.Blocks['gogo_bright.input_sensor_color_is'] = {
	init: function () {
		var sensor_ports = [];
		for (var i = 1; i <= 4; i++) {
			sensor_ports.push([String(i), String(i)]);
		}
		this.appendDummyInput()
			.appendField(Blockly.Msg.SENSOR_SENSOR)
			.appendField(new Blockly.FieldDropdown(sensor_ports), 'SENSOR')
			.appendField(Blockly.Msg.SENSOR_IS)
			.appendField(new Blockly.FieldDropdown([[Blockly.Msg.SENSOR_COLOR_GREEN, 'green'], [Blockly.Msg.SENSOR_COLOR_YELLOW, 'yellow'], [Blockly.Msg.SENSOR_COLOR_RED, 'red']]), 'COLOR')
		this.setOutput(true, 'Boolean')
		this.setColour(Blockly.Msg.COLOR_SENSOR)
		this.setHelpUrl('https://code.gogoboard.org/')
	}
}

// ********************* Motor ********************* //

Blockly.Blocks['gogo_bright.action_motor'] = {
	init: function () {
		this.setColour(Blockly.Msg.COLOR_MOTOR)
		this.appendDummyInput()
			.appendField(Blockly.Msg.MOTOR_TALK_TO)
			.appendField(new Blockly.FieldCheckbox('FALSE'), 'a').appendField('A ')
			.appendField(new Blockly.FieldCheckbox('FALSE'), 'b').appendField('B ')
		// .appendField(new Blockly.FieldCheckbox('FALSE'), 'c').appendField('C ')
		// .appendField(new Blockly.FieldCheckbox('FALSE'), 'd').appendField('D')

		this.setPreviousStatement(true, null)
		this.setNextStatement(true, null)
		this.setTooltip(Blockly.Msg.MOTOR_TALK_TO_TOOLTIP)
	}
}

Blockly.Blocks['gogo_bright.motor_action_turn'] = {
	init: function () {
		this.setColour(Blockly.Msg.COLOR_MOTOR)
		this.appendDummyInput()
			.appendField(Blockly.Msg.MOTOR_TURN)
			.appendField(new Blockly.FieldDropdown([[Blockly.Msg.MOTOR_ON, 'on'], [Blockly.Msg.MOTOR_OFF, 'off']]), 'turn')
		this.setPreviousStatement(true, null)
		this.setNextStatement(true, null)
		this.setTooltip(Blockly.Msg.MOTOR_ONOFF_TOOLTIP)
	}
};

Blockly.Blocks['gogo_bright.motor_action_power'] = {
	init: function () {
		this.setColour(Blockly.Msg.COLOR_MOTOR)
		this.appendValueInput('power', Number)
			.appendField(Blockly.Msg.MOTOR_SET_POWER)
		this.setInputsInline(true)
		this.setPreviousStatement(true, null)
		this.setNextStatement(true, null)
		this.setTooltip(Blockly.Msg.MOTOR_SET_POWER_TOOLTIP)
	}
};

Blockly.Blocks['gogo_bright.motor_action_cw'] = {
	init: function () {
		this.setColour(Blockly.Msg.COLOR_MOTOR)
		this.appendDummyInput()
			.appendField(new Blockly.FieldDropdown([[Blockly.Msg.MOTOR_TURN_CW, 'cw'], [Blockly.Msg.MOTOR_TURN_CCW, 'ccw']]), 'clockwise')
		this.setPreviousStatement(true, null)
		this.setNextStatement(true, null)
		this.setTooltip('')
	}
}

Blockly.Blocks['gogo_bright.motor_action_rd'] = {
	init: function () {
		this.setColour(Blockly.Msg.COLOR_MOTOR)
		this.appendDummyInput()
			.appendField(Blockly.Msg.MOTOR_RD)
		this.setPreviousStatement(true, null)
		this.setNextStatement(true, null)
		this.setTooltip(Blockly.Msg.MOTOR_RD_TOOLTIP)
	}
}

// ********************* Servo ********************* //

Blockly.Blocks['gogo_bright.action_servo'] = {
	init: function () {
		this.setColour(Blockly.Msg.COLOR_SERVO)
		this.appendDummyInput()
			.appendField(Blockly.Msg.SERVO_TALK_TO)
			.appendField(new Blockly.FieldCheckbox('FALSE'), 'a').appendField('1 ')
			.appendField(new Blockly.FieldCheckbox('FALSE'), 'b').appendField('2 ')
			.appendField(new Blockly.FieldCheckbox('FALSE'), 'c').appendField('3 ')
			.appendField(new Blockly.FieldCheckbox('FALSE'), 'd').appendField('4 ')

		this.setPreviousStatement(true, null)
		this.setNextStatement(true, null)
		this.setTooltip(Blockly.Msg.MOTOR_TALK_TO_TOOLTIP)
	}
}

Blockly.Blocks['gogo_bright.servo_seth'] = {
	init: function () {
		this.setColour(Blockly.Msg.COLOR_SERVO)
		this.appendValueInput('heading', Number)
			.appendField(Blockly.Msg.SERVO_SET_HEADING)
		this.setInputsInline(true)
		this.setPreviousStatement(true)
		this.setNextStatement(true)
		this.setTooltip(Blockly.Msg.MOTOR_SET_HEADING_TOOLTIP)
	}
}

Blockly.Blocks['gogo_bright.servo_turn_cw'] = {
	init: function () {
		this.setColour(Blockly.Msg.COLOR_SERVO)
		this.appendValueInput('heading', Number)
			.appendField(Blockly.Msg.SERVO_CW_TURN)
		this.setInputsInline(true)
		this.setPreviousStatement(true)
		this.setNextStatement(true)
		this.setTooltip('')
	}
}

Blockly.Blocks['gogo_bright.servo_turn_ccw'] = {
	init: function () {
		this.setColour(Blockly.Msg.COLOR_SERVO)
		this.appendValueInput('heading', Number)
			.appendField(Blockly.Msg.SERVO_CCW_TURN)
		this.setInputsInline(true)
		this.setPreviousStatement(true)
		this.setNextStatement(true)
		this.setTooltip('')
	}
}

// ********************* Other : Relay ********************* //

Blockly.Blocks['gogo_bright.action_relay'] = {
	init: function () {

		var servo_ports = [];
		for (var i = 1; i <= 4; i++) {
			servo_ports.push([String(i), String(i)]);
		}

		this.setColour(Blockly.Msg.COLOR_RELAY)
		this.appendDummyInput()
			.appendField(Blockly.Msg.RELAY_TURN)
			.appendField(new Blockly.FieldDropdown([[Blockly.Msg.MOTOR_ON, 'on'], [Blockly.Msg.MOTOR_OFF, 'off']]), 'turn')
			.appendField(Blockly.Msg.RELAY_TALK_TO)
			.appendField(new Blockly.FieldDropdown(servo_ports), 'PORT')
			.appendField(Blockly.Msg.RELAY_END);
			
		this.setPreviousStatement(true, null)
		this.setNextStatement(true, null)
		this.setTooltip(Blockly.Msg.RELAY_TOOLTIP)
	}
}
