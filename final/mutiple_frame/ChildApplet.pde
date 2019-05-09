import java.awt.Frame;
import processing.core.*;
import java.awt.*;
import java.applet.*;

public class ChildApplet extends PApplet {

  int x, y, w = 128, h = 128;
  float f;
  PVector acr, pos, ofst;

  ChildApplet(int idx) {
    //super();
    acr = new PVector(idx*hInterval-amt*.5*hInterval+960, 500);
    ofst = new PVector(0, 0);
    pos = new PVector(0, 0);
    f = TWO_PI/amt*idx;
    //PApplet.runSketch(new String[] {this.getClass().getSimpleName()}, this);
  }

  public void update() {
    
    ofst.set(
      cos(f)*hRange, sin(f)*vRange
    );
    
    f += PI*.001;

    pos.set(
      acr.x + ofst.x, 
      acr.y + ofst.y
      );
      
    w = round(128 + sin(f*2)*32);
    h = round(128 + cos(f*4)*32);
    
    //w = round(128);
    //h = round(128);

    x = int(pos.x);
    y = int(pos.y);
  }
  
  
  //public void draw() {
  //  rect(10,10,20,20);
  //}
}