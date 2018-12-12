// ********************* Sensor ********************* //

Blockly.Blocks["gogo_bright.input_sensor"] = {
	init: function() {

		var sensor_ports = [];
		for (var i = 1;i <= 4; i++) {
			sensor_ports.push([String(i), String(i)]);
		}
		this.appendDummyInput()
			.appendField(Blockly.Msg.SENSOR_SENSOR)
			.appendField(new Blockly.FieldDropdown(sensor_ports), 'sensor');

		this.setOutput(true, 'Number');
		this.setInputsInline(true);
		this.setPreviousStatement(false);
		this.setNextStatement(false);
		this.setColour(Blockly.Msg.COLOR_SENSOR)
	}
};

// ********************* Motor ********************* //

Blockly.Blocks['gogo_bright.action_motor'] = {
	init: function () {
		this.setColour(Blockly.Msg.COLOR_MOTOR)
		this.appendDummyInput()
			.appendField(Blockly.Msg.MOTOR_TALK_TO)
			.appendField(new Blockly.FieldCheckbox('FALSE'), 'a').appendField('A ')
			.appendField(new Blockly.FieldCheckbox('FALSE'), 'b').appendField('B ')
			.appendField(new Blockly.FieldCheckbox('FALSE'), 'c').appendField('C ')
			.appendField(new Blockly.FieldCheckbox('FALSE'), 'd').appendField('D')

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
		this.setTooltip('')
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
