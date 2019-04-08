// ********************* HC-SR04 ********************* //
Blockly.JavaScript['gogo_bright.start_ultrasonic'] = function (block) {
	var dropdown_select_sensor_type = block.getFieldValue('select_sensor_type')
	var dropdown_select_unit = block.getFieldValue('select_unit')
	var code = 'DEV_I2C1.SENSOR_HC_SR04().startUltrasonic(' + dropdown_select_sensor_type + ', ' + dropdown_select_unit + ');\n'
	return code
};

Blockly.JavaScript['gogo_bright.get_ultrasonic_distance'] = function (block) {
	var code = 'DEV_I2C1.SENSOR_HC_SR04().readDistance()'
	return [code, Blockly.JavaScript.ORDER_ATOMIC]
};
