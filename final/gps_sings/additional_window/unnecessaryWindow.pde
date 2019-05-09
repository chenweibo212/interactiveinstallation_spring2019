import processing.core.*;
import java.awt.*;
import java.applet.*;


public class unnecessaryWindow extends PApplet {
  //String cname;
  //int handle;
  String[] buttonList = {"3 state button", "button", "button drop down", "button list box", "button menu", "checkbox", "checked", "clickable", "clock", "closed", "collapsed", "comb box", "context menu", "default", "desktop", "dialog", "dialog page", "disabled", "document", "edit", "edit combo", "edit spin box", "extended select list box", "expanded", "file upload edit", "forms mode off", "forms mode on", "frame", "ftp link", "graphic", "grayed", "header bar", "group box", "header level 1 to 6", "hot key edit", "html document body", "html farm", "icon", "image map link", "list box", "list view", "menu", "multi select list box", "mews link", "not checked", "on mouse over", "opened", "outline button", "pressed", "password edit", "progress bar", "radio button", "read only edit", "same page link", "scroll bar", "send mail link", "spin box", "split button", "start button", "start menu", "status bar", "sub menu", "tab", "table", "table cell", "table column", "task bar", "tool bar", "track bar", "tool tip", "tree view", "up down scroll bar", "up down slider", "heading level 1", "heading level 2", "heading level 3", "heading level 4", "heading level 5", "heading level 6"};
  float x,increase;
  
  unnecessaryWindow() {
    super();
    PApplet.runSketch(new String[] {this.getClass().getSimpleName()}, this);
  }
   
  public void settings() {
    size((int)random(100,400), (int)random(100,400));
  }


  public void setup() {
    //println(args);
    //cname=args[0];
    //handle=int(args[1]);
    //getSurface().setTitle(cname+":"+handle);
    textFont(font);
    noFill();
    x = 0;
    increase = 0;
   //listening from port 9001
    oscP5 = new OscP5(this,12000);
   //sent address to other application
    myRemoteLocation = new NetAddress("192.168.1.153",12000);   
    registerMethod("pre", this);    
  }
  
  void pre() {
    //Frame needs to exist before you call this method
    getSurface().setLocation((int)random(width, displayWidth-width), (int)random(height, displayHeight-height)); 
    //getSurface().setLocation(xPos, yPos); 
    unregisterMethod("pre", this);
  }

  public void draw() {
    background(200);
    fill(20);
    textAlign(CENTER);
    
    text(buttonList[textIndex1],width/2,height * 1/10);
    text(buttonList[textIndex2],width/2,height * 2/10);
    text(buttonList[textIndex3],width/2,height * 3/10);
    text(buttonList[textIndex4],width/2,height * 4/10);
    text(buttonList[textIndex5],width/2,height * 5/10);
    text(buttonList[textIndex6],width/2,height * 6/10);
    text(buttonList[textIndex7],width/2,height * 7/10);
    text(buttonList[textIndex8],width/2,height * 8/10);
    text(buttonList[textIndex9],width/2,height * 9/10);

    //if (x > width){
    //  x = (int)random(width);
    //  increase = 0;
    //}
    //printArray(buttonList);
  }
  
  void mousePressed(){
    surface.setVisible(false); 
  }
  
  void setInVisible(){
    frame.dispose();
    surface.setVisible(false); 
  }
}