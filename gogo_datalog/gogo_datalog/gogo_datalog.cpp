#ifndef __GOGO_DATA_LOG_CPP__
#define __GOGO_DATA_LOG_CPP__

#include "gogo_datalog.h"

static const char *TAG = "GOGO_DATALOG";

#define TOKEN_SIZE 64
#define AUTH_SIZE 100
#define POST_DATA_BUFFER_SIZE 512

GOGO_DATALOG::GOGO_DATALOG() {
	this->access_token = (char*) malloc(TOKEN_SIZE);
}

void GOGO_DATALOG::init(void) {
	
	
	// set initialized flag
	this->initialized = true;
	// clear error flag
	this->error = false;
}

int GOGO_DATALOG::prop_count(void) {
	// not supported
	return 0;
}

bool GOGO_DATALOG::prop_name(int index, char *name) {
	// not supported
	return false;
}

bool GOGO_DATALOG::prop_unit(int index, char *unit) {
	// not supported
	return false;
}

bool GOGO_DATALOG::prop_attr(int index, char *attr) {
	// not supported
	return false;
}

bool GOGO_DATALOG::prop_read(int index, char *value) {
	// not supported
	return false;
}

bool GOGO_DATALOG::prop_write(int index, char *value) {
	// not supported
	return false;
}

void GOGO_DATALOG::process(Driver *drv) {
	
}

void GOGO_DATALOG::setAccessToken(const char *token) {
	memset(this->access_token, 0, TOKEN_SIZE);
	strcpy(this->access_token, token);
}

void GOGO_DATALOG::record(const char *field, double value) {

	if (sizeof(this->access_token) == 0) {
		return;
	}
	char *post_data = (char *)malloc(POST_DATA_BUFFER_SIZE);
	
	char string_value[32];
	snprintf(string_value, sizeof(string_value), "%g", value);

	// Post data
	memset(post_data, 0, POST_DATA_BUFFER_SIZE);
	strcpy(post_data, "api_key=");
	strcat(post_data, this->access_token);
	strcat(post_data, "&field");
	strcat(post_data, field);
	strcat(post_data, "=");
	strcat(post_data, string_value);
	
	// Use esp http api
	esp_http_client_config_t config = {
        .url = "https://data.learninginventions.org/update"
    };
    esp_http_client_handle_t client = esp_http_client_init(&config);
    esp_http_client_set_method(client, HTTP_METHOD_POST);
    esp_http_client_set_post_field(client, post_data, strlen(post_data));
	
    esp_err_t err = esp_http_client_perform(client);

    if (err == ESP_OK) {
        ESP_LOGI(TAG, "HTTPS Status = %d, content_length = %d",
                esp_http_client_get_status_code(client),
                esp_http_client_get_content_length(client));
    } else {
        ESP_LOGE(TAG, "Error perform http request %s", esp_err_to_name(err));
    }
    esp_http_client_cleanup(client);
	
	free(post_data);
}

#endif
