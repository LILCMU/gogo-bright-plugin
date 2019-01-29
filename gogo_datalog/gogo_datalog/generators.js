
Blockly.JavaScript['gogo_data_log_set_apikey'] = function(block) {
	var value_token = block.getFieldValue('API_KEY');
	try {
		value_token = value_token.trim()
	} catch (error) {
		
	}
	var code = `DEV_IO.GOGO_DATALOG().setAccessToken("${value_token}");\n`;
	return code;
};

Blockly.JavaScript['gogo_data_log_record'] = function(block) {
	var value_field = block.getFieldValue('FIELD');
	var value_value = Blockly.JavaScript.valueToCode(block, 'VALUE', Blockly.JavaScript.ORDER_ATOMIC);
	var code = `DEV_IO.GOGO_DATALOG().record("${value_field}", ${value_value});\n`;
	return code;
};
