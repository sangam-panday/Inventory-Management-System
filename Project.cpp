#include <iostream>
#include <fstream>
#include <graphics.h>
#include <conio.h>
#include <string.h>
using namespace std;

void drawUI() {
	cleardevice();
    setfillstyle(SOLID_FILL, BLACK);
    floodfill(1, 1, WHITE);

    setcolor(WHITE);
    rectangle(50, 50, 550, 100); 
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
    outtextxy(150, 70, "Inventory Management");

    setcolor(CYAN);
    rectangle(50, 150, 200, 200); 
    outtextxy(70, 165, "Add Item");

    rectangle(250, 150, 400, 200); 
    outtextxy(270, 165, "View Items");

    rectangle(450, 150, 600, 200); 
    outtextxy(470, 165, "Buy Item");

    rectangle(100, 220, 250, 270); 
    outtextxy(140, 235, "Exit");
    
    rectangle(300, 220, 450, 270);
    outtextxy(340, 235, "Search");

    setcolor(WHITE);
    rectangle(50, 300, 600, 380); 
    outtextxy(200, 320, "Select an action...");
}
bool isInside(int x, int y, int x1, int y1, int x2, int y2) {
    return (x >= x1 && x <= x2 && y >= y1 && y <= y2);
}
void getTextInput(int x, int y, char input[], int maxLength) {
    int index = 0;
    char ch;
    input[0] = '\0'; 

    while (true) {
        ch = getch();  

        if (ch == 13) { 
            break;
        } 
        else if (ch == 8) {  
            if (index > 0) {
                index--;
                input[index] = '\0';

                setcolor(BLACK);
                rectangle(x, y, x + 200, y + 20); 
                setcolor(WHITE);
                outtextxy(x, y, input);
            }
        } 
        else if (index < maxLength - 1) { 
            input[index] = ch;
            index++;
            input[index] = '\0';
            outtextxy(x, y, input);
        }
    }
}
void AddItems(){
	cleardevice();
    
    char name[20], idStr[10], quantityStr[10], priceStr[10], batchNo[20], expiryDate[15];
    
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
    outtextxy(100, 100, "Enter Product ID: ");
    getTextInput(250, 100, idStr, 10);
    
    outtextxy(100, 150, "Enter Product Name: ");
    getTextInput(300, 150, name, 20);
    
    outtextxy(100, 200, "Enter Quantity: ");
    getTextInput(250, 200, quantityStr, 10);
    
    outtextxy(100, 250, "Enter Price: ");
    getTextInput(220, 250, priceStr, 10);
    
    outtextxy(100, 300, "Enter Batch No: ");
    getTextInput(250, 300, batchNo, 20);
    
    outtextxy(100, 350, "Enter Expiry Date (Days remaining): ");
    getTextInput(400, 350, expiryDate, 15);

	int expdate = atoi(expiryDate);
    int id = atoi(idStr);
    int quantity = atoi(quantityStr);
    double price = atof(priceStr);
	
	ifstream filef("inventory.txt");
	if(!filef){
		cout<<"Error to open the file.";
		delay(2000);
		return;
	}
	int fid, fquantity, fexpiryDate;
	char fname[20], fbatchNo[20];
	double fprice;
	int total = 0;
	
	while(filef >> fid >> fname >> fquantity >> fprice >> fbatchNo >> fexpiryDate){
		total += 1;
        if(fid == id){
        	outtextxy(200, 400,"Items with this id already exists");
        	outtextxy(200, 450, "Exiting...               ");
        	filef.close();
        	return;
		}
	}	
	filef.close();
	
	if(total<= 50)
	{
		ofstream file("inventory.txt", ios::app);
	    if (file.is_open()) {
	        file << id << " " << name << " " << quantity << " " << price << " " << batchNo << " " << expdate <<endl;
	        file.close();
	    } else {
	        outtextxy(100, 400, "Error: Unable to open file!");
	        delay(2000);
	        return;
    	}
	}
	else{
		outtextxy(200, 400,"Inventory Full");
    	outtextxy(200, 450, "Exiting...               ");
    	return;
	}
    
    rectangle(260, 390, 360, 430);
    outtextxy(280, 400, "Exit");
    int x, y;
    while (true) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x, y);
            if (isInside(x, y, 260, 390, 360, 430)) {
                outtextxy(200, 450, "Exiting...               ");
                return;
            }
        }
        delay(50);  
    }
}
void ViewItems(){
	cleardevice();
	ifstream file("inventory.txt");
	if(!file){
		cout<<"Error to open the file.";
		delay(2000);
		return;
	}
	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
	setcolor(WHITE);
	
	outtextxy(50, 50, "ID");
	outtextxy(100, 50, "Name");
	outtextxy(225, 50, "Quantity");
	outtextxy(320, 50, "Price");
	outtextxy(440, 50, "BatchNO");
	outtextxy(540, 50, "Exp date");
	line(0, 70, 600, 70);
	
	int down = 80;
	int id, quantity, expdate;
	double price;
	char name[20], batchNo[20];
	while(file >> id >> name >> quantity >> price >> batchNo >> expdate){
		
		char idStr[10], quantityStr[10], priceStr[10];
		char expiryDate[10];
		sprintf(expiryDate,"%d", expdate);
		sprintf(idStr,"%d",id);
		sprintf(quantityStr,"%d",quantity);
		sprintf(priceStr,"%.2f",price);
		
		outtextxy(50, down, idStr);
        outtextxy(100, down, name);
        outtextxy(225, down, quantityStr);
        outtextxy(320, down, priceStr);
        outtextxy(440, down, batchNo);
        outtextxy(540, down, expiryDate);
        down += 20;
	}
	rectangle(260, 390, 360, 430);
    outtextxy(280, 400, "Exit");
    int x, y;
    while (true) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x, y);
            if (isInside(x, y, 260, 390, 360, 430)) {
                outtextxy(200, 450, "Exiting...               ");
                return;
            }
        }
        delay(50);  
    }
}
void BuyItems(){
	cleardevice();
	ifstream file("inventory.txt");
	if(!file){
		cout<<"Error to open the file.";
		delay(2000);
		return;
	}
	
	char idStr[10], quantityStr[10];
	
	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
	setcolor(WHITE);
	outtextxy(50, 100, "Enter ID: ");
	getTextInput(120 , 100 ,idStr , 10);
	outtextxy(50, 150, "Enter Quantity: ");
	getTextInput(200, 150, quantityStr, 10);
	
	int id = atoi(idStr);
	int quantity = atoi(quantityStr);
	
	ofstream temp("temp.txt");
    if (!temp) {
        cout<<"Error to open the file.";
		delay(2000);
		return;
    }
	
	int total = 0;
	bool found = false;
	int fid, fquantity, fexpdate;
	char fname[20], fbatchNo[20];
	double fprice;
	while(file >> fid >> fname >> fquantity >> fprice >> fbatchNo >> fexpdate){
		total += 1;
        if(fid == id){
        	found = true;
			if(fquantity >= quantity){
				int bill = quantity * fprice;
				char billStr[20];
				sprintf(billStr, "The price is %d", bill);
				outtextxy(270, 300, billStr);
				fquantity -= quantity;
				outtextxy(270, 350, "Bought..");
			}
			else{
				outtextxy(270, 300,"Not enough quantity");
			}
		}
		if(fquantity != 0){
			temp<<fid<<" "<<fname<<" "<<fquantity<<" "<<fprice<<" "<<fbatchNo<<" "<<fexpdate<<endl;	
		}
	}
	if(!found){
		outtextxy(270, 300, "Item with this id not found.. ");
	}
	
	file.close();
	temp.close();
	remove("inventory.txt");
    rename("temp.txt", "inventory.txt");
    
	rectangle(260, 390, 360, 430);
    outtextxy(280, 400, "Exit");
    int x, y;
    while (true) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x, y);
            if (isInside(x, y, 260, 390, 360, 430)) {
                outtextxy(200, 450, "Exiting...               ");
                return;
            }
        }
        delay(50);  
    }
}
void SearchItems() {
    cleardevice();
    int down = 140;
    char item[20];

    outtextxy(50, 50, "Enter the name of the item: ");
    getTextInput(280, 50, item, 20);

    ifstream file("inventory.txt");
    if (!file) {
        outtextxy(200, 250, "Error opening the file!");
        delay(2000);
        return;
    }

    int id, quantity, expdate;
    char name[20], batchNo[20];
    double price;
    
    bool found = false;

    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
    setcolor(WHITE);
    outtextxy(50, 100, "ID");
    outtextxy(100, 100, "Name");
    outtextxy(225, 100, "Quantity");
    outtextxy(320, 100, "Price");
    outtextxy(440, 100, "BatchNO");
    outtextxy(540, 100, "Exp date");
    line(0, 125, 600, 125);

    while (file >> id >> name >> quantity >> price >> batchNo >> expdate) {
        if (strcasecmp(name, item) == 0) { // Case-insensitive comparison
            char idStr[10], quantityStr[10], priceStr[10], expiryDate[10];
            sprintf(idStr, "%d", id);
            sprintf(quantityStr, "%d", quantity);
            sprintf(priceStr, "%.2f", price);
            sprintf(expiryDate, "%d", expdate);

            outtextxy(50, down, idStr);
            outtextxy(100, down, name);
            outtextxy(225, down, quantityStr);
            outtextxy(320, down, priceStr);
            outtextxy(440, down, batchNo);
            outtextxy(540, down, expiryDate);
            down += 20;
            found = true;
        }
    }
    
    if (!found) {
        outtextxy(200, 300, "Item with this name not found");
    }
    
    file.close();

    // Exit Button
    rectangle(260, 390, 360, 430);
    outtextxy(280, 400, "Exit");

    int x, y;
    while (true) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x, y);
            if (isInside(x, y, 260, 390, 360, 430)) {
                outtextxy(200, 450, "Exiting...");
                return;
            }
        }
        delay(50);
    }
}

