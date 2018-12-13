// ********************* DHTxx ********************* //

Blockly.Blocks["gogo_bright.get_dht12_temp"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.SENSOR_DHTXX_TEMP)
		this.setOutput(true, 'Number');
		this.setInputsInline(true);
		this.setPreviousStatement(false);
		this.setNextStatement(false);
		this.setColour(Blockly.Msg.COLOR_SENSOR_DHTXX)
	}
};


Blockly.Blocks["gogo_bright.get_dht12_humi"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.SENSOR_DHTXX_HUMI)
		this.setOutput(true, 'Number');
		this.setInputsInline(true);
		this.setPreviousStatement(false);
		this.setNextStatement(false);
		this.setColour(Blockly.Msg.COLOR_SENSOR_DHTXX)
	}
};