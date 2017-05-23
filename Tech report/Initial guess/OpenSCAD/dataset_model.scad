//$fn=100;
//include <MCAD\regular_shapes.scad>

					/////PARAMETERS\\\\\

//VISIBLE ROOMS AND OBJECTS:
ceilings = true;
doors = true;
v315 = true;
v317 = true;
v314 = false;
serverRoom = false;
hallway = true;
windowsill = true;
windows = true;

//GENERAL
wall_t = 0.21; 
ceiling_h = 3.77;
room_x_def = 6.67;
door_y = 0.9;
door_z = 2.08;

//V315
v315_x = room_x_def;
v315_y = 7.02;
v315_z = ceiling_h;
v315_dist_2_door = 0.96;

//V317
v317_x = 4.12;
v317_y = 3.42;
v317_z = ceiling_h;
v317_dist_2_door = 0.93;


//HALLWAY CONNECTION
con_x = 0.83;
con_y = 1.12;
con_z = 2.45;

//HALLWAY
hal_x = 1.74;
hal_y = 10;
hal_z = 2.60;

//V314
v314_x = room_x_def;
v314_y = 3.41;
v314_z = ceiling_h;
v314_dist_2_door_hallway = 1.52;
v314_dist_2_door_server = 0.25;

//SERVER ROOM
serv_x = room_x_def;
serv_y = 3.41;
serv_z = ceiling_h;

//BEAMS
beam_x = v315_x;
beam_y = 0.39;
beam_z = 0.484;

//WINDOWSILL
windowsill_x = beam_y+0.06;
windowsill_h = 1.11;
windowsill_z = 0.17;

//WINDOW
window_z = 1.8;
window_y = 2.96;
window_x = 0.5;
window_h = windowsill_h + windowsill_z + 0.09;

//CABLE TRACK
track_x = 0.786;
track_y = v315_y+v314_y+serv_y;
track_z = 0.1;
track_h = 3.193;

					 /////MODEL\\\\
if(v315)	v315();
if(v317)	v317();
if(v314)	v314();
if(serverRoom)	serverRoom();
if(hallway) hallway();


					/////MODULES\\\\\

module room(x,y,z){
	difference(){
    	cube([x+wall_t,y+wall_t,z+wall_t]);
			if(ceilings){
				translate([wall_t,wall_t,wall_t]) cube([x-wall_t,y-wall_t,z-wall_t]);
			}
			else{
				translate([wall_t,wall_t,wall_t]) cube([x-wall_t,y-wall_t,z+wall_t]);
			}
    	
	}
}

module connection(x,y,z){
	difference(){
    	translate([0,0,wall_t])cube([x,y,z]);
    	translate([-0.25,0.05,wall_t+0.0001])cube([x+0.5,y-0.1,z-0.1]);
	}
}

module beamCorner(){
	translate([0,0,ceiling_h-beam_z+wall_t])cube([beam_x,beam_y,beam_z]);
	translate([room_x_def-beam_y,0,0])cube([beam_y,beam_y,ceiling_h]);
}

module windowsill(y){
		translate([v315_x-beam_y,0,windowsill_h])cube([windowsill_x,y,windowsill_z]);
}

module window(y){
	translate([v315_x - wall_t/2,0,window_h])cube([window_x,y,window_z]);
}

module cableTrack(y){
	translate([0,0,track_h+track_z])cube([track_x,y,track_z]);
}

module v315(){
	difference(){
	    	room(v315_x,v315_y,v315_z);
			if(doors){
				//DOOR 2 HALLWAY
				translate([-wall_t/2,v315_y+wall_t/2-con_y-v315_dist_2_door,wall_t])cube([wall_t*2,door_y,door_z]);
				//DOOR 2 V317
				translate([v315_x-v317_x+v317_dist_2_door+wall_t,v315_y-wall_t/2,wall_t])cube([door_y,wall_t*2,door_z]);
			}

			if(windows){
				translate([0,v315_y/2+beam_y/2+0.14,0])window(window_y);
				translate([0,beam_y/2+0.14,0])window(window_y);
			}
	}
	cableTrack(v315_y);

