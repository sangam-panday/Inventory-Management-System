#include <iostream>
#include <fstream>
#include <graphics.h>
#include <conio.h>
#include <string.h>
#include <time.h>
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

    rectangle(50, 220, 200, 270); 
    outtextxy(70, 235, "Exit");
    
    rectangle(250, 220, 400, 270);
    outtextxy(270, 235, "Search");
    
    rectangle(450, 220, 600, 270);
    outtextxy(455, 235, "Purchase History");

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
void ViewItems() {
    cleardevice();
    ifstream file("inventory.txt");
    if (!file) {
        cout << "Error opening the file.";
        delay(2000);
        return;
    }

    struct Item {
        int id, quantity, expdate;
        double price;
        char name[20], batchNo[20];
    };

    Item items[100]; // assume max 100 items
    int totalItems = 0;

    while (file >> items[totalItems].id >> items[totalItems].name 
                >> items[totalItems].quantity >> items[totalItems].price 
                >> items[totalItems].batchNo >> items[totalItems].expdate) {
        totalItems++;
    }
    file.close();

    int itemsPerPage = 14;
    int currentPage = 0;
    int totalPages = (totalItems + itemsPerPage - 1) / itemsPerPage;

    bool exitFlag = false;

    while (!exitFlag) {
        cleardevice();
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
        setcolor(WHITE);

        outtextxy(50, 50, "ID");
        outtextxy(100, 50, "Name");
        outtextxy(225, 50, "Quantity");
        outtextxy(320, 50, "Price");
        outtextxy(440, 50, "BatchNO");
        outtextxy(540, 50, "Exp date");
        line(0, 70, 600, 70);

        int startIdx = currentPage * itemsPerPage;
        int endIdx = (startIdx + itemsPerPage < totalItems) ? (startIdx + itemsPerPage) : totalItems;
        int down = 80;

        for (int i = startIdx; i < endIdx; ++i) {
            char idStr[10], quantityStr[10], priceStr[10], expiryDate[10];
            sprintf(idStr, "%d", items[i].id);
            sprintf(quantityStr, "%d", items[i].quantity);
            sprintf(priceStr, "%.2f", items[i].price);
            sprintf(expiryDate, "%d", items[i].expdate);

            outtextxy(50, down, idStr);
            outtextxy(100, down, items[i].name);
            outtextxy(225, down, quantityStr);
            outtextxy(320, down, priceStr);
            outtextxy(440, down, items[i].batchNo);
            outtextxy(540, down, expiryDate);

            down += 20;
        }

        // Draw Navigation Buttons
        if (currentPage > 0) {
            rectangle(100, 390, 200, 430); // Previous
            outtextxy(120, 400, "Previous");
        }
        if (currentPage < totalPages - 1) {
            rectangle(220, 390, 320, 430); // Next
            outtextxy(250, 400, "Next");
        }
        rectangle(350, 390, 450, 430); // Exit
        outtextxy(380, 400, "Exit");

        // Page info
        char pageInfo[50];
        sprintf(pageInfo, "Page %d of %d", currentPage + 1, totalPages);
        outtextxy(500, 400, pageInfo);

        // Wait for click
        int x = -1, y = -1;
        while (true) {
            if (ismouseclick(WM_LBUTTONDOWN)) {
                getmouseclick(WM_LBUTTONDOWN, x, y);

                // Now check where the click happened
                if (currentPage > 0 && isInside(x, y, 100, 390, 200, 430)) {
                    currentPage--;
                    break;
                }
                if (currentPage < totalPages - 1 && isInside(x, y, 220, 390, 320, 430)) {
                    currentPage++;
                    break;
                }
                if (isInside(x, y, 350, 390, 450, 430)) {
                    exitFlag = true;
                    break;
                }
            }
            delay(50); // to reduce CPU usage
        }
    }
}
void SavePurchaseHistory(const char* itemName, int quantity, double unitPrice, double totalPrice) {
    // Open the purchase history file in append mode
    ofstream historyFile("purchase_history.txt", ios::app);
    if (!historyFile) {
        cout << "Error opening the purchase history file.";
        delay(2000);
        return;
    }

    // Get the current time to record the purchase date
    time_t now = time(0);
    char* dt = ctime(&now);

    // Write purchase details to the file
    historyFile << "Item Name: " << itemName << endl;
    historyFile << "Quantity: " << quantity << endl;
    historyFile << "Unit Price: " << unitPrice << endl;
    historyFile << "Total Price: " << totalPrice << endl;
    historyFile << "Purchase Date: " << dt;
    historyFile << "----------------------------------------" << endl;

    historyFile.close();
}

