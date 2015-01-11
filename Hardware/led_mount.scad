fineness=50;
plate_thickness = 1;
plate_width = 35*4 + 10;
plate_height = 50;
led_lead_dia = 2;
led_lead_sep = 3;
led_sep = 5.5;
hoz_bar_sep = 20;
vert_bar_sep = 20;
post_height = 4;
post_dia = 4;
post_cutout_width = 1;
post_hoz_sep = 10;
post_vert_sep = 20;
led_dia = 5;
pad_dia=5;
digit_sep=10;

// mounting lugs
lug_height=6;
lug_width=6;
lug_hole_dia=2;
lug_thickness=1;
lug_side_web=2;
lug_top_web=4;
lug_corner_offset=3;

body();

module body() {
plate();
cathode_posts();
anode_posts();
mounting_lugs();

// visualise LEDs
if (0){
led_vis_h();
translate([0,-vert_bar_sep,0]){led_vis_h();}
translate([0,vert_bar_sep,0]){led_vis_h();}

translate([-vert_bar_sep/2,-hoz_bar_sep/2,0]){led_vis_v();}
translate([-vert_bar_sep/2,hoz_bar_sep/2,0]){led_vis_v();}
translate([vert_bar_sep/2,-hoz_bar_sep/2,0]){led_vis_v();}
translate([vert_bar_sep/2,hoz_bar_sep/2,0]){led_vis_v();}
}
}

module mounting_lugs() {
// top and bottom
translate([0,-plate_height/2+lug_thickness/2,lug_height/2+plate_thickness/2]){ rotate([90,0,180]){lug();}}
translate([0,plate_height/2-lug_thickness/2,lug_height/2+plate_thickness/2]){ rotate([90,0,0]){lug();}}

// top left
translate([-plate_width/2+lug_width/2+lug_corner_offset,plate_height/2-lug_thickness/2,lug_height/2+plate_thickness/2]){ rotate([90,0,0]){lug();}}
translate([-plate_width/2+lug_thickness/2,plate_height/2-lug_width/2-lug_corner_offset,lug_height/2+plate_thickness/2]){ rotate([90,0,90]){lug();}}

// top right
translate([plate_width/2-lug_width/2-lug_corner_offset,plate_height/2-lug_thickness/2,lug_height/2+plate_thickness/2]){ rotate([90,0,0]){lug();}}
translate([plate_width/2-lug_thickness/2,plate_height/2-lug_width/2-lug_corner_offset,lug_height/2+plate_thickness/2]){ rotate([90,0,-90]){lug();}}

// bot left
translate([-plate_width/2+lug_width/2+lug_corner_offset,-plate_height/2+lug_thickness/2,lug_height/2+plate_thickness/2]){ rotate([90,0,180]){lug();}}
translate([-plate_width/2+lug_thickness/2,-plate_height/2+lug_width/2+lug_corner_offset,lug_height/2+plate_thickness/2]){ rotate([90,0,90]){lug();}}

// bot right
translate([plate_width/2-lug_width/2-lug_corner_offset,-plate_height/2+lug_thickness/2,lug_height/2+plate_thickness/2]){ rotate([90,0,180]){lug();}}
translate([plate_width/2-lug_thickness/2,-plate_height/2+lug_width/2+lug_corner_offset,lug_height/2+plate_thickness/2]){ rotate([90,0,-90]){lug();}}

}

module lug(rotate=0) {
difference(){
cube (size = [lug_width,lug_height,lug_thickness], center = true);
translate([0,0,-2]){cylinder(h=2+lug_thickness,r=lug_hole_dia/2,$fn=fineness);}
}

// webbing
translate([-lug_width/2+lug_thickness/2,-lug_height/2+lug_top_web/2,lug_thickness/2+lug_side_web/2]) {support_web();}
translate([lug_width/2-lug_thickness/2,-lug_height/2+lug_top_web/2,lug_thickness/2+lug_side_web/2]) {support_web();}
}

module support_web(){
diag=sqrt(pow(2,lug_top_web)+pow(2,lug_side_web));
rot=atan(lug_side_web/lug_top_web);
difference(){
cube (size = [lug_thickness,lug_top_web,lug_side_web], center=true);
translate([0,lug_top_web/2,-lug_side_web/2]){ // 0,0,0 lug_thickness/2,lug_top_web/2,0
  rotate(a=[-rot,0,0]){
    translate([0,-lug_top_web/2,lug_side_web/2]){ // 0,0,0 -lug_thickness/2,-lug_top_web/2,0
       translate([0.1,(-diag+lug_top_web)/2,0]){
        cube (size = [lug_thickness+0.5,diag,lug_side_web], center=true);
      }
    }
  }
}
}
}

