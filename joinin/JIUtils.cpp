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

#include "JIUtils.h"

obs_data_t* JIUtils::ConfigureStream() {
	//obs_service_t *oldService = obs_get_service;
	obs_data_t *data = obs_data_create();
	//obs_data_t *sources_data = obs_data_create();
	//obs_service_t *service = obs_service_create("rtmp_common", "default_service", nullptr,	nullptr);
	obs_service_t *service = obs_get_service_by_name("default_service");

	obs_data_t *service_data = obs_data_create();
	obs_data_set_string(service_data, "key", "54321");
	obs_data_set_string(service_data, "server", "rtmp://a.rtmp.youtube.com/live2");
	obs_data_set_string(service_data, "service", "YouTube / YouTube Gaming");
	obs_service_update(service, service_data);

	//obs_enum_sources([](void *sources_data, obs_source_t *source);
	//obs_enum_sources([](void *sources_data, obs_source_t *source);

	obs_data_t *settings = obs_service_get_settings(service);
	obs_data_set_string(data, "debug", "xxxx");
	const char *json = obs_data_get_json(settings);
	obs_data_set_string(data, "service", json);

	//obs_data_release(data);

	return data;
}