void BuyItems() {
    cleardevice();
    ifstream file("inventory.txt");
    if (!file) {
        cout << "Error opening the file.";
        delay(2000);
        return;
    }

    char idStr[10], quantityStr[10];

    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
    setcolor(WHITE);
    outtextxy(50, 100, "Enter ID: ");
    getTextInput(120, 100, idStr, 10);
    outtextxy(50, 150, "Enter Quantity: ");
    getTextInput(200, 150, quantityStr, 10);

    int id = atoi(idStr);
    int quantity = atoi(quantityStr);

    ofstream temp("temp.txt");
    if (!temp) {
        cout << "Error opening the file.";
        delay(2000);
        return;
    }

    bool found = false;
    bool bought = false;
    int fid, fquantity, fexpdate;
    char fname[20], fbatchNo[20];
    double fprice;

    char billItem[20];
    int boughtQty = 0;
    double unitPrice = 0.0, totalPrice = 0.0;

    while (file >> fid >> fname >> fquantity >> fprice >> fbatchNo >> fexpdate) {
        if (fid == id) {
            found = true;
            if (fquantity >= quantity) {
                bought = true;
                boughtQty = quantity;
                unitPrice = fprice;
                totalPrice = boughtQty * unitPrice;
                strcpy(billItem, fname);

                fquantity -= quantity; // Update quantity after buying
            } else {
                outtextxy(270, 300, "Not enough quantity available.");
            }
        }
        if (fquantity != 0) {
            temp << fid << " " << fname << " " << fquantity << " " << fprice << " " << fbatchNo << " " << fexpdate << endl;
        }
    }
    file.close();
    temp.close();
    remove("inventory.txt");
    rename("temp.txt", "inventory.txt");

    if (!found) {
        outtextxy(270, 300, "Item with this ID not found.");
    } else if (bought) {
        // Print the bill
        cleardevice();
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
        setcolor(WHITE);

        outtextxy(200, 50, "Bill Receipt");
        line(150, 80, 450, 80);

        char text[50];

        sprintf(text, "Item Name: %s", billItem);
        outtextxy(100, 120, text);

        sprintf(text, "Quantity: %d", boughtQty);
        outtextxy(100, 170, text);

        sprintf(text, "Unit Price: %.2f", unitPrice);
        outtextxy(100, 220, text);

        sprintf(text, "Total Price: %.2f", totalPrice);
        outtextxy(100, 270, text);

        line(150, 310, 450, 310);
        outtextxy(200, 330, "Thank you for your purchase!");

        // Save purchase history
        SavePurchaseHistory(billItem, boughtQty, unitPrice, totalPrice);
    }

    // Exit Button
    rectangle(260, 390, 360, 430);
    outtextxy(280, 400, "Exit");
    int x, y;
    while (true) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x, y);
            if (isInside(x, y, 260, 390, 360, 430)) {
                outtextxy(200, 450, "Exiting...");
                delay(500);
                return;
            }
        }
        delay(50);
    }
}

