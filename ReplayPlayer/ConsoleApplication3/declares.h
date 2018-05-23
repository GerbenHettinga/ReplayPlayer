// -- Global variable/method declarations -- [point of file: keep main.cpp cleaner]
	
	HANDLE process_hook;				// [Storing this as a global to avoid having to pass it into EVERY call to a memory editing method]
	
	// 'Function Status' Variables
	bool function_lock, debug_mode;
	bool max_jiffied, max_zoomed, max_tilted, noclip, y_blocker;
	bool cinematic_hold;
	bool weather_control, time_control;
	bool freeze_all, freeze_replay, freeze_camera, save_camera;
	bool vehicle_lock, headlight_control, invisible;
	bool trails, no_camera_shake;
	
	// Other Variables
	string picker_mode;
	int picker_current_digit;
	float save_camera_matrix [16];
	int silly_sizes, silly_angles;		// (these are 'function status' guys too, but cannot be bool because they have 2 different on-states)
	
	// Function Methods					// [Some have two optional params: generally, the toggle-style guys which may be called from within others]
	void init_freeplay();				// [							   eg. if they need to be called to explicitly disable, rather than 'toggle', from do_disable()]
	
	void do_lock();
	
	void do_max_jiffy(string force = "", bool silent = false);
	void do_zoom_limits(string force = "", bool silent = false);
	void do_tilt_limits(string force = "", bool silent = false);
	void do_noclip(string force = "", bool silent = false);
	void do_y_blocker(string force = "", bool silent = false);
	
	void do_vehicle_camera(int mode, bool silent = false);
	
	void do_cinematic_hold(string force = "", bool silent = false);
	void do_cinematic_change();
	void do_cinematic_custom();
	void do_cinematic_custom2();
	
	void do_weather_control(string force = "", bool silent = false);
	void do_weather(int mode);
	void do_weather_custom(string force = "", bool silent = false);
	
	void do_time_control(string force = "", bool silent = false);
	void do_time(int hour, int min);
	
	void do_freeze_all(string force = "", bool silent = false);
	void do_freeze_replay(string force = "", bool silent = false);
	void do_freeze_camera(string force = "", bool silent = false);
	void do_save_camera();
	void do_load_camera();
	
	void do_vehicle_lock(string force = "", bool silent = false);
	void do_carcol_p(string force = "", bool silent = false);
	void do_carcol_s(string force = "", bool silent = false);
	void do_headlight_control(string force = "", bool silent = false);
	void do_headlight_swap();
	void do_siren_swap();
	void do_invisible(string force = "", bool silent = false);
	
	void do_trails();				/* *** (re force/silent guys: dont think we want them here, game crashes if not in menu when trails toggled, so never wanna do unless explicit by user... ? *** */
	void do_no_camera_shake(string force = "", bool silent = false);
	void do_silly_sizes(string force = "", bool silent = false);
	void do_silly_angles(string force = "", bool silent = false);
	
	void do_picker(int new_digit);
	void do_picker_weather();
	void do_picker_colourP();
	void do_picker_colourS();
	
	void do_manual_zoom(string mode, bool slowmo);
	void do_manual_cam_posX(string mode, bool slowmo);
	void do_manual_cam_posY(string mode, bool slowmo);
	void do_manual_cam_posZ(string mode, bool slowmo);
	
	void do_debug(string force = "", bool silent = false);
	void do_disable();

