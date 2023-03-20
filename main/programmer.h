void write_IAD(int D){
    digitalWrite( PEEL_IAD7 , D & (1<<7));
    digitalWrite( PEEL_IAD6 , D & (1<<6));
    digitalWrite( PEEL_IAD5 , D & (1<<5));
    digitalWrite( PEEL_IAD4 , D & (1<<4));
    digitalWrite( PEEL_IAD3 , D & (1<<3));
    digitalWrite( PEEL_IAD2 , D & (1<<2));
    digitalWrite( PEEL_IAD1 , D & (1<<1));
    digitalWrite( PEEL_IAD0 , D & (1<<0));
}
void write_TGA(int D){
    digitalWrite( PEEL_TGA4 , D & (1<<4));
    digitalWrite( PEEL_TGA3 , D & (1<<3));
    digitalWrite( PEEL_TGA2 , D & (1<<2));
    digitalWrite( PEEL_TGA1 , D & (1<<1));
    digitalWrite( PEEL_TGA0 , D & (1<<0));
}
void turn_off_all_pin(){
    pinMode(  PEEL_IAD7 , 0);
    pinMode(  PEEL_IAD6 , 0);
    pinMode(  PEEL_IAD5 , 0);
    pinMode(  PEEL_IAD4 , 0);
    pinMode(  PEEL_IAD3 , 0);
    pinMode(  PEEL_IAD2 , 0);
    pinMode(  PEEL_IAD1 , 0);
    pinMode(  PEEL_IAD0 , 0);
    pinMode(  PEEL_TGA4 , 0);
    pinMode(  PEEL_TGA3 , 0);
    pinMode(  PEEL_TGA2 , 0);
    pinMode(  PEEL_TGA1 , 0);
    pinMode(  PEEL_TGA0 , 0);
    pinMode(  MODE_A , 0);
    pinMode(  MODE_B , 0);
    pinMode( PCK   , 0);
    pinMode( ILL  , 0);
    pinMode( PVE   , 0);
    digitalWrite(PVE , 0);
   
}
void IDA_TGA_EN(){
    pinMode(  PEEL_IAD7 , 1);
    pinMode(  PEEL_IAD6 , 1);
    pinMode(  PEEL_IAD5 , 1);
    pinMode(  PEEL_IAD4 , 1);
    pinMode(  PEEL_IAD3 , 1);
    pinMode(  PEEL_IAD2 , 1);
    pinMode(  PEEL_IAD1 , 1);
    pinMode(  PEEL_IAD0 , 1);
    pinMode(  PEEL_TGA4 , 1);
    pinMode(  PEEL_TGA3 , 1);
    pinMode(  PEEL_TGA2 , 1);
    pinMode(  PEEL_TGA1 , 1);
    pinMode(  PEEL_TGA0 , 1);
}
void IDA_DIS(){
    pinMode(  PEEL_IAD7 , 0);
    pinMode(  PEEL_IAD6 , 0);
    pinMode(  PEEL_IAD5 , 0);
    pinMode(  PEEL_IAD4 , 0);
    pinMode(  PEEL_IAD3 , 0);
    pinMode(  PEEL_IAD2 , 0);
    pinMode(  PEEL_IAD1 , 0);
    pinMode(  PEEL_IAD0 , 0);
}

void PEEL_erase(){
    //init
    digitalWrite(PVE  , 0);
    digitalWrite(PCK  , 0);
    digitalWrite(ILL , 0);
    
    pinMode( PVE   , 1);
    pinMode( PCK   , 1);
    pinMode( ILL  , 1);
    pinMode( MODE_A   , 1);
    pinMode( MODE_B   , 1);
   
    //erase mode
    digitalWrite(MODE_A , 0);
    digitalWrite(MODE_B , 0);
    delay(10);
    //erase all (100 ms)
    digitalWrite(PVE  , 1);
    delay(100);
    digitalWrite(PCK  , 1);
    delay(100);
    digitalWrite(PCK  , 0);
    delay(1);
    digitalWrite( PVE , 0);

    delay(10);

    //program mode
    digitalWrite(MODE_A , 0);
    digitalWrite(MODE_B , 1);
    delay(10);
    //pregram all
    digitalWrite(PVE , 1);
    delay(1);
    digitalWrite(PCK , 1);
    delay(100);
    digitalWrite(PCK  , 0);
    delay(1);
    digitalWrite(PVE , 0);

    delay(10);
    
    //erase mode
    digitalWrite(MODE_A , 0);
    digitalWrite(MODE_B , 0);
    delay(1);
    //erase all (20 ms)
    digitalWrite(PVE  , 1);
    delay(100);
    digitalWrite(PCK  , 1);
    delay(20);
    digitalWrite(PCK  , 0);
    delay(1);

    turn_off_all_pin();
}

