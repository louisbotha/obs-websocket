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


obs_data_t* JIUtils::CloseOBS(obs_data_t *config_data) {
	//TODO
	//see window-basic-main -> OBSBasic::closeEvent(QCloseEvent *event)
	obs_data_t *result = obs_data_create();
	return result;
}

obs_data_t* JIUtils::ConfigureVideo(obs_data_t *config_data) {

	//see window-basic-settings.cpp -> SaveSettings()
	long new_output_width = obs_data_get_int(config_data, "output_width");
	long new_output_height = obs_data_get_int(config_data, "output_height");

	//obs_output_update
	//config_set_default_uint

	obs_video_info *ovi = new obs_video_info();
	bool hasVideo = obs_get_video_info(ovi);
	ovi->fps_num = 20;
	ovi->output_width = new_output_width;
	ovi->output_height = new_output_height;
	obs_reset_video(ovi);

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

obs_data_t* JIUtils::ProfileConfig(obs_data_t *config_data) {
	
	obs_data_t *result = obs_data_create();
	const char *action = obs_data_get_string(config_data, "action");

	config_t *config = obs_frontend_get_profile_config(); //basic.ini

	if (strcmpi(action, "set") == 0) {
		const char *section_name = obs_data_get_string(config_data, "section_name");
		const char *key = obs_data_get_string(config_data, "key");
		const char *value = obs_data_get_string(config_data, "value");

		const char *config_before = config_get_string(config, section_name, key);
		obs_data_set_string(result, "before", config_before);
		config_set_string(config, section_name, key, value);
		const char *config_after = config_get_string(config, section_name, key);
		obs_data_set_string(result, "after", config_after);

		obs_data_set_string(result, "section_name", section_name);
		obs_data_set_string(result, "key", key);
		obs_data_set_string(result, "value", value);
		obs_data_set_string(result, "result", "set");
	}
	else if (strcmpi(action, "save") == 0) {
		config_save_safe(config, "tmp", "bak");
		obs_frontend_get_profile_config();
		obs_data_set_string(result, "result", "saved");
	}
	else {
		obs_data_set_string(result, "result", "none");
	}
	//config_close(config);
	obs_data_set_string(result, "action", action);
	
	return result;

}

/*
obs_data_t* JIUtils::ConfigureOutput(obs_data_t *config_data2) {
	//see window-basic-main-outputs.cpp -> AdvancedOutput::SetupFFmpeg() (reads from saved config file "basic.ini")
	//see window-basic-settings.cpp line 2587
	
	//streamOutput = obs_output_create("rtmp_output", "adv_stream", nullptr, nullptr)
	// to file: simple_ffmpeg_output
	//advanced ffmpeg: adv_ffmpeg_output
	//obs_output *fileOutput = obs_output_create("ffmpeg_output", "adv_ffmpeg_output", nullptr, nullptr);
	//obs_output *fileOutput = obs_output_create("rtmp_output","adv_stream", nullptr, nullptr);

	obs_data_t *settings = obs_data_create();
	obs_data_set_string(settings,"url", "udp://@127.0.0.1:9999");
	obs_data_set_string(settings, "format_name", "mpegts");
	obs_data_set_string(settings, "video_encoder", "mpeg2video");
	obs_data_set_int(settings, "video_bitrate", 999);

	//obs_output_set_media(fileOutput, obs_get_video(), obs_get_audio());
	//obs_output_update(fileOutput, settings);
	//obs_output_release(fileOutput);
	//obs_frontend_get_global_config();
	//obs_frontend_save();
	obs_data_release(settings);

	obs_data_t *h264Settings = obs_data_create();
	obs_data_set_string(h264Settings, "rate_control", "CBR");
	obs_data_set_int(h264Settings, "bitrate", 999);
	//obs_encoder_t *h264Streaming = obs_video_encoder_create("obs_x264", "simple_h264_stream", nullptr, nullptr);
	//obs_encoder_update(h264Streaming, h264Settings);

	// obs_output_t *op = obs_frontend_get_streaming_output();
	//obs_output_t *op = obs_frontend_get_recording_output();
	obs_output_t *op = obs_get_output_by_name("adv_ffmpeg_output");
	obs_data_t *settings2 = obs_output_get_settings(op);

	obs_service_t *serv=	obs_output_get_service(op);
	obs_data_t *settings3 = obs_service_get_settings(serv);

	obs_data_t *current = obs_data_create();

	
		
	obs_data_set_string(settings2, "url", "udp://@127.0.0.1:9999");
	obs_output_update(op, settings2);

	//settings2 = obs_output_get_settings(op);

	obs_properties_t *props = obs_output_properties(op);

	obs_properties_get_param(props);
	obs_property_t *first = obs_properties_first(props);

	const char *id = obs_output_get_id(op);
	obs_data_set_string(current, "id", obs_output_get_id(op));
	obs_data_set_string(current, "name", obs_output_get_name(op));
	obs_data_set_string(current, "display_name", obs_output_get_display_name(id));
	
	obs_data_set_string(current, "prop", obs_property_name(first));


	obs_data_set_string(current, "format_name", obs_data_get_string(settings2, "format_name"));
	obs_data_set_string(current, "url", obs_data_get_string(settings2, "url"));
	obs_data_set_string(current, "video_offset", obs_data_get_string(settings2, "video_offset"));

	const char *json2 = obs_data_get_json(settings2);
	obs_data_set_string(current, "settings2", json2);

	const char *json3 = obs_data_get_json(settings3);
	obs_data_set_string(current, "settings3", json3);

	
	config_t *config = obs_frontend_get_global_config(); //global.ini

	const char *sect = config_get_section(config,1);
	obs_data_set_string(current, "sect", sect);

	config_t *config2 = obs_frontend_get_profile_config(); //basic.ini
	const char *sect2 = config_get_section(config2, 2);
	const char *citem = config_get_string(config2, "AdvOut", "FFURL");

	config_set_string(config2, "AdvOut", "FFURL", "udp://@127.0.0.1:9999");


	obs_data_set_string(current, "sect2", sect2);
	obs_data_set_string(current, "citem", citem);

	//obs_data_set_int(current, "nums", nums);

	return current;
}
*/

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
