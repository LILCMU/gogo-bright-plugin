const filterNumber = function(number) {
	return Math.floor(number.replace("(double)", ""))
}

// ********************* Sensor ********************* //

Blockly.JavaScript['gogo_bright.input_sensor'] = function(block) {
	return [
		'DEV_I2C0.GOGO_BRIGHT().readInput(' + block.getFieldValue('sensor') + ')',
		Blockly.JavaScript.ORDER_ATOMIC
	];
};

// ********************* Motor ********************* //

Blockly.JavaScript['gogo_bright.action_motor'] = function () {
	var checkboxA = this.getFieldValue('a')
	var checkboxB = this.getFieldValue('b')
	var checkboxC = this.getFieldValue('c')
	var checkboxD = this.getFieldValue('d')

	var code = 'DEV_I2C0.GOGO_BRIGHT().talkToOutput("' + (checkboxA === 'TRUE' ? 'a' : '') +
		(checkboxB === 'TRUE' ? 'b' : '') +
		(checkboxC === 'TRUE' ? 'c' : '') +
		(checkboxD === 'TRUE' ? 'd' : '') +
		'");\n'
	if (code === 'DEV_I2C0.GOGO_BRIGHT().talkToOutput("");\n') { code = '\n' }
	return code;
}

Blockly.JavaScript['gogo_bright.motor_action_turn'] = function () {
	var dropdownTurn = this.getFieldValue('turn')
	var code = 'DEV_I2C0.GOGO_BRIGHT().' + (dropdownTurn == 'on' ? 'turnOutputON' : 'turnOutputOFF') + '();\n'
	return code;
}

Blockly.JavaScript['gogo_bright.motor_action_power'] = function (block) {
	var valuePower = Blockly.JavaScript.valueToCode(block, 'power', Blockly.JavaScript.ORDER_NONE)
	var code = 'DEV_I2C0.GOGO_BRIGHT().setOutputPower(' + filterNumber(valuePower) + ');\n'
	return code
}

Blockly.JavaScript['gogo_bright.motor_action_cw'] = function () {
	var dropdownThisway = this.getFieldValue('clockwise')
	var code = 'DEV_I2C0.GOGO_BRIGHT().' + (dropdownThisway == 'cw' ? 'turnOutputCW' : 'turnOutputCCW') + '();\n'
	return code
}

Blockly.JavaScript['gogo_bright.motor_action_rd'] = function () {
	var code = 'DEV_I2C0.GOGO_BRIGHT().reverseOutputDirection();\n'
	return code
}

// ********************* Servo ********************* //

Blockly.JavaScript['gogo_bright.action_servo'] = function () {
	var checkboxA = this.getFieldValue('a')
	var checkboxB = this.getFieldValue('b')
	var checkboxC = this.getFieldValue('c')
	var checkboxD = this.getFieldValue('d')

	var code = 'DEV_I2C0.GOGO_BRIGHT().talkToServo("' + (checkboxA === 'TRUE' ? '1' : '') +
		(checkboxB === 'TRUE' ? '2' : '') +
		(checkboxC === 'TRUE' ? '3' : '') +
		(checkboxD === 'TRUE' ? '4' : '') +
		'");\n'
	if (code === 'DEV_I2C0.GOGO_BRIGHT().talkToServo("");\n') { code = '' }
	return code;
}

Blockly.JavaScript['gogo_bright.servo_seth'] = function (block) {
	var valueHeading = Blockly.JavaScript.valueToCode(block, 'heading', Blockly.JavaScript.ORDER_NONE)
	var code = `DEV_I2C0.GOGO_BRIGHT().setServoAngle(${filterNumber(valueHeading)});\n`
	return code
}

Blockly.JavaScript['gogo_bright.servo_turn_cw'] = function (block) {
	var valueHeading = Blockly.JavaScript.valueToCode(block, 'heading', Blockly.JavaScript.ORDER_NONE)
	var code = `DEV_I2C0.GOGO_BRIGHT().turnServoCW(${filterNumber(valueHeading)});\n`
	return code
}

Blockly.JavaScript['gogo_bright.servo_turn_ccw'] = function (block) {
	var valueHeading = Blockly.JavaScript.valueToCode(block, 'heading', Blockly.JavaScript.ORDER_NONE)
	var code = `DEV_I2C0.GOGO_BRIGHT().turnServoCCW(${filterNumber(valueHeading)});\n`
	return code
}