void PEEL_program(int MC_cfg){
    //JED[][6]
    //init
    digitalWrite(PVE  , 0);
    digitalWrite(PCK  , 0);
    digitalWrite(ILL , 0);
    
    pinMode( PVE   , 1);
    pinMode( PCK   , 1);
    pinMode( ILL  , 1);
    pinMode( MODE_A   , 1);
    pinMode( MODE_B   , 1);
    
    //program mode
    digitalWrite(MODE_A , 1);
    digitalWrite(MODE_B , 1);

    digitalWrite(PVE , 1);
    delay(100);

    IDA_TGA_EN();
    for(int j=0 ; j<=16 ;j++){
        write_TGA(j);
        delayMicroseconds(10);
        for(int i=0 ; i<44 ; i++){
            write_IAD(i);//line num
            delayMicroseconds(5);
            digitalWrite(ILL , 1);

            delayMicroseconds(5);
            
            //write_IAD();//fuse data
            digitalWrite(PEEL_IAD0 , JED[j*8+0][i/8] & (1<<(7-i%8)) ); 
            digitalWrite(PEEL_IAD1 , JED[j*8+1][i/8] & (1<<(7-i%8)) ); 
            digitalWrite(PEEL_IAD2 , JED[j*8+2][i/8] & (1<<(7-i%8)) ); 
            digitalWrite(PEEL_IAD3 , JED[j*8+3][i/8] & (1<<(7-i%8)) ); 
            digitalWrite(PEEL_IAD4 , JED[j*8+4][i/8] & (1<<(7-i%8)) ); 
            digitalWrite(PEEL_IAD5 , JED[j*8+5][i/8] & (1<<(7-i%8)) ); 
            digitalWrite(PEEL_IAD6 , JED[j*8+6][i/8] & (1<<(7-i%8)) ); 
            digitalWrite(PEEL_IAD7 , JED[j*8+7][i/8] & (1<<(7-i%8)) ); 
            
            delayMicroseconds(5);
            
            digitalWrite(PCK , 1);
            delay(2);
            digitalWrite(PCK , 0);
            
            delayMicroseconds(5);
            digitalWrite(ILL , 0);
            
            delayMicroseconds(5);
        }
    }
    delay(100);
    for(int i=0 ; i<10 ; i++){
        write_TGA(i+1);
        delayMicroseconds(10);

        write_IAD(44);//line num
        delayMicroseconds(5);
        digitalWrite(ILL , 1);
        delayMicroseconds(5);
            //write_IAD();//fuse data
        digitalWrite(PEEL_IAD0 , MC_cfg & (1<<0) ); 
        digitalWrite(PEEL_IAD1 , MC_cfg & (1<<1) ); 
        digitalWrite(PEEL_IAD2 , MC_cfg & (1<<2) ); 
        digitalWrite(PEEL_IAD3 , MC_cfg & (1<<3) ); 
        digitalWrite(PEEL_IAD4 , MC_cfg & (1<<4) ); 
        digitalWrite(PEEL_IAD5 , MC_cfg & (1<<5) ); 
        digitalWrite(PEEL_IAD6 , MC_cfg & (1<<6) ); 
        digitalWrite(PEEL_IAD7 , MC_cfg & (1<<7) ); 
        delayMicroseconds(5);
        
        digitalWrite(PCK , 1);
        delay(2);
        digitalWrite(PCK , 0);
        delayMicroseconds(5);
        digitalWrite(ILL , 0);
        delayMicroseconds(5);
    }
    delay(1);
    turn_off_all_pin();
    
}