module cathode_posts() {
// Four digits
translate([-vert_bar_sep*3/2-digit_sep*2,0,0]){cathode_posts_single();}
translate([-vert_bar_sep/2-digit_sep,0,0]){cathode_posts_single();}
translate([vert_bar_sep*3/2+digit_sep*2,0,0]){cathode_posts_single();}
translate([vert_bar_sep/2+digit_sep,0,0]){cathode_posts_single();}

// and a pair of separators
translate([-led_lead_sep/2,-led_sep*3/2,0]){corner_post();}
translate([-led_lead_sep/2,led_sep*3/2,0]){corner_post();}

}

module anode_posts() {
// Four digits
translate([-vert_bar_sep*3/2-digit_sep*2,0,0]){anode_posts_single();}
translate([-vert_bar_sep/2-digit_sep,0,0]){anode_posts_single();}
translate([vert_bar_sep*3/2+digit_sep*2,0,0]){anode_posts_single();}
translate([vert_bar_sep/2+digit_sep,0,0]){anode_posts_single();}

// and a pair of separators
translate([led_lead_sep/2,-led_sep*3/2,0]){corner_post();}
translate([led_lead_sep/2,led_sep*3/2,0]){corner_post();}
}

module cathode_posts_single() {
color(""){
//bottom
translate([-post_hoz_sep+led_lead_sep/2,-post_vert_sep+led_lead_sep/2,0]){corner_post(rotate=0);}
translate([post_hoz_sep-led_lead_sep/2,-post_vert_sep+led_lead_sep/2,0]){corner_post(rotate=0);}

//middle
translate([-post_hoz_sep+led_lead_sep/2,+led_lead_sep/2,0]){corner_post(rotate=0);}
translate([post_hoz_sep-led_lead_sep/2,+led_lead_sep/2,0]){corner_post(rotate=0);}
translate([-post_hoz_sep+led_lead_sep/2,-led_lead_sep/2,0]){corner_post(rotate=0);}
translate([post_hoz_sep-led_lead_sep/2,-led_lead_sep/2,0]){corner_post(rotate=0);}

//top
translate([-post_hoz_sep+led_lead_sep/2,post_vert_sep-led_lead_sep/2,0]){corner_post(rotate=0);}
translate([post_hoz_sep-led_lead_sep/2,post_vert_sep-led_lead_sep/2,0]){corner_post(rotate=0);}
}
}

module anode_posts_single() {

//bottom
color(""){
translate([-post_hoz_sep+led_lead_sep/2,-post_vert_sep-led_lead_sep/2,0]){corner_post(rotate=0);}
translate([post_hoz_sep-led_lead_sep/2,-post_vert_sep-led_lead_sep/2,0]){corner_post(rotate=0);}
translate([-post_hoz_sep-led_lead_sep/2,-post_vert_sep+led_lead_sep/2,0]){corner_post(rotate=0);}
translate([post_hoz_sep+led_lead_sep/2,-post_vert_sep+led_lead_sep/2,0]){corner_post(rotate=0);}
}
//middle

translate([-led_sep,-vert_bar_sep/2+led_sep,0]){corner_post(rotate=0);}
translate([led_sep,-vert_bar_sep/2+led_sep,0]){corner_post(rotate=0);}
translate([-post_hoz_sep-led_lead_sep/2,-led_lead_sep/2,0]){corner_post(rotate=0);}
translate([post_hoz_sep+led_lead_sep/2,-led_lead_sep/2,0]){corner_post(rotate=0);}

translate([-post_hoz_sep-led_lead_sep/2,led_lead_sep/2,0]){corner_post(rotate=0);}
translate([post_hoz_sep+led_lead_sep/2,led_lead_sep/2,0]){corner_post(rotate=0);}

//top
translate([-post_hoz_sep+led_lead_sep/2,post_vert_sep+led_lead_sep/2,0]){corner_post(rotate=0);}
translate([post_hoz_sep-led_lead_sep/2,post_vert_sep+led_lead_sep/2,0]){corner_post(rotate=0);}
color(""){
translate([-post_hoz_sep-led_lead_sep/2,post_vert_sep-led_lead_sep/2,0]){corner_post(rotate=0);}
translate([post_hoz_sep+led_lead_sep/2,post_vert_sep-led_lead_sep/2,0]){corner_post(rotate=0);}
}
}

