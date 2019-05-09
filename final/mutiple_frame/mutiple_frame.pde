ChildApplet [] cas;
ChildFrame [] cfs;

int amt = 11;
float hInterval = 150;
float hRange = 100;
float vRange = 200;

int startTime, currentTime, endTime;
boolean erase;

//import oscP5.*;
//import netP5.*;

//OscP5 oscP5;
//NetAddress myRemoteLocation;

int stopSignal;

void setup() {
  //oscP5 = new OscP5(this,12000);
  //myRemoteLocation = new NetAddress("10.18.133.189",12000); 
  
  size(150, 150);
  cas = new ChildApplet[amt];
  cfs = new ChildFrame[amt];

  for (int i=0; i<amt; i++) {
    cas[i] = new ChildApplet(i);
    cfs[i] = new ChildFrame(cas[i]);
  }
  startTime = millis();
  endTime = 125000;
}

void draw() {

  background(255);

  for (int i=0; i<amt; i++) {
    cas[i].update();
    cfs[i].setBounds(cas[i].x-cas[i].w/2, cas[i].y-cas[i].h/2, cas[i].w+19, cas[i].h+48);
  }
  println(millis());
  currentTime = millis() - startTime;
  if (currentTime >= endTime){
    exit();
  }
}

//void oscEvent(OscMessage theOscMessage){
//   if(theOscMessage.checkAddrPattern("start/index/0")==true){
//     stopSignal = theOscMessage.get(0).intValue();
//     println("start:"+stopSignal);
//   }
   
//   if(stopSignal == 1){
//     erase = true;
//   }
//}