bool PEEL_verify(int MC_cfg){
    digitalWrite(PVE  , 0);
    digitalWrite(PCK  , 0);
    digitalWrite(ILL , 0);
    
    pinMode( PVE   , 1);
    pinMode( PCK   , 1);
    pinMode( ILL  , 1);
    pinMode( MODE_A   , 1);
    pinMode( MODE_B   , 1);
    
    //verify mode
    digitalWrite(MODE_A , 1);
    digitalWrite(MODE_B , 0);

    digitalWrite(PVE , 1);
    delay(100);

    IDA_TGA_EN();
    for(int j=0 ; j<=16 ;j++){
        write_TGA(j);
        delayMicroseconds(10);
        for(int i=0 ; i<44 ; i++){
            write_IAD(i);//line num
            delayMicroseconds(5);
            digitalWrite(ILL , 1);
            delayMicroseconds(5);
            IDA_DIS();
            digitalWrite(PCK , 1);
            delayMicroseconds(5);
            if(j!=16){
                if(digitalRead( PEEL_IAD0)!=bool(JED[j*8+0][i/8] & (1<<(7-i%8))) ){turn_off_all_pin(); return 0;}
                if(digitalRead( PEEL_IAD1)!=bool(JED[j*8+1][i/8] & (1<<(7-i%8))) ){turn_off_all_pin(); return 0;}
                if(digitalRead( PEEL_IAD2)!=bool(JED[j*8+2][i/8] & (1<<(7-i%8))) ){turn_off_all_pin(); return 0;}
                if(digitalRead( PEEL_IAD3)!=bool(JED[j*8+3][i/8] & (1<<(7-i%8))) ){turn_off_all_pin(); return 0;}
                if(digitalRead( PEEL_IAD4)!=bool(JED[j*8+4][i/8] & (1<<(7-i%8))) ){turn_off_all_pin(); return 0;}
                if(digitalRead( PEEL_IAD5)!=bool(JED[j*8+5][i/8] & (1<<(7-i%8))) ){turn_off_all_pin(); return 0;}
                if(digitalRead( PEEL_IAD6)!=bool(JED[j*8+6][i/8] & (1<<(7-i%8))) ){turn_off_all_pin(); return 0;}
                if(digitalRead( PEEL_IAD7)!=bool(JED[j*8+7][i/8] & (1<<(7-i%8))) ){turn_off_all_pin(); return 0;}
            }
            else{
                if(digitalRead( PEEL_IAD0)!=bool(JED[j*8+0][i/8] & (1<<(7-i%8))) ){turn_off_all_pin();return 0;}
                if(digitalRead( PEEL_IAD1)!=bool(JED[j*8+1][i/8] & (1<<(7-i%8))) ){turn_off_all_pin();return 0;}
                if(digitalRead( PEEL_IAD2)!=bool(JED[j*8+2][i/8] & (1<<(7-i%8))) ){turn_off_all_pin();return 0;}
                if(digitalRead( PEEL_IAD3)!=bool(JED[j*8+3][i/8] & (1<<(7-i%8))) ){turn_off_all_pin();return 0;}
            }
            digitalWrite(PCK , 0);
            delayMicroseconds(5);
            digitalWrite(ILL , 0);
            delayMicroseconds(5);
            IDA_TGA_EN();
        }
    }
    delay(20);
    
    for(int i=0 ; i<10 ; i++){
        write_TGA(i+1);
        write_IAD(44);//line num
        delayMicroseconds(5);
        digitalWrite(ILL , 1);
        delayMicroseconds(5);
        IDA_DIS();
        digitalWrite(PCK , 1);
        delayMicroseconds(5);
        if( digitalRead(PEEL_IAD0) != bool(MC_cfg & (1<<0)) ){turn_off_all_pin();return 0;}
        //if( digitalRead(PEEL_IAD1) != bool(MC_cfg & (1<<1)) ){turn_off_all_pin();return 0;}
        if( digitalRead(PEEL_IAD2) != bool(MC_cfg & (1<<2)) ){turn_off_all_pin();return 0;}
        //if( digitalRead(PEEL_IAD3) != bool(MC_cfg & (1<<3)) ){turn_off_all_pin();return 0;}
        if( digitalRead(PEEL_IAD4) != bool(MC_cfg & (1<<4)) ){turn_off_all_pin();return 0;}
        //if( digitalRead(PEEL_IAD5) != bool(MC_cfg & (1<<5)) ){turn_off_all_pin();return 0;}
        if( digitalRead(PEEL_IAD6) != bool(MC_cfg & (1<<6)) ){turn_off_all_pin();return 0;}
        //if( digitalRead(PEEL_IAD7) != bool(MC_cfg & (1<<7)) ){turn_off_all_pin();return 0;}
        digitalWrite(PCK , 0);
        delayMicroseconds(5);
        digitalWrite(ILL , 0);
        delayMicroseconds(5);
    }
    delay(1);
    turn_off_all_pin();
    return 1;
}




/*
void setup(){
    int cfg = 0b00000001;
    Serial.begin(250000);
    Serial.println("ready");
    while(digitalRead(A12)){}
    PEEL_erase();
    delay(100);
    PEEL_program(cfg);
    Serial.println("finish");
    Serial.println(verify(cfg));
}

void loop(){

}
*/