module plate() {
difference() {
cube (size = [plate_width,plate_height,plate_thickness], center = true);
// Four digits
translate([-vert_bar_sep*3/2-digit_sep*2,0,0]){led_holes();}
translate([-vert_bar_sep/2-digit_sep,0,0]){led_holes();}
translate([vert_bar_sep*3/2+digit_sep*2,0,0]){led_holes();}
translate([vert_bar_sep/2+digit_sep,0,0]){led_holes();}

// and a pair of separators
translate([0,-led_sep,0]){led_hole_h();}
translate([0,led_sep,0]){led_hole_h();}
}

// corner pads
translate([-plate_width/2-pad_dia/4,-plate_height/2-pad_dia/4,-plate_thickness/2]){cylinder (h=plate_thickness,r=pad_dia/2,$fn=fineness);}
translate([-plate_width/2-pad_dia/4,plate_height/2+pad_dia/4,-plate_thickness/2]){cylinder (h=plate_thickness,r=pad_dia/2,$fn=fineness);}
translate([plate_width/2+pad_dia/4,-plate_height/2-pad_dia/4,-plate_thickness/2]){cylinder (h=plate_thickness,r=pad_dia/2,$fn=fineness);}
translate([plate_width/2+pad_dia/4,plate_height/2+pad_dia/4,-plate_thickness/2]){cylinder (h=plate_thickness,r=pad_dia/2,$fn=fineness);}
}

module led_holes(){
translate([0,-hoz_bar_sep,0]){hoz_bar();}
translate([0,0,0]){hoz_bar();}
translate([0,hoz_bar_sep,0]){hoz_bar();}
translate([-vert_bar_sep/2,-hoz_bar_sep/2,0]){vert_bar();}
translate([-vert_bar_sep/2,hoz_bar_sep/2,0]){vert_bar();}
translate([vert_bar_sep/2,-hoz_bar_sep/2,0]){vert_bar();}
translate([vert_bar_sep/2,hoz_bar_sep/2,0]){vert_bar();}

}

module hoz_bar(){
led_hole_v();
translate([-led_sep,0,0]){led_hole_v();}
translate([led_sep,0,0]){led_hole_v();}
}

module led_vis_h() {
color("blue", 0.5){
translate ([0,0,-4]){cylinder(h=5,r=led_dia/2,$fn=fineness);}
translate ([-led_sep,0,-4]){cylinder(h=5,r=led_dia/2,$fn=fineness);}
translate ([led_sep,0,-4]){cylinder(h=5,r=led_dia/2,$fn=fineness);}
}
}

module vert_bar(){
led_hole_h();
translate([0,-led_sep,0]){led_hole_h();}
translate([0,led_sep,0]){led_hole_h();}
}

module led_vis_v() {
color("blue", 0.5){
translate ([0,0,-4]){cylinder(h=5,r=led_dia/2,$fn=fineness);}
translate ([0,-led_sep,-4]){cylinder(h=5,r=led_dia/2,$fn=fineness);}
translate ([0,led_sep,-4]){cylinder(h=5,r=led_dia/2,$fn=fineness);}
}
}

module led_hole_v() {
translate ([0,-led_lead_sep/2,-2]){cylinder(h=5,r=led_lead_dia/2,$fn=fineness);}
translate ([0,led_lead_sep/2,-2]){cylinder(r=led_lead_dia/2,h=5,$fn=fineness);}
}


module led_hole_h() {
translate ([-led_lead_sep/2,0,-2]){cylinder(h=5,r=led_lead_dia/2,$fn=fineness);}
translate ([led_lead_sep/2,0,-2]){cylinder(r=led_lead_dia/2,h=5,$fn=fineness);}
}


module corner_post(rotate=0){
rotate([0,0,rotate]){
difference(){
cylinder(h=post_height,r=post_dia/2,$fn=fineness);
translate([0,0,post_height]){
cube (size = [post_dia+1,post_cutout_width,3*post_cutout_width], center = true);
cube (size = [post_cutout_width,post_dia+1,3*post_cutout_width], center = true);
}
}
}
}