int main(){
	int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI"); 
    int x, y;
    while (true) {
    	cleardevice();
    	drawUI();
	    ////////////////////////////////////////////////
	    ofstream temp("temp.txt");
	    ifstream file("inventory.txt");
	    
		int fid, fquantity, fexpdate;
		char fname[20], fbatchNo[20];
		double fprice;
		while(file >> fid >> fname >> fquantity >> fprice >> fbatchNo >> fexpdate){
			if(fexpdate != 0){
				fexpdate -= 1;
				temp<<fid<<" "<<fname<<" "<<fquantity<<" "<<fprice<<" "<<fbatchNo<<" "<<fexpdate<<endl;
				if (ismouseclick(WM_LBUTTONDOWN)) {
	            	getmouseclick(WM_LBUTTONDOWN, x, y);
	            
		            if (isInside(x, y, 50, 150, 200, 200)) {
		                AddItems();
		            } 
		            else if (isInside(x, y, 250, 150, 400, 200)) {
		                ViewItems();
		            } 
		            else if (isInside(x, y, 450, 150, 600, 200)) {
		                BuyItems();
		            } 
		            else  if(isInside(x, y, 300, 220, 450, 270)){
		            	SearchItems();
					}
		            else if (isInside(x, y, 100, 220, 250, 270)) {
		                outtextxy(200, 320, "Exiting...               ");
		                closegraph();
		                exit(0);
		            }
	        	}	
			}
			else{
				char message[30];
				sprintf(message,"Item %s expired",fname);
				outtextxy(200, 320, message);
				delay(2000);
			}
			delay(1000);
		}
		file.close();
		temp.close();
		remove("inventory.txt");
	    rename("temp.txt", "inventory.txt");
    	///////////////////////////////////////////////////////////////
    }
    getch();
    closegraph();
}
