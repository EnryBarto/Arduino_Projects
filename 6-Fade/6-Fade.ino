#define led 9
#define led1 10
#define button 2

void setup(){
}
  
void loop(){
if(digitalRead(button)==HIGH){
   for(int i=0; i<255; i++){
  analogWrite(led, i);
  analogWrite(led1,i); 
  delay(5);
 }
 delay(200);
 for(int i=255; i>=0; i--){
  analogWrite(led, i);
  analogWrite(led1, i);
  delay(5);
 }
 delay(500);
} 
}
