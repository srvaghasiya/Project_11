char input = 0;
void setup()
{
  Serial.begin(115200);
}

void loop()
{
  if(Serial.available() > 0)
  {
    input = Serial.read();
    if(input == 's')
    { 
       (void)count30fun();
    }
  }
}

int count30fun()
{
  int count=0;
  int count0=0;
  int i;
  int a0;
  for(i=0;i<300;i++)
  {
    a0=analogRead(A0);
    if(a0 > 30)
    {
      count++;
    }
    else if(a0 == 0)
    {
      count0++;
    }
    delay(100);
  }

  if(count > 30)
  {
    Serial.println('l');
  }
  else if(count0 > 280)
  {
    Serial.println('n');
  }
  else
  {
    Serial.println('t');
  }
  return count;
}
