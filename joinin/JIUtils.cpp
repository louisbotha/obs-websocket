/*
obs-websocket
Copyright (C) 2016	Stéphane Lepin <stephane.lepin@gmail.com>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program. If not, see <https://www.gnu.org/licenses/>
*/

#include "Utils.h"
#include "JIUtils.h"

obs_data_t* JIUtils::ConfigureStream(obs_data_t *config_data) {

	obs_data_t *result = obs_data_create();
	const char *config_key = obs_data_get_string(config_data, "key");
	const char *config_server = obs_data_get_string(config_data, "server");
	const char *config_service = obs_data_get_string(config_data, "service");

	//obs_data_t *sources_data = obs_data_create();
	//obs_service_t *service = obs_service_create("rtmp_common", "default_service", nullptr,	nullptr);
	obs_service_t *service = obs_get_service_by_name("default_service");

	obs_data_t *service_data = obs_data_create();
	obs_data_set_string(service_data, "key", config_key);
	obs_data_set_string(service_data, "server", config_server);
	obs_data_set_string(service_data, "service", config_service);
	obs_service_update(service, service_data);

	//obs_enum_sources([](void *sources_data, obs_source_t *source);
	//obs_enum_sources([](void *sources_data, obs_source_t *source);

	return JIUtils::GetStreamConfig(config_data);
}


obs_data_t* JIUtils::GetStreamConfig(obs_data_t *config_data) {

	obs_data_t *result = obs_data_create();
	obs_service_t *service = obs_get_service_by_name("default_service");
	obs_data_t *settings = obs_service_get_settings(service);
	const char *json = obs_data_get_json(settings);
	obs_data_set_string(result, "service", json);

	return result;
}

