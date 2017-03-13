#include <AFMotor.h>

int vel;
int c;
float danger;
int z;
int sleep1 = 600;
int center= 400;
int sleep2 = 1050; 
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);

#define ST_BLOCK 25
int st_ozto=0;    // Estado de bloqueo. 0->No bloqueo ....5->bloqueo
int st_ozto_old=0;  // Guardar el ultimo estado 0 Libre 1 bloqueo

static int npck=0;

#define POS_2LINE       "\x1b[2;0H"
#define POS_4LINE       "\x1b[4;0H"
#define DEL_LINE  "\x1b[0K\x1b[0m\r\n\x1b[0K"

#define CLS "\x1b[2J\x1b[H"

#define POS_MIN "\x1b[6;0H"

#define BLINK "\x1b[5m\x1b[31m"
#define INVERSE "\x1b[7m"
#define NORMAL "\x1b[0m"

#define MAX_FRAME 16

int get_cmd(int cmd,int *tbl, int size)
{
int i;
  for(i=0;i<size;i++) {
    if(tbl[i] == cmd)
      return(i);
  }
  return(-1);
}

char *frame[]= {
  "\x1b[6;0H", "\x1b[7;0H", "\x1b[8;0H", "\x1b[9;0H", "\x1b[10;0H", "\x1b[11;0H",
  "\x1b[12;0H", "\x1b[13;0H", "\x1b[14;0H", "\x1b[15;0H", "\x1b[16;0H", "\x1b[17;0H",
  "\x1b[18;0H", "\x1b[19;0H", "\x1b[20;0H", "\x1b[21;0H"
};

char buf[256];


char *print_frame()
{
  sprintf(buf,"\x1b[1;10HABIADURA:\x1b[1;30HNORABIDEA:\x1b[1;50HLUZEERA:\n\n\rKONTROL MEZUA\n\r=============\n\r");
  return(buf);
}

#define MAX_VEL_TYPE 5

char *msg_vel[]={ "-100","   0"," 80%"," 90%","100%"};

char *print_vel(int vel)
{
  if(vel <-1 || vel > 3)
    return("");
  sprintf(buf,"\x1b[1;20H\x1b[31m%s\x1b[0m",msg_vel[vel+1]);
  return(buf);
}


#define MAX_DIR_TYPE 3

int tbl_dir[]={-100,0,100};

char *msg_dir[]={ "EZKERRA","  ZUZEN","ESKUINA"};

char *print_dir(int dir)
{
int id;
  if((id=get_cmd(dir,tbl_dir,MAX_DIR_TYPE))==-1)
    return("");
  sprintf(buf,"\x1b[1;40H\x1b[31m%s\x1b[0m",msg_dir[id]);
  return(buf); 
}

#define MAX_CMD 8

int tbl_cmd[]={ 's',' ','a','d','w','i','o','p'};
char *msg_cmd[]={ ">> Atzera",">> Geldi",">> Aurrera Motel",">> Aurrera Normal",">> Aurrera Bizkor",">> Ezkerra",">> Zuzen",">> Eskuina"};

char *print_msg(char *msg,int type)
{
static int nmsg=0;
  if(type) {
    sprintf(buf,"%s%s\x1b[31m%s%s",frame[nmsg%MAX_FRAME],
      (nmsg%2) ? INVERSE : "", msg,DEL_LINE);
  } else {
    sprintf(buf,"%s%s%s%s",frame[nmsg%MAX_FRAME],
      (nmsg%2) ? INVERSE : "", msg,DEL_LINE);
  }
  nmsg++;
  return(buf);
}

char *print_cmd(int cmd)
{
int id_cmd;
  if((id_cmd=get_cmd(cmd,tbl_cmd,MAX_CMD)) != -1)
    return(print_msg(msg_cmd[id_cmd],0));
  return("");
}

#define MAX_LUZ 300.0
#define MIN_LUZ 5.0

char *print_luze(float luz)
{
  if(luz < MIN_LUZ || luz > MAX_LUZ)
    return("");
    sprintf(buf,"\x1b[1;60H\x1b[31m%03d cm\x1b[0m",(int)luz);
  return(buf);
}

