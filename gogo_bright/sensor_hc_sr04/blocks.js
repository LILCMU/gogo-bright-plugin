// ********************* HC-SR04 ********************* //
Blockly.Blocks['gogo_bright.get_ultrasonic_distance'] = {
	init: function () {
		this.appendDummyInput()
			.appendField(Blockly.Msg.SENSOR_HC_SR04_PREFIX)
			.appendField(new Blockly.FieldDropdown([["Centimeters", "0"], ["Inches", "1"]]), "selectUnit")
			.appendField(Blockly.Msg.SENSOR_HC_SR04_POSTFIX)
		this.setOutput(true, null);
		this.setColour(Blockly.Msg.COLOR_SENSOR_HC_SR04);
	}
};
