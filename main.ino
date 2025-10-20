
#define l2 A0
#define l1 A1
#define c A2
#define r1 A3
#define r2 A4
#define lm1 9
#define lm2 10
#define rm1 5
#define rm2 6
float lasterror=0;
float P;
float I=0;
float D;
int m=1000;
float kp=0.001;
float ki=0;
float kd=0.001;

void setup()
{	
  pinMode(l2, INPUT);
  pinMode(l1,INPUT);
  pinMode(c,INPUT);
  pinMode(r1,INPUT);
  pinMode(r2,INPUT);
  pinMode(lm1,OUTPUT);
  pinMode(lm2,OUTPUT);
  pinMode(rm1,OUTPUT);
  pinMode(rm2,OUTPUT);
}

void loop()
{
  int v[5]={digitalRead(l2),digitalRead(l1),digitalRead(c),digitalRead(r1),digitalRead(r2)};
  int p=(v[1]+v[2]*2+v[3]*3+v[4]*4)*m;
  int q=v[0]+v[1]+v[2]+v[3]+v[4];
  float pos;
  if(q!=0){pos=p/q;}
  else {pos=2*m;}
  
  float error=2*m-pos;
  P=error;
  I+=error;
  D=error-lasterror;
  lasterror=error;
  float value=kp*P+ki*I+kd*D;
  int leftmotor=basespeed-value;
  int rightmotor=basespeed+value;
  leftmotor=constrain(leftmotor,0,255);
  rightmotor=constrain(rightmotor,0,255);
  analogWrite(lm1,leftmotor);
  analogWrite(lm2,0);
  analogWrite(rm1,rightmotor);
  analogWrite(rm2,0);
  
}