char *print_ozto(int flag)
{
  if(flag) {
    return("\x1b[2;50H\x1b[7mOZTOPOA\x1b[0m");
  }
  return("\x1b[2;50H\x1b[0m       ");
}




int forward (int parameter){
  motor1.run(FORWARD);
  if (parameter == 1){
    //Serial.println("\nAurrerantz %80\n ");
    motor1.setSpeed(200);
    vel = 1;
  } else if (parameter == 2){
    //Serial.println("\nAurrerantz %90\n ");
    motor1.setSpeed(225);
    vel = 2;
  } else if (parameter == 3){
    //Serial.println("\nAurrerantz %100\n ");
    motor1.setSpeed(255);
    vel = 3;
  } else
    return(-1); 
  Serial.print(print_vel(parameter));
  return(0);
}

int backward(){
  vel = -1;
  printf("%s\n",print_vel(-1));
  //Serial.println("\nAtzerantz %100\n ");
  motor1.run(BACKWARD);
  motor1.setSpeed(255);
}
int frenar(int vel){
  //Serial.println("\n Autoa gelditu da!! \n");
  if ( vel == -1 ){
    motor1.run(RELEASE);
    motor1.run(FORWARD);
    motor1.setSpeed(255);
    delay(350);
    motor1.run(RELEASE);
  } else if ( vel = 1 ){
    motor1.run(RELEASE);
    motor1.run(BACKWARD);
    motor1.setSpeed(255);
    delay(150);
    motor1.run(RELEASE);
  } else if ( vel = 2 ){
    motor1.run(RELEASE);
    motor1.run(BACKWARD);
    motor1.setSpeed(255);
    delay(250);
    motor1.run(RELEASE);
  } else if ( vel = 3 ){
    motor1.run(RELEASE);
    motor1.run(BACKWARD);
    motor1.setSpeed(255);
    delay(350);
    motor1.run(RELEASE);
  }
  vel = 0;
}

int turn_left(){
  if (z == -100) {
    //Serial.println("\n Ezkerra \n");
  } else if (z == 0){
    //Serial.println("\n Ezkerra \n");
    motor2.run(BACKWARD);
    motor2.setSpeed(255);
    delay(sleep1);
    z = z -100;
    Serial.print(print_dir(z));
    motor2.run(RELEASE);
  } else if (z == 100){
    //Serial.println("\n Ezkerra \n");
    motor2.run(BACKWARD);
    motor2.setSpeed(255);
    delay(sleep2);
    z = z - 200;
    Serial.print(print_dir(z));
    motor2.run(RELEASE);
  }
}

int turn_center(){
  
  if (z == -100){
    //Serial.println("\n Zuzen \n");
    motor2.run(FORWARD);
    motor2.setSpeed(255);
    delay(300);
    z = z + 100;
    Serial.print(print_dir(z));
    motor2.run(RELEASE);
  } else if (z == 0){
    //Serial.println("\n Zuzen \n");
  } else if (z == 100) {
    //Serial.println("\n Zuzen \n");
    motor2.run(BACKWARD);
    motor2.setSpeed(255);
    delay(450);
    z = z - 100;
    Serial.print(print_dir(z));
    motor2.run(RELEASE);
  }
}

int turn_right(){
  
  if (z == -100) {
    //Serial.println("\n Eskuina \n");
    motor2.run(FORWARD);
    motor2.setSpeed(255);
    delay(sleep2);
    z = z + 200;
    Serial.print(print_dir(z));
    motor2.run(RELEASE);
  } else if (z == 0){
    //Serial.println("\n Eskuina \n");
    motor2.run(FORWARD);
    motor2.setSpeed(255);
    delay(sleep1);
    z = z + 100;
    Serial.print(print_dir(z));
    motor2.run(RELEASE);
  } else if (z == 100){
    //Serial.println("\n Eskuina \n");
  } 
}

