import processing.core.*;
import java.awt.*;
import java.applet.*;

import oscP5.*;
import netP5.*;

OscP5 oscP5;
NetAddress myRemoteLocation;

int textIndex1, textIndex2, textIndex3, textIndex4, textIndex5, textIndex6, textIndex7, textIndex8, textIndex9;
int startSignal;

boolean centered, displayed, removed;
boolean addWindow, subWindow;
int ctr=100;

int peoplecounting, startpeople;

int startTime, currentTime, endTime;

PFont font;

generateWindow moreWindow;

public void settings() {
  size(320, 240);
}

void setup() { 
   //listening from port 9001
   oscP5 = new OscP5(this,12000);
   //sent address to other application
   myRemoteLocation = new NetAddress("10.18.133.189",12000);  
   
   addWindow = false;
   subWindow = false;
   startTime = millis();
   endTime = 5000;
   
   moreWindow = new generateWindow();
   
   font = createFont("Roboto-Light.ttf", 15);
   textFont(font);
}

void draw() {
  background(100);
  //println("people"+ peoplecounting);
 
  if(displayed){
    currentTime = millis()-startTime;
    if (currentTime >= endTime){
      moreWindow.addWindow();
      startTime = millis();
    }
  } 
  
  if(mousePressed && (mouseButton == RIGHT)){
      moreWindow.removeWindow();
  }
   fill(10);
   text(textIndex1,10,height/2);
   text(textIndex2,40,height/2);
   text(textIndex3,70,height/2);
   text(textIndex4,100,height/2);
   text(textIndex5,130,height/2);
   text(textIndex6,160,height/2);
   text(textIndex7,190,height/2);
   text(textIndex8,220,height/2);
   text(textIndex9,250,height/2);
   text(startSignal,280,height/2);
}

void mousePressed() {
  println("mousePressed in primary window");
  displayed = true;
}

void keyPressed(){
}


class generateWindow {
  ArrayList<unnecessaryWindow> windows;

  generateWindow() {
    //origin = position.copy();
    windows = new ArrayList<unnecessaryWindow>();
  }

  void addWindow() {
    windows.add(new unnecessaryWindow());
  }    
  
  void removeWindow(){
     for (int i = windows.size()-1; i >= 0; i--) {
      unnecessaryWindow p = windows.get(i);
      p.setInVisible();
    }
    
    //for (int i = particles.size()-1; i >= 0; i--) {
    //  Particle p = particles.get(i);
    //  p.run();
    //  if (p.isDead()) {
    //    particles.remove(i);
    //  }
    //}
  }
}

void oscEvent(OscMessage theOscMessage){
   print("### received an osc message.");
   print(" addrpattern: "+ theOscMessage.addrPattern());
   println(" typetag: "+ theOscMessage.typetag());
   //if(theStartMessage.checkAddrPattern("start/index/0")==true){
   //   startSignal = theStartMessage.get(0).intValue();
   //   println("start:"+startSignal);
   //   if(startSignal == 1){
   //     displayed = true;
   //   }
   //}
  //}
  if(theOscMessage.checkAddrPattern("text/index/0")==true){
    textIndex1 = theOscMessage.get(0).intValue();
    println("index1:"+textIndex1);
  }
   if(theOscMessage.checkAddrPattern("text/index/1")==true){
    textIndex2 = theOscMessage.get(0).intValue();
    println("index2:"+textIndex2);
  }
   if(theOscMessage.checkAddrPattern("text/index/2")==true){
    textIndex3 = theOscMessage.get(0).intValue();
    println("index3:"+textIndex3);
  }
   if(theOscMessage.checkAddrPattern("text/index/3")==true){
    textIndex4 = theOscMessage.get(0).intValue();
    println("index4:"+textIndex4);
  }
   if(theOscMessage.checkAddrPattern("text/index/4")==true){
    textIndex5 = theOscMessage.get(0).intValue();
    println("index5:"+textIndex5);
  }
   if(theOscMessage.checkAddrPattern("text/index/5")==true){
    textIndex6 = theOscMessage.get(0).intValue();
    println("index6:"+textIndex6);
  }
   if(theOscMessage.checkAddrPattern("text/index/6")==true){
    textIndex7 = theOscMessage.get(0).intValue();
    println("index7:"+textIndex7);
  }
   if(theOscMessage.checkAddrPattern("text/index/7")==true){
    textIndex8 = theOscMessage.get(0).intValue();
    println("index8:"+textIndex8);
  }
   if(theOscMessage.checkAddrPattern("text/index/8")==true){
    textIndex9 = theOscMessage.get(0).intValue();
    println("index9:"+textIndex9);
  }
  
   if(theOscMessage.checkAddrPattern("start/index/0")==true){
     startSignal = theOscMessage.get(0).intValue();
     println("start:"+startSignal);
   }
   
   if(startSignal == 1){
     displayed = true;
   }
}