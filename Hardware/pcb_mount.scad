fineness=50;
plate_thickness = 1;
//plate_width = 35*4 + 10;
plate_height = 8;
plate_width = 8;

//led_lead_dia = 2;
//led_lead_sep = 3;
//led_sep = 5.5;
//hoz_bar_sep = 20;
//vert_bar_sep = 20;
//post_height = 4;
//post_dia = 4;
//post_cutout_width = 1;
//post_hoz_sep = 10;
//post_vert_sep = 20;
//led_dia = 5;
//pad_dia=5;
//digit_sep=10;

// mounting lugs
lug_height=6;
lug_width=8;
lug_hole_dia=2;
lug_thickness=1.5;
lug_side_web=2;
lug_top_web=6;
lug_corner_offset=3;

body();

module body() {
bottom();
mounting_lugs();

module bottom(){
hole_offset = 2.54/2;
hole_diag_spacing = sqrt(2*pow(2,hole_offset));
translate([0,plate_width/2-lug_thickness/2,-lug_thickness/2]){
difference(){
cube (size = [plate_width,plate_height,lug_thickness], center = true);
union(){
translate([0.5+hole_diag_spacing/2,0.5+hole_diag_spacing/2,-2]){cylinder(h=2+lug_thickness,r=lug_hole_dia/2,$fn=fineness);}
translate([0.5+-hole_diag_spacing/2,0.5-hole_diag_spacing/2,-2]){cylinder(h=2+lug_thickness,r=lug_hole_dia/2,$fn=fineness);}
}
}
}
}

module mounting_lugs() {
// top and bottom
translate([0,0,lug_height/2]){
rotate([90,0,180]){lug(web_left=1);}
}

translate([-plate_width/2+lug_thickness/2,plate_height/2-lug_thickness/2,lug_height/2]){
rotate([90,0,90]){lug(web_left=0);}
}

}

module lug(web_left=1) {
difference(){
cube (size = [lug_width,lug_height,lug_thickness], center = true);
translate([-0,0,-2]){cylinder(h=2+lug_thickness,r=lug_hole_dia/2,$fn=fineness);}
}

// webbing
if (web_left){
translate([-lug_width/2+lug_thickness/2,-lug_height/2+lug_top_web/2,lug_thickness/2+lug_side_web/2]) {support_web();}
} else {
translate([lug_width/2-lug_thickness/2,-lug_height/2+lug_top_web/2,lug_thickness/2+lug_side_web/2]) {support_web();}
}
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
}