	translate([0,-wall_t/2,0])beamCorner();
	translate([0,v315_y/2-beam_y/2,0]) beamCorner();
	translate([0,v315_y-wall_t/2,0])beamCorner();

	if(windowsill){
   		windowsill(v315_y);
	}
}

module v317(){
	difference(){
	   translate([v315_x-v317_x,v315_y,0])room(v317_x,v317_y,v317_z);
		if(doors){
			//DOOR 2 V315
			translate([v315_x-v317_x+v317_dist_2_door+wall_t,v315_y-wall_t/2,wall_t])cube([door_y,wall_t*2,door_z]);
		}

		if(windows){
			translate([0,v315_y+beam_y,0])window(window_y);
		}
	}
	if(windowsill){
		translate([0,v315_y,0])windowsill(v317_y);
	}

	
}

module v314(){
	difference(){
	   translate([0,-v315_y+v314_y+wall_t,0])room(v314_x,v314_y,v314_z);
		if(doors){
			//DOOR 2 HALLWAY
			translate([-wall_t/2,-v314_y+v314_dist_2_door_hallway+wall_t*1.5,wall_t+0.0001])cube([wall_t*2,door_y,door_z]);
			//DOOR 2 SERVER ROOM
			translate([v314_dist_2_door_server+wall_t,-v314_y-wall_t/2,wall_t])cube([door_y,wall_t*2,door_z]);
		}

		if(windows){
			translate([0,-v314_y+beam_y,0])window(window_y-0.1);
		}
	}

	translate([0,-v314_y,0])cableTrack(v314_y);
	
	translate([0,-wall_t/2,0])beamCorner();
	translate([0,-v314_y-wall_t/2,0])beamCorner();
	
	if(windowsill){
		translate([0,-v314_y,0])windowsill(v314_y);
	}
}

module serverRoom(){
	difference(){
	translate([0,-(v315_y+v314_y)+serv_y+wall_t,0])room(serv_x,serv_y,serv_z);
		if(doors){
			//DOOR 2 V314
			translate([v314_dist_2_door_server+wall_t,-v314_y-wall_t/2,wall_t])cube([door_y,wall_t*2,door_z]);
		}

		if(windows){
			translate([0,-v314_y-serv_y+beam_y,0])window(window_y-0.1);
		}
	}
	translate([0,-v314_y-serv_y,0])cableTrack(v314_y);

	translate([0,-v314_y-wall_t/2,0])beamCorner();
	translate([0,-v314_y*2,0])beamCorner();

	if(windowsill){
		translate([0,-v314_y-serv_y,0])windowsill(v314_y);
	}
}

module hallway(){
	difference(){
		translate([-(hal_x+con_x),-v314_y,0])room(hal_x,hal_y,hal_z);
		translate([-(hal_x+con_x)+wall_t,v315_y-wall_t*2.5,wall_t])cube([hal_x-wall_t,wall_t*2,hal_z+wall_t]);

		if(doors){
			//DOOR V315
			translate([-con_x-wall_t/2,v315_y-con_y-v315_dist_2_door,wall_t+0.0001])cube([wall_t*2,con_y,door_z]);

			//DOOR V314
			translate([-con_x-wall_t/2,-v314_y+wall_t+v314_dist_2_door_hallway,wall_t+0.0001])cube([wall_t*2,con_y,door_z]);
		}
	}

	//HALLWAY CONNECTIONS
	//HALLWAY CONNECTION V315
	translate([-con_x,v315_y-con_y-v315_dist_2_door,0])connection(con_x+0.1,con_y,con_z);

	//HALLWAY CONNECTION V314
	translate([-con_x,-v314_y+wall_t+v314_dist_2_door_hallway,0])connection(con_x+0.1,con_y,con_z);
}





