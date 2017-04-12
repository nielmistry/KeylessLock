void setup(){//Password = 0000
int p1 = 0; //hex code for it
int p2 = 0;//hex code for it
int p3 = 0; //hex code for it
int p4 = 0; //hex code for it

int input = a;
int input = b;
int input = c;
int input = c;

int incorrect = 0;
}
void loop(){
if(p1 == a && p2 == b && p3 == c && p4 == d){
	LCD.print("Correct! Welcome!")
	incorrect = 0;
}else{
	incorrect++;	
}
if(incorrect>2){
	while(1){
	LCD.print("Too many incorrect attempts. You have been locked out permanently")
	}
}
}