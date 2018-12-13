// ********************* HC-SR04 ********************* //

Blockly.JavaScript['gogo_bright.get_ultrasonic_distance'] = function (block) {
	return [
		'DEV_I2C0.SENSOR_HC_SR04().readDistance(' + block.getFieldValue('selectUnit') + ')',
		Blockly.JavaScript.ORDER_ATOMIC
	];
};
