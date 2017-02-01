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


obs_data_t* JIUtils::ConfigureVideo(obs_data_t *config_data) {

	obs_video_info *ovi = new obs_video_info();
	bool hasVideo = obs_get_video_info(ovi);
	ovi->fps_num = 20;

	//see obs-defs.h
	/*
	#define OBS_VIDEO_SUCCESS           0
	#define OBS_VIDEO_FAIL             -1
	#define OBS_VIDEO_NOT_SUPPORTED    -2
	#define OBS_VIDEO_INVALID_PARAM    -3
	#define OBS_VIDEO_CURRENTLY_ACTIVE -4
	#define OBS_VIDEO_MODULE_NOT_FOUND -5
	*/
	int video_result = obs_reset_video(ovi);
	//obs.c: obs_reset_video
	//window-basic-main.cpp: ret = AttemptToResetVideo(&ovi);
	//obs_output_set_video
	//obs_reset_video
	//obs_service_apply_encoder_settings
	obs_data_t *result = JIUtils::GetVideoConfig(config_data);
	obs_data_set_int(result, "attempt", video_result);

	return result;
}


obs_data_t* JIUtils::ConfigureScene(obs_data_t *config_data) {

	//TODO create scene with camera and screencast
	obs_data_t *result = obs_data_create();
	const char *scene_name = "test scene";
	obs_scene_t *new_scene = obs_scene_create(scene_name);

	return result;
}


obs_data_t* JIUtils::ConfigureStream(obs_data_t *config_data) {

	obs_data_t *result = obs_data_create();

	const char *config_key = obs_data_get_string(config_data, "key");
	const char *config_server = obs_data_get_string(config_data, "server");
	const char *config_service = obs_data_get_string(config_data, "service");

	obs_data_t *service_data = obs_data_create();
	obs_data_set_string(service_data, "key", config_key);			// rtmp stream key
	obs_data_set_string(service_data, "server", config_server);		// rtmp://a.rtmp.youtube.com/live2
	obs_data_set_string(service_data, "service", config_service);	// YouTube / YouTube Gaming

	obs_service_t *service = obs_get_service_by_name("default_service");
	obs_service_update(service, service_data);

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

obs_data_t* JIUtils::GetVideoConfig(obs_data_t *config_data) {

	obs_data_t *result = obs_data_create();
	obs_video_info *ovi = new obs_video_info();
	bool hasVideo = obs_get_video_info(ovi);
	obs_data_set_string(result, "graphics_module", ovi->graphics_module);
	obs_data_set_int(result, "base_width", ovi->base_width);
	obs_data_set_int(result, "base_height", ovi->base_height);
	obs_data_set_int(result, "output_width", ovi->output_width);
	obs_data_set_int(result, "output_height", ovi->output_height);
	obs_data_set_int(result, "base_width", ovi->base_width);
	obs_data_set_int(result, "fps_num", ovi->fps_num);
	obs_data_set_int(result, "fps_den", ovi->fps_den);
	//obs_data_set_obj(result, "output_format",(char) ovi->output_format);

	return result;
}