void SearchItems() {
    cleardevice();
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
    setcolor(WHITE);

    char name[20];
    outtextxy(50, 100, "Enter Item Name to Search: ");
    getTextInput(350, 100, name, 20);

    ifstream file("inventory.txt");
    if (!file) {
        cout << "Error opening the file.";
        delay(2000);
        return;
    }

    // Array to store matching items
    struct Item {
        int id;
        char name[20];
        int quantity;
        double price;
        char batchNo[20];
        int expDate;
    } items[100];
    int count = 0;

    int id, quantity, expDate;
    char tempName[20], batchNo[20];
    double price;

    while (file >> id >> tempName >> quantity >> price >> batchNo >> expDate) {
        if (strcmpi(tempName, name) == 0) { // case-insensitive match
            items[count].id = id;
            strcpy(items[count].name, tempName);
            items[count].quantity = quantity;
            items[count].price = price;
            strcpy(items[count].batchNo, batchNo);
            items[count].expDate = expDate;
            count++;
        }
    }
    file.close();

    if (count == 0) {
        outtextxy(270, 300, "Item not found.");
        delay(2000);
        return;
    }

    int currentIndex = 0;

    while (true) {
        cleardevice();
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
        setcolor(WHITE);

        // Display the current item
        char text[100];

        sprintf(text, "ID: %d", items[currentIndex].id);
        outtextxy(100, 100, text);

        sprintf(text, "Name: %s", items[currentIndex].name);
        outtextxy(100, 150, text);

        sprintf(text, "Quantity: %d", items[currentIndex].quantity);
        outtextxy(100, 200, text);

        sprintf(text, "Price: %.2f", items[currentIndex].price);
        outtextxy(100, 250, text);

        sprintf(text, "Batch No: %s", items[currentIndex].batchNo);
        outtextxy(100, 300, text);

        sprintf(text, "Expiry Date: %d", items[currentIndex].expDate);
        outtextxy(100, 350, text);

        // Draw Buttons
        rectangle(150, 400, 250, 440); // Previous
        outtextxy(170, 410, "Previous");

        rectangle(300, 400, 400, 440); // Next
        outtextxy(330, 410, "Next");

        rectangle(450, 400, 550, 440); // Exit
        outtextxy(480, 410, "Exit");

        int x, y;
        while (true) {
            if (ismouseclick(WM_LBUTTONDOWN)) {
                getmouseclick(WM_LBUTTONDOWN, x, y);

                if (isInside(x, y, 150, 400, 250, 440)) { // Previous
                    if (currentIndex > 0)
                        currentIndex--;
                    break;
                } else if (isInside(x, y, 300, 400, 400, 440)) { // Next
                    if (currentIndex < count - 1)
                        currentIndex++;
                    break;
                } else if (isInside(x, y, 450, 400, 550, 440)) { // Exit
                    return;
                }
            }
            delay(50);
        }
    }
}
void ViewPurchaseHistory() {
    cleardevice();
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
    setcolor(WHITE);

    ifstream file("purchase_history.txt");
    if (!file) {
        outtextxy(250, 300, "No Purchase History Found!");
        delay(2000);
        return;
    }

    struct HistoryItem {
        int id;
        char name[20];
        int quantity;
        double price;
        char batchNo[20];
        int expDate;
    } items[100];
    int count = 0;

    int id, quantity, expDate;
    char name[20], batchNo[20];
    double price;

    while (file >> id >> name >> quantity >> price >> batchNo >> expDate) {
        items[count].id = id;
        strcpy(items[count].name, name);
        items[count].quantity = quantity;
        items[count].price = price;
        strcpy(items[count].batchNo, batchNo);
        items[count].expDate = expDate;
        count++;
    }
    file.close();

    if (count == 0) {
        outtextxy(270, 300, "No purchases yet.");
        delay(2000);
        return;
    }

    int currentIndex = 0;

    while (true) {
        cleardevice();
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
        setcolor(WHITE);

        char text[100];

        sprintf(text, "ID: %d", items[currentIndex].id);
        outtextxy(100, 100, text);

        sprintf(text, "Name: %s", items[currentIndex].name);
        outtextxy(100, 150, text);

        sprintf(text, "Quantity Bought: %d", items[currentIndex].quantity);
        outtextxy(100, 200, text);

        sprintf(text, "Price per Unit: %.2f", items[currentIndex].price);
        outtextxy(100, 250, text);

        sprintf(text, "Batch No: %s", items[currentIndex].batchNo);
        outtextxy(100, 300, text);

        sprintf(text, "Expiry Date: %d", items[currentIndex].expDate);
        outtextxy(100, 350, text);

        // Draw Buttons
        rectangle(150, 400, 250, 440); // Previous
        outtextxy(170, 410, "Previous");

        rectangle(300, 400, 400, 440); // Next
        outtextxy(330, 410, "Next");

        rectangle(450, 400, 550, 440); // Exit
        outtextxy(480, 410, "Exit");

        int x, y;
        while (true) {
            if (ismouseclick(WM_LBUTTONDOWN)) {
                getmouseclick(WM_LBUTTONDOWN, x, y);

                if (isInside(x, y, 150, 400, 250, 440)) { // Previous
                    if (currentIndex > 0)
                        currentIndex--;
                    break;
                } else if (isInside(x, y, 300, 400, 400, 440)) { // Next
                    if (currentIndex < count - 1)
                        currentIndex++;
                    break;
                } else if (isInside(x, y, 450, 400, 550, 440)) { // Exit
                    return;
                }
            }
            delay(50);
        }
    }
}

int main() {
    // Setup
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI"); 

    while (true) {
        cleardevice();
        drawUI();

        // 1. First, Decrease expiry dates
        ifstream file("inventory.txt");
        ofstream temp("temp.txt");

        int fid, fquantity, fexpdate;
        char fname[20], fbatchNo[20];
        double fprice;

        while (file >> fid >> fname >> fquantity >> fprice >> fbatchNo >> fexpdate) {
            if (fexpdate > 0) {
                temp << fid << " " << fname << " " << fquantity << " " << fprice << " " << fbatchNo << " " << fexpdate << endl;
            }
        }
        file.close();
        temp.close();
        remove("inventory.txt");
        rename("temp.txt", "inventory.txt");

        // 2. Now WAIT for user CLICK
        int x = -1, y = -1;
        while (true) {
            if (ismouseclick(WM_LBUTTONDOWN)) {
                getmouseclick(WM_LBUTTONDOWN, x, y);

                if (isInside(x, y, 50, 150, 200, 200)) {
                    AddItems();
                    break;  // after adding, redraw UI
                } 
                else if (isInside(x, y, 250, 150, 400, 200)) {
                    ViewItems();
                    break;
                } 
                else if (isInside(x, y, 450, 150, 600, 200)) {
                    BuyItems();
                    break;
                }
                else if (isInside(x, y, 250, 220, 400, 270)) {
                    SearchItems();
                    break;
                }
                else if (isInside(x, y, 50, 220, 200, 270)) {
                    // **EXIT BUTTON WORKS**
                    outtextxy(200, 320, "Exiting...");
                    delay(1000);
                    closegraph();
                    exit(0);
                }
                else if( isInside(x, y, 450, 220, 600, 270)){
                	ViewPurchaseHistory();
                	break;
				}
            }
            delay(50); // small delay to avoid CPU usage
        }
    }

    getch();
    closegraph();
}

