    String incomingByte;
    int vmRight=2;
    int vmLeft=3;
    const int xPin = A0;
  const int yPin = A1;
  const int zPin = A2;
  int minVal = 265;
  int maxVal = 320;
  double x;
  double y;
  double z;
  double x1;
  double y1;
  double z1;
  const int pwPin = 12;
  int arraysize = 9;
  int rangevalue[] = {  0, 0, 0, 0, 0, 0, 0, 0, 0};
  long pulse;
  int modE;
  
  
    void setup()
    {
      pinMode(LED_BUILTIN, OUTPUT);
    pinMode(vmRight,OUTPUT);
    pinMode(vmLeft,OUTPUT);
    pinMode(pwPin, INPUT);
    Serial.begin(9600);
    int xRead = analogRead(xPin);
  int yRead = analogRead(yPin);
  int zRead = analogRead(zPin);
   int xAng = map(xRead, minVal, maxVal, -90, 90);
  int yAng = map(yRead, minVal, maxVal, -90, 90);
  int zAng = map(zRead, minVal, maxVal, -90, 90);
   x = RAD_TO_DEG * (atan2(-yAng, -zAng) + PI);
  y = RAD_TO_DEG * (atan2(-xAng, -zAng) + PI);
  z = RAD_TO_DEG * (atan2(-yAng, -xAng) + PI);
  x1=x;
  y1=y;
  z1=z;
    
    
    }
    
    void loop()
    {
    

  for (int i = 0; i < arraysize; i++)
  {

    pulse = pulseIn(pwPin, HIGH);
    rangevalue[i] = pulse / 58;
    delay(10);
  }

    isort(rangevalue, arraysize);
    modE = mode(rangevalue, arraysize);
       
    
      
    if(modE<50 && modE>0)
    {
    digitalWrite(vmRight,HIGH);
    digitalWrite(vmLeft,HIGH);
    delay(3000);
    digitalWrite(vmLeft,LOW);
    digitalWrite(vmRight,LOW);
        Serial.println("OBSTACLE");
        //Serial.println(modE);
      }
    
    
    if (Serial.available() > 0)
    {
      
                    incomingByte = Serial.readString();
                    if(incomingByte.equalsIgnoreCase("left"))
                    {
                      digitalWrite(vmLeft,HIGH);
                      delay(2000);
                      digitalWrite(vmLeft,LOW);
                      delay(1000);
                      digitalWrite(vmLeft,HIGH);
                      delay(1000);
                      digitalWrite(vmLeft,LOW);
                    }
                    else if(incomingByte.equalsIgnoreCase("right"))
                      {
                      digitalWrite(vmRight,HIGH);
                      delay(2000);
                      digitalWrite(vmRight,LOW);
                      delay(1000);
                      digitalWrite(vmRight,HIGH);
                      delay(1000);
                      digitalWrite(vmRight,LOW);
                    }
                    else 
                      {
                        Serial.println('1');
                       digitalWrite(vmRight,HIGH);
    digitalWrite(vmLeft,HIGH);
    digitalWrite(LED_BUILTIN,HIGH);
    delay(3000);
    digitalWrite(vmLeft,LOW);
    digitalWrite(vmRight,LOW);
    digitalWrite(LED_BUILTIN,LOW);
    delay(1000);
    digitalWrite(vmRight,HIGH);
    digitalWrite(vmLeft,HIGH);
    digitalWrite(LED_BUILTIN,HIGH);
    delay(3000);
    digitalWrite(vmLeft,LOW);
    digitalWrite(vmRight,LOW);
    digitalWrite(LED_BUILTIN,LOW);
    delay(1000);
    digitalWrite(vmRight,HIGH);
    digitalWrite(vmLeft,HIGH);
    digitalWrite(LED_BUILTIN,HIGH);
    delay(3000);
    digitalWrite(vmLeft,LOW);
    digitalWrite(vmRight,LOW);
    digitalWrite(LED_BUILTIN,LOW);
    delay(1000);
                    }
                   
                    
                    Serial.println(incomingByte);
            }
                //read the analog values from the accelerometer
      int xRead = analogRead(xPin);
      int yRead = analogRead(yPin);
      int zRead = analogRead(zPin);
    
      //convert read values to degrees -90 to 90 - Needed for atan2
      int xAng = map(xRead, minVal, maxVal, -90, 90);
      int yAng = map(yRead, minVal, maxVal, -90, 90);
      int zAng = map(zRead, minVal, maxVal, -90, 90);
    
      //Caculate 360deg values like so: atan2(-yAng, -zAng)
      //atan2 outputs the value of -π to π (radians)
      //We are then converting the radians to degrees
      x = RAD_TO_DEG * (atan2(-yAng, -zAng) + PI);
      y = RAD_TO_DEG * (atan2(-xAng, -zAng) + PI);
      z = RAD_TO_DEG * (atan2(-yAng, -xAng) + PI);
      
      if((x>(1.5*x1)&&y>(1.5*y1))||(y>(1.5*y1)&&z>(1.5*z1))||(z>(1.5*z1)&&x>(1.5*x1)))
      {
        Serial.println("FALL");
       }
      
     x1=x;
     y1=y;
     z1=z;
      
      
      delay(100);//just here to slow down the serial output - Easier to read
    }
    
    
    //Sorting function
      void isort(int *a, int n) {
        //  *a is an array pointer function
      
        for (int i = 1; i < n; ++i)
        {
          int j = a[i];
          int k;
          for (k = i - 1; (k >= 0) && (j < a[k]); k--)
          {
            a[k + 1] = a[k];
          }
          a[k + 1] = j;
        }
      }
      
      //Mode function, returning the mode or median.
      int mode(int *x, int n) {
        int i = 0;
        int count = 0;
        int maxCount = 0;
        int mode = 0;
        int bimodal;
        int prevCount = 0;
      
        while (i < (n - 1)) {
          prevCount = count;
          count = 0;
      
          while (x[i] == x[i + 1]) {
            count++;
            i++;
          }
      
          if (count > prevCount & count > maxCount) {
            mode = x[i];
            maxCount = count;
            bimodal = 0;
          }
          if (count == 0) {
            i++;
          }
          if (count == maxCount) { //If the dataset has 2 or more modes.
            bimodal = 1;
          }
          if (mode == 0 || bimodal == 1) { //Return the median if there is no mode.
            mode = x[(n / 2)];
          }
          return mode;
        }
      }
      
          
          

