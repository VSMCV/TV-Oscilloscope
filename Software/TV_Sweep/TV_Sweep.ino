#define signal_pin A3
#define sawtooth_pin A4
#define square_pin 9

#define TRIGGER_LEVEL 400
#define TRIGGER_RESOLUTION 3
#define RETURN_LEVEL 510

int signal_level, sawtooth_level, past_signal_level = 0;
int mode = 0; //trigger on rising edge
int edge = 0;

void setup()
{
  pinMode(signal_pin, INPUT);
  pinMode(sawtooth_pin, INPUT);
  pinMode(square_pin, OUTPUT);
}

void loop()
{ 
  signal_level = analogRead(signal_pin);
  
  switch(mode)
  { 
    case 0:

      if(abs(signal_level - TRIGGER_LEVEL) < TRIGGER_RESOLUTION)
      {
        if(edge == 0)
	{
	  if(signal_level > past_signal_level)
	  {
	    digitalWrite(square_pin, HIGH);

	    mode = 1;
	  }
	}
	else
        {
	  if(signal_level < past_signal_level)
	  {
	    digitalWrite(square_pin, HIGH);

	    mode = 1;
	  }
	}
      }

      break;

    case 1:

      sawtooth_level = analogRead(sawtooth_pin);

      if(sawtooth_level > RETURN_LEVEL)
      {
        digitalWrite(square_pin, LOW);
        
        delayMicroseconds(300);
        
	      mode = 0;
      }
      
      break;
  }
  
  past_signal_level = signal_level;
}
