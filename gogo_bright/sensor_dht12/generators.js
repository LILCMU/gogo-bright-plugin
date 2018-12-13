// ********************* DHT12 ********************* //

Blockly.JavaScript['gogo_bright.get_dht12_temp'] = function(block) {
	return [
		'DEV_I2C0.SENSOR_DHT12().readTemp()',
		Blockly.JavaScript.ORDER_ATOMIC
	];
};

Blockly.JavaScript['gogo_bright.get_dht12_humi'] = function(block) {
	return [
		'DEV_I2C0.SENSOR_DHT12().readHumi()',
		Blockly.JavaScript.ORDER_ATOMIC
	];
};