int circulo1(int parameter){
  if (parameter == 1){
    turn_left();
    forward(3);
    delay(5000);
    frenar(vel);
  } else if (parameter == 2) {
    turn_left();
    forward(3);
    delay(4800);
  } 
}


int circulo ( int number ){
  turn_left();
  forward(3);
  delay( number*4150 );
  frenar(vel);
}


int distance_sensor(int out, int in, int wait){
  float cm;
  static unsigned int count=0;
  pinMode(out, OUTPUT);
  pinMode(in, INPUT);
  digitalWrite(out,LOW); /* Por cuestión de estabilización del sensor*/
  delayMicroseconds(2);
  digitalWrite(out, HIGH); /* envío del pulso ultrasónico*/
  delayMicroseconds(10);
  digitalWrite(out, LOW);
  cm = pulseIn(in, HIGH) / 58.0;
  cm = (int(cm * 100.0)) / 100.0;
  count++; 
  if(!(count % 100))
    Serial.print(print_luze(cm));
  return cm; 
}


void setup(){
  Serial.begin(9600);
  z = 0;
  danger = 20;
  vel = 0;
  c = 0;
  pinMode(31, OUTPUT);
  pinMode (53, OUTPUT);
  digitalWrite(31, LOW);
  digitalWrite(53, LOW);
  delay(2000);
  Serial.print(CLS);
  Serial.print(print_frame());
}

void loop(){
  float distance = distance_sensor(26, 24, 15);
  int serial;
  char lectura; 
  if((distance < danger and distance > 5.10) or (distance > 0 and distance < 2.50 )){
    //Serial.println("\n OZTOPOA!! \n");
    //Serial.print(distance);
    //Serial.println("zm");
    //Serial.print(distance);
    //Serial.println("zm");
    digitalWrite(31, HIGH);
    digitalWrite(53, LOW);
    
    if(st_ozto++ >= ST_BLOCK) {
        st_ozto=ST_BLOCK;
        if(st_ozto_old == 0) {
           frenar(vel);
           Serial.print(print_msg("OZTOPOA",1));
           Serial.print(print_ozto(1));
           st_ozto_old = 1;
        }
    }
     
    if((serial=Serial.available())  > 0) {  
      if((lectura=Serial.read()) == 'i') {
        turn_left();
      } else if(lectura == 'o'){
        turn_center();
      } else if(lectura == 'p'){
        turn_right();
      } else if ( lectura == 's'){
        //Serial.println("\n Autoa atzera doa!!\n");
        while(((distance=distance_sensor(26, 24, 15)) < danger and distance > 5.10) or (distance > 0 and distance < 2.50 )){
          motor1.run(BACKWARD);
          motor1.setSpeed(255);
          delay(15);
        }
        st_ozto_old = st_ozto=0;
        Serial.print(print_ozto(0));
          
        motor1.run(RELEASE);
      }
    }
  } else {
    if(st_ozto > 0){
      st_ozto--;
    }else{
      if(st_ozto_old == 1) {
        Serial.print(print_ozto(0));
        st_ozto_old = 0; 
      }
    }
    digitalWrite(31, LOW);
    digitalWrite(53, HIGH);
    if(serial=Serial.available()  > 0) {
      lectura=Serial.read();
      //Serial.println(lectura);
      Serial.print(print_cmd(lectura));
      if ( lectura == 'i' ) {
        turn_left();
      } else if(lectura == 'o'){
        turn_center();
      } else if(lectura == 'p'){
        turn_right();
      } else if(lectura == 's'){
        backward();
      } else if(lectura == 'a') {
        forward(1);
        danger = 25.00;
        vel = 1;
      } else if(lectura == 'd') {
        forward(2);
        danger = 33.00;
        vel = 2;
      } else if(lectura == 'w') {
        forward(3);
        danger = 40;
        vel = 3;
      } else if(lectura == ' ' ) {
        frenar(vel);
      } else if (lectura == 49){
        circulo1(1);
      } else if (lectura > 49 and lectura < 58){
        circulo1(2);
        circulo(lectura - 49);   
      }
    }
  }
}

