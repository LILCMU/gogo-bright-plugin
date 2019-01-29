Blockly.Blocks['gogo_data_log_set_apikey'] = {
	init: function () {
		this.appendDummyInput()
			.appendField(Blockly.Msg.GOGO_DATALOG_SET_KEY)
			.appendField(new Blockly.FieldTextInput(""), "API_KEY");
		this.setInputsInline(true);
		this.setColour(120);
		this.setTooltip("");
		this.setHelpUrl("https://data.learninginventions.org/");
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
	}
};

Blockly.Blocks['gogo_data_log_record'] = {
	init: function () {
		this.appendValueInput("VALUE")
			.setCheck(["Boolean", "Number"])
			.appendField(Blockly.Msg.GOGO_DATALOG_RECORD);
		this.appendDummyInput()
			.appendField(Blockly.Msg.GOGO_DATALOG_INTO_FIELD)
			.appendField(new Blockly.FieldDropdown([["1", "1"], ["2", "2"], ["3", "3"], ["4", "4"], ["5", "5"], ["6", "6"], ["7", "7"], ["8", "8"]]), "FIELD");
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(120);
		this.setTooltip("");
		this.setHelpUrl("");
	}
};

