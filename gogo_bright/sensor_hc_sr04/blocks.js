// ********************* HC-SR04 ********************* //
Blockly.Blocks['gogo_bright.start_ultrasonic'] = {
	init: function () {
		this.appendDummyInput()
			.appendField(Blockly.Msg.SENSOR_HC_SR04_START_PREFIX)
			.appendField(new Blockly.FieldDropdown([["HC-SR04", "0"], ["SEEED Ultrasonic", "1"]]), "select_sensor_type")
			.appendField(Blockly.Msg.SENSOR_HC_SR04_START_POSTFIX)
			.appendField(new Blockly.FieldDropdown([["centimeters", "0"], ["inches", "1"]]), "select_unit");
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(Blockly.Msg.COLOR_SENSOR_HC_SR04);
	}
};

Blockly.Blocks['gogo_bright.get_ultrasonic_distance'] = {
	init: function () {
		this.appendDummyInput()
			.appendField(Blockly.Msg.SENSOR_HC_SR04_GET_DISTANCE)
		this.setOutput(true, null);
		this.setColour(Blockly.Msg.COLOR_SENSOR_HC_SR04);
	